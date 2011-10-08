#ifndef PINK_CACTION_H
#define PINK_CACTION_H

#include "common\scummsys.h"
#include "cnamedobject.h"

namespace Pink {
	class CActor;
}

namespace Pink {

	class CAction : public CNamedObject {
	public:
		CAction();
		virtual ~CAction();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		CActor *actor;
	};

};

#endif //PINK_CACTION_H
