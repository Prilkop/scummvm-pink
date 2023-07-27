#ifndef PINK_CSEQUENCEAUDIO_H
#define PINK_CSEQUENCEAUDIO_H

#include "common/scummsys.h"
#include "csequence.h"

namespace Common {
	class String;
}

namespace Pink {

	class CSequenceAudio : public CSequence {
	public:
		CSequenceAudio();
		virtual ~CSequenceAudio();

		static CObject *createObject();
		static CRuntimeClass *RuntimeClass();
		virtual CRuntimeClass *getRuntimeClass();

		virtual void deserialize(CArchive &archive);

		Common::String *sound;
	private:
	};

};

#endif //PINK_CSEQUENCEAUDIO_H
