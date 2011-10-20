#include "csequence.h"
#include "carchive.h"
#include "cruntimeclass.h"

#include "common/str.h"
#include "common/array.h"

#include "cgamepage.h"
#include "cactor.h"
#include "caction.h"
#include "csequencer.h"
#include "csequenceitem.h"
#include "csequenceitemleader.h"

namespace Pink {

	CSequence::CSequence() : sequencer(NULL), items(NULL), _next_item_index(0) {
	}

	CSequence::~CSequence() {
		delete items;
	}

	void CSequence::deserialize(CArchive &archive) {
		this->CNamedObject::deserialize(archive);
		sequencer = (CSequencer *)archive.readCObject();
		items = archive.readCObArray();
	}

	void CSequence::init(PinkEngine *pink) {
		do {
			CSequenceItem *item = (CSequenceItem *)items->at(_next_item_index);
			CActor *actor = sequencer->page->getActor(*item->actor);
			actor->getCurrentAction()->destroy(pink);
			actor->setCurrentAction(*item->action);
			actor->getCurrentAction()->init(pink);
			_next_item_index++;
		} while (_next_item_index < items->size() &&
		         !CSequenceItemLeader::RuntimeClass()->isInstance(items->at(_next_item_index)));
	}

	void CSequence::execute(PinkEngine *pink) {

	}
};