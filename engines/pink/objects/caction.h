#ifndef PINK_CACTION_H
#define PINK_CACTION_H

#include "common/scummsys.h"
#include "cnamedobject.h"

namespace Pink {
	class PinkEngine;
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

		virtual void init(PinkEngine *pink) {};
		virtual void execute(PinkEngine *pink) {};
		virtual void destroy(PinkEngine *pink) {};

		CActor *actor;
	};

};

#endif //PINK_CACTION_H
