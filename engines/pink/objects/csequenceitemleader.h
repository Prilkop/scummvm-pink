#ifndef PINK_CSEQUENCEITEMLEADER_H
#define PINK_CSEQUENCEITEMLEADER_H

#include "common/scummsys.h"
#include "csequenceitem.h"

namespace Pink {

	class CSequenceItemLeader : public CSequenceItem {
	public:
		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

	private:
	};

};

#endif //PINK_CSEQUENCEITEMLEADER_H
