#include "cgame.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"
#include "common/array.h"

#include "cmoduleproxy.h"

namespace Pink {
	using Common::Array;

	CGame::CGame() : path(NULL), ini(NULL) {
	}


	CGame::~CGame() {
		delete path;
		delete ini;
		delete modules;
	}

	void CGame::deserialize(CArchive &archive) {
		path = archive.readCString();
		ini = archive.readCString();
		modules = (Array<CModuleProxy *> *)archive.readCObArray();
	}

};