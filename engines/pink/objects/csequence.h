#ifndef PINK_CSEQUENCE_H
#define PINK_CSEQUENCE_H

#include "common/scummsys.h"
#include "cnamedobject.h"

namespace Common {
	template<class T> class Array;
}

namespace Pink {
	class PinkEngine;
	class CSequencer;
}

namespace Pink {

	class CSequence : public CNamedObject {
	public:
		CSequence();
		virtual ~CSequence();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		virtual void init(PinkEngine *pink);
		virtual void execute(PinkEngine *pink);

		CSequencer *sequencer;
		Common::Array<CObject *> *items;

	private:
		uint _next_item_index;
	};

};

#endif //PINK_CSEQUENCE_H
