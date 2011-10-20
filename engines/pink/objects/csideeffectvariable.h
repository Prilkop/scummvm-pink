#ifndef PINK_CSIDEEFFECTVARIABLE_H
#define PINK_CSIDEEFFECTVARIABLE_H

#include "common/scummsys.h"
#include "csideeffect.h"

namespace Common {
	class String;
}

namespace Pink {

	class CSideEffectVariable : public CSideEffect {
	public:
		CSideEffectVariable();
		virtual ~CSideEffectVariable();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

	private:
		Common::String *variable;
		Common::String *value;
	};

};

#endif //PINK_CSIDEEFFECTVARIABLE_H
