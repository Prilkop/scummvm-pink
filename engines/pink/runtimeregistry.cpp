#include "runtimeregistry.h"

#include "common/scummsys.h"

#include "objects/cobject.h"
#include "objects/caction.h"
#include "objects/cactioncel.h"
#include "objects/cactionhide.h"
#include "objects/cactionloop.h"
#include "objects/cactionplay.h"
#include "objects/cactionplaywithsfx.h"
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
#include "objects/csequenceaudio.h"
#include "objects/csequenceitem.h"
#include "objects/csequenceitemdefaultaction.h"
#include "objects/csequenceitemleader.h"
#include "objects/csequenceitemleaderaudio.h"
#include "objects/csequencer.h"
#include "objects/csideeffect.h"
#include "objects/csideeffectexit.h"
#include "objects/csideeffectmodulevariable.h"
#include "objects/csideeffectvariable.h"
#include "objects/csupportingactor.h"
#include "objects/cwalkmgr.h"

namespace Pink {

	uint32 CRuntimeClass::runtimeclassesCount = 35;

	CRuntimeClass CRuntimeClass::runtimeclasses[] = {
		REGISTER_RUNTIME_CLASS(CObject, NULL),
		REGISTER_RUNTIME_CLASS(CAction, &runtimeclasses[20]),
		REGISTER_RUNTIME_CLASS(CActionCEL, &runtimeclasses[1]),
		REGISTER_RUNTIME_CLASS(CActionHide, &runtimeclasses[1]),
		REGISTER_RUNTIME_CLASS(CActionLoop, &runtimeclasses[5]),
		REGISTER_RUNTIME_CLASS(CActionPlay, &runtimeclasses[8]),
		REGISTER_RUNTIME_CLASS(CActionPlayWithSfx, &runtimeclasses[5]),
		REGISTER_RUNTIME_CLASS(CActionSound, &runtimeclasses[1]),
		REGISTER_RUNTIME_CLASS(CActionStill, &runtimeclasses[2]),
		REGISTER_RUNTIME_CLASS(CActor, &runtimeclasses[20]),
		REGISTER_RUNTIME_CLASS(CCursorMgr, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CGame, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CGamePage, &runtimeclasses[21]),
		REGISTER_RUNTIME_CLASS(CHandler, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CHandlerMgr, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CHandlerSequences, &runtimeclasses[13]),
		REGISTER_RUNTIME_CLASS(CHandlerStartPage, &runtimeclasses[15]),
		REGISTER_RUNTIME_CLASS(CLeadActor, &runtimeclasses[9]),
		REGISTER_RUNTIME_CLASS(CModule, &runtimeclasses[20]),
		REGISTER_RUNTIME_CLASS(CModuleProxy, &runtimeclasses[20]),
		REGISTER_RUNTIME_CLASS(CNamedObject, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CPage, &runtimeclasses[20]),
		REGISTER_RUNTIME_CLASS(CSequence, &runtimeclasses[20]),
		REGISTER_RUNTIME_CLASS(CSequenceAudio, &runtimeclasses[22]),
		REGISTER_RUNTIME_CLASS(CSequenceItem, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CSequenceItemDefaultAction, &runtimeclasses[24]),
		REGISTER_RUNTIME_CLASS(CSequenceItemLeader, &runtimeclasses[24]),
		REGISTER_RUNTIME_CLASS(CSequenceItemLeaderAudio, &runtimeclasses[26]),
		REGISTER_RUNTIME_CLASS(CSequencer, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CSideEffect, &runtimeclasses[0]),
		REGISTER_RUNTIME_CLASS(CSideEffectExit, &runtimeclasses[29]),
		REGISTER_RUNTIME_CLASS(CSideEffectModuleVariable, &runtimeclasses[32]),
		REGISTER_RUNTIME_CLASS(CSideEffectVariable, &runtimeclasses[29]),
		REGISTER_RUNTIME_CLASS(CSupportingActor, &runtimeclasses[9]),
		REGISTER_RUNTIME_CLASS(CWalkMgr, &runtimeclasses[0]),
	};

	IMPLEMENT_RUNTIME_CLASS(0, CObject);
	IMPLEMENT_RUNTIME_CLASS(1, CAction);
	IMPLEMENT_RUNTIME_CLASS(2, CActionCEL);
	IMPLEMENT_RUNTIME_CLASS(3, CActionHide);
	IMPLEMENT_RUNTIME_CLASS(4, CActionLoop);
	IMPLEMENT_RUNTIME_CLASS(5, CActionPlay);
	IMPLEMENT_RUNTIME_CLASS(6, CActionPlayWithSfx);
	IMPLEMENT_RUNTIME_CLASS(7, CActionSound);
	IMPLEMENT_RUNTIME_CLASS(8, CActionStill);
	IMPLEMENT_RUNTIME_CLASS(9, CActor);
	IMPLEMENT_RUNTIME_CLASS(10, CCursorMgr);
	IMPLEMENT_RUNTIME_CLASS(11, CGame);
	IMPLEMENT_RUNTIME_CLASS(12, CGamePage);
	IMPLEMENT_RUNTIME_CLASS(13, CHandler);
	IMPLEMENT_RUNTIME_CLASS(14, CHandlerMgr);
	IMPLEMENT_RUNTIME_CLASS(15, CHandlerSequences);
	IMPLEMENT_RUNTIME_CLASS(16, CHandlerStartPage);
	IMPLEMENT_RUNTIME_CLASS(17, CLeadActor);
	IMPLEMENT_RUNTIME_CLASS(18, CModule);
	IMPLEMENT_RUNTIME_CLASS(19, CModuleProxy);
	IMPLEMENT_RUNTIME_CLASS(20, CNamedObject);
	IMPLEMENT_RUNTIME_CLASS(21, CPage);
	IMPLEMENT_RUNTIME_CLASS(22, CSequence);
	IMPLEMENT_RUNTIME_CLASS(23, CSequenceAudio);
	IMPLEMENT_RUNTIME_CLASS(24, CSequenceItem);
	IMPLEMENT_RUNTIME_CLASS(25, CSequenceItemDefaultAction);
	IMPLEMENT_RUNTIME_CLASS(26, CSequenceItemLeader);
	IMPLEMENT_RUNTIME_CLASS(27, CSequenceItemLeaderAudio);
	IMPLEMENT_RUNTIME_CLASS(28, CSequencer);
	IMPLEMENT_RUNTIME_CLASS(29, CSideEffect);
	IMPLEMENT_RUNTIME_CLASS(30, CSideEffectExit);
	IMPLEMENT_RUNTIME_CLASS(31, CSideEffectModuleVariable);
	IMPLEMENT_RUNTIME_CLASS(32, CSideEffectVariable);
	IMPLEMENT_RUNTIME_CLASS(33, CSupportingActor);
	IMPLEMENT_RUNTIME_CLASS(34, CWalkMgr);

}
