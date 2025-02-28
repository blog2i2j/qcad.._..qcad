// ***** AUTOGENERATED CODE, DO NOT EDIT *****
            // ***** This class is not copyable.
        
        #ifndef RECMACLIPBOARDOPERATION_H
        #define RECMACLIPBOARDOPERATION_H

        #include "ecmaapi_global.h"

        #include <QScriptEngine>
        #include <QScriptValue>
        #include <QScriptContextInfo>
        #include <QDebug>

        
                #include "RClipboardOperation.h"
            

        /**
         * \ingroup scripting_ecmaapi
         */
        class
        
        QCADECMAAPI_EXPORT
        REcmaClipboardOperation {

        public:
      static  void initEcma(QScriptEngine& engine, QScriptValue* proto 
    =NULL
    ) 
    ;static  QScriptValue createEcma(QScriptContext* context, QScriptEngine* engine) 
    ;

    // conversion functions for base classes:
    static  QScriptValue getROperation(QScriptContext *context,
            QScriptEngine *engine)
        ;static  QScriptValue getRRequireHeap(QScriptContext *context,
            QScriptEngine *engine)
        ;

    // returns class name:
    static  QScriptValue getClassName(QScriptContext *context, QScriptEngine *engine) 
        ;

    // returns all base classes (in case of multiple inheritance):
    static  QScriptValue getBaseClasses(QScriptContext *context, QScriptEngine *engine) 
        ;

    // properties:
    

    // public methods:
    static  QScriptValue
        apply
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        copy
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        copyEntity
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        copyEntityBlock
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        copyBlock
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        copyEntityLayer
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        copyLayer
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        copyEntityLinetype
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        copyLinetype
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setCopyEmptyBlocks
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setCopyAllLayers
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setKeepSelection
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setBlockOwnership
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        setCustomEntityType
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue
        createBlockReferenceEntity
        (QScriptContext* context, QScriptEngine* engine) 
        ;static  QScriptValue toString
    (QScriptContext *context, QScriptEngine *engine)
    ;static  QScriptValue destroy(QScriptContext *context, QScriptEngine *engine)
    ;static RClipboardOperation* getSelf(const QString& fName, QScriptContext* context)
    ;static RClipboardOperation* getSelfShell(const QString& fName, QScriptContext* context)
    ;};
    #endif
    