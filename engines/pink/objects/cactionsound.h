#ifndef PINK_CACTIONSOUND_H
#define PINK_CACTIONSOUND_H

#include "common/scummsys.h"
#include "audio/mixer.h"
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

		virtual void init(PinkEngine *pink);

		Common::String *sound;
		uint32 volume;
		bool loop;
		bool background;

	private:
		Audio::SoundHandle _handle;
	};

};

#endif //PINK_CACTIONSOUND_H
