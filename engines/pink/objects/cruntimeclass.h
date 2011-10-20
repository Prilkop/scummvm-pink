#include "common/scummsys.h"

namespace Pink {
	class CObject;
}

namespace Pink {

	typedef CObject *(*createObjectMethod)();

	class CRuntimeClass {
	public:
		const char *getName() const { return _name; };
		const CRuntimeClass *getBaseClass() const { return _baseClass; };
		CObject *createObject();
		bool isInstance(CObject *obj);

		static CRuntimeClass *registerRuntimeClasses();
		static CRuntimeClass *getRuntimeClassByName(const char *name);
		static CRuntimeClass runtimeclasses[];
		static uint32 runtimeclassesCount;

		const char *_name;
		createObjectMethod _createObject;
		const CRuntimeClass *_baseClass;
	};

}
