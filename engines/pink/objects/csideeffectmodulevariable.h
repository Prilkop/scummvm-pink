#ifndef PINK_CSIDEEFFECTMODULEVARIABLE_H
#define PINK_CSIDEEFFECTMODULEVARIABLE_H

#include "common/scummsys.h"
#include "csideeffectvariable.h"

namespace Pink {

	class CSideEffectModuleVariable : public CSideEffectVariable {
	public:
		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

	private:
	};

};

#endif //PINK_CSIDEEFFECTMODULEVARIABLE_H
