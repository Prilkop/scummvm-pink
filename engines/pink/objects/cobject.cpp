#include "cobject.h"
#include "carchive.h"
#include "cruntimeclass.h"

namespace Pink {

	CObject::CObject() {
	}


	CObject::~CObject() {
	}

	void CObject::deserialize(CArchive &archive) {
	}

	void CObject::readFromOrb(CArchive &archive) {
		archive.mapObject(this);
		this->deserialize(archive);
	}

};
