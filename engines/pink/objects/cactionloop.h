#ifndef PINK_CACTIONLOOP_H
#define PINK_CACTIONLOOP_H

#include "common/scummsys.h"
#include "cactionplay.h"

namespace Pink {

	class CActionLoop : public CActionPlay {
	public:
		CActionLoop();
		virtual ~CActionLoop();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		enum LoopStyle {
			Forward = 1,
			PingPong = 2,
			Random = 3
		};

		bool intro;
		LoopStyle style;
	};

};

#endif //PINK_CACTIONLOOP_H
