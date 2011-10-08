#include "objects/cruntimeclass.h"

#define IMPLEMENT_RUNTIME_CLASS(index, cls) \
		CObject *cls::createObject() { \
			return new cls(); \
		} \
		\
		CRuntimeClass *cls::getRuntimeClass() { \
			return &CRuntimeClass::runtimeclasses[index]; \
		} \
		\
		CRuntimeClass *cls::RuntimeClass() { \
			return &CRuntimeClass::runtimeclasses[index]; \
		}

#define REGISTER_RUNTIME_CLASS(cls, base_runtimeclass) {#cls, (createObjectMethod)cls::createObject, base_runtimeclass}
