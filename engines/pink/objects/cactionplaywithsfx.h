#ifndef PINK_CACTIONPLAYWITHSFX_H
#define PINK_CACTIONPLAYWITHSFX_H

#include "common/scummsys.h"
#include "cactionplay.h"

namespace Common {
	template<class T> class Array;
}

namespace Pink {

	class CActionPlayWithSfx : public CActionPlay {
	public:
		CActionPlayWithSfx();
		virtual ~CActionPlayWithSfx();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		int loop;
		Common::Array<CObject *> *sfx;
	};

};

#endif //PINK_CACTIONPLAYWITHSFX_H
