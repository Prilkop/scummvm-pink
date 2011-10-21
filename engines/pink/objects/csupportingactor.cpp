#include "csupportingactor.h"
#include "carchive.h"

#include "common/str.h"

#include "chandlermgr.h"

namespace Pink {

	CSupportingActor::CSupportingActor() : handler_manager(NULL) {
	}

	CSupportingActor::~CSupportingActor() {
		delete location;
		delete pda_link;
		delete cursor;
		delete handler_manager;
	}

	void CSupportingActor::deserialize(CArchive &archive) {
		this->CActor::deserialize(archive);
		location = archive.readCString();
		pda_link = archive.readCString();
		cursor = archive.readCString();
		handler_manager = (CHandlerMgr *)archive.readCObject();
	}

};