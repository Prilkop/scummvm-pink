#include "cactionsound.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"

namespace Pink {

	CActionSound::CActionSound() : sound(NULL), volume(0), loop(false),
			background(false) {
	}

	CActionSound::~CActionSound() {
		delete sound;
	}

	void CActionSound::deserialize(CArchive &archive) {
		this->CAction::deserialize(archive);
		sound = archive.readCString();
		volume = archive.readDWORD();
		loop = archive.readDWORD();
		background = archive.readDWORD();
	}

};