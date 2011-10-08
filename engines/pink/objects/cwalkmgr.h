#ifndef PINK_CWALKMGR_H
#define PINK_CWALKMGR_H

#include "common\scummsys.h"
#include "cobject.h"

namespace Common {
	template<class T> class Array;
}

namespace Pink {
	class CLeadActor;
}

namespace Pink {

	class CWalkMgr : public CObject {
	public:
		CWalkMgr();
		virtual ~CWalkMgr();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		CLeadActor *getLeadActor();
		CObject *getLocation(uint32 index);

	private:
		CLeadActor *lead_actor;
		Common::Array<CObject *> *locations;
	};

};

#endif //PINK_CWALKMGR_H
