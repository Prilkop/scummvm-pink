#ifndef PINK_CACTIONSTILL_H
#define PINK_CACTIONSTILL_H

#include "common\scummsys.h"
#include "cactioncel.h"

namespace Pink {

	class CActionStill : public CActionCEL {
	public:
		CActionStill();
		virtual ~CActionStill();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		int32 startFrame;
	};

};

#endif //PINK_CACTIONSTILL_H
