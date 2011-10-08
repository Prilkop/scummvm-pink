#include "runtimeregistry.h"

#include "common/scummsys.h"

#include "objects/cobject.h"
#include "objects/caction.h"
#include "objects/cactioncel.h"
#include "objects/cactionhide.h"
#include "objects/cactionplay.h"
#include "objects/cactionsound.h"
#include "objects/cactionstill.h"
#include "objects/cactor.h"
#include "objects/ccursormgr.h"
#include "objects/cgame.h"
#include "objects/cgamepage.h"
#include "objects/chandler.h"
#include "objects/chandlermgr.h"
#include "objects/chandlerstartpage.h"
#include "objects/cleadactor.h"
#include "objects/cmodule.h"
#include "objects/cmoduleproxy.h"
#include "objects/cnamedobject.h"
#include "objects/cpage.h"
#include "objects/csequence.h"
#include "objects/csequenceitem.h"
#include "objects/csequenceitemdefaultaction.h"
#include "objects/csequenceitemleader.h"
#include "objects/csequenceitemleaderaudio.h"
#include "objects/csequencer.h"
#include "objects/csideeffect.h"
#include "objects/csideeffectexit.h"
#include "objects/cwalkmgr.h"

namespace Pink {

	uint32 CRuntimeClass::runtimeclassesCount = 28;

	CRuntimeClass CRuntimeClass::runtimeclasses[] = {
		REGISTER_RUNTIME_CLASS(CObject, NULL),
		REGISTER_RUNTIME_CLASS(CAction, &runtimeclasses[17]),
		REGISTER_RUNTIME_CLASS(CActionCEL, &runtimeclasses[1]),
		REGISTER_RUNTIME_CLASS(CActionHide, &runtimeclasses[1]),
		REGISTER_RUNTIME_CLASS(CActionPlay, &runtimeclasses[6]),
		REGISTER_RUNTIME_CLASS(CActionSound, &runtimeclasses[1]),
		REGISTER_RUNTIME_CLASS(CActionStill, &runtimeclasses[2]),
		REGISTER_RUNTIME_CLASS(CActor, &runtimeclasses[17]),
		REGISTER_RUNTIME_CLASS(CCursorMgr, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CGame, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CGamePage, &runtimeclasses[18]),
		REGISTER_RUNTIME_CLASS(CHandler, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CHandlerMgr, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CHandlerStartPage, &runtimeclasses[11]),
		REGISTER_RUNTIME_CLASS(CLeadActor, &runtimeclasses[7]),
		REGISTER_RUNTIME_CLASS(CModule, &runtimeclasses[17]),
		REGISTER_RUNTIME_CLASS(CModuleProxy, &runtimeclasses[17]),
		REGISTER_RUNTIME_CLASS(CNamedObject, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CPage, &runtimeclasses[17]),
		REGISTER_RUNTIME_CLASS(CSequence, &runtimeclasses[17]),
		REGISTER_RUNTIME_CLASS(CSequenceItem, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CSequenceItemDefaultAction, &runtimeclasses[20]),
		REGISTER_RUNTIME_CLASS(CSequenceItemLeader, &runtimeclasses[20]),
		REGISTER_RUNTIME_CLASS(CSequenceItemLeaderAudio, &runtimeclasses[22]),
		REGISTER_RUNTIME_CLASS(CSequencer, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CSideEffect, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CSideEffectExit, &runtimeclasses[25]),
		REGISTER_RUNTIME_CLASS(CWalkMgr, &runtimeclasses[0]),
	};

	IMPLEMENT_RUNTIME_CLASS(0, CObject);
	IMPLEMENT_RUNTIME_CLASS(1, CAction);
	IMPLEMENT_RUNTIME_CLASS(2, CActionCEL);
	IMPLEMENT_RUNTIME_CLASS(3, CActionHide);
	IMPLEMENT_RUNTIME_CLASS(4, CActionPlay);
	IMPLEMENT_RUNTIME_CLASS(5, CActionSound);
	IMPLEMENT_RUNTIME_CLASS(6, CActionStill);
	IMPLEMENT_RUNTIME_CLASS(7, CActor);
	IMPLEMENT_RUNTIME_CLASS(8, CCursorMgr);
	IMPLEMENT_RUNTIME_CLASS(9, CGame);
	IMPLEMENT_RUNTIME_CLASS(10, CGamePage);
	IMPLEMENT_RUNTIME_CLASS(11, CHandler);
	IMPLEMENT_RUNTIME_CLASS(12, CHandlerMgr);
	IMPLEMENT_RUNTIME_CLASS(13, CHandlerStartPage);
	IMPLEMENT_RUNTIME_CLASS(14, CLeadActor);
	IMPLEMENT_RUNTIME_CLASS(15, CModule);
	IMPLEMENT_RUNTIME_CLASS(16, CModuleProxy);
	IMPLEMENT_RUNTIME_CLASS(17, CNamedObject);
	IMPLEMENT_RUNTIME_CLASS(18, CPage);
	IMPLEMENT_RUNTIME_CLASS(19, CSequence);
	IMPLEMENT_RUNTIME_CLASS(20, CSequenceItem);
	IMPLEMENT_RUNTIME_CLASS(21, CSequenceItemDefaultAction);
	IMPLEMENT_RUNTIME_CLASS(22, CSequenceItemLeader);
	IMPLEMENT_RUNTIME_CLASS(23, CSequenceItemLeaderAudio);
	IMPLEMENT_RUNTIME_CLASS(24, CSequencer);
	IMPLEMENT_RUNTIME_CLASS(25, CSideEffect);
	IMPLEMENT_RUNTIME_CLASS(26, CSideEffectExit);
	IMPLEMENT_RUNTIME_CLASS(27, CWalkMgr);

}
