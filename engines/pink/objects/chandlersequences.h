#ifndef PINK_CHANDLERSEQUENCES_H
#define PINK_CHANDLERSEQUENCES_H

#include "common/scummsys.h"
#include "chandler.h"

namespace Common {
	class String;
}

namespace Pink {

	class CHandlerSequences : public CHandler {
	public:
		CHandlerSequences();
		virtual ~CHandlerSequences();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		Common::Array<Common::String *> *sequences;
	};

};

#endif //PINK_CHANDLERSEQUENCES_H
