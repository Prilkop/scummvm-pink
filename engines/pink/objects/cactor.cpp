#include "cactor.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"
#include "common/array.h"

#include "cpage.h"
#include "caction.h"

namespace Pink {

	CActor::CActor() : page(NULL), actions(NULL), _current_action(NULL) {
	}

	CActor::~CActor() {
		delete actions;
	}

	void CActor::deserialize(CArchive &archive) {
		this->CNamedObject::deserialize(archive);
		page = (CPage *)archive.readCObject();
		actions = (Common::Array<CAction *> *)archive.readCObArray(CAction::RuntimeClass());
		for (uint32 i = 0; i < actions->size(); i++) {
			CAction *action = actions->at(i);
			_actions_map[*(action->name)] = action;
		}
		_current_action = getAction("Idle");
	}

	void CActor::init(PinkEngine *pink) {
		_current_action->init(pink);
	}
	void CActor::execute(PinkEngine *pink) {
		_current_action->execute(pink);
	}

	void CActor::destroy(PinkEngine *pink) {
		_current_action->destroy(pink);
	}

	CAction *CActor::getAction(const Common::String &name) {
		return _actions_map.getVal(name, NULL);
	}

	CAction *CActor::getCurrentAction() {
		return _current_action;
	}

	void CActor::setCurrentAction(const Common::String &name) {
		CAction *action = getAction(name);
		if (action == NULL) {
			return;
		}
		_current_action = action;
	}

};