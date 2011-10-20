#ifndef PINK_CCURSORMGR_H
#define PINK_CCURSORMGR_H

#include "common/scummsys.h"
#include "cobject.h"

namespace Pink {

	class CCursorMgr : public CObject {
	public:
		//CCursorMgr();
		//virtual ~CCursorMgr();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		//virtual void deserialize(CArchive &archive);


	};

};

#endif //PINK_CCURSORMGR_H
