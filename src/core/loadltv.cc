#include <array>
#include <vector>
#include <bit>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <clasp/core/core.h>
#include <clasp/core/bformat.h>
#include <clasp/core/ql.h>            // ql::list
#include <clasp/core/primitives.h>    // cl__fdefinition
#include <clasp/core/bytecode.h>      // modules, functions
#include <clasp/core/lispStream.h>    // I/O
#include <clasp/core/hashTable.h>     // making hash tables
#include <clasp/core/bignum.h>        // making bignums
#include <clasp/core/package.h>       // making packages
#include <clasp/core/pathname.h>      // making pathnames
#include <clasp/core/unixfsys.h>      // cl__truename
#include <clasp/llvmo/llvmoPackage.h> // cmp__compile_trampoline

// FIXME: Move these to the generated file thingie
#define LTV_OP_NIL 65
#define LTV_OP_T 66
#define LTV_OP_CONS 69
#define LTV_OP_RPLACA 70
#define LTV_OP_RPLACD 71
#define LTV_OP_MAKE_ARRAY 74
#define LTV_OP_SRMA 75
#define LTV_OP_HASHT 76
#define LTV_OP_SHASH 77
#define LTV_OP_SB64 78
#define LTV_OP_PACKAGE 79
#define LTV_OP_BIGNUM 80
#define LTV_OP_FLOAT 90
#define LTV_OP_DOUBLE 91
#define LTV_OP_RATIO 67
#define LTV_OP_COMPLEX 68
#define LTV_OP_SYMBOL 81
#define LTV_OP_INTERN 82
#define LTV_OP_CHARACTER 83
#define LTV_OP_PATHNAME 85
#define LTV_OP_BCFUNC 87
#define LTV_OP_BCMOD 88
#define LTV_OP_SLITS 89
#define LTV_OP_FDEF 95
#define LTV_OP_CREATE 93
#define LTV_OP_INIT 94
#define LTV_OP_CLASS 98
#define LTV_OP_INIT_OBJECT_ARRAY 99
#define LTV_OP_ATTR 255

namespace core {

#define BC_HEADER_SIZE 16

#define BC_VERSION_MAJOR 0
#define BC_VERSION_MINOR 9

// versions are std::arrays so that we can compare them.
typedef std::array<uint16_t, 2> BCVersion;

const BCVersion min_version = {BC_VERSION_MAJOR, BC_VERSION_MINOR};
const BCVersion max_version = {BC_VERSION_MAJOR, BC_VERSION_MINOR};

static uint64_t ltv_header_decode(uint8_t *header) {
  if (header[0] != FASL_MAGIC_NUMBER_0 || header[1] != FASL_MAGIC_NUMBER_1 || header[2] != FASL_MAGIC_NUMBER_2 || header[3] != FASL_MAGIC_NUMBER_3)
    SIMPLE_ERROR("Invalid FASL: incorrect magic number 0x%" PRIx8 "%" PRIx8 "%" PRIx8 "%" PRIx8, header[0], header[1], header[2],
                 header[3]);
  // C++ guarantees sequencing in the aggregate initialization.
  BCVersion version = {header[4] << 8 | header[5], header[6] << 8 | header[7]};
  if ((version < min_version) || (version > max_version))
    // FIXME: Condition classes
    SIMPLE_ERROR("FASL version %" PRIu16 ".%" PRIu16 " is out of range of this loader", version[0], version[1]);
  return ((uint64_t)header[8] << 56) | ((uint64_t)header[9] << 48) | ((uint64_t)header[10] << 40) | ((uint64_t)header[11] << 32) |
         ((uint64_t)header[12] << 24) | ((uint64_t)header[13] << 16) | ((uint64_t)header[14] << 8) | ((uint64_t)header[15] << 0);
}

static void ltv_header_encode(uint8_t *header, uint64_t instruction_count) {
  header[0] = FASL_MAGIC_NUMBER_0;
  header[1] = FASL_MAGIC_NUMBER_1;
  header[2] = FASL_MAGIC_NUMBER_2;
  header[3] = FASL_MAGIC_NUMBER_3;
  header[4] = (uint8_t)(BC_VERSION_MAJOR >> 8);
  header[5] = (uint8_t)(BC_VERSION_MAJOR >> 0);
  header[6] = (uint8_t)(BC_VERSION_MINOR >> 8);
  header[7] = (uint8_t)(BC_VERSION_MINOR >> 0);
  header[8] = (uint8_t)(instruction_count >> 56);
  header[9] = (uint8_t)(instruction_count >> 48);
  header[10] = (uint8_t)(instruction_count >> 40);
  header[11] = (uint8_t)(instruction_count >> 32);
  header[12] = (uint8_t)(instruction_count >> 24);
  header[13] = (uint8_t)(instruction_count >> 16);
  header[14] = (uint8_t)(instruction_count >> 8);
  header[15] = (uint8_t)(instruction_count >> 0);
}

struct loadltv {
  Stream_sp _stream;
  gctools::Vec0<T_sp> _literals;
  uint8_t _index_bytes;

