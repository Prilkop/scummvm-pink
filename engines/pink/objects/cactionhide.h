#ifndef PINK_CACTIONHIDE_H
#define PINK_CACTIONHIDE_H

#include "common/scummsys.h"
#include "caction.h"

namespace Pink {

	class CActionHide : public CAction {
	public:
		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

	private:
	};

};

#endif //PINK_CACTIONHIDE_H
