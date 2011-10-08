#include "chandler.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"
#include "common/array.h"

namespace Pink {

	CHandler::CHandler() : conditions(NULL), side_effects(NULL) {
	}


	CHandler::~CHandler() {
		delete conditions;
		delete side_effects;
	}

	void CHandler::deserialize(CArchive &archive) {
		conditions = archive.readCObArray();
		side_effects = archive.readCObArray();
	}

};