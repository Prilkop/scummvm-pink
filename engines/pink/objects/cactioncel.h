#ifndef PINK_CACTIONCEL_H
#define PINK_CACTIONCEL_H

#include "common\scummsys.h"
#include "caction.h"

namespace Common {
	class String;
}

namespace Pink {

	class CActionCEL : public CAction {;
	public:
		CActionCEL();
		virtual ~CActionCEL();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		Common::String *cel;
		uint32 z;
	};

};

#endif //PINK_CACTIONCEL_H
