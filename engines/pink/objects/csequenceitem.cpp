#include "csequenceitem.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"

namespace Pink {

	CSequenceItem::CSequenceItem() : actor(NULL), action(NULL) {
	}

	CSequenceItem::~CSequenceItem() {
		delete actor;
		delete action;
	}

	void CSequenceItem::deserialize(CArchive &archive) {
		actor = archive.readCString();
		action = archive.readCString();
	}
};