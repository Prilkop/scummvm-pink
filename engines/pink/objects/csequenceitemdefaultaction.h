#ifndef PINK_CSEQUENCEITEMDEFAULTACTION_H
#define PINK_CSEQUENCEITEMDEFAULTACTION_H

#include "common\scummsys.h"
#include "csequenceitem.h"

namespace Pink {

	class CSequenceItemDefaultAction : public CSequenceItem {
	public:
		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

	private:
	};

};

#endif //PINK_CSEQUENCEITEMDEFAULTACTION_H
