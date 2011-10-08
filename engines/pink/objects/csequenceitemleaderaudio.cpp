#include "csequenceitemleaderaudio.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"

#include "csequenceitemleader.h"

namespace Pink {

	CSequenceItemLeaderAudio::CSequenceItemLeaderAudio() : sample(0) {
	}

	CSequenceItemLeaderAudio::~CSequenceItemLeaderAudio() {
	}

	void CSequenceItemLeaderAudio::deserialize(CArchive &archive) {
		this->CSequenceItemLeader::deserialize(archive);
		sample = archive.readDWORD();
	}

};