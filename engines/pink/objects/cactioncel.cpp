#include "cactioncel.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"

namespace Pink {

	CActionCEL::CActionCEL() : cel(NULL), z(0) {
	}

	CActionCEL::~CActionCEL() {
		delete cel;
	}

	void CActionCEL::deserialize(CArchive &archive) {
		this->CAction::deserialize(archive);
		cel = archive.readCString();
		z = archive.readDWORD();
	}

};