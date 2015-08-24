// This file was GENERATED by command:
//     pump.py clbind_static_members.pmp
// DO NOT EDIT BY HAND!!!

// // TEMPLATE_TOP
// template_ = 0
// isConst = 0
// ret = 0 (RetSV)
//
// innerCount = 0
// numArgs = 8 (ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7)
// numVoids = 0
//
/* Specialization  */
template <typename Pols, typename OT , typename RT  ,typename ARG1,typename ARG2,typename ARG3,typename ARG4,typename ARG5,
    typename ARG6,typename ARG7 >
class IndirectVariadicMethoid
< Pols,OT ,RT (*)( ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7)  >
: public core::Functoid {
public:
virtual const char* describe() const { return "IndirectVariadicMethoid"; };
typedef RT (*Type)( ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7) ;
Type mptr;
public:
enum { NumParams = 8 };
IndirectVariadicMethoid(core::T_sp name, Type ptr) : core::Functoid(name), mptr(ptr) {};
DISABLE_NEW();

inline LCC_RETURN LISP_CALLING_CONVENTION()
{
INVOCATION_HISTORY_FRAME();
gc::frame::Frame frame(8);
core::StackFrameDynamicScopeManager scope(frame);
lambdaListHandler_createBindings(this,this->_lambdaListHandler,scope,LCC_PASS_ARGS);
// translate::from_object<OT*> objPtr(frame.arg(0));
OT* objPtr = gc::As<core::WrappedPointer_sp>(frame.arg(0))->cast<OT>();
translate::from_object<ARG1,typename DoesNotContain_<Pols,pureOutValue<1> >::type > a1(frame.arg(1));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<1> >::type >::go(args);
translate::from_object<ARG2,typename DoesNotContain_<Pols,pureOutValue<2> >::type > a2(frame.arg(2));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<2> >::type >::go(args);
translate::from_object<ARG3,typename DoesNotContain_<Pols,pureOutValue<3> >::type > a3(frame.arg(3));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<3> >::type >::go(args);
translate::from_object<ARG4,typename DoesNotContain_<Pols,pureOutValue<4> >::type > a4(frame.arg(4));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<4> >::type >::go(args);
translate::from_object<ARG5,typename DoesNotContain_<Pols,pureOutValue<5> >::type > a5(frame.arg(5));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<5> >::type >::go(args);
translate::from_object<ARG6,typename DoesNotContain_<Pols,pureOutValue<6> >::type > a6(frame.arg(6));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<6> >::type >::go(args);
translate::from_object<ARG7,typename DoesNotContain_<Pols,pureOutValue<7> >::type > a7(frame.arg(7));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<7> >::type >::go(args);
RT retval =  ((*objPtr).*(this->mptr))(a1._v,a2._v,a3._v,a4._v,a5._v,a6._v,a7._v);
core::MultipleValues& returnValues = core::lisp_multipleValues();
returnValues.setSize(0);
int oidx = 1;
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,1>::type()
, typename AdoptPointer<Pols,1>::type()
, a1._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,2>::type()
, typename AdoptPointer<Pols,2>::type()
, a2._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,3>::type()
, typename AdoptPointer<Pols,3>::type()
, a3._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,4>::type()
, typename AdoptPointer<Pols,4>::type()
, a4._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,5>::type()
, typename AdoptPointer<Pols,5>::type()
, a5._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,6>::type()
, typename AdoptPointer<Pols,6>::type()
, a6._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,7>::type()
, typename AdoptPointer<Pols,7>::type()
, a7._v);
return gctools::multiple_values<core::T_O>(translate::to_object<RT,typename AdoptPointer<Pols,result>::type >::convert(retval),
    oidx);
}
};
// TEMPLATE_TOP
// template_ = 1
// isConst = 0
// ret = 0 (RetSV)
//
// innerCount = 1
// numArgs = 7 (ARG1, ARG2, ARG3, ARG4, ARG5, ARG6)
// numVoids = 1
//
/* Specialization  */
template <typename Pols, typename OT , typename RT  ,typename ARG1,typename ARG2,typename ARG3,typename ARG4,typename ARG5,
    typename ARG6 >
