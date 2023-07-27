#include "csupportingactor.h"
#include "carchive.h"

#include "common/str.h"

#include "chandlermgr.h"

namespace Pink {

	CSupportingActor::CSupportingActor() : location(NULL), pda_link(NULL), cursor(NULL) {
	}

	CSupportingActor::~CSupportingActor() {
		delete location;
		delete pda_link;
		delete cursor;
	}

	void CSupportingActor::deserialize(CArchive &archive) {
		this->CActor::deserialize(archive);
		location = archive.readCString();
		pda_link = archive.readCString();
		cursor = archive.readCString();
		handler_manager.deserialize(archive);
	}

};