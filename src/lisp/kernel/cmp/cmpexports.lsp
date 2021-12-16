(in-package :cmp)
(eval-when (:compile-toplevel :load-toplevel :execute)
  (export '(with-debug-info-source-position
            with-interpreter
            calculate-cleavir-lambda-list-analysis
            module-report
            transform-lambda-parts
            codegen-startup-shutdown
            jit-startup-shutdown-function-names
            irc-simple-function-create
            *primitives*
            primitive-argument-types
            primitive-varargs
            *track-inlined-functions*
            *track-inlinee-name*
            *debug-link-options* ;; A list of strings to inject into link commands
            *compile-file-debug-dump-module* ;; Dump intermediate modules
            *compile-debug-dump-module* ;; Dump intermediate modules
            *default-linkage*
            *compile-file-parallel-write-bitcode*
            *default-compile-linkage*
            quick-module-dump
            write-bitcode
            load-bitcode
            *irbuilder*
            *compile-file-unique-symbol-prefix*
            %ltv*%
            irc-function-create
            irc-make-function-description
            irc-local-function-create
            irc-xep-functions-create
            xep-arity-arity
            xep-arity-function-or-placeholder
            xep-group-lookup
            xep-group-p
            xep-group-arities
            xep-group-name
            xep-group-entry-point-reference
            xep-group-cleavir-lambda-list-analysis
            +c++-stamp-max+
            %opaque-fn-prototype*%
            fn-prototype
            *cleavir-compile-file-hook*
            *cleavir-compile-hook*
            *compile-print*
            *current-function*
            *current-function-name*
            *current-unwind-landing-pad-dest*
            *debug-compile-file*
            *debug-compile-file-counter*
            *generate-compile-file-load-time-values*
            module-literal-table
            *gv-current-function-name*
            *implicit-compile-hook*
            *irbuilder*
            *thread-safe-context*
            thread-local-llvm-context
            *load-time-value-holder-global-var*
            *low-level-trace*
            *low-level-trace-print*
            *run-time-values-table-name*
            #+(or)*run-time-values-table-global-var*
            *the-module*
            +header-size+
            +header-stamp-size+
            +header-stamp-offset+
            +cons-tag+
            +fixnum-mask+
            +fixnum00-tag+
            +fixnum01-tag+
            #+tag-bits4 +fixnum10-tag+
            #+tag-bits4 +fixnum11-tag+
            +alignment+
            #+tag-bits4 +vaslist-ptag-mask+
            +vaslist0-tag+
            #+tag-bits4 +vaslist1-tag+
            +single-float-tag+
            +character-tag+
            +general-tag+
            +where-tag-mask+
            +derivable-where-tag+
            +rack-where-tag+
            +wrapped-where-tag+
            +header-where-tag+
            +literal-tag-char-code+
            *startup-primitives-as-list*
            %i1%
            %exception-struct%
            %i32%
            %i32*%
            %i64%
            %i8**%
            %i8*%
            %i8%
            %fixnum%
            %word%
            %mv-struct%
            %size_t%
            %t*%
            %t*[0]%
            %tsp%
            %t*[0]*%
            %tsp*%
            %t**%
            %t*[DUMMY]%
            %t*[DUMMY]*%
            %tmv%
            %valvec%
            %symbol%
            %float%
            %double%
            %gcroots-in-module%
            %gcroots-in-module*%
            gcroots-in-module-initial-value
            %function-description%
            %function-description*%
            entry-point-reference-index
            irc-funcall-results-in-registers
            function-type-create-on-the-fly
            evaluate-foreign-arguments
            calling-convention-closure
            calling-convention-vaslist*
            calling-convention-vaslist.va-arg
            calling-convention-nargs
            calling-convention-register-args
            cmp-log
            cmp-log-dump-module
            cmp-log-dump-function
            make-file-metadata
            make-function-metadata
            function-info
            function-info-cleavir-lambda-list-analysis
            make-function-info
            generate-function-for-arity-p

            irc-create-call-wft
            irc-calculate-entry
            compile-file-to-module
            optimize-module-for-compile
            optimize-module-for-compile-file
            codegen
            compile-error-if-not-enough-arguments
            compile-in-env
            compile-lambda-function
            compile-lambda-list-code
            make-calling-convention
            compiler-error
            compiler-warn
            compiler-style-warn
            define-primitive
            warn-undefined-global-variable
            warn-undefined-type
            warn-cannot-coerce
            warn-invalid-number-type
            warn-icsp-iesp-both-specified
            register-global-function-def
            register-global-function-ref
            safe-system
            jit-constant-uintptr_t
            irc-sext
            irc-zext
            irc-int-to-ptr
            irc-ptr-to-int
            irc-verify-module-safe
            irc-verify-function
            *suppress-llvm-output*
            *optimization-level*
            with-track-llvm-time
            irc-add
            irc-sub
            irc-add-clause
            alloca
            alloca-t*
            alloca-i8
            alloca-i8*
            alloca-i32
            alloca-size_t
            alloca-return
            alloca-vaslist
            alloca-temp-values
            alloca-arguments
            irc-and
            irc-or
            irc-xor
            irc-not
            irc-basic-block-create
            irc-begin-block
            irc-br
            irc-branch-to-and-begin-block
            irc-cond-br
            irc-call-or-invoke
            irc-intrinsic-call
            irc-intrinsic-invoke
            irc-bit-cast
            irc-pointer-cast
            irc-maybe-cast-integer-to-t*
            irc-create-invoke-default-unwind
            irc-create-landing-pad
            irc-exception-typeid*
            irc-extract-value
            irc-gep
            irc-gep-variable
            irc-smart-ptr-extract
            irc-set-insert-point-basic-block
            irc-size_t-*current-source-pos-info*-filepos
            irc-size_t-*current-source-pos-info*-column
            irc-size_t-*current-source-pos-info*-lineno
            irc-icmp-eq
            irc-icmp-sle
            irc-icmp-slt
            irc-icmp-sge
            irc-icmp-sgt
            irc-intrinsic
            irc-load
            irc-load-atomic
            irc-low-level-trace
            irc-phi
            irc-personality-function
            irc-phi-add-incoming
            irc-renv
            irc-ret-void
            irc-ret-null-t*
            irc-ret
            irc-undef-value-get
            irc-store
            irc-store-atomic
            irc-cmpxchg
            irc-struct-gep
            vaslist-start
            irc-read-slot
            irc-write-slot
            irc-make-tmv
            irc-tmv-primary
            irc-tmv-nret
            irc-t*-result
            irc-tmv-result
            irc-make-valvec
            irc-valvec-nvals
            irc-valvec-values
            irc-header-stamp
            irc-rack-stamp
            irc-wrapped-stamp
            irc-derivable-stamp
            irc-switch
            irc-add-case
            irc-tag-fixnum
            irc-trunc
            irc-unreachable
            irc-untag-fixnum
            irc-untag-general
            irc-untag-cons
            irc-unbox-single-float
            irc-box-single-float
            irc-unbox-double-float
            irc-box-double-float
            irc-fdefinition
            irc-setf-fdefinition
            irc-real-array-displacement
            irc-real-array-index-offset
            irc-array-total-size
            irc-array-rank
            gen-%array-dimension
            irc-vaslist-nargs-address
            gen-instance-rack
            gen-instance-rack-set
            gen-rack-ref
            gen-rack-set
            gen-vaslist-pop
            gen-vaslist-length
            jit-constant-i1
            jit-constant-i8
            jit-constant-i32
            jit-constant-i64
            *default-function-attributes*
            ensure-jit-constant-i64
            jit-constant-size_t
            jit-constant-unique-string-ptr
            jit-function-name
            module-make-global-string
            make-boot-function-global-variable
            llvm-link
            load-bitcode
            setup-calling-convention
            initialize-calling-convention
            ensure-cleavir-lambda-list
            ensure-cleavir-lambda-list-analysis
            process-cleavir-lambda-list-analysis
            cleavir-lambda-list-analysis-cleavir-lambda-list
            cleavir-lambda-list-analysis-rest
            process-bir-lambda-list
            treat-as-special-operator-p
            typeid-core-unwind
            with-begin-end-catch
            preserve-exception-info
            *dbg-generate-dwarf*
            *dbg-current-function-metadata*
            *dbg-current-function-lineno*
            *dbg-current-scope*
            with-new-function
            with-guaranteed-*current-source-pos-info*
            with-dbg-function
            with-dbg-lexical-block
            dbg-variable-alloca
            dbg-variable-value
            compile-file-source-pos-info
            compile-file-serial
            compile-file-parallel
            c++-field-offset
            c++-field-index
            c++-struct-type
            c++-struct*-type
            c++-field-ptr
            %closure-with-slots%.offset-of[n]/t*
            with-try
            with-new-function-prepare-for-try
            with-debug-info-generator
            with-irbuilder
            with-landing-pad
            bclasp-compile
            make-uintptr_t
            +cons-car-offset+
            +cons-cdr-offset+
            +simple-vector._length-offset+
            +entry-point-arity-begin+
            +entry-point-arity-end+
            +number-of-entry-points+
            %uintptr_t%
            %return-type%
            %vaslist%
            null-t-ptr
            compile-error-if-too-many-arguments
            *irbuilder-function-alloca*
            irc-calculate-call-info
            %RUN-AND-LOAD-TIME-VALUE-HOLDER-GLOBAL-VAR-TYPE%
            compute-rest-alloc
            compile-tag-check
            compile-header-check
            ensure-xep-function-not-placeholder
            general-entry-point-redirect-name
            get-or-declare-function-or-error
            )))