  loadltv(Stream_sp stream) : _stream(stream), _index_bytes(1) {}

  inline uint8_t read_u8() { return clasp_read_byte(_stream).unsafe_fixnum(); }

  inline int8_t read_s8() {
    uint8_t byte = read_u8();
    union {
      uint8_t u;
      int8_t i;
    } converter;
    converter.u = byte;
    return converter.i;
  }

  inline uint16_t read_u16() {
    // Ideally we'd want to use something like read-sequence here.
    uint16_t high = read_u8();
    uint16_t low = read_u8();
    return (high << 8) | low;
  }

  inline int16_t read_s16() {
    uint16_t hw = read_u16();
    union {
      uint16_t u;
      int16_t i;
    } converter;
    converter.u = hw;
    return converter.i;
  }

  inline uint32_t read_u32() {
    uint32_t b0 = read_u8();
    uint32_t b1 = read_u8();
    uint32_t b2 = read_u8();
    uint32_t b3 = read_u8();
    return (b0 << 24) | (b1 << 16) | (b2 << 8) | (b3 << 0);
  }

  inline int32_t read_s32() {
    uint32_t w = read_u32();
    union {
      uint32_t u;
      int32_t i;
    } converter;
    converter.u = w;
    return converter.i;
  }

  inline uint64_t read_u64() {
    uint64_t b0 = read_u8();
    uint64_t b1 = read_u8();
    uint64_t b2 = read_u8();
    uint64_t b3 = read_u8();
    uint64_t b4 = read_u8();
    uint64_t b5 = read_u8();
    uint64_t b6 = read_u8();
    uint64_t b7 = read_u8();
    return (b0 << 56) | (b1 << 48) | (b2 << 40) | (b3 << 32) | (b4 << 24) | (b5 << 16) | (b6 << 8) | (b7 << 0);
  }

  inline int64_t read_s64() {
    uint64_t dw = read_u64();
    union {
      uint64_t u;
      int64_t i;
    } converter;
    converter.u = dw;
    return converter.i;
  }

  inline float read_f32() {
    union {
      float f;
      uint32_t i;
    } converter;
    converter.i = read_u32();
    return converter.f;
  }

  inline double read_f64() {
    union {
      double d;
      uint64_t i;
    } converter;
    converter.i = read_u64();
    return converter.d;
  }

  inline uint8_t read_opcode() { return read_u8(); }

  inline size_t read_index() {
    switch (_index_bytes) {
    case 1:
      return read_u8();
    case 2:
      return read_u16();
    case 4:
      return read_u32();
    case 8:
      return read_u64();
    default:
      UNREACHABLE();
    }
  }

  void check_initialization() {
    // bool vectors are apparently stupid and weird so using std algorithms
    // may not work. so we do something stupid.
    for (size_t i = 0; i < _literals.size(); ++i)
      if (_literals[i].unboundp()) // not initialized
        SIMPLE_ERROR("Invalid FASL: did not initialize object #%zu", i);
  }

  T_sp get_ltv(size_t index) {
    if (index >= _literals.size())
      SIMPLE_ERROR("Invalid FASL: requested object #%zu, which is out of range", index);
    if (_literals[index].unboundp())
      SIMPLE_ERROR("Invalid FASL: requested object #%zu, which has not yet been initialized", index);
    return _literals[index];
  }

  void set_ltv(T_sp value, size_t index) {
    if (index >= _literals.size())
      SIMPLE_ERROR("Invalid FASL: Tried to set object #%zu, which is out of range", index);
    if (!_literals[index].unboundp())
      SIMPLE_ERROR("Invalid FASL: Tried to set object #%zu, which has already been initialized", index);
    _literals[index] = value;
  }

