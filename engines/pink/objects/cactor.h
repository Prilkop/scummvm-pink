#ifndef PINK_CACTOR_H
#define PINK_CACTOR_H

#include "common\scummsys.h"
#include "cnamedobject.h"

namespace Common {
	template<class T> class Array;
}

namespace Pink {
	class CPage;
	class CAction;
}

namespace Pink {

	class CActor : public CNamedObject {
	public:
		CActor();
		virtual ~CActor();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		CPage *page;
		Common::Array<CAction *>*actions;
	};

};

#endif //PINK_CACTOR_H