;;; exports for runall
(export '(
          with-make-new-run-all
          with-run-all-entry-codegen
          with-run-all-body-codegen
          generate-load-time-values
          ))

;;; exports for conditions
(export '(deencapsulate-compiler-condition
          *default-condition-origin*
          compiler-condition-origin
          compiled-program-error
          compiler-condition
          undefined-variable-warning
          undefined-function-warning
          undefined-type-warning
          redefined-function-warning
          wrong-argcount-warning
          compiler-macro-expansion-error-warning
          fold-failure))

(in-package :literal)

(export '(
          *byte-codes*
          add-creator
          next-value-table-holder-name
          general-entry-placeholder-p
          ensure-not-placeholder
          make-general-entry-placeholder
          make-literal-node-call
          make-literal-node-creator
          setup-literal-machine-function-vectors
          run-all-add-node
          entry-point-datum-for-xep-group
          register-local-function-index
          register-xep-function-indices
          literal-node-runtime-p
          literal-node-runtime-object
          literal-node-closure-p
          literal-node-creator-p
          literal-node-creator-object
          literal-node-creator-name
          literal-node-creator-arguments
          literal-node-side-effect-p
          literal-node-side-effect-name
          literal-node-side-effect-arguments
          literal-node-call-p
          literal-node-call-function
          literal-node-call-source-pos-info
          literal-node-call-holder
          lookup-literal-index
          reference-literal
          load-time-reference-literal
          codegen-rtv-bclasp
          codegen-rtv-cclasp
          codegen-literal
          codegen-quote
          compile-reference-to-literal
          ltv-global
          compile-load-time-value-thunk
          new-table-index
          constants-table-reference
          constants-table-value
          load-time-value-from-thunk
          with-rtv
          arrange-thunk-as-top-level
          with-literal-table
          generate-run-time-code-for-closurette))

(in-package :clasp-ffi)
(export '(with-foreign-object
          with-foreign-objects
          %foreign-alloc
          %foreign-free
          %mem-ref
          %mem-set
          %foreign-funcall
          %foreign-funcall-pointer
          %load-foreign-library
          %close-foreign-library
          %foreign-symbol-pointer
          %foreign-type-size
          %foreign-type-alignment
          %defcallback
          %callback
          %get-callback
          safe-translator-type))

(use-package :literal :cmp)