  void op_nil() { set_ltv(nil<T_O>(), read_index()); }

  void op_t() { set_ltv(cl::_sym_T_O, read_index()); }

  void op_cons() { set_ltv(Cons_O::create(nil<T_O>(), nil<T_O>()), read_index()); }

  void op_rplaca() {
    Cons_sp c = gc::As<Cons_sp>(get_ltv(read_index()));
    c->rplaca(get_ltv(read_index()));
  }

  void op_rplacd() {
    Cons_sp c = gc::As<Cons_sp>(get_ltv(read_index()));
    c->rplacd(get_ltv(read_index()));
  }

  enum class UAETCode : uint8_t {
    nil = 0b00000000,
    base_char = 0b10000000,
    character = 0b11000000,
    short_float = 0b10100000,
    single_float = 0b00100000,
    double_float = 0b01100000,
    long_float = 0b11100000,
    complex_short = 0b10110000,
    complex_single = 0b00110000,
    complex_double = 0b01110000,
    complex_long = 0b11110000,
    bit = 0b00000001,
    ub2 = 0b00000010,
    ub4 = 0b00000011,
    ub8 = 0b00000100,
    ub16 = 0b00000101,
    ub32 = 0b00000110,
    ub64 = 0b00000111,
    sb8 = 0b10000100,
    sb16 = 0b10000101,
    sb32 = 0b10000110,
    sb64 = 0b10000111,
    t = 0b11111111
  };

  T_sp decode_uaet(uint8_t code) {
    switch (UAETCode{code}) {
    case UAETCode::nil:
      return nil<T_O>();
    case UAETCode::base_char:
      return cl::_sym_base_char;
    case UAETCode::character:
      return cl::_sym_character;
    // case UAETCode::short_float: return cl::_sym_ShortFloat_O;
    case UAETCode::single_float:
      return cl::_sym_single_float;
    case UAETCode::double_float:
      return cl::_sym_DoubleFloat_O;
    // case UAETCode::long_float: return cl::_sym_LongFloat_O;
    // case UAETCode::complex_short:
    // case UAETCode::complex_single:
    // case UAETCode::complex_double:
    // case UAETCode::complex_long:
    case UAETCode::bit:
      return cl::_sym_bit;
    case UAETCode::ub2:
      return ext::_sym_byte2;
    case UAETCode::ub4:
      return ext::_sym_byte4;
    case UAETCode::ub8:
      return ext::_sym_byte8;
    case UAETCode::ub16:
      return ext::_sym_byte16;
    case UAETCode::ub32:
      return ext::_sym_byte32;
    case UAETCode::ub64:
      return ext::_sym_byte64;
    case UAETCode::sb8:
      return ext::_sym_integer8;
    case UAETCode::sb16:
      return ext::_sym_integer16;
    case UAETCode::sb32:
      return ext::_sym_integer32;
    case UAETCode::sb64:
      return ext::_sym_integer64;
    case UAETCode::t:
      return cl::_sym_T_O;
    default:
      SIMPLE_ERROR("Invalid FASL: Unknown UAET code %" PRIx8, code);
    }
  }

  void fill_sub_byte(Array_sp array, size_t total_size, size_t nbits) {
    // FIXME: Very inefficient.
    // In a best case scenario we can move in entire bit_array_words at a time,
    // probably?
    size_t perbyte = 8 / nbits;
    size_t full_bytes = total_size / perbyte;
    size_t remainder = total_size % perbyte;
    uint8_t mask = (1 << nbits) - 1;
    for (size_t byte_index = 0; byte_index < full_bytes; ++byte_index) {
      size_t index = perbyte * byte_index;
      uint8_t byte = read_u8();
      for (size_t j = 0; j < perbyte; ++j) {
        size_t bit_index = nbits * (perbyte - j - 1);
        uint8_t bits = (byte & (mask << bit_index)) >> bit_index;
        array->rowMajorAset(index + j, clasp_make_fixnum(bits));
      }
    }
    // write remainder
    if (remainder != 0) {
      size_t index = perbyte * full_bytes;
      uint8_t byte = read_u8(); // should this be read when remainder = 0?
      for (size_t j = 0; j < remainder; ++j) {
        size_t bit_index = nbits * (perbyte - j - 1);
        uint8_t bits = (byte & (mask << bit_index)) >> bit_index;
        array->rowMajorAset(index + j, clasp_make_fixnum(bits));
      }
    }
  }

