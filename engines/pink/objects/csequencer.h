#ifndef PINK_CSEQUENCER_H
#define PINK_CSEQUENCER_H

#include "common\scummsys.h"
#include "cobject.h"

namespace Common {
	template<class T> class Array;
}

namespace Pink {
	class CSequence;
	class CPage;
}

namespace Pink {

	class CSequencer : public CObject {
	public:
		CSequencer();
		virtual ~CSequencer();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		Common::Array<CObject *> *sequences;
		Common::Array<CObject *> *timers;
		CPage *page;
	};

};

#endif //PINK_CSEQUENCER_H
