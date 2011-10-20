#ifndef PINK_CSEQUENCE_H
#define PINK_CSEQUENCE_H

#include "common/scummsys.h"
#include "cnamedobject.h"

namespace Common {
	template<class T> class Array;
}

namespace Pink {
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

		CSequencer *sequencer;
		Common::Array<CObject *> *items;
	};

};

#endif //PINK_CSEQUENCE_H
