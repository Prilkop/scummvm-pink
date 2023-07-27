#include "csequenceaudio.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"

namespace Pink {

	CSequenceAudio::CSequenceAudio() : sound(NULL) {
	}

	CSequenceAudio::~CSequenceAudio() {
	}

	void CSequenceAudio::deserialize(CArchive &archive) {
		this->CSequence::deserialize(archive);
		sound = archive.readCString();
	}

};