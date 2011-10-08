#ifndef PINK_CMODULE_H
#define PINK_CMODULE_H

#include "common/str.h"
#include "cnamedobject.h"

namespace Common {
	class String;
	template<class T> class Array;
}

namespace Pink {
	class CPage;
}

namespace Pink {

	class CModule : public CNamedObject {
	public:
		CModule();
		virtual ~CModule();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		Common::String *directory;
		Common::Array<CObject *> *inv;
		Common::Array<CPage *> *pages;
	};

};

#endif //PINK_CMODULE_H
