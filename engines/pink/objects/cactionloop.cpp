#include "cactionloop.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"

namespace Pink {

	CActionLoop::CActionLoop() : intro(false), style(Forward) {
	}

	CActionLoop::~CActionLoop() {
	}

	void CActionLoop::deserialize(CArchive &archive) {
		this->CActionPlay::deserialize(archive);
		intro = (bool)archive.readDWORD();
		short styleIndex = archive.readWORD();
		if (styleIndex >= Forward && styleIndex <= Random)
			style = (LoopStyle)styleIndex;
		else
			style = Forward;
	}

};