  void fill_array(Array_sp array, size_t total_size, uint8_t packing) {
    // FIXME: Inefficient.
    // Really we ought to be able to read(2) stuff in directly sometimes.
    // And can we do the simple form here for multidimensional arrays?
#define READ_ARRAY(BaseType, EXPR, EXTEXPR)                                                                                        \
  if (gc::IsA<BaseType>(array)) {                                                                                                  \
    BaseType sv = gc::As_unsafe<BaseType>(array);                                                                                  \
    for (size_t i = 0; i < total_size; ++i)                                                                                        \
      (*sv)[i] = (EXPR);                                                                                                           \
  } else {                                                                                                                         \
    for (size_t i = 0; i < total_size; ++i)                                                                                        \
      array->rowMajorAset(i, (EXTEXPR));                                                                                           \
  }
    switch (UAETCode{packing}) {
    case UAETCode::nil:
      break;
    case UAETCode::base_char:
      READ_ARRAY(SimpleBaseString_sp, read_u8(), clasp_make_character(read_u8()));
      break;
    case UAETCode::character:
      READ_ARRAY(SimpleCharacterString_sp, read_u32(), clasp_make_character(read_u32()));
      break;
    case UAETCode::single_float:
      READ_ARRAY(SimpleVector_float_sp, read_f32(), clasp_make_single_float(read_f32()));
      break;
    case UAETCode::double_float:
      READ_ARRAY(SimpleVector_double_sp, read_f64(), clasp_make_double_float(read_f64()));
      break;
    case UAETCode::bit:
      fill_sub_byte(array, total_size, 1);
      break;
    case UAETCode::ub2:
      fill_sub_byte(array, total_size, 2);
      break;
    case UAETCode::ub4:
      fill_sub_byte(array, total_size, 4);
      break;
    case UAETCode::ub8:
      READ_ARRAY(SimpleVector_byte8_t_sp, read_u8(), clasp_make_fixnum(read_u8()));
      break;
    case UAETCode::ub16:
      READ_ARRAY(SimpleVector_byte16_t_sp, read_u16(), clasp_make_fixnum(read_u16()));
      break;
    case UAETCode::ub32:
      READ_ARRAY(SimpleVector_byte32_t_sp, read_u32(), clasp_make_fixnum(read_u32()));
      break;
    case UAETCode::ub64:
      READ_ARRAY(SimpleVector_byte64_t_sp, read_u64(), Integer_O::create(read_u64()));
      break;
    case UAETCode::sb8:
      READ_ARRAY(SimpleVector_int8_t_sp, read_s8(), clasp_make_fixnum(read_s8()));
      break;
    case UAETCode::sb16:
      READ_ARRAY(SimpleVector_int16_t_sp, read_s16(), clasp_make_fixnum(read_s16()));
      break;
    case UAETCode::sb32:
      READ_ARRAY(SimpleVector_int32_t_sp, read_s32(), clasp_make_fixnum(read_s32()));
      break;
    case UAETCode::sb64:
      READ_ARRAY(SimpleVector_int64_t_sp, read_s64(), Integer_O::create(read_s64()));
      break;
    case UAETCode::t:
      break; // handled by setf row-major-aref
    default:
      SIMPLE_ERROR("Not implemented: packing code %" PRIx8, packing);
    }
#undef READ_ARRAY
  }

  void op_array() {
    // FIXME: This is pretty inefficient, including consing way more than it
    // ought to. We don't really have C++ equivalents for make-array.
    size_t index = read_index();
    uint8_t uaet_code = read_u8();
    T_sp uaet = decode_uaet(uaet_code);
    uint8_t packing_code = read_u8();
    uint8_t rank = read_u8();
    size_t total = 1;
    // FIXME: Shouldn't cons a list, but we don't have a lower level maker
    // that can handle all the different element types.
    ql::list dims;
    for (size_t i = 0; i < rank; ++i) {
      uint16_t dim = read_u16();
      dims << clasp_make_fixnum(dim);
      total *= dim;
    }
    Array_sp arr =
        (rank == 1)
            // very unsure about the cast, but this is an ambiguous ?: otherwise
            ? gc::As<Array_sp>(
                  core__make_vector(uaet, total, false, nil<T_O>(), nil<T_O>(), clasp_make_fixnum(0), nil<T_O>(), false))
            : gc::As<Array_sp>(core__make_mdarray(dims.cons(), uaet, false, nil<T_O>(), clasp_make_fixnum(0), nil<T_O>(), false));
    set_ltv(arr, index);
    fill_array(arr, total, packing_code);
  }

