#include "cgamepage.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"
#include "common/array.h"

#include "ccursormgr.h"
#include "cwalkmgr.h"
#include "csequencer.h"
#include "cmodule.h"
#include "cleadactor.h"

namespace Pink {

	CGamePage::CGamePage() : cursor_manager(NULL), walk_manager(NULL), 
			sequencer(NULL), lead_actor(NULL), handlers(NULL) {
		cursor_manager = new CCursorMgr();
		walk_manager = new CWalkMgr();
		sequencer = new CSequencer();
	}

	CGamePage::~CGamePage() {
		delete cursor_manager;
		delete walk_manager;
		delete sequencer;
		delete lead_actor;
		delete handlers;
	}

	void CGamePage::deserialize(CArchive &archive) {
		this->CNamedObject::deserialize(archive);
		_module = (CModule *)archive.readCObject();
	}

	void CGamePage::readFromOrb(CArchive &archive) {
		archive.mapObject(cursor_manager);
		archive.mapObject(walk_manager);
		archive.mapObject(sequencer);

		this->CPage::readFromOrb(archive);

		lead_actor = (CLeadActor *)archive.readCObject();
		cursor_manager->deserialize(archive);
		walk_manager->deserialize(archive);
		sequencer->deserialize(archive);
		handlers = archive.readCObArray();
	}

};