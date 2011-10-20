#include "cactioncel.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"
#include "video/flic_decoder.h"

#include "pink/pink.h"

namespace Pink {

	CActionCEL::CActionCEL() : cel(NULL), z(0), decoder(NULL) {
	}

	CActionCEL::~CActionCEL() {
		delete cel;
	}

	void CActionCEL::deserialize(CArchive &archive) {
		this->CAction::deserialize(archive);
		cel = archive.readCString();
		z = archive.readDWORD();
	}

	void CActionCEL::init(PinkEngine *pink) {
		CAction::init(pink);
		delete decoder;
		decoder = new Video::FlicDecoder();
		decoder->loadStream(pink->getPageResource(cel));
		pink->stageGfxAction(this);
	}

	void CActionCEL::execute(PinkEngine *pink) {
		CAction::execute(pink);
		if (!decoder->getTimeToNextFrame() && !decoder->endOfVideo()) {
			decoder->decodeNextFrame();
			pink->askScreenUpdate();
		}
	}

	void CActionCEL::destroy(PinkEngine *pink) {
		CAction::destroy(pink);
		pink->unstageActor(actor);
	}

	void CActionCEL::draw(PinkEngine *pink) {
		pink->copyToScreen(decoder);
	}
};