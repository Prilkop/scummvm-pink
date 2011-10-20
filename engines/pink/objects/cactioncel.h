#ifndef PINK_CACTIONCEL_H
#define PINK_CACTIONCEL_H

#include "common/scummsys.h"
#include "caction.h"

namespace Common {
	class String;
}

namespace Video {
	class FlicDecoder;
}

namespace Pink {
	class PinkEngine;
}

namespace Pink {

	class CActionCEL : public CAction {
	public:
		CActionCEL();
		virtual ~CActionCEL();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		virtual void init(PinkEngine *pink);
		virtual void execute(PinkEngine *pink);
		virtual void destroy(PinkEngine *pink);

		virtual void draw(PinkEngine *pink);

		Common::String *cel;
		uint32 z;

	private:
		Video::FlicDecoder *decoder;
	};

};

#endif //PINK_CACTIONCEL_H
