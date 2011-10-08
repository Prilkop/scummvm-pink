#include "chandlermgr.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"
#include "common/array.h"

#include "chandler.h"

namespace Pink {

	CHandlerMgr::CHandlerMgr() : left_click_handlers(NULL),
		use_click_handlers(NULL), timer_handlers(NULL) {
	}


	CHandlerMgr::~CHandlerMgr() {
		delete left_click_handlers;
		delete use_click_handlers;
		delete timer_handlers;
	}

	void CHandlerMgr::deserialize(CArchive &archive) {
		left_click_handlers = archive.readCObArray();
		use_click_handlers = archive.readCObArray();
		timer_handlers = archive.readCObArray();
	}

};