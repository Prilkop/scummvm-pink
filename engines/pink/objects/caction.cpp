#include "caction.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"

#include "cactor.h"

namespace Pink {

	CAction::CAction() : actor(NULL) {
	}

	CAction::~CAction() {
		delete actor;
	}

	void CAction::deserialize(CArchive &archive) {
		this->CNamedObject::deserialize(archive);
		actor = (CActor *)archive.readCObject();
	}

};