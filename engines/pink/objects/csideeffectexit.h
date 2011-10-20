#ifndef PINK_CSIDEEFFECTEXIT_H
#define PINK_CSIDEEFFECTEXIT_H

#include "common/scummsys.h"
#include "csideeffect.h"

namespace Common {
	class String;
}

namespace Pink {

	class CSideEffectExit : public CSideEffect {
	public:
		CSideEffectExit();
		virtual ~CSideEffectExit();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		const char *getNextModule();
		const char *getNextPage();

	private:
		Common::String *next_module;
		Common::String *next_page;
	};

};

#endif //PINK_CSIDEEFFECTEXIT_H
