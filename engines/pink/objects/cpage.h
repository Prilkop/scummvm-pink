#ifndef PINK_CPAGE_H
#define PINK_CPAGE_H

#include "common/str.h"
#include "common/hash-str.h"

#include "cnamedobject.h"

namespace Common {
	class String;
	template<class T> class Array;
}

namespace Pink {
	class PinkEngine;
	class CActor;
	class CLeadActor;
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

		virtual void init(PinkEngine *pink);
		virtual void execute(PinkEngine *pink);
		virtual void destroy(PinkEngine *pink);

		virtual CActor *getActor(const Common::String &name);

		Common::String *directory;
		Common::Array<CActor *> *actors;
		CLeadActor *lead_actor;

	private:
		Common::HashMap<Common::String, CActor *> _actors_map;
	};

};

#endif //PINK_CPAGE_H
