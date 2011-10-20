#ifndef PINK_CSEQUENCER_H
#define PINK_CSEQUENCER_H

#include "common/scummsys.h"
#include "cobject.h"

namespace Common {
	template<class T> class Array;
}

namespace Pink {
	class PinkEngine;
	class CSequence;
	class CGamePage;
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

		virtual void init(PinkEngine *pink);
		virtual void execute(PinkEngine *pink);

		Common::Array<CObject *> *sequences;
		Common::Array<CObject *> *timers;
		CGamePage *page;

	private:
		CSequence *_current_sequence;
	};

};

#endif //PINK_CSEQUENCER_H
