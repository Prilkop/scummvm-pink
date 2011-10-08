#ifndef PINK_CGAME_H
#define PINK_CGAME_H

#include "common/scummsys.h"
#include "common/array.h"

#include "cobject.h"

namespace Common {
	class String;
	template<class T> class Array;
}

namespace Pink {
	class CModuleProxy;
}

namespace Pink {

	class CGame : public CObject {
	public:
		CGame();
		virtual ~CGame();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		Common::String *path;
		Common::String *ini;
		Common::Array<CModuleProxy *> *modules;
	};

};

#endif //PINK_CGAME_H
