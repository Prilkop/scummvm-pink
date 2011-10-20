#ifndef PINK_CACTOR_H
#define PINK_CACTOR_H

#include "common/scummsys.h"
#include "common/hash-str.h"

#include "cnamedobject.h"

namespace Common {
	template<class T> class Array;
}

namespace Pink {
	class PinkEngine;
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

		virtual void init(PinkEngine *pink);
		virtual void execute(PinkEngine *pink);
		virtual void destroy(PinkEngine *pink);
		
		virtual CAction *getAction(const Common::String &name);

		CAction *getCurrentAction();
		void setCurrentAction(const Common::String &name);

		CPage *page;
		Common::Array<CAction *>*actions;

	private:
		Common::HashMap<Common::String, CAction *> _actions_map;
		CAction *_current_action;
	};

};

#endif //PINK_CACTOR_H