class IndirectVariadicMethoid
< Pols,OT ,RT (*)( ARG1, ARG2, ARG3, ARG4, ARG5, ARG6)  >
: public core::Functoid {
public:
virtual const char* describe() const { return "IndirectVariadicMethoid"; };
typedef RT (*Type)( ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) ;
Type mptr;
public:
enum { NumParams = 7 };
IndirectVariadicMethoid(core::T_sp name, Type ptr) : core::Functoid(name), mptr(ptr) {};
DISABLE_NEW();

inline LCC_RETURN LISP_CALLING_CONVENTION()
{
INVOCATION_HISTORY_FRAME();
gc::frame::Frame frame(7);
core::StackFrameDynamicScopeManager scope(frame);
lambdaListHandler_createBindings(this,this->_lambdaListHandler,scope,LCC_PASS_ARGS);
// translate::from_object<OT*> objPtr(frame.arg(0));
OT* objPtr = gc::As<core::WrappedPointer_sp>(frame.arg(0))->cast<OT>();
translate::from_object<ARG1,typename DoesNotContain_<Pols,pureOutValue<1> >::type > a1(frame.arg(1));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<1> >::type >::go(args);
translate::from_object<ARG2,typename DoesNotContain_<Pols,pureOutValue<2> >::type > a2(frame.arg(2));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<2> >::type >::go(args);
translate::from_object<ARG3,typename DoesNotContain_<Pols,pureOutValue<3> >::type > a3(frame.arg(3));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<3> >::type >::go(args);
translate::from_object<ARG4,typename DoesNotContain_<Pols,pureOutValue<4> >::type > a4(frame.arg(4));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<4> >::type >::go(args);
translate::from_object<ARG5,typename DoesNotContain_<Pols,pureOutValue<5> >::type > a5(frame.arg(5));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<5> >::type >::go(args);
translate::from_object<ARG6,typename DoesNotContain_<Pols,pureOutValue<6> >::type > a6(frame.arg(6));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<6> >::type >::go(args);
RT retval =  ((*objPtr).*(this->mptr))(a1._v,a2._v,a3._v,a4._v,a5._v,a6._v);
core::MultipleValues& returnValues = core::lisp_multipleValues();
returnValues.setSize(0);
int oidx = 1;
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,1>::type()
, typename AdoptPointer<Pols,1>::type()
, a1._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,2>::type()
, typename AdoptPointer<Pols,2>::type()
, a2._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,3>::type()
, typename AdoptPointer<Pols,3>::type()
, a3._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,4>::type()
, typename AdoptPointer<Pols,4>::type()
, a4._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,5>::type()
, typename AdoptPointer<Pols,5>::type()
, a5._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,6>::type()
, typename AdoptPointer<Pols,6>::type()
, a6._v);
return gctools::multiple_values<core::T_O>(translate::to_object<RT,typename AdoptPointer<Pols,result>::type >::convert(retval),
    oidx);
}
};
// TEMPLATE_TOP
// template_ = 2
// isConst = 0
// ret = 0 (RetSV)
//
// innerCount = 2
// numArgs = 6 (ARG1, ARG2, ARG3, ARG4, ARG5)
// numVoids = 2
//
/* Specialization  */
template <typename Pols, typename OT , typename RT  ,typename ARG1,typename ARG2,typename ARG3,typename ARG4,typename ARG5 >
class IndirectVariadicMethoid
< Pols,OT ,RT (*)( ARG1, ARG2, ARG3, ARG4, ARG5)  >
: public core::Functoid {
public:
virtual const char* describe() const { return "IndirectVariadicMethoid"; };
typedef RT (*Type)( ARG1, ARG2, ARG3, ARG4, ARG5) ;
Type mptr;
public:
enum { NumParams = 6 };
IndirectVariadicMethoid(core::T_sp name, Type ptr) : core::Functoid(name), mptr(ptr) {};
DISABLE_NEW();

inline LCC_RETURN LISP_CALLING_CONVENTION()
{
INVOCATION_HISTORY_FRAME();
gc::frame::Frame frame(6);
core::StackFrameDynamicScopeManager scope(frame);
lambdaListHandler_createBindings(this,this->_lambdaListHandler,scope,LCC_PASS_ARGS);
// translate::from_object<OT*> objPtr(frame.arg(0));
OT* objPtr = gc::As<core::WrappedPointer_sp>(frame.arg(0))->cast<OT>();
translate::from_object<ARG1,typename DoesNotContain_<Pols,pureOutValue<1> >::type > a1(frame.arg(1));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<1> >::type >::go(args);
translate::from_object<ARG2,typename DoesNotContain_<Pols,pureOutValue<2> >::type > a2(frame.arg(2));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<2> >::type >::go(args);
translate::from_object<ARG3,typename DoesNotContain_<Pols,pureOutValue<3> >::type > a3(frame.arg(3));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<3> >::type >::go(args);
translate::from_object<ARG4,typename DoesNotContain_<Pols,pureOutValue<4> >::type > a4(frame.arg(4));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<4> >::type >::go(args);
translate::from_object<ARG5,typename DoesNotContain_<Pols,pureOutValue<5> >::type > a5(frame.arg(5));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<5> >::type >::go(args);
RT retval =  ((*objPtr).*(this->mptr))(a1._v,a2._v,a3._v,a4._v,a5._v);
core::MultipleValues& returnValues = core::lisp_multipleValues();
returnValues.setSize(0);
int oidx = 1;
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,1>::type()
, typename AdoptPointer<Pols,1>::type()
, a1._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,2>::type()
, typename AdoptPointer<Pols,2>::type()
, a2._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,3>::type()
, typename AdoptPointer<Pols,3>::type()
, a3._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,4>::type()
, typename AdoptPointer<Pols,4>::type()
, a4._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,5>::type()
, typename AdoptPointer<Pols,5>::type()
, a5._v);
return gctools::multiple_values<core::T_O>(translate::to_object<RT,typename AdoptPointer<Pols,result>::type >::convert(retval),
    oidx);
}
};
// TEMPLATE_TOP
// template_ = 3
// isConst = 0
// ret = 0 (RetSV)
//
// innerCount = 3
// numArgs = 5 (ARG1, ARG2, ARG3, ARG4)
// numVoids = 3
//
/* Specialization  */
template <typename Pols, typename OT , typename RT  ,typename ARG1,typename ARG2,typename ARG3,typename ARG4 >
class IndirectVariadicMethoid
< Pols,OT ,RT (*)( ARG1, ARG2, ARG3, ARG4)  >
: public core::Functoid {
public:
virtual const char* describe() const { return "IndirectVariadicMethoid"; };
typedef RT (*Type)( ARG1, ARG2, ARG3, ARG4) ;
Type mptr;
public:
enum { NumParams = 5 };
IndirectVariadicMethoid(core::T_sp name, Type ptr) : core::Functoid(name), mptr(ptr) {};
DISABLE_NEW();

inline LCC_RETURN LISP_CALLING_CONVENTION()
{
INVOCATION_HISTORY_FRAME();
gc::frame::Frame frame(5);
core::StackFrameDynamicScopeManager scope(frame);
lambdaListHandler_createBindings(this,this->_lambdaListHandler,scope,LCC_PASS_ARGS);
// translate::from_object<OT*> objPtr(frame.arg(0));
OT* objPtr = gc::As<core::WrappedPointer_sp>(frame.arg(0))->cast<OT>();
translate::from_object<ARG1,typename DoesNotContain_<Pols,pureOutValue<1> >::type > a1(frame.arg(1));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<1> >::type >::go(args);
translate::from_object<ARG2,typename DoesNotContain_<Pols,pureOutValue<2> >::type > a2(frame.arg(2));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<2> >::type >::go(args);
translate::from_object<ARG3,typename DoesNotContain_<Pols,pureOutValue<3> >::type > a3(frame.arg(3));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<3> >::type >::go(args);
translate::from_object<ARG4,typename DoesNotContain_<Pols,pureOutValue<4> >::type > a4(frame.arg(4));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<4> >::type >::go(args);
RT retval =  ((*objPtr).*(this->mptr))(a1._v,a2._v,a3._v,a4._v);
core::MultipleValues& returnValues = core::lisp_multipleValues();
returnValues.setSize(0);
int oidx = 1;
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,1>::type()
, typename AdoptPointer<Pols,1>::type()
, a1._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,2>::type()
, typename AdoptPointer<Pols,2>::type()
, a2._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,3>::type()
, typename AdoptPointer<Pols,3>::type()
, a3._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,4>::type()
, typename AdoptPointer<Pols,4>::type()
, a4._v);
return gctools::multiple_values<core::T_O>(translate::to_object<RT,typename AdoptPointer<Pols,result>::type >::convert(retval),
    oidx);
}
};
// TEMPLATE_TOP
// template_ = 4
// isConst = 0
// ret = 0 (RetSV)
//
// innerCount = 4
// numArgs = 4 (ARG1, ARG2, ARG3)
// numVoids = 4
//
/* Specialization  */
template <typename Pols, typename OT , typename RT  ,typename ARG1,typename ARG2,typename ARG3 >
class IndirectVariadicMethoid
< Pols,OT ,RT (*)( ARG1, ARG2, ARG3)  >
: public core::Functoid {
public:
virtual const char* describe() const { return "IndirectVariadicMethoid"; };
typedef RT (*Type)( ARG1, ARG2, ARG3) ;
Type mptr;
public:
enum { NumParams = 4 };
IndirectVariadicMethoid(core::T_sp name, Type ptr) : core::Functoid(name), mptr(ptr) {};
DISABLE_NEW();

inline LCC_RETURN LISP_CALLING_CONVENTION()
{
INVOCATION_HISTORY_FRAME();
gc::frame::Frame frame(4);
core::StackFrameDynamicScopeManager scope(frame);
lambdaListHandler_createBindings(this,this->_lambdaListHandler,scope,LCC_PASS_ARGS);
// translate::from_object<OT*> objPtr(frame.arg(0));
OT* objPtr = gc::As<core::WrappedPointer_sp>(frame.arg(0))->cast<OT>();
translate::from_object<ARG1,typename DoesNotContain_<Pols,pureOutValue<1> >::type > a1(frame.arg(1));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<1> >::type >::go(args);
translate::from_object<ARG2,typename DoesNotContain_<Pols,pureOutValue<2> >::type > a2(frame.arg(2));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<2> >::type >::go(args);
translate::from_object<ARG3,typename DoesNotContain_<Pols,pureOutValue<3> >::type > a3(frame.arg(3));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<3> >::type >::go(args);
RT retval =  ((*objPtr).*(this->mptr))(a1._v,a2._v,a3._v);
core::MultipleValues& returnValues = core::lisp_multipleValues();
returnValues.setSize(0);
int oidx = 1;
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,1>::type()
, typename AdoptPointer<Pols,1>::type()
, a1._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,2>::type()
, typename AdoptPointer<Pols,2>::type()
, a2._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,3>::type()
, typename AdoptPointer<Pols,3>::type()
, a3._v);
return gctools::multiple_values<core::T_O>(translate::to_object<RT,typename AdoptPointer<Pols,result>::type >::convert(retval),
    oidx);
}
};
// TEMPLATE_TOP
// template_ = 5
// isConst = 0
// ret = 0 (RetSV)
//
// innerCount = 5
// numArgs = 3 (ARG1, ARG2)
// numVoids = 5
//
/* Specialization  */
template <typename Pols, typename OT , typename RT  ,typename ARG1,typename ARG2 >
class IndirectVariadicMethoid
< Pols,OT ,RT (*)( ARG1, ARG2)  >
: public core::Functoid {
public:
virtual const char* describe() const { return "IndirectVariadicMethoid"; };
typedef RT (*Type)( ARG1, ARG2) ;
Type mptr;
public:
enum { NumParams = 3 };
IndirectVariadicMethoid(core::T_sp name, Type ptr) : core::Functoid(name), mptr(ptr) {};
DISABLE_NEW();

inline LCC_RETURN LISP_CALLING_CONVENTION()
{
INVOCATION_HISTORY_FRAME();
gc::frame::Frame frame(3);
core::StackFrameDynamicScopeManager scope(frame);
lambdaListHandler_createBindings(this,this->_lambdaListHandler,scope,LCC_PASS_ARGS);
// translate::from_object<OT*> objPtr(frame.arg(0));
OT* objPtr = gc::As<core::WrappedPointer_sp>(frame.arg(0))->cast<OT>();
translate::from_object<ARG1,typename DoesNotContain_<Pols,pureOutValue<1> >::type > a1(frame.arg(1));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<1> >::type >::go(args);
translate::from_object<ARG2,typename DoesNotContain_<Pols,pureOutValue<2> >::type > a2(frame.arg(2));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<2> >::type >::go(args);
RT retval =  ((*objPtr).*(this->mptr))(a1._v,a2._v);
core::MultipleValues& returnValues = core::lisp_multipleValues();
returnValues.setSize(0);
int oidx = 1;
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,1>::type()
, typename AdoptPointer<Pols,1>::type()
, a1._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,2>::type()
, typename AdoptPointer<Pols,2>::type()
, a2._v);
return gctools::multiple_values<core::T_O>(translate::to_object<RT,typename AdoptPointer<Pols,result>::type >::convert(retval),
    oidx);
}
};
// TEMPLATE_TOP
// template_ = 6
// isConst = 0
// ret = 0 (RetSV)
//
// innerCount = 6
// numArgs = 2 (ARG1)
// numVoids = 6
//
/* Specialization  */
template <typename Pols, typename OT , typename RT  ,typename ARG1 >
class IndirectVariadicMethoid
< Pols,OT ,RT (*)( ARG1)  >
: public core::Functoid {
public:
virtual const char* describe() const { return "IndirectVariadicMethoid"; };
typedef RT (*Type)( ARG1) ;
Type mptr;
public:
enum { NumParams = 2 };
IndirectVariadicMethoid(core::T_sp name, Type ptr) : core::Functoid(name), mptr(ptr) {};
DISABLE_NEW();

inline LCC_RETURN LISP_CALLING_CONVENTION()
{
INVOCATION_HISTORY_FRAME();
gc::frame::Frame frame(2);
core::StackFrameDynamicScopeManager scope(frame);
lambdaListHandler_createBindings(this,this->_lambdaListHandler,scope,LCC_PASS_ARGS);
// translate::from_object<OT*> objPtr(frame.arg(0));
OT* objPtr = gc::As<core::WrappedPointer_sp>(frame.arg(0))->cast<OT>();
translate::from_object<ARG1,typename DoesNotContain_<Pols,pureOutValue<1> >::type > a1(frame.arg(1));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<1> >::type >::go(args);
RT retval =  ((*objPtr).*(this->mptr))(a1._v);
core::MultipleValues& returnValues = core::lisp_multipleValues();
returnValues.setSize(0);
int oidx = 1;
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,1>::type()
, typename AdoptPointer<Pols,1>::type()
, a1._v);
return gctools::multiple_values<core::T_O>(translate::to_object<RT,typename AdoptPointer<Pols,result>::type >::convert(retval),
    oidx);
}
};
// TEMPLATE_TOP
// template_ = 7
// isConst = 0
// ret = 0 (RetSV)
//
// innerCount = 7
// numArgs = 1 ()
// numVoids = 7
//
/* Specialization  */
template <typename Pols, typename OT , typename RT   >
class IndirectVariadicMethoid
< Pols,OT ,RT (*)( )  >
: public core::Functoid {
public:
virtual const char* describe() const { return "IndirectVariadicMethoid"; };
typedef RT (*Type)( ) ;
Type mptr;
public:
enum { NumParams = 1 };
IndirectVariadicMethoid(core::T_sp name, Type ptr) : core::Functoid(name), mptr(ptr) {};
DISABLE_NEW();

inline LCC_RETURN LISP_CALLING_CONVENTION()
{
INVOCATION_HISTORY_FRAME();
gc::frame::Frame frame(1);
core::StackFrameDynamicScopeManager scope(frame);
lambdaListHandler_createBindings(this,this->_lambdaListHandler,scope,LCC_PASS_ARGS);
// translate::from_object<OT*> objPtr(frame.arg(0));
OT* objPtr = gc::As<core::WrappedPointer_sp>(frame.arg(0))->cast<OT>();
RT retval =  ((*objPtr).*(this->mptr))();
core::MultipleValues& returnValues = core::lisp_multipleValues();
returnValues.setSize(0);
int oidx = 1;
return gctools::multiple_values<core::T_O>(translate::to_object<RT,typename AdoptPointer<Pols,result>::type >::convert(retval),
    oidx);
}
};
// TEMPLATE_TOP
// template_ = 8
// isConst = 0
// ret = 1 (void)
//
// innerCount = 0
// numArgs = 8 (ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7)
// numVoids = 0
//
/* Specialization  */
template <typename Pols, typename OT  ,typename ARG1,typename ARG2,typename ARG3,typename ARG4,typename ARG5,typename ARG6,
    typename ARG7 >
