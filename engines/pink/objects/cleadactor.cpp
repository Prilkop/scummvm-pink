#include "cleadactor.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"

#include "ccursormgr.h"
#include "cwalkmgr.h"
#include "csequencer.h"

namespace Pink {

	CLeadActor::CLeadActor() : cursor_manager(NULL), walk_manager(NULL), 
		sequencer(NULL) {
	}

	CLeadActor::~CLeadActor() {
	}

	void CLeadActor::deserialize(CArchive &archive) {
		this->CActor::deserialize(archive);
		cursor_manager = (CCursorMgr *)archive.readCObject();
		walk_manager = (CWalkMgr *)archive.readCObject();
		sequencer = (CSequencer *)archive.readCObject();
	}

};