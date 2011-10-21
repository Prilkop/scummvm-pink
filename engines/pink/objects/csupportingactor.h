#ifndef PINK_CSUPPORTINGACTOR_H
#define PINK_CSUPPORTINGACTOR_H

#include "common/scummsys.h"
#include "cactor.h"

namespace Common {
	class String;
}

namespace Pink {
	class CHandlerMgr;
}

namespace Pink {

	class CSupportingActor : public CActor {
	public:
		CSupportingActor();
		virtual ~CSupportingActor();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		Common::String *location;
		Common::String *pda_link;
		Common::String *cursor;
		CHandlerMgr *handler_manager;
	};

};

#endif //PINK_CSUPPORTINGACTOR_H
