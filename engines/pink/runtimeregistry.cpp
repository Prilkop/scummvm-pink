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
#include "objects/chandlersequences.h"
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
#include "objects/csideeffectmodulevariable.h"
#include "objects/csideeffectvariable.h"
#include "objects/cwalkmgr.h"

namespace Pink {

	uint32 CRuntimeClass::runtimeclassesCount = 31;

	CRuntimeClass CRuntimeClass::runtimeclasses[] = {
		REGISTER_RUNTIME_CLASS(CObject, NULL),
		REGISTER_RUNTIME_CLASS(CAction, &runtimeclasses[18]),
		REGISTER_RUNTIME_CLASS(CActionCEL, &runtimeclasses[1]),
		REGISTER_RUNTIME_CLASS(CActionHide, &runtimeclasses[1]),
		REGISTER_RUNTIME_CLASS(CActionPlay, &runtimeclasses[6]),
		REGISTER_RUNTIME_CLASS(CActionSound, &runtimeclasses[1]),
		REGISTER_RUNTIME_CLASS(CActionStill, &runtimeclasses[2]),
		REGISTER_RUNTIME_CLASS(CActor, &runtimeclasses[18]),
		REGISTER_RUNTIME_CLASS(CCursorMgr, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CGame, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CGamePage, &runtimeclasses[19]),
		REGISTER_RUNTIME_CLASS(CHandler, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CHandlerMgr, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CHandlerSequences, &runtimeclasses[11]),
		REGISTER_RUNTIME_CLASS(CHandlerStartPage, &runtimeclasses[13]),
		REGISTER_RUNTIME_CLASS(CLeadActor, &runtimeclasses[7]),
		REGISTER_RUNTIME_CLASS(CModule, &runtimeclasses[18]),
		REGISTER_RUNTIME_CLASS(CModuleProxy, &runtimeclasses[18]),
		REGISTER_RUNTIME_CLASS(CNamedObject, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CPage, &runtimeclasses[18]),
		REGISTER_RUNTIME_CLASS(CSequence, &runtimeclasses[18]),
		REGISTER_RUNTIME_CLASS(CSequenceItem, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CSequenceItemDefaultAction, &runtimeclasses[21]),
		REGISTER_RUNTIME_CLASS(CSequenceItemLeader, &runtimeclasses[21]),
		REGISTER_RUNTIME_CLASS(CSequenceItemLeaderAudio, &runtimeclasses[23]),
		REGISTER_RUNTIME_CLASS(CSequencer, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CSideEffect, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CSideEffectExit, &runtimeclasses[26]),
		REGISTER_RUNTIME_CLASS(CSideEffectModuleVariable, &runtimeclasses[29]),
		REGISTER_RUNTIME_CLASS(CSideEffectVariable, &runtimeclasses[26]),
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
	IMPLEMENT_RUNTIME_CLASS(13, CHandlerSequences);
	IMPLEMENT_RUNTIME_CLASS(14, CHandlerStartPage);
	IMPLEMENT_RUNTIME_CLASS(15, CLeadActor);
	IMPLEMENT_RUNTIME_CLASS(16, CModule);
	IMPLEMENT_RUNTIME_CLASS(17, CModuleProxy);
	IMPLEMENT_RUNTIME_CLASS(18, CNamedObject);
	IMPLEMENT_RUNTIME_CLASS(19, CPage);
	IMPLEMENT_RUNTIME_CLASS(20, CSequence);
	IMPLEMENT_RUNTIME_CLASS(21, CSequenceItem);
	IMPLEMENT_RUNTIME_CLASS(22, CSequenceItemDefaultAction);
	IMPLEMENT_RUNTIME_CLASS(23, CSequenceItemLeader);
	IMPLEMENT_RUNTIME_CLASS(24, CSequenceItemLeaderAudio);
	IMPLEMENT_RUNTIME_CLASS(25, CSequencer);
	IMPLEMENT_RUNTIME_CLASS(26, CSideEffect);
	IMPLEMENT_RUNTIME_CLASS(27, CSideEffectExit);
	IMPLEMENT_RUNTIME_CLASS(28, CSideEffectModuleVariable);
	IMPLEMENT_RUNTIME_CLASS(29, CSideEffectVariable);
	IMPLEMENT_RUNTIME_CLASS(30, CWalkMgr);

}
