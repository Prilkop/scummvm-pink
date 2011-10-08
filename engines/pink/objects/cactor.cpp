#include "cactor.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"
#include "common/array.h"

#include "cpage.h"
#include "caction.h"

namespace Pink {

	CActor::CActor() : page(NULL), actions(NULL) {
	}

	CActor::~CActor() {
		delete page;
		delete actions;
	}

	void CActor::deserialize(CArchive &archive) {
		this->CNamedObject::deserialize(archive);
		page = (CPage *)archive.readCObject();
		actions = (Common::Array<CAction *> *)archive.readCObArray(CAction::RuntimeClass());
	}

};