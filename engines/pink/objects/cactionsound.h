#ifndef PINK_CACTIONSOUND_H
#define PINK_CACTIONSOUND_H

#include "common/scummsys.h"
#include "caction.h"

namespace Common {
	class String;
}

namespace Pink {

	class CActionSound : public CAction {
	public:
		CActionSound();
		virtual ~CActionSound();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		Common::String *sound;
		uint32 volume;
		bool loop;
		bool background;
	};

};

#endif //PINK_CACTIONSOUND_H