  void op_srma() {
    Array_sp arr = gc::As<Array_sp>(get_ltv(read_index()));
    size_t aindex = read_u16();
    T_sp value = get_ltv(read_index());
    arr->rowMajorAset(aindex, value);
  }

  void op_hasht() {
    size_t index = read_index();
    uint8_t testcode = read_u8();
    uint16_t count = read_u16();
    // Resolve test
    T_sp test = nil<T_O>();
    switch (testcode) {
    case 0b00:
      test = cl::_sym_eq;
      break;
    case 0b01:
      test = cl::_sym_eql;
      break;
    case 0b10:
      test = cl::_sym_equal;
      break;
    case 0b11:
      test = cl::_sym_equalp;
      break;
    default:
      SIMPLE_ERROR("Unknown hash table test code %" PRIx8, testcode);
    }
    set_ltv(cl__make_hash_table(test, clasp_make_fixnum(count), clasp_make_single_float(2.0), clasp_make_single_float(0.7),
                                nil<T_O>(), nil<T_O>(), nil<T_O>(), nil<T_O>()),
            index);
  }

  void op_shash() {
    HashTableBase_sp ht = gc::As<HashTableBase_sp>(get_ltv(read_index()));
    T_sp key = get_ltv(read_index());
    T_sp val = get_ltv(read_index());
    ht->hash_table_setf_gethash(key, val);
  }

  void op_sb64() {
    size_t index = read_index();
    set_ltv(Integer_O::create(read_s64()), index);
  }

  void op_package() {
    size_t index = read_index();
    String_sp name = gc::As<String_sp>(get_ltv(read_index()));
    set_ltv(_lisp->findPackage(name->get_std_string()), index);
  }

  void op_bignum() {
    size_t index = read_index();
    int64_t ssize = read_s64();
    mp_limb_t limbs[std::abs(ssize)];
    for (size_t i = std::abs(ssize); i > 0; --i)
      limbs[i - 1] = read_u64();
    set_ltv(bignum_result(ssize, limbs), index);
  }

  void op_float() {
    size_t index = read_index();
    set_ltv(clasp_make_single_float(read_f32()), index);
  }

  void op_double() {
    size_t index = read_index();
    set_ltv(clasp_make_double_float(read_f64()), index);
  }

  void op_ratio() {
    size_t index = read_index();
    Integer_sp num = gc::As<Integer_sp>(get_ltv(read_index()));
    Integer_sp den = gc::As<Integer_sp>(get_ltv(read_index()));
    set_ltv(contagion_div(num, den), index);
  }

  void op_complex() {
    size_t index = read_index();
    Real_sp real = gc::As<Real_sp>(get_ltv(read_index()));
    Real_sp imag = gc::As<Real_sp>(get_ltv(read_index()));
    set_ltv(clasp_make_complex(real, imag), index);
  }

  void op_symbol() {
    size_t index = read_index();
    SimpleString_sp name = gc::As<SimpleString_sp>(get_ltv(read_index()));
    set_ltv(Symbol_O::create(name), index);
  }

  void op_intern() {
    size_t index = read_index();
    Package_sp pack = gc::As<Package_sp>(get_ltv(read_index()));
    SimpleString_sp name = gc::As<SimpleString_sp>(get_ltv(read_index()));
    set_ltv(pack->intern(name), index);
  }

  void op_character() {
    size_t index = read_index();
    uint32_t code = read_u32();
    set_ltv(clasp_make_character(code), index);
  }

  void op_pathname() {
    size_t index = read_index();
    T_sp host = get_ltv(read_index());
    T_sp device = get_ltv(read_index());
    T_sp directory = get_ltv(read_index());
    T_sp name = get_ltv(read_index());
    T_sp type = get_ltv(read_index());
    T_sp version = get_ltv(read_index());
    set_ltv(Pathname_O::makePathname(host, device, directory, name, type, version, kw::_sym_local), index);
  }

