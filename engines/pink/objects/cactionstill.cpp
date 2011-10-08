#include "cactionstill.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"

namespace Pink {

	CActionStill::CActionStill() : startFrame(0) {
	}

	CActionStill::~CActionStill() {
	}

	void CActionStill::deserialize(CArchive &archive) {
		this->CActionCEL::deserialize(archive);
		startFrame = archive.readDWORD();
	}

};