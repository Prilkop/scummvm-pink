#include "csideeffectexit.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"

namespace Pink {

	CSideEffectExit::CSideEffectExit() : next_module(NULL), next_page(NULL) {
	}

	CSideEffectExit::~CSideEffectExit() {
		delete next_module;
		delete next_page;
	}

	void CSideEffectExit::deserialize(CArchive &archive) {
		next_module = archive.readCString();
		next_page = archive.readCString();
	}

};