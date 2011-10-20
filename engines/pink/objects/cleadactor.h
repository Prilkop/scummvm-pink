#ifndef PINK_CLEADACTOR_H
#define PINK_CLEADACTOR_H

#include "common/scummsys.h"
#include "cactor.h"

namespace Pink {
	class CCursorMgr;
	class CWalkMgr;
	class CSequencer;
}

namespace Pink {

	class CLeadActor : public CActor {
	public:
		CLeadActor();
		virtual ~CLeadActor();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		CCursorMgr *cursor_manager;
		CWalkMgr *walk_manager;
		CSequencer *sequencer;
	};

};

#endif //PINK_CLEADACTOR_H
