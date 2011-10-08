#ifndef PINK_CSEQUENCEITEM_H
#define PINK_CSEQUENCEITEM_H

#include "common\scummsys.h"
#include "cobject.h"

namespace Common {
	class String;
}

namespace Pink {

	class CSequenceItem : public CObject {
	public:
		CSequenceItem();
		virtual ~CSequenceItem();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		Common::String *actor;
		Common::String *action;
	};

};

#endif //PINK_CSEQUENCEITEM_H
