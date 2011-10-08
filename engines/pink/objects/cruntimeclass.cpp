#include "cruntimeclass.h"
#include "common/scummsys.h"

#include "cobject.h"

namespace Pink {

	CObject *CRuntimeClass::createObject() {
		return _createObject();
	}

	CRuntimeClass *CRuntimeClass::getRuntimeClassByName(const char *name) {
		for (uint32 i = 0; i < runtimeclassesCount; i++) {
			CRuntimeClass *runtimeclass = &runtimeclasses[i];
			if (strcmp(name, runtimeclass->getName()) == 0)
				return runtimeclass;
		}
		return NULL;
	}

	bool CRuntimeClass::isInstance(CObject *obj) {
		const CRuntimeClass *runtimeclass = obj->getRuntimeClass();
		while(runtimeclass != NULL && runtimeclass != this) {
			runtimeclass = runtimeclass->getBaseClass();
		}

		return runtimeclass;
	}
}