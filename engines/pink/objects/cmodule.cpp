#include "cmodule.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"
#include "common/array.h"

#include "cpage.h"

namespace Pink {

	CModule::CModule() : directory(NULL), inv(NULL), pages(NULL) {

	}

	CModule::~CModule() {
		delete directory;
		delete inv;
		delete pages;
	}

	void CModule::deserialize(CArchive &archive) {
		this->CNamedObject::deserialize(archive);
		directory = archive.readCString();
		inv = archive.readCObArray();
		pages = (Common::Array<CPage *> *)archive.readCObArray();
	}

};