#include "cwalkmgr.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"
#include "common/array.h"

#include "cleadactor.h"

namespace Pink {

	CWalkMgr::CWalkMgr() : lead_actor(NULL), locations(NULL) {
	}


	CWalkMgr::~CWalkMgr() {
		delete lead_actor;
		delete locations;
	}

	void CWalkMgr::deserialize(CArchive &archive) {
		lead_actor = (CLeadActor *)archive.readCObject();
		locations = archive.readCObArray();
	}

};