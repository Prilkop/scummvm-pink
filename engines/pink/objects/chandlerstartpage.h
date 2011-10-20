#ifndef PINK_CHANDLERSTARTPAGE_H
#define PINK_CHANDLERSTARTPAGE_H

#include "common/scummsys.h"
#include "chandlersequences.h"

namespace Pink {

	class CHandlerStartPage : public CHandlerSequences {
	public:
		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

	private:
	};

};

#endif //PINK_CHANDLERSTARTPAGE_H