  void op_bcfunc() {
    size_t index = read_index();
    uint32_t entry_point = read_u32();
    uint32_t final_size = read_u32();
    uint16_t nlocals = read_u16();
    uint16_t nclosed = read_u16();
    BytecodeModule_sp module = gc::As<BytecodeModule_sp>(get_ltv(read_index()));
    T_sp name = get_ltv(read_index());
    T_sp lambda_list = get_ltv(read_index());
    T_sp docstring = get_ltv(read_index());
    FunctionDescription_sp fdesc = makeFunctionDescription(name, lambda_list, docstring, nil<T_O>(), nil<T_O>(), -1, -1, -1);
    GlobalBytecodeSimpleFun_sp fun = core__makeGlobalBytecodeSimpleFun(fdesc, module, nlocals, nclosed, entry_point, final_size,
                                                                       llvmo::cmp__compile_trampoline(name));
    set_ltv(fun, index);
  }

  void op_bcmod() {
    size_t index = read_index();
    uint32_t len = read_u32();
    BytecodeModule_sp mod = BytecodeModule_O::make();
    SimpleVector_byte8_t_sp bytes = SimpleVector_byte8_t_O::make(len);
    mod->setf_bytecode(bytes);
    cl__read_sequence(bytes, _stream, clasp_make_fixnum(0), nil<T_O>());
    set_ltv(mod, index);
  }

  void op_slits() {
    BytecodeModule_sp mod = gc::As<BytecodeModule_sp>(get_ltv(read_index()));
    uint16_t len = read_u16();
    SimpleVector_sp lits = SimpleVector_O::make(len);
    mod->setf_literals(lits);
    for (size_t i = 0; i < len; ++i)
      (*lits)[i] = get_ltv(read_index());
  }

  void op_fdef() {
    size_t index = read_index();
    T_sp name = get_ltv(read_index());
    set_ltv(cl__fdefinition(name), index);
  }

  void op_create() {
    size_t index = read_index();
    Function_sp func = gc::As<Function_sp>(get_ltv(read_index()));
    // fmt::print("create {}\n", _rep_(func));
    uint16_t nargs = read_u16();
    T_O *args[nargs];
    for (size_t i = 0; i < nargs; ++i)
      args[i] = get_ltv(read_index()).raw_();
    T_sp res = funcall_general<Function_O>((gc::Tagged)(func.raw_()), nargs, args);
    set_ltv(res, index);
  }

  void op_init() {
    Function_sp func = gc::As<Function_sp>(get_ltv(read_index()));
    // fmt::print("init {}\n", _rep_(func));
    uint16_t nargs = read_u16();
    T_O *args[nargs];
    for (size_t i = 0; i < nargs; ++i)
      args[i] = get_ltv(read_index()).raw_();
    funcall_general<Function_O>((gc::Tagged)(func.raw_()), nargs, args);
  }

  void op_class() {
    size_t index = read_index();
    Symbol_sp name = gc::As<Symbol_sp>(get_ltv(read_index()));
    set_ltv(cl__find_class(name, true, nil<T_O>()), index);
  }

  void attr_clasp_source_pos_info(uint32_t bytes) {
    Function_sp func = gc::As<Function_sp>(get_ltv(read_index()));
    T_sp path = get_ltv(read_index());
    uint64_t line = read_u64(), column = read_u64(), filepos = read_u64();
    // fmt::print("spi {} {} {} {}\n", _rep_(path), line, column, filepos);
    func->setSourcePosInfo(path, filepos, line, column);
  }

  void attr_clasp_module_debug_info(uint32_t bytes) {
    BytecodeModule_sp mod = gc::As<BytecodeModule_sp>(get_ltv(read_index()));
    gctools::Vec0<T_sp> vargs;

    for (uint16_t fcount = read_u16(); fcount > 0; --fcount) {
      vargs.push_back(get_ltv(read_index()));
    }

    for (uint32_t vcount = read_u32(); vcount > 0; --vcount) {
      Integer_sp start = Integer_O::create(read_u32()), end = Integer_O::create(read_u32());
      gctools::Vec0<T_sp> bindings;
      for (uint16_t bcount = read_u16(); bcount > 0; --bcount) {
        T_sp name = get_ltv(read_index());
        uint8_t flag = read_u8();
        Integer_sp framei = Integer_O::create(read_u16());
        bindings.push_back((flag == 0) ? Cons_O::create(name, framei) : Cons_O::createList(name, framei));
      }
      vargs.push_back(BytecodeDebugVars_O::make(start, end, Cons_O::createFromVec0(bindings)));
    }
    mod->setf_debugInfo(SimpleVector_O::make(vargs));
  }

