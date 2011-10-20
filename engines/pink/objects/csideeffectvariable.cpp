#include "csideeffectvariable.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"

namespace Pink {

	CSideEffectVariable::CSideEffectVariable() : variable(NULL), value(NULL) {
	}

	CSideEffectVariable::~CSideEffectVariable() {
		delete variable;
		delete value;
	}

	void CSideEffectVariable::deserialize(CArchive &archive) {
		variable = archive.readCString();
		value = archive.readCString();
	}

};