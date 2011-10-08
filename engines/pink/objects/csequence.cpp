#include "csequence.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"
#include "common/array.h"

#include "csequencer.h"

namespace Pink {

	CSequence::CSequence() : sequencer(NULL), items(NULL) {
	}

	CSequence::~CSequence() {
		delete items;
	}

	void CSequence::deserialize(CArchive &archive) {
		this->CNamedObject::deserialize(archive);
		sequencer = (CSequencer *)archive.readCObject();
		items = archive.readCObArray();
	}

};