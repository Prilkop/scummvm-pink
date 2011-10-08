#ifndef PINK_CPAGE_H
#define PINK_CPAGE_H

#include "common/str.h"
#include "cnamedobject.h"

namespace Common {
	class String;
	template<class T> class Array;
}

namespace Pink {
	class CActor;
}

namespace Pink {

	class CPage : public CNamedObject {
	public:
		CPage();
		virtual ~CPage();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);
		virtual void readFromOrb(CArchive &archive);

		Common::String *directory;
		Common::Array<CActor *> *actors;
	};

};

#endif //PINK_CPAGE_H
