#ifndef PINK_CHANDLER_H
#define PINK_CHANDLER_H

#include "common/scummsys.h"
#include "cobject.h"

namespace Common {
	template<class T> class Array;
}

namespace Pink {
	class CCondition;
	class CSideEffect;
}

namespace Pink {

	class CHandler : public CObject {
	public:
		CHandler();
		virtual ~CHandler();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		Common::Array<CObject *>*conditions;
		Common::Array<CObject *>*side_effects;
	};

};

#endif //PINK_CHANDLER_H
