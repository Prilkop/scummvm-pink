#ifndef PINK_CNAMEDOBJECT_H
#define PINK_CNAMEDOBJECT_H

#include "cobject.h"

namespace Common {
	class String;
}

namespace Pink {

	class CNamedObject : public CObject {
	public:
		CNamedObject();
		virtual ~CNamedObject();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		Common::String *name;
	};

};

#endif //PINK_CNAMEDOBJECT_H
