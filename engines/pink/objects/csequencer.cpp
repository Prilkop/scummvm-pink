#include "csequencer.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"
#include "common/array.h"

#include "csequence.h"

namespace Pink {

	CSequencer::CSequencer() : sequences(NULL), timers(NULL) {
	}


	CSequencer::~CSequencer() {
		delete sequences;
		delete timers;
	}

	void CSequencer::deserialize(CArchive &archive) {
		sequences = archive.readCObArray();
		timers = archive.readCObArray();
	}

};