class IndirectVariadicMethoid
< Pols,OT ,void(*)( ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7)  >
: public core::Functoid {
public:
virtual const char* describe() const { return "IndirectVariadicMethoid"; };
typedef void (*Type)( ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7) ;
Type mptr;
public:
enum { NumParams = 8 };
IndirectVariadicMethoid(core::T_sp name, Type ptr) : core::Functoid(name), mptr(ptr) {};
DISABLE_NEW();

inline LCC_RETURN LISP_CALLING_CONVENTION()
{
INVOCATION_HISTORY_FRAME();
gc::frame::Frame frame(8);
core::StackFrameDynamicScopeManager scope(frame);
lambdaListHandler_createBindings(this,this->_lambdaListHandler,scope,LCC_PASS_ARGS);
// translate::from_object<OT*> objPtr(frame.arg(0));
OT* objPtr = gc::As<core::WrappedPointer_sp>(frame.arg(0))->cast<OT>();
translate::from_object<ARG1,typename DoesNotContain_<Pols,pureOutValue<1> >::type > a1(frame.arg(1));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<1> >::type >::go(args);
translate::from_object<ARG2,typename DoesNotContain_<Pols,pureOutValue<2> >::type > a2(frame.arg(2));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<2> >::type >::go(args);
translate::from_object<ARG3,typename DoesNotContain_<Pols,pureOutValue<3> >::type > a3(frame.arg(3));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<3> >::type >::go(args);
translate::from_object<ARG4,typename DoesNotContain_<Pols,pureOutValue<4> >::type > a4(frame.arg(4));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<4> >::type >::go(args);
translate::from_object<ARG5,typename DoesNotContain_<Pols,pureOutValue<5> >::type > a5(frame.arg(5));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<5> >::type >::go(args);
translate::from_object<ARG6,typename DoesNotContain_<Pols,pureOutValue<6> >::type > a6(frame.arg(6));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<6> >::type >::go(args);
translate::from_object<ARG7,typename DoesNotContain_<Pols,pureOutValue<7> >::type > a7(frame.arg(7));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<7> >::type >::go(args);
((*objPtr).*(this->mptr))(a1._v,a2._v,a3._v,a4._v,a5._v,a6._v,a7._v);
core::MultipleValues& returnValues = core::lisp_multipleValues();
returnValues.setSize(0);
int oidx = 0;                                                                     ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,1>::type()
, typename AdoptPointer<Pols,1>::type()
, a1._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,2>::type()
, typename AdoptPointer<Pols,2>::type()
, a2._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,3>::type()
, typename AdoptPointer<Pols,3>::type()
, a3._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,4>::type()
, typename AdoptPointer<Pols,4>::type()
, a4._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,5>::type()
, typename AdoptPointer<Pols,5>::type()
, a5._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,6>::type()
, typename AdoptPointer<Pols,6>::type()
, a6._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,7>::type()
, typename AdoptPointer<Pols,7>::type()
, a7._v);
return gctools::multiple_values<core::T_O>(returnValues.valueGet(0,oidx),oidx);
}
};
// TEMPLATE_TOP
// template_ = 9
// isConst = 0
// ret = 1 (void)
//
// innerCount = 1
// numArgs = 7 (ARG1, ARG2, ARG3, ARG4, ARG5, ARG6)
// numVoids = 1
//
/* Specialization  */
template <typename Pols, typename OT  ,typename ARG1,typename ARG2,typename ARG3,typename ARG4,typename ARG5,typename ARG6 >
class IndirectVariadicMethoid
< Pols,OT ,void(*)( ARG1, ARG2, ARG3, ARG4, ARG5, ARG6)  >
: public core::Functoid {
public:
virtual const char* describe() const { return "IndirectVariadicMethoid"; };
typedef void (*Type)( ARG1, ARG2, ARG3, ARG4, ARG5, ARG6) ;
Type mptr;
public:
enum { NumParams = 7 };
IndirectVariadicMethoid(core::T_sp name, Type ptr) : core::Functoid(name), mptr(ptr) {};
DISABLE_NEW();

inline LCC_RETURN LISP_CALLING_CONVENTION()
{
INVOCATION_HISTORY_FRAME();
gc::frame::Frame frame(7);
core::StackFrameDynamicScopeManager scope(frame);
lambdaListHandler_createBindings(this,this->_lambdaListHandler,scope,LCC_PASS_ARGS);
// translate::from_object<OT*> objPtr(frame.arg(0));
OT* objPtr = gc::As<core::WrappedPointer_sp>(frame.arg(0))->cast<OT>();
translate::from_object<ARG1,typename DoesNotContain_<Pols,pureOutValue<1> >::type > a1(frame.arg(1));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<1> >::type >::go(args);
translate::from_object<ARG2,typename DoesNotContain_<Pols,pureOutValue<2> >::type > a2(frame.arg(2));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<2> >::type >::go(args);
translate::from_object<ARG3,typename DoesNotContain_<Pols,pureOutValue<3> >::type > a3(frame.arg(3));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<3> >::type >::go(args);
translate::from_object<ARG4,typename DoesNotContain_<Pols,pureOutValue<4> >::type > a4(frame.arg(4));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<4> >::type >::go(args);
translate::from_object<ARG5,typename DoesNotContain_<Pols,pureOutValue<5> >::type > a5(frame.arg(5));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<5> >::type >::go(args);
translate::from_object<ARG6,typename DoesNotContain_<Pols,pureOutValue<6> >::type > a6(frame.arg(6));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<6> >::type >::go(args);
((*objPtr).*(this->mptr))(a1._v,a2._v,a3._v,a4._v,a5._v,a6._v);
core::MultipleValues& returnValues = core::lisp_multipleValues();
returnValues.setSize(0);
int oidx = 0;                                                                     ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,1>::type()
, typename AdoptPointer<Pols,1>::type()
, a1._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,2>::type()
, typename AdoptPointer<Pols,2>::type()
, a2._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,3>::type()
, typename AdoptPointer<Pols,3>::type()
, a3._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,4>::type()
, typename AdoptPointer<Pols,4>::type()
, a4._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,5>::type()
, typename AdoptPointer<Pols,5>::type()
, a5._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,6>::type()
, typename AdoptPointer<Pols,6>::type()
, a6._v);
return gctools::multiple_values<core::T_O>(returnValues.valueGet(0,oidx),oidx);
}
};
// TEMPLATE_TOP
// template_ = 10
// isConst = 0
// ret = 1 (void)
//
// innerCount = 2
// numArgs = 6 (ARG1, ARG2, ARG3, ARG4, ARG5)
// numVoids = 2
//
/* Specialization  */
template <typename Pols, typename OT  ,typename ARG1,typename ARG2,typename ARG3,typename ARG4,typename ARG5 >
class IndirectVariadicMethoid
< Pols,OT ,void(*)( ARG1, ARG2, ARG3, ARG4, ARG5)  >
: public core::Functoid {
public:
virtual const char* describe() const { return "IndirectVariadicMethoid"; };
typedef void (*Type)( ARG1, ARG2, ARG3, ARG4, ARG5) ;
Type mptr;
public:
enum { NumParams = 6 };
IndirectVariadicMethoid(core::T_sp name, Type ptr) : core::Functoid(name), mptr(ptr) {};
DISABLE_NEW();

inline LCC_RETURN LISP_CALLING_CONVENTION()
{
INVOCATION_HISTORY_FRAME();
gc::frame::Frame frame(6);
core::StackFrameDynamicScopeManager scope(frame);
lambdaListHandler_createBindings(this,this->_lambdaListHandler,scope,LCC_PASS_ARGS);
// translate::from_object<OT*> objPtr(frame.arg(0));
OT* objPtr = gc::As<core::WrappedPointer_sp>(frame.arg(0))->cast<OT>();
translate::from_object<ARG1,typename DoesNotContain_<Pols,pureOutValue<1> >::type > a1(frame.arg(1));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<1> >::type >::go(args);
translate::from_object<ARG2,typename DoesNotContain_<Pols,pureOutValue<2> >::type > a2(frame.arg(2));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<2> >::type >::go(args);
translate::from_object<ARG3,typename DoesNotContain_<Pols,pureOutValue<3> >::type > a3(frame.arg(3));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<3> >::type >::go(args);
translate::from_object<ARG4,typename DoesNotContain_<Pols,pureOutValue<4> >::type > a4(frame.arg(4));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<4> >::type >::go(args);
translate::from_object<ARG5,typename DoesNotContain_<Pols,pureOutValue<5> >::type > a5(frame.arg(5));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<5> >::type >::go(args);
((*objPtr).*(this->mptr))(a1._v,a2._v,a3._v,a4._v,a5._v);
core::MultipleValues& returnValues = core::lisp_multipleValues();
returnValues.setSize(0);
int oidx = 0;                                                                     ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,1>::type()
, typename AdoptPointer<Pols,1>::type()
, a1._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,2>::type()
, typename AdoptPointer<Pols,2>::type()
, a2._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,3>::type()
, typename AdoptPointer<Pols,3>::type()
, a3._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,4>::type()
, typename AdoptPointer<Pols,4>::type()
, a4._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,5>::type()
, typename AdoptPointer<Pols,5>::type()
, a5._v);
return gctools::multiple_values<core::T_O>(returnValues.valueGet(0,oidx),oidx);
}
};
// TEMPLATE_TOP
// template_ = 11
// isConst = 0
// ret = 1 (void)
//
// innerCount = 3
// numArgs = 5 (ARG1, ARG2, ARG3, ARG4)
// numVoids = 3
//
/* Specialization  */
template <typename Pols, typename OT  ,typename ARG1,typename ARG2,typename ARG3,typename ARG4 >
class IndirectVariadicMethoid
< Pols,OT ,void(*)( ARG1, ARG2, ARG3, ARG4)  >
: public core::Functoid {
public:
virtual const char* describe() const { return "IndirectVariadicMethoid"; };
typedef void (*Type)( ARG1, ARG2, ARG3, ARG4) ;
Type mptr;
public:
enum { NumParams = 5 };
IndirectVariadicMethoid(core::T_sp name, Type ptr) : core::Functoid(name), mptr(ptr) {};
DISABLE_NEW();

inline LCC_RETURN LISP_CALLING_CONVENTION()
{
INVOCATION_HISTORY_FRAME();
gc::frame::Frame frame(5);
core::StackFrameDynamicScopeManager scope(frame);
lambdaListHandler_createBindings(this,this->_lambdaListHandler,scope,LCC_PASS_ARGS);
// translate::from_object<OT*> objPtr(frame.arg(0));
OT* objPtr = gc::As<core::WrappedPointer_sp>(frame.arg(0))->cast<OT>();
translate::from_object<ARG1,typename DoesNotContain_<Pols,pureOutValue<1> >::type > a1(frame.arg(1));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<1> >::type >::go(args);
translate::from_object<ARG2,typename DoesNotContain_<Pols,pureOutValue<2> >::type > a2(frame.arg(2));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<2> >::type >::go(args);
translate::from_object<ARG3,typename DoesNotContain_<Pols,pureOutValue<3> >::type > a3(frame.arg(3));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<3> >::type >::go(args);
translate::from_object<ARG4,typename DoesNotContain_<Pols,pureOutValue<4> >::type > a4(frame.arg(4));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<4> >::type >::go(args);
((*objPtr).*(this->mptr))(a1._v,a2._v,a3._v,a4._v);
core::MultipleValues& returnValues = core::lisp_multipleValues();
returnValues.setSize(0);
int oidx = 0;                                                                     ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,1>::type()
, typename AdoptPointer<Pols,1>::type()
, a1._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,2>::type()
, typename AdoptPointer<Pols,2>::type()
, a2._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,3>::type()
, typename AdoptPointer<Pols,3>::type()
, a3._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,4>::type()
, typename AdoptPointer<Pols,4>::type()
, a4._v);
return gctools::multiple_values<core::T_O>(returnValues.valueGet(0,oidx),oidx);
}
};
// TEMPLATE_TOP
// template_ = 12
// isConst = 0
// ret = 1 (void)
//
// innerCount = 4
// numArgs = 4 (ARG1, ARG2, ARG3)
// numVoids = 4
//
/* Specialization  */
template <typename Pols, typename OT  ,typename ARG1,typename ARG2,typename ARG3 >
class IndirectVariadicMethoid
< Pols,OT ,void(*)( ARG1, ARG2, ARG3)  >
: public core::Functoid {
public:
virtual const char* describe() const { return "IndirectVariadicMethoid"; };
typedef void (*Type)( ARG1, ARG2, ARG3) ;
Type mptr;
public:
enum { NumParams = 4 };
IndirectVariadicMethoid(core::T_sp name, Type ptr) : core::Functoid(name), mptr(ptr) {};
DISABLE_NEW();

inline LCC_RETURN LISP_CALLING_CONVENTION()
{
INVOCATION_HISTORY_FRAME();
gc::frame::Frame frame(4);
core::StackFrameDynamicScopeManager scope(frame);
lambdaListHandler_createBindings(this,this->_lambdaListHandler,scope,LCC_PASS_ARGS);
// translate::from_object<OT*> objPtr(frame.arg(0));
OT* objPtr = gc::As<core::WrappedPointer_sp>(frame.arg(0))->cast<OT>();
translate::from_object<ARG1,typename DoesNotContain_<Pols,pureOutValue<1> >::type > a1(frame.arg(1));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<1> >::type >::go(args);
translate::from_object<ARG2,typename DoesNotContain_<Pols,pureOutValue<2> >::type > a2(frame.arg(2));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<2> >::type >::go(args);
translate::from_object<ARG3,typename DoesNotContain_<Pols,pureOutValue<3> >::type > a3(frame.arg(3));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<3> >::type >::go(args);
((*objPtr).*(this->mptr))(a1._v,a2._v,a3._v);
core::MultipleValues& returnValues = core::lisp_multipleValues();
returnValues.setSize(0);
int oidx = 0;                                                                     ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,1>::type()
, typename AdoptPointer<Pols,1>::type()
, a1._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,2>::type()
, typename AdoptPointer<Pols,2>::type()
, a2._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,3>::type()
, typename AdoptPointer<Pols,3>::type()
, a3._v);
return gctools::multiple_values<core::T_O>(returnValues.valueGet(0,oidx),oidx);
}
};
// TEMPLATE_TOP
// template_ = 13
// isConst = 0
// ret = 1 (void)
//
// innerCount = 5
// numArgs = 3 (ARG1, ARG2)
// numVoids = 5
//
/* Specialization  */
template <typename Pols, typename OT  ,typename ARG1,typename ARG2 >
class IndirectVariadicMethoid
< Pols,OT ,void(*)( ARG1, ARG2)  >
: public core::Functoid {
public:
virtual const char* describe() const { return "IndirectVariadicMethoid"; };
typedef void (*Type)( ARG1, ARG2) ;
Type mptr;
public:
enum { NumParams = 3 };
IndirectVariadicMethoid(core::T_sp name, Type ptr) : core::Functoid(name), mptr(ptr) {};
DISABLE_NEW();

inline LCC_RETURN LISP_CALLING_CONVENTION()
{
INVOCATION_HISTORY_FRAME();
gc::frame::Frame frame(3);
core::StackFrameDynamicScopeManager scope(frame);
lambdaListHandler_createBindings(this,this->_lambdaListHandler,scope,LCC_PASS_ARGS);
// translate::from_object<OT*> objPtr(frame.arg(0));
OT* objPtr = gc::As<core::WrappedPointer_sp>(frame.arg(0))->cast<OT>();
translate::from_object<ARG1,typename DoesNotContain_<Pols,pureOutValue<1> >::type > a1(frame.arg(1));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<1> >::type >::go(args);
translate::from_object<ARG2,typename DoesNotContain_<Pols,pureOutValue<2> >::type > a2(frame.arg(2));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<2> >::type >::go(args);
((*objPtr).*(this->mptr))(a1._v,a2._v);
core::MultipleValues& returnValues = core::lisp_multipleValues();
returnValues.setSize(0);
int oidx = 0;                                                                     ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,1>::type()
, typename AdoptPointer<Pols,1>::type()
, a1._v);
ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,2>::type()
, typename AdoptPointer<Pols,2>::type()
, a2._v);
return gctools::multiple_values<core::T_O>(returnValues.valueGet(0,oidx),oidx);
}
};
// TEMPLATE_TOP
// template_ = 14
// isConst = 0
// ret = 1 (void)
//
// innerCount = 6
// numArgs = 2 (ARG1)
// numVoids = 6
//
/* Specialization  */
template <typename Pols, typename OT  ,typename ARG1 >
class IndirectVariadicMethoid
< Pols,OT ,void(*)( ARG1)  >
: public core::Functoid {
public:
virtual const char* describe() const { return "IndirectVariadicMethoid"; };
typedef void (*Type)( ARG1) ;
Type mptr;
public:
enum { NumParams = 2 };
IndirectVariadicMethoid(core::T_sp name, Type ptr) : core::Functoid(name), mptr(ptr) {};
DISABLE_NEW();

inline LCC_RETURN LISP_CALLING_CONVENTION()
{
INVOCATION_HISTORY_FRAME();
gc::frame::Frame frame(2);
core::StackFrameDynamicScopeManager scope(frame);
lambdaListHandler_createBindings(this,this->_lambdaListHandler,scope,LCC_PASS_ARGS);
// translate::from_object<OT*> objPtr(frame.arg(0));
OT* objPtr = gc::As<core::WrappedPointer_sp>(frame.arg(0))->cast<OT>();
translate::from_object<ARG1,typename DoesNotContain_<Pols,pureOutValue<1> >::type > a1(frame.arg(1));
// IncWhen<typename DoesNotContain_<Pols,pureOutValue<1> >::type >::go(args);
((*objPtr).*(this->mptr))(a1._v);
core::MultipleValues& returnValues = core::lisp_multipleValues();
returnValues.setSize(0);
int oidx = 0;                                                                     ReturnValueWhen(returnValues,oidx
, typename is_outValue<Pols,1>::type()
, typename AdoptPointer<Pols,1>::type()
, a1._v);
return gctools::multiple_values<core::T_O>(returnValues.valueGet(0,oidx),oidx);
}
};
// TEMPLATE_TOP
// template_ = 15
// isConst = 0
// ret = 1 (void)
//
// innerCount = 7
// numArgs = 1 ()
// numVoids = 7
//
/* Specialization  */
template <typename Pols, typename OT   >
class IndirectVariadicMethoid
< Pols,OT ,void(*)( )  >
: public core::Functoid {
public:
virtual const char* describe() const { return "IndirectVariadicMethoid"; };
typedef void (*Type)( ) ;
Type mptr;
public:
enum { NumParams = 1 };
IndirectVariadicMethoid(core::T_sp name, Type ptr) : core::Functoid(name), mptr(ptr) {};
DISABLE_NEW();

inline LCC_RETURN LISP_CALLING_CONVENTION()
{
INVOCATION_HISTORY_FRAME();
gc::frame::Frame frame(1);
core::StackFrameDynamicScopeManager scope(frame);
lambdaListHandler_createBindings(this,this->_lambdaListHandler,scope,LCC_PASS_ARGS);
// translate::from_object<OT*> objPtr(frame.arg(0));
OT* objPtr = gc::As<core::WrappedPointer_sp>(frame.arg(0))->cast<OT>();
((*objPtr).*(this->mptr))();
core::MultipleValues& returnValues = core::lisp_multipleValues();
returnValues.setSize(0);
int oidx = 0;
    return gctools::multiple_values<core::T_O>(returnValues.valueGet(0,oidx),oidx);
}
};

