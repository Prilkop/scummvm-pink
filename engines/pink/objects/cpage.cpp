#include "cpage.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"
#include "common/array.h"

#include "cactor.h"

namespace Pink {

	CPage::CPage() : directory(NULL), actors(NULL), lead_actor(NULL) {
	}

	CPage::~CPage() {
		delete directory;
		delete actors;
	}

	void CPage::deserialize(CArchive &archive) {
		this->CNamedObject::deserialize(archive);
		directory = archive.readCString();
		actors = (Common::Array<CActor *> *)archive.readCObArray(CActor::RuntimeClass());
		for (uint32 i = 0; i < actors->size(); i++) {
			CActor *actor = actors->at(i);
			_actors_map[*(actor->name)] = actor;
		}
	}

	void CPage::readFromOrb(CArchive &archive) {
		archive.mapObject(this);
		this->CPage::deserialize(archive);
	}

	void CPage::init(PinkEngine *pink) {
		for (uint i = 0; i < actors->size(); i++) {
			actors->at(i)->init(pink);
		}
	}

	void CPage::execute(PinkEngine *pink) {
		for (uint i = 0; i < actors->size(); i++) {
			actors->at(i)->execute(pink);
		}
	}

	void CPage::destroy(PinkEngine *pink) {
		for (uint i = 0; i < actors->size(); i++) {
			actors->at(i)->destroy(pink);
		}
	}

	CActor *CPage::getActor(const Common::String &name) {
		return _actors_map.getVal(name, NULL);
	}
};