#include "cactionplaywithsfx.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "cactionsound.h"

namespace Pink {

	CActionPlayWithSfx::CActionPlayWithSfx() : loop(0), sfx(NULL) {
	}

	CActionPlayWithSfx::~CActionPlayWithSfx() {
	}

	void CActionPlayWithSfx::deserialize(CArchive &archive) {
		this->CActionPlay::deserialize(archive);
		loop = (bool)archive.readDWORD();
		sfx = archive.readCObArray(CActionSound::RuntimeClass());
	}

};