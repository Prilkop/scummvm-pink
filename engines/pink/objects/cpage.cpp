#include "cpage.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"
#include "common/array.h"

#include "cactor.h"

namespace Pink {

	CPage::CPage() : directory(NULL), actors(NULL) {
	}

	CPage::~CPage() {
		delete directory;
		delete actors;
	}

	void CPage::deserialize(CArchive &archive) {
		this->CNamedObject::deserialize(archive);
		directory = archive.readCString();
		actors = (Common::Array<CActor *> *)archive.readCObArray(CActor::RuntimeClass());
	}

	void CPage::readFromOrb(CArchive &archive) {
		archive.mapObject(this);
		this->CPage::deserialize(archive);
	}

};