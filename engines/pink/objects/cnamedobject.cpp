#include "cnamedobject.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"

namespace Pink {
	CNamedObject::CNamedObject() {
	}


	CNamedObject::~CNamedObject() {
	}

	void CNamedObject::deserialize(CArchive &archive) {
		name = archive.readCString();
	}

};