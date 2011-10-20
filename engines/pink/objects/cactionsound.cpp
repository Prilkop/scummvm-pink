#include "cactionsound.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"
#include "audio/audiostream.h"
#include "audio/decoders/wave.h"
#include "audio/mixer.h"

#include "pink/pink.h"

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

	void CActionSound::init(PinkEngine *pink) {
		CAction::init(pink);
		Audio::RewindableAudioStream *as = Audio::makeWAVStream(pink->getPageResource(sound), DisposeAfterUse::YES);
		if (background) {
			pink->playMusic(&_handle, as, volume);
		}
	}

};