  void attr_clasp_module_debug_locations(uint32_t bytes) {
    BytecodeModule_sp mod = gc::As<BytecodeModule_sp>(get_ltv(read_index()));
    gctools::Vec0<T_sp> vargs;

    for (uint32_t lcount = read_u32(); lcount > 0; --lcount) {
      Integer_sp start = Integer_O::create(read_u32());
      Integer_sp end = Integer_O::create(read_u32());
      T_sp path = get_ltv(read_index());
      uint64_t line = read_u64(), column = read_u64(), filepos = read_u64();
      T_mv sfi_mv = core__file_scope(path);
      FileScope_sp sfi = gc::As<FileScope_sp>(sfi_mv);
      SourcePosInfo_sp spi
        = SourcePosInfo_O::create(sfi->fileHandle(),
                                  filepos, line, column);
      vargs.push_back(BytecodeDebugLocation_O::make(start, end, spi));
    }
    // KLUDGE: This is cl:concatenate
    SimpleVector_sp nvec = SimpleVector_O::make(vargs);
    SimpleVector_sp ovec = mod->debugInfo();
    size_t no = ovec->length();
    SimpleVector_sp ndbg = SimpleVector_O::make(nvec->length() + no);
    for (size_t i = 0; i < ovec->length(); ++i)
      (*ndbg)[i] = (*ovec)[i];
    for (size_t j = 0; j < nvec->length(); ++j)
      (*ndbg)[j + no] = (*nvec)[j];
    mod->setf_debugInfo(ndbg);
  }

  void op_attribute() {
    std::string name = (gc::As<String_sp>(get_ltv(read_index())))->get_std_string();
    uint32_t attrbytes = read_u32();
    if (name == "clasp:source-pos-info") {
      attr_clasp_source_pos_info(attrbytes);
    } else if (name == "clasp:module-debug-info") {
      attr_clasp_module_debug_info(attrbytes);
    } else if (name == "clasp:module-debug-locations") {
      attr_clasp_module_debug_locations(attrbytes);
    } else {
      for (size_t i = 0; i < attrbytes; ++i)
        read_u8();
    }
  }

  void op_init_object_array() {
    check_initialization();
    uint64_t nobjs = read_u64();
    if (nobjs <= std::numeric_limits<uint8_t>::max()) {
      _index_bytes = 1;
    } else if (nobjs <= std::numeric_limits<uint16_t>::max()) {
      _index_bytes = 2;
    } else if (nobjs <= std::numeric_limits<uint32_t>::max()) {
      _index_bytes = 4;
    } else {
      _index_bytes = 8;
    }
    _literals.assign(nobjs, unbound<T_O>());
  }

  void load_instruction() {
    uint8_t opcode = read_opcode();
    // fmt::print("op {:02x}\n", opcode);
    switch (opcode) {
    case LTV_OP_NIL:
      op_nil();
      break;
    case LTV_OP_T:
      op_t();
      break;
    case LTV_OP_CONS:
      op_cons();
      break;
    case LTV_OP_RPLACA:
      op_rplaca();
      break;
    case LTV_OP_RPLACD:
      op_rplacd();
      break;
    case LTV_OP_MAKE_ARRAY:
      op_array();
      break;
    case LTV_OP_SRMA:
      op_srma();
      break; // (setf row-major-aref)
    case LTV_OP_HASHT:
      op_hasht();
      break; // make-hash-table
    case LTV_OP_SHASH:
      op_shash();
      break; // (setf gethash)
    case LTV_OP_SB64:
      op_sb64();
      break;
    case LTV_OP_PACKAGE:
      op_package();
      break;
    case LTV_OP_BIGNUM:
      op_bignum();
      break;
    case LTV_OP_FLOAT:
      op_float();
      break;
    case LTV_OP_DOUBLE:
      op_double();
      break;
    case LTV_OP_RATIO:
      op_ratio();
      break;
    case LTV_OP_COMPLEX:
      op_complex();
      break;
    case LTV_OP_SYMBOL:
      op_symbol();
      break;
    case LTV_OP_INTERN:
      op_intern();
      break;
    case LTV_OP_CHARACTER:
      op_character();
      break;
    case LTV_OP_PATHNAME:
      op_pathname();
      break;
    case LTV_OP_BCFUNC:
      op_bcfunc();
      break;
    case LTV_OP_BCMOD:
      op_bcmod();
      break;
    case LTV_OP_SLITS:
      op_slits();
      break; // setf literals
    case LTV_OP_FDEF:
      op_fdef();
      break;
    case LTV_OP_CREATE:
      op_create();
      break; // funcall-create
    case LTV_OP_INIT:
      op_init();
      break; // funcall-initialize
    case LTV_OP_CLASS:
      op_class();
      break;
    case LTV_OP_INIT_OBJECT_ARRAY:
      op_init_object_array();
      break;
    case LTV_OP_ATTR:
      op_attribute();
      break;
    default:
      SIMPLE_ERROR("Unknown opcode %" PRIx8, opcode);
    }
  }

