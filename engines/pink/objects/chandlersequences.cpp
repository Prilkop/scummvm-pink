#include "chandlersequences.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"

namespace Pink {
	CHandlerSequences::CHandlerSequences() : sequences(NULL) {
	}

	CHandlerSequences::~CHandlerSequences() {
	}

	void CHandlerSequences::deserialize(CArchive &archive) {
		this->CHandler::deserialize(archive);
		sequences = archive.readCStringArray();
	}

};