#ifndef PINK_CSIDEEFFECT_H
#define PINK_CSIDEEFFECT_H

#include "common\scummsys.h"
#include "cobject.h"

namespace Pink {

	class CSideEffect : public CObject {
	public:
		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

	private:
	};

};

#endif //PINK_CSIDEEFFECT_H