  void load() {
    uint8_t header[BC_HEADER_SIZE];
    clasp_read_byte8(_stream, header, BC_HEADER_SIZE);
    uint64_t ninsts = ltv_header_decode(header);
    for (size_t i = 0; i < ninsts; ++i)
      load_instruction();
    // TODO: Check EOF
    check_initialization();
  }
};

CL_DEFUN void load_bytecode_stream(Stream_sp stream) {
  loadltv loader(stream);
  loader.load();
}

CL_DEFUN bool load_bytecode(T_sp filename, bool verbose, bool print, T_sp external_format) {
  T_sp strm =
      cl__open(filename, kw::_sym_input, ext::_sym_byte8, nil<T_O>(), false, nil<T_O>(), false, external_format, nil<T_O>());
  if (strm.nilp())
    return false;
  load_bytecode_stream(gc::As<Stream_sp>(strm));
  cl__close(strm);
  return true;
}

struct ltv_MmapInfo {
  uint8_t *_Memory;
  size_t _Len;
  ltv_MmapInfo(uint8_t *mem, size_t len) : _Memory(mem), _Len(len){};
};

CL_LAMBDA(output-designator files &optional (verbose nil));
CL_DEFUN void core__link_fasl_files(T_sp output, List_sp files, bool verbose) {
  size_t instruction_count = 0;
  std::vector<ltv_MmapInfo> mmaps;

  for (size_t ii = 0; files.notnilp(); ++ii) {
    String_sp filename = gc::As<String_sp>(cl__namestring(oCar(files)));
    files = oCdr(files);
    int fd = open(filename->get_std_string().c_str(), O_RDONLY);
    off_t fsize = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    uint8_t *memory = (uint8_t *)mmap(NULL, fsize, PROT_READ, MAP_SHARED | MAP_FILE, fd, 0);
    close(fd);
    if (memory == MAP_FAILED) {
      SIMPLE_ERROR("Could not mmap {} because of {}", _rep_(filename), strerror(errno));
    }
    mmaps.emplace_back(ltv_MmapInfo(memory, fsize));
    instruction_count += ltv_header_decode(memory);
  }

  String_sp filename = gc::As<String_sp>(cl__namestring(output));
  std::string sfilename = filename->get_std_string();
  char bfilename[sfilename.size()+7];
  strncpy( bfilename, sfilename.c_str(), sfilename.size() );
  bfilename[sfilename.size()] = '\0';
  strcat( bfilename, "XXXXXX" );
  int fout = mkstemp(bfilename);
  if (fout<0) {
    SIMPLE_ERROR("Could not open temporary mkstemp file with {} as the template - error: {}",
                 _rep_(filename), strerror(errno));
  }

  if (verbose) {
    clasp_write_string(fmt::format("Writing file: {}\n", _rep_(filename)));
  }

  // Write header
  uint8_t header[BC_HEADER_SIZE];
  ltv_header_encode(header, instruction_count);
  write( fout, header, BC_HEADER_SIZE );

  for (auto mmap : mmaps) {
    write( fout, mmap._Memory + BC_HEADER_SIZE, mmap._Len - BC_HEADER_SIZE );
    int res = munmap(mmap._Memory, mmap._Len);
    if (res != 0) {
      SIMPLE_ERROR("Could not munmap memory");
    }
  }

  if (verbose)
    clasp_write_string(fmt::format("Closing {}\n", _rep_(filename)));
  close(fout);
  int ren = rename( bfilename, sfilename.c_str() );
  if (ren<0) {
    std::string sbfilename(bfilename);
    SIMPLE_ERROR("Could not rename {} to {}", sbfilename, sfilename.c_str() );
  }
  if (verbose)
    clasp_write_string(fmt::format("Returning {}\n", _rep_(filename)));
}

}; // namespace core
