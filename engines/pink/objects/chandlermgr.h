#ifndef PINK_CHANDLERMGR_H
#define PINK_CHANDLERMGR_H

#include "common\scummsys.h"
#include "cobject.h"

namespace Common {
	template<class T> class Array;
}

namespace Pink {
	class CHandler;
}

namespace Pink {

	class CHandlerMgr : public CObject {
	public:
		CHandlerMgr();
		virtual ~CHandlerMgr();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		Common::Array<CObject *>*left_click_handlers;
		Common::Array<CObject *>*use_click_handlers;
		Common::Array<CObject *>*timer_handlers;
	};

};

#endif //PINK_CHANDLERMGR_H
