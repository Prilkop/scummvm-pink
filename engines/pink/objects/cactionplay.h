#ifndef PINK_CACTIONPLAY_H
#define PINK_CACTIONPLAY_H

#include "common\scummsys.h"
#include "cactionstill.h"

namespace Pink {

	class CActionPlay : public CActionStill {
	public:
		CActionPlay();
		virtual ~CActionPlay();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		int32 stopFrame;
	};

};

#endif //PINK_CACTIONPLAY_H
