#include "csequencer.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"
#include "common/array.h"
#include "pink/pink.h"

#include "csequence.h"


namespace Pink {

	CSequencer::CSequencer() : sequences(NULL), timers(NULL), _current_sequence(NULL) {
	}


	CSequencer::~CSequencer() {
		delete sequences;
		delete timers;
	}

	void CSequencer::deserialize(CArchive &archive) {
		sequences = archive.readCObArray(CSequence::RuntimeClass());
		timers = archive.readCObArray();

		_current_sequence = (CSequence *)*(sequences->begin());
	}

	void CSequencer::init(PinkEngine *pink) {
		_current_sequence->init(pink);
	}

	void CSequencer::execute(PinkEngine *pink) {

	}

};