#include "cactionplay.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"

namespace Pink {

	CActionPlay::CActionPlay() : stopFrame(0) {
	}

	CActionPlay::~CActionPlay() {
	}

	void CActionPlay::deserialize(CArchive &archive) {
		this->CActionStill::deserialize(archive);
		stopFrame = archive.readDWORD();
	}

};