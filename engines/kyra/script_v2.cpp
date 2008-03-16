/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#include "kyra/kyra_v2.h"
#include "kyra/text_v2.h"
#include "kyra/wsamovie.h"

#include "common/endian.h"

namespace Kyra {

int KyraEngine_v2::o2_setCharacterFacingRefresh(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_setCharacterFacingRefresh(%p) (-, %d, %d)", (const void *)script, stackPos(1), stackPos(2));
	int animFrame = stackPos(2);
	if (animFrame >= 0)
		_mainCharacter.animFrame = animFrame;
	_mainCharacter.facing = stackPos(1);
	updateCharacterAnim(0);
	refreshAnimObjectsIfNeed();
	return 0;
}

int KyraEngine_v2::o2_setCharacterPos(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_setCharacterFacingRefresh(%p) (-, %d, %d)", (const void *)script, stackPos(1), stackPos(2));
	int x = stackPos(1);
	int y = stackPos(2);

	if (x != -1 && y != -1) {
		x &= ~3;
		y &= ~1;
	}

	restorePage3();
	_mainCharacter.x2 = _mainCharacter.x1 = x;
	_mainCharacter.y2 = _mainCharacter.y1 = y;
	return 0;
}

int KyraEngine_v2::o2_defineObject(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_defineObject(%p) (%d, '%s', %d, %d, %d, %d)", (const void *)script,
			stackPos(0), stackPosString(1), stackPos(2), stackPos(3), stackPos(4), stackPos(5));
	TalkObject *object = &_talkObjectList[stackPos(0)];
	strcpy(object->filename, stackPosString(1));
	object->scriptId = stackPos(2);
	object->x = stackPos(3);
	object->y = stackPos(4);
	object->color = stackPos(5);
	return 0;
}

int KyraEngine_v2::o2_refreshCharacter(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_refreshCharacter(%p) (-, %d, %d, %d)", (const void *)script, stackPos(1), stackPos(2), stackPos(3));
	int unk = stackPos(1);
	int facing = stackPos(2);
	int refresh = stackPos(3);
	if (facing >= 0)
		_mainCharacter.facing = facing;
	if (unk >= 0 && unk != 32)
		_mainCharacter.animFrame = _characterFrameTable[_mainCharacter.facing];
	updateCharacterAnim(0);
	if (refresh)
		refreshAnimObjectsIfNeed();
	return 0;
}

int KyraEngine_v2::o2_getCharacterX(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_getCharacterX(%p) ()", (const void *)script);
	return _mainCharacter.x1;
}

int KyraEngine_v2::o2_getCharacterY(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_getCharacterY(%p) ()", (const void *)script);
	return _mainCharacter.y1;
}

int KyraEngine_v2::o2_getCharacterFacing(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_getCharacterFacing(%p) ()", (const void *)script);
	return _mainCharacter.facing;
}

int KyraEngine_v2::o2_getCharacterScene(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_getCharacterScene(%p) ()", (const void *)script);
	return _mainCharacter.sceneId;
}

int KyraEngine_v2::o2_setSceneComment(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_setSceneComment(%p) ('%s')", (const void *)script, stackPosString(0));
	_sceneCommentString = stackPosString(0);
	return 0;
}

int KyraEngine_v2::o2_setCharacterAnimFrame(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_setCharacterAnimFrame(%p) (-, %d, %d)", (const void *)script, stackPos(1), stackPos(2));
	int animFrame = stackPos(1);
	int updateAnim = stackPos(2);

	_mainCharacter.animFrame = animFrame;
	if (updateAnim)
		updateCharacterAnim(0);

	return 0;
}

int KyraEngine_v2::o2_trySceneChange(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_trySceneChange(%p) (%d, %d, %d, %d)", (const void *)script,
			stackPos(0), stackPos(1), stackPos(2), stackPos(3));

	_unkHandleSceneChangeFlag = 1;
	int success = inputSceneChange(stackPos(0), stackPos(1), stackPos(2), stackPos(3));
	_unkHandleSceneChangeFlag = 0;

	if (success) {
		_scriptInterpreter->initScript(script, script->dataPtr);
		_unk4 = 0;
		_unk3 = -1;
		_unk5 = 1;
		return 0;
	} else {
		return (_unk4 != 0) ? 1 : 0;
	}
}

int KyraEngine_v2::o2_showChapterMessage(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_showChapterMessage(%p) (%d, %d)", (const void *)script, stackPos(0), stackPos(1));
	showChapterMessage(stackPos(0), stackPos(1));
	return 0;
}

int KyraEngine_v2::o2_wsaClose(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_wsaClose(%p) (%d)", (const void *)script, stackPos(0));
	assert(stackPos(0) >= 0 && stackPos(0) < ARRAYSIZE(_wsaSlots));
	_wsaSlots[stackPos(0)]->close();
	return 0;
}

int KyraEngine_v2::o2_displayWsaFrame(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_displayWsaFrame(%p) (%d, %d, %d, %d, %d, %d, %d, %d, %d)", (const void *)script,
			stackPos(0), stackPos(1), stackPos(2), stackPos(3), stackPos(4), stackPos(5), stackPos(6), stackPos(7), stackPos(8));
	int frame = stackPos(0);
	int x = stackPos(1);
	int y = stackPos(2);
	int waitTime = stackPos(3);
	int slot = stackPos(4);
	int copyParam = stackPos(5);
	int doUpdate = stackPos(6);
	int dstPage = stackPos(7);
	int backUp = stackPos(8);

	_screen->hideMouse();
	uint32 endTime = _system->getMillis() + waitTime * _tickLength;
	_wsaSlots[slot]->setX(x);
	_wsaSlots[slot]->setY(y);
	_wsaSlots[slot]->setDrawPage(dstPage);
	_wsaSlots[slot]->displayFrame(frame, copyParam | 0xC000);
	_screen->updateScreen();

	if (backUp)
		memcpy(_gamePlayBuffer, _screen->getCPagePtr(3), 46080);

	while (_system->getMillis() < endTime) {
		if (doUpdate)
			update();

		if (endTime - _system->getMillis() >= 10)
			delay(10);
	}
	_screen->showMouse();
	return 0;
}

int KyraEngine_v2::o2_displayWsaSequentialFramesLooping(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_displayWsaSequentialFramesLooping(%p) (%d, %d, %d, %d, %d, %d, %d, %d)", (const void *)script,
			stackPos(0), stackPos(1), stackPos(2), stackPos(3), stackPos(4), stackPos(5), stackPos(6), stackPos(7));
	int startFrame = stackPos(0);
	int endFrame = stackPos(1);
	int x = stackPos(2);
	int y = stackPos(3);
	int waitTime = stackPos(4);
	int slot = stackPos(5);
	int maxTimes = stackPos(6);
	int copyFlags = stackPos(7);

	if (maxTimes > 1)
		maxTimes = 1;

	_wsaSlots[slot]->setX(x);
	_wsaSlots[slot]->setY(y);
	_wsaSlots[slot]->setDrawPage(0);

	_screen->hideMouse();
	int curTime = 0;
	while (curTime < maxTimes) {
		if (startFrame < endFrame) {
			for (int i = startFrame; i <= endFrame; ++i) {
				uint32 endTime = _system->getMillis() + waitTime * _tickLength;
				_wsaSlots[slot]->displayFrame(i, 0xC000 | copyFlags);
				_screen->updateScreen();

				do {
					update();

					if (endTime - _system->getMillis() >= 10)
						delay(10);
				} while (_system->getMillis() < endTime);
			}
		} else {
			for (int i = startFrame; i >= endFrame; --i) {
				uint32 endTime = _system->getMillis() + waitTime * _tickLength;
				_wsaSlots[slot]->displayFrame(i, 0xC000 | copyFlags);
				_screen->updateScreen();

				do {
					update();

					if (endTime - _system->getMillis() >= 10)
						delay(10);
				} while (_system->getMillis() < endTime);
			}
		}

		++curTime;
	}
	_screen->showMouse();
	return 0;
}

int KyraEngine_v2::o2_wsaOpen(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_wsaOpen(%p) ('%s', %d)", (const void *)script, stackPosString(0), stackPos(1));
	assert(stackPos(1) >= 0 && stackPos(1) < ARRAYSIZE(_wsaSlots));
	_wsaSlots[stackPos(1)]->open(stackPosString(0), 1, 0);
	return 0;
}

int KyraEngine_v2::o2_displayWsaSequentialFrames(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_displayWsaSequentialFrames(%p) (%d, %d, %d, %d, %d, %d, %d)", (const void *)script, stackPos(0), stackPos(1), stackPos(2), stackPos(3), stackPos(4), stackPos(5), stackPos(6));
	
	uint16 frameDelay = stackPos(2) * _tickLength;
	uint16 currentFrame = stackPos(3);
	uint16 lastFrame = stackPos(4);
	uint16 index = stackPos(5);
	uint16 copyParam = stackPos(6) | 0xc000;

	_wsaSlots[index]->setX(stackPos(0));
	_wsaSlots[index]->setY(stackPos(1));
	_wsaSlots[index]->setDrawPage(0);
	
	_screen->hideMouse();

	while (currentFrame <= lastFrame) {	
		uint32 endTime = _system->getMillis() + frameDelay;
		_wsaSlots[index]->displayFrame(currentFrame++, copyParam);
		_screen->updateScreen();
		delayUntil(endTime);
	}

	_screen->showMouse();

	return 0;
}

int KyraEngine_v2::o2_displayWsaSequence(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_displayWsaSequence(%p) (%d, %d, %d, %d, %d, %d)", (const void *)script, stackPos(0), stackPos(1), stackPos(2), stackPos(3), stackPos(4), stackPos(5));
	
	const int frameDelay = stackPos(2) * _tickLength;
	const int index = stackPos(3);
	const bool doUpdate = (stackPos(4) != 0);
	const uint16 copyParam = stackPos(5) | 0xc000;

	_wsaSlots[index]->setX(stackPos(0));
	_wsaSlots[index]->setY(stackPos(1));
	_wsaSlots[index]->setDrawPage(0);
	
	_screen->hideMouse();

	int currentFrame = 0;
	const int lastFrame = _wsaSlots[index]->frames();

	while (currentFrame <= lastFrame) {	
		uint32 endTime = _system->getMillis() + frameDelay;
		_wsaSlots[index]->displayFrame(currentFrame++, copyParam);
		if (doUpdate)
			update();
		_screen->updateScreen();
		delayUntil(endTime);
	}

	_screen->showMouse();

	return 0;
}

int KyraEngine_v2::o2_checkForItem(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_checkForItem(%p) (%d, %d)", (const void *)script, stackPos(0), stackPos(1));
	return findItem(stackPos(0), stackPos(1)) == -1 ? 0 : 1;
}

int KyraEngine_v2::o2_defineItem(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_defineItem(%p) (%d, %d, %d, %d)", (const void *)script,
			stackPos(0), stackPos(1), stackPos(2), stackPos(3));
	int freeItem = findFreeItem();

	if (freeItem >= 0) {
		_itemList[freeItem].id = stackPos(0);
		_itemList[freeItem].x = stackPos(1);
		_itemList[freeItem].y = stackPos(2);
		_itemList[freeItem].sceneId = stackPos(3);
	}

	return freeItem;
}

int KyraEngine_v2::o2_removeItemFromInventory(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_removeItemFromInventory(%p) (%d)", (const void *)script, stackPos(0));
	uint16 item = stackPos(0);
	int slot = -1;
	while ((slot = getInventoryItemSlot(item)) != -1)
		removeItemFromInventory(slot);
	return 0;
}

int KyraEngine_v2::o2_countItemInInventory(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_countItemInInventory(%p) (%d, %d)", (const void *)script, stackPos(0), stackPos(1));
	uint16 item = stackPos(1);
	int count = 0;

	for (int i = 0; i < 20; ++i) {
		if (_mainCharacter.inventory[i] == item)
			++count;
	}

	if ((stackPos(0) == 0) && _itemInHand == int16(item))
		++count;

	return count;
}

int KyraEngine_v2::o2_queryGameFlag(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_queryGameFlag(%p) (%d)", (const void *)script, stackPos(0));
	return queryGameFlag(stackPos(0));
}

int KyraEngine_v2::o2_resetGameFlag(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_resetGameFlag(%p) (%d)", (const void *)script, stackPos(0));
	return resetGameFlag(stackPos(0));
}

int KyraEngine_v2::o2_setGameFlag(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_setGameFlag(%p) (%d)", (const void *)script, stackPos(0));
	return setGameFlag(stackPos(0));
}

int KyraEngine_v2::o2_setHandItem(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_setHandItem(%p) (%d)", (const void *)script, stackPos(0));
	setHandItem(stackPos(0));
	return 0;
}

int KyraEngine_v2::o2_removeHandItem(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_removeHandItem(%p) ()", (const void *)script);
	removeHandItem();
	return 0;
}

int KyraEngine_v2::o2_handItemSet(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_handItemSet(%p) ()", (const void *)script);
	return _handItemSet;
}

int KyraEngine_v2::o2_hideMouse(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_hideMouse(%p) ()", (const void *)script);
	_screen->hideMouse();
	return 0;
}

int KyraEngine_v2::o2_addSpecialExit(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_addSpecialExit(%p) (%d, %d, %d, %d, %d)", (const void *)script,
		stackPos(0), stackPos(1), stackPos(2), stackPos(3), stackPos(4));
	if (_specialExitCount < 5) {
		_specialExitTable[_specialExitCount+0] = stackPos(0);
		_specialExitTable[_specialExitCount+5] = stackPos(1);
		_specialExitTable[_specialExitCount+10] = stackPos(2) + stackPos(0) - 1;
		_specialExitTable[_specialExitCount+15] = stackPos(3) + stackPos(1) - 1;
		_specialExitTable[_specialExitCount+20] = stackPos(4);
		++_specialExitCount;
	}
	return 0;
}

int KyraEngine_v2::o2_setMousePos(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_setMousePos(%p) (%d, %d)", (const void *)script, stackPos(0), stackPos(1));
	setMousePos(stackPos(0), stackPos(1));
	return 0;
}

int KyraEngine_v2::o2_showMouse(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_showMouse(%p) ()", (const void *)script);
	_screen->showMouse();
	return 0;
}

int KyraEngine_v2::o2_delaySecs(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_delaySecs(%p) (%d, %d)", (const void *)script, stackPos(0), stackPos(1));
	delay(stackPos(0) * 1000, true);
	return 0;
}

int KyraEngine_v2::o2_delay(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_delay(%p) (%d, %d)", (const void *)script, stackPos(0), stackPos(1));
	//if (stackPos(1))
	//	sub_27100(stackPos(0) * _tickLength);
	//else
		delay(stackPos(0) * _tickLength, true);
	return 0;
}

int KyraEngine_v2::o2_setScaleTableItem(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_setScaleTableItem(%p) (%d, %d)", (const void *)script, stackPos(0), stackPos(1));
	setScaleTableItem(stackPos(0), stackPos(1));
	return 0;
}

int KyraEngine_v2::o2_setDrawLayerTableItem(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_setDrawLayerTableItem(%p) (%d, %d)", (const void *)script, stackPos(0), stackPos(1));
	setDrawLayerTableEntry(stackPos(0), stackPos(1));
	return 0;
}

int KyraEngine_v2::o2_setCharPalEntry(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_setCharPalEntry(%p) (%d, %d)", (const void *)script, stackPos(0), stackPos(1));
	setCharPalEntry(stackPos(0), stackPos(1));
	return 0;
}

int KyraEngine_v2::o2_drawSceneShape(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_drawSceneShape(%p) (%d, %d, %d, %d)", (const void *)script, stackPos(0), stackPos(1),
		stackPos(2), stackPos(3));

	int shape = stackPos(0);
	int x = stackPos(1);
	int y = stackPos(2);
	int flag = (stackPos(3) != 0) ? 1 : 0;

	_screen->hideMouse();
	restorePage3();

	_screen->drawShape(2, _sceneShapeTable[shape], x, y, 2, flag);

	memcpy(_gamePlayBuffer, _screen->getCPagePtr(3), 46080);

	_screen->drawShape(0, _sceneShapeTable[shape], x, y, 2, flag);

	//sub_B521();
	flagAnimObjsForRefresh();
	refreshAnimObjectsIfNeed();
	_screen->showMouse();
	return 0;
}

int KyraEngine_v2::o2_drawSceneShapeOnPage(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_drawSceneShapeOnPage(%p) (%d, %d, %d, %d, %d)", (const void *)script,
		stackPos(0), stackPos(1), stackPos(2), stackPos(3), stackPos(4));
	int shape = stackPos(0);
	int x = stackPos(1);
	int y = stackPos(2);
	int flag = stackPos(3);
	int drawPage = stackPos(4);

	_screen->drawShape(drawPage, _sceneShapeTable[shape], x, y, 2, flag ? 1 : 0);
	return 0;
}

int KyraEngine_v2::o2_disableAnimObject(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_disableAnimObject(%p) (%d)", (const void *)script, stackPos(0));
	_animObjects[stackPos(0)+1].enabled = false;
	return 0;
}

int KyraEngine_v2::o2_enableAnimObject(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_enableAnimObject(%p) (%d)", (const void *)script, stackPos(0));
	_animObjects[stackPos(0)+1].enabled = true;
	return 0;
}

int KyraEngine_v2::o2_restoreBackBuffer(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_restoreBackBuffer(%p) (%d)", (const void *)script, stackPos(0));
	int disable = stackPos(0);
	int oldState = 0;

	if (disable) {
		oldState = _animObjects[0].enabled;
		_animObjects[0].enabled = 0;
	}

	restorePage3();

	if (disable)
		_animObjects[0].enabled = oldState;

	return 0;
}

int KyraEngine_v2::o2_update(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_update(%p) (%d)", (const void *)script, stackPos(0));

	int times = stackPos(0);
	while (times--) {
		if (_chatText)
			updateWithText();
		else
			update();
	}

	return 0;
}

int KyraEngine_v2::o2_fadeScenePal(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_fadeScenePal(%p) (%d, %d)", (const void *)script, stackPos(0), stackPos(1));
	fadeScenePal(stackPos(0), stackPos(1));
	return 0;
}

int KyraEngine_v2::o2_enterNewSceneEx(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_enterNewSceneEx(%p) (%d, %d, %d, %d, %d)", (const void *)script, stackPos(0),
		stackPos(1), stackPos(2), stackPos(3), stackPos(4));

	int skipNpcScript = stackPos(3);
	enterNewScene(stackPos(0), stackPos(1), stackPos(2), skipNpcScript, stackPos(4));

	if (!skipNpcScript)
		runSceneScript4(0);

	_unk5 = 1;

	if (_mainCharX == -1 || _mainCharY == -1) {
		_mainCharacter.animFrame = _characterFrameTable[_mainCharacter.facing];
		updateCharacterAnim(0);
	}

	return 0;
}

int KyraEngine_v2::o2_switchScene(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_switchScene(%p) (%d)", (const void *)script, stackPos(0));
	setGameFlag(0x1EF);
	_mainCharX = _mainCharacter.x1;
	_mainCharY = _mainCharacter.y1;
	_noScriptEnter = 0;
	enterNewScene(stackPos(0), _mainCharacter.facing, 0, 0, 0);
	_noScriptEnter = 1;
	return 0;
}

int KyraEngine_v2::o2_getShapeFlag1(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_getShapeFlag1(%p) (%d, %d)", (const void *)script, stackPos(0), stackPos(1));
	return _screen->getShapeFlag1(stackPos(0), stackPos(1));
}

int KyraEngine_v2::o2_setLayerFlag(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_setLayerFlag(%p) (%d)", (const void *)script, stackPos(0));
	int layer = stackPos(0);
	if (layer >= 1 && layer <= 16)
		_layerFlagTable[layer] = 1;
	return 0;
}

int KyraEngine_v2::o2_setZanthiaPos(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_setZanthiaPos(%p) (%d, %d)", (const void *)script, stackPos(0), stackPos(1));
	_mainCharX = stackPos(0);
	_mainCharY = stackPos(1);

	if (_mainCharX == -1 && _mainCharY == -1)
		_mainCharacter.animFrame = 32;
	else
		_mainCharacter.animFrame = _characterFrameTable[_mainCharacter.facing];

	return 0;
}

int KyraEngine_v2::o2_loadMusicTrack(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_loadMusicTrack(%p) (%d)", (const void *)script, stackPos(0));
	snd_loadSoundFile(stackPos(0));
	return 0;
}

int KyraEngine_v2::o2_playWanderScoreViaMap(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_playWanderScoreViaMap(%p) (%d, %d)", (const void *)script, stackPos(0), stackPos(1));
	snd_playWanderScoreViaMap(stackPos(0), stackPos(1));
	return 0;
}

int KyraEngine_v2::o2_playSoundEffect(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_playSoundEffect(%p) (%d)", (const void *)script, stackPos(0));
	snd_playSoundEffect(stackPos(0));
	return 0;
}

int KyraEngine_v2::o2_getRand(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_getRand(%p) (%d, %d)", (const void *)script, stackPos(0), stackPos(1));
	assert(stackPos(0) < stackPos(1));
	return _rnd.getRandomNumberRng(stackPos(0), stackPos(1));
}

int KyraEngine_v2::o2_setDrawNoShapeFlag(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_setDrawNoShapeFlag(%p) (%d)", (const void *)script, stackPos(0));
	_drawNoShapeFlag = (stackPos(0) != 0);
	return 0;
}

int KyraEngine_v2::o2_showLetter(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_showLetter(%p) (%d)", (const void *)script, stackPos(0));
	const int letter = stackPos(0);
	char filename[16];

	_screen->hideMouse();

	showMessage(0, 0xCF);
	displayInvWsaLastFrame();
	backUpPage0();

	memcpy(_screen->getPalette(2), _screen->getPalette(0), 768);

	_screen->clearPage(3);
	_screen->loadBitmap("_NOTE.CPS", 3, 3, 0);

	sprintf(filename, "_NTEPAL%.1d.COL", letter+1);
	_res->loadFileToBuf(filename, _screen->getPalette(0), 768);

	_screen->fadeToBlack(0x14);
	
	sprintf(filename, "LETTER%.1d.", letter);
	strcat(filename, _languageExtension[_lang]);

	uint8 *letterBuffer = _res->fileData(filename, 0);
	if (letterBuffer) {
		bookDecodeText(letterBuffer);
		bookPrintText(2, letterBuffer, 0xC, 0xA, 0x20);
	}

	_screen->copyRegion(0, 0, 0, 0, 320, 200, 2, 0);
	_screen->fadePalette(_screen->getPalette(0), 0x14);
	_screen->setMouseCursor(0, 0, getShapePtr(0));
	setMousePos(280, 160);

	_screen->showMouse();

	bool running = true;
	while (running) {
		int inputFlag = checkInput(0);
		removeInputTop();

		if (inputFlag == 198 || inputFlag == 199)
			running = false;

		_screen->updateScreen();
		_system->delayMillis(10);
	}

	_screen->hideMouse();
	_screen->fadeToBlack(0x14);
	restorePage0();
	memcpy(_screen->getPalette(0), _screen->getPalette(2), 768);
	_screen->fadePalette(_screen->getPalette(0), 0x14);
	setHandItem(_itemInHand);
	_screen->showMouse();

	return 0;
}

int	KyraEngine_v2::o2_fillRect(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_fillRect(%p) (%d, %d, %d, %d, %d, %d)", (const void *)script, stackPos(0), stackPos(1), stackPos(2), stackPos(3), stackPos(4), stackPos(5));
	_screen->fillRect(stackPos(1), stackPos(2), stackPos(1)+stackPos(3), stackPos(2)+stackPos(4), stackPos(5), stackPos(0));
	return 0;
}

int KyraEngine_v2::o2_encodeShape(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_encodeShape(%p) (%d, %d, %d, %d, %d)", (const void *)script, stackPos(0), stackPos(1),
		stackPos(2), stackPos(3), stackPos(4));
	_sceneShapeTable[stackPos(0)] = _screen->encodeShape(stackPos(1), stackPos(2), stackPos(3), stackPos(4), 2);
	return 0;
}

int KyraEngine_v2::o2_defineRoomEntrance(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_defineRoomEntrance(%p) (%d, %d, %d)", (const void *)script, stackPos(0), stackPos(1), stackPos(2));
	switch (stackPos(0)) {
	case 0:
		_sceneEnterX1 = stackPos(1);
		_sceneEnterY1 = stackPos(2);
		break;

	case 1:
		_sceneEnterX2 = stackPos(1);
		_sceneEnterY2 = stackPos(2);
		break;

	case 2:
		_sceneEnterX3 = stackPos(1);
		_sceneEnterY3 = stackPos(2);
		break;

	case 3:
		_sceneEnterX4 = stackPos(1);
		_sceneEnterY4 = stackPos(2);
		break;

	default:
		break;
	}
	return 0;
}

int KyraEngine_v2::o2_runTemporaryScript(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_runTemporaryScript(%p) ('%s', %d, %d, %d)", (const void *)script, stackPosString(0), stackPos(1),
			stackPos(2), stackPos(3));

	runTemporaryScript(stackPosString(0), stackPos(3), stackPos(2) ? 1 : 0, stackPos(1), stackPos(2));
	return 0;
}

int KyraEngine_v2::o2_setSpecialSceneScriptRunTime(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_setSpecialSceneScriptRunTime(%p) (%d, %d)", (const void *)script, stackPos(0), stackPos(1));
	assert(stackPos(0) >= 0 && stackPos(0) < 10);
	_sceneSpecialScriptsTimer[stackPos(0)] = _system->getMillis() + stackPos(1) * _tickLength;
	return 0;
}

int KyraEngine_v2::o2_defineSceneAnim(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_defineSceneAnim(%p) (%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, '%s')", (const void *)script,
			stackPos(0), stackPos(1), stackPos(2), stackPos(3), stackPos(4), stackPos(5), stackPos(6), stackPos(7), stackPos(8),
			stackPos(9), stackPos(10), stackPos(11), stackPosString(12));
	int animId = stackPos(0);
	SceneAnim &anim = _sceneAnims[animId];
	anim.flags = stackPos(1);
	anim.x = stackPos(2);
	anim.y = stackPos(3);
	anim.x2 = stackPos(4);
	anim.y2 = stackPos(5);
	anim.width = stackPos(6);
	anim.height = stackPos(7);
	anim.unkE = stackPos(8);
	anim.specialSize = stackPos(9);
	anim.unk12 = stackPos(10);
	anim.shapeIndex = stackPos(11);
	if (stackPosString(12) != 0)
		strcpy(anim.filename, stackPosString(12));

	if (anim.flags & 0x40) {
		if (!_sceneAnimMovie[animId]->open(anim.filename, 1, 0))
			error("couldn't load '%s'", anim.filename);

		if (_sceneAnimMovie[animId]->xAdd() || _sceneAnimMovie[animId]->yAdd())
			anim.wsaFlag = 1;
		else
			anim.wsaFlag = 0;
	}

	return 0;
}

int KyraEngine_v2::o2_updateSceneAnim(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_updateSceneAnim(%p) (%d, %d)", (const void *)script, stackPos(0), stackPos(1));
	updateSceneAnim(stackPos(0), stackPos(1));
	_specialSceneScriptRunFlag = false;
	return 0;
}

int KyraEngine_v2::o2_setSceneAnimPosAndUpdate(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_setSceneAnimPosAndUpdate(%p) (%d, %d, %d, %d)", (const void *)script, stackPos(0), stackPos(1), stackPos(2), stackPos(3));
	const int anim = stackPos(0);
	_sceneAnims[anim].x2 = stackPos(1);
	_sceneAnims[anim].y2 = stackPos(2);
	if (_sceneAnims[anim].flags & 2) {
		_sceneAnims[anim].x = stackPos(1);
		_sceneAnims[anim].y = stackPos(2);
	}
	updateSceneAnim(anim, stackPos(3));
	_specialSceneScriptRunFlag = false;
	return 0;
}

int KyraEngine_v2::o2_useItemOnMainChar(ScriptState *script) {
	ScriptState tmpScript;
	_scriptInterpreter->initScript(&tmpScript, &_npcScriptData);
	_scriptInterpreter->startScript(&tmpScript, 0);
	tmpScript.regs[4] = _itemInHand;
	tmpScript.regs[0] = _mainCharacter.sceneId;

	int oldVocH = _vocHigh;
	_vocHigh = 0x5a;

	while(_scriptInterpreter->validScript(&tmpScript))
		_scriptInterpreter->runScript(&tmpScript);

	_vocHigh = oldVocH;

	return 0;
}

int KyraEngine_v2::o2_startDialogue(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_startDialogue(%p) (%d)", (const void *)script, stackPos(0));
	startDialogue(stackPos(0));
	return 0;
}

int KyraEngine_v2::o2_zanthRandomChat(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_zanthRandomChat(%p)", (const void *)script);
	zanthRandomChat();
	return 0;
}

int KyraEngine_v2::o2_setupDialogue(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_setupDialogue(%p) (%d)", (const void *)script, stackPos(0));
	setNewDlgIndex(stackPos(0));
	return 0;
}

int KyraEngine_v2::o2_getDlgIndex(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_setNewDlgIndex(%p) (%d)", (const void *)script, stackPos(0));
	return _mainCharacter.dlgIndex;
}

int KyraEngine_v2::o2_defineRoom(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_defineRoom(%p) (%d, '%s', %d, %d, %d, %d, %d, %d)", (const void *)script,
			stackPos(0), stackPosString(1), stackPos(2), stackPos(3), stackPos(4), stackPos(5), stackPos(6), stackPos(7));
	SceneDesc *scene = &_sceneList[stackPos(0)];
	strcpy(scene->filename, stackPosString(1));
	scene->exit1 = stackPos(2);
	scene->exit2 = stackPos(3);
	scene->exit3 = stackPos(4);
	scene->exit4 = stackPos(5);
	scene->flags = stackPos(6);
	scene->sound = stackPos(7);

	if (_mainCharacter.sceneId == stackPos(0)) {
		_sceneExit1 = scene->exit1;
		_sceneExit2 = scene->exit2;
		_sceneExit3 = scene->exit3;
		_sceneExit4 = scene->exit4;
	}

	return 0;
}

int KyraEngine_v2::o2_addCauldronStateTableEntry(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_addCauldronStateTableEntry(%p) (%d, %d)", (const void *)script, stackPos(0), stackPos(1));
	return addToCauldronStateTable(stackPos(0), stackPos(1)) ? 1 : 0;
}

int KyraEngine_v2::o2_setCountDown(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_setCountDown(%p) (%d)", (const void *)script, stackPos(0));
	_scriptCountDown = _system->getMillis() + stackPos(0) * _tickLength;
	return 0;
}

int KyraEngine_v2::o2_getCountDown(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_getCountDown(%p)", (const void *)script);
	uint32 time = _system->getMillis();
	return (time > _scriptCountDown) ? 0 : (_scriptCountDown - time) / _tickLength;
}

int KyraEngine_v2::o2_pressColorKey(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_pressColorKey(%p) (%d)", (const void *)script, stackPos(0));
	for (int i = 6; i; i--)
		_inputColorCode[i] = _inputColorCode[i - 1];
	_inputColorCode[0] = stackPos(0) & 0xff;
	for (int i = 0; i < 7; i++) {
		if (_presetColorCode[i] != _inputColorCode[6 - i])
			return 0;
	}
	return 1;
}

int KyraEngine_v2::o2_objectChat(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_objectChat(%p) ('%s', %d)", (const void *)script, stackPosString(0), stackPos(1));
	if (_flags.isTalkie)
		warning("Unexpected call: o2_objectChat(%p) ('%s', %d)", (const void *)script, stackPosString(0), stackPos(1));
	else
		objectChat(stackPosString(0), stackPos(1));
	return 0;
}

int KyraEngine_v2::o2_chapterChange(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_chapterChange(%p) (%d, %d)", (const void *)script, stackPos(0), stackPos(1));
	const int chapter = stackPos(0);
	const int scene = stackPos(1);

	resetItemList();

	_newChapterFile = chapter;
	runStartScript(chapter, 0);

	_mainCharacter.dlgIndex = 0;
	memset(_newSceneDlgState, 0, 32);

	static const int zShapeList[] = { 1, 2, 2, 2, 4 };
	assert(chapter > 1 && chapter <= ARRAYSIZE(zShapeList));
	loadZShapes(zShapeList[chapter-1]);

	enterNewScene(scene, (chapter == 2) ? 2 : 0, 0, 0, 0);

	return 0;
}

int KyraEngine_v2::o2_getColorCodeFlag1(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_getColorCodeFlag1(%p) ()", (const void *)script);
	return _colorCodeFlag1;
}

int KyraEngine_v2::o2_setColorCodeFlag1(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_getColorCodeFlag1(%p) (%d)", (const void *)script, stackPos(0));
	_colorCodeFlag1 = stackPos(0);
	return 0;
}

int KyraEngine_v2::o2_getColorCodeFlag2(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_getColorCodeFlag2(%p) ()", (const void *)script);
	return _colorCodeFlag2;
}

int KyraEngine_v2::o2_setColorCodeFlag2(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_getColorCodeFlag2(%p) (%d)", (const void *)script, stackPos(0));
	_colorCodeFlag2 = stackPos(0);
	return 0;
}

int KyraEngine_v2::o2_getColorCodeValue(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_getColorCodeValue(%p) (%d)", (const void *)script, stackPos(0));
	return _presetColorCode[stackPos(0)];
}

int KyraEngine_v2::o2_setColorCodeValue(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_setColorCodeValue(%p) (%d, %d)", (const void *)script, stackPos(0), stackPos(1));
	_presetColorCode[stackPos(0)] = stackPos(1) & 0xff;
	return stackPos(1) & 0xff;
}

int KyraEngine_v2::o2_countItemInstances(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_countItemInstances(%p) (%d)", (const void *)script, stackPos(0));
	uint16 item = stackPos(0);

	int count = 0;
	for (int i = 0; i < 20; ++i) {
		if (_mainCharacter.inventory[i] == item)
			++count;
	}

	if (_itemInHand == int16(item))
		++count;

	for (int i = 0; i < 30; ++i) {
		if (_itemList[i].id == item)
			++count;
	}

	if (_hiddenItems[0] == item && _newChapterFile == 1)
		++count;
	if (_hiddenItems[1] == item && _newChapterFile == 1)
		++count;
	if (_hiddenItems[2] == item && _newChapterFile == 2)
		++count;
	if (_hiddenItems[3] == item && _newChapterFile == 2)
		++count;
	if (_hiddenItems[4] == item && _newChapterFile == 1)
		++count;

	return count;
}

int KyraEngine_v2::o2_initObject(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_initObject(%p) (%d)", (const void *)script, stackPos(0));
	initTalkObject(stackPos(0));
	return 0;
}

int KyraEngine_v2::o2_npcChat(ScriptState *script) {
	if (_flags.isTalkie) {
		debugC(3, kDebugLevelScriptFuncs, "o2_npcChat(%p) ('%s', %d, %d, %d)", (const void *)script, stackPosString(0), stackPos(1), _vocHigh, stackPos(2));
		npcChatSequence(stackPosString(0), stackPos(1), _vocHigh, stackPos(2));
	} else {
		debugC(3, kDebugLevelScriptFuncs, "o2_npcChat(%p) ('%s', %d)", (const void *)script, stackPosString(0), stackPos(1));
		npcChatSequence(stackPosString(0), stackPos(1));
	}
	return 0;
}

int KyraEngine_v2::o2_deinitObject(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_deinitObject(%p) (%d)", (const void *)script, stackPos(0));
	deinitTalkObject(stackPos(0));
	return 0;
}

int KyraEngine_v2::o2_playTimSequence(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_playTimSequence(%p) ('%s')", (const void *)script, stackPosString(0));
	tim_playFullSequence(stackPosString(0));
	return 0;
}

int KyraEngine_v2::o2_makeBookOrCauldronAppear(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_makeBookOrCauldronAppear(%p) (%d)", (const void *)script, stackPos(0));
	seq_makeBookOrCauldronAppear(stackPos(0));
	return 0;
}

int KyraEngine_v2::o2_setSpecialSceneScriptState(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_setSpecialSceneScriptState(%p) (%d)", (const void *)script, stackPos(0));
	_specialSceneScriptState[stackPos(0)] = 1;
	return 1;
}

int KyraEngine_v2::o2_clearSpecialSceneScriptState(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_clearSpecialSceneScriptState(%p) (%d)", (const void *)script, stackPos(0));
	_specialSceneScriptState[stackPos(0)] = 0;
	return 0;
}

int KyraEngine_v2::o2_querySpecialSceneScriptState(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_querySpecialSceneScriptState(%p) (%d)", (const void *)script, stackPos(0));
	return _specialSceneScriptState[stackPos(0)];
}

int KyraEngine_v2::o2_resetInputColorCode(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_resetInputColorCode(%p)", (const void *)script);
	memset(_inputColorCode, 255, 7);
	return 0;
}

int KyraEngine_v2::o2_setHiddenItemsEntry(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_setHiddenItemsEntry(%p) (%d, %d)", (const void *)script, stackPos(0), stackPos(1));
	return (_hiddenItems[stackPos(0)] = stackPos(1));
}

int KyraEngine_v2::o2_getHiddenItemsEntry(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_getHiddenItemsEntry(%p) (%d)", (const void *)script, stackPos(0));
	return _hiddenItems[stackPos(0)];
}

int KyraEngine_v2::o2_mushroomEffect(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_mushroomEffect(%p)", (const void *)script);
	memcpy(_screen->getPalette(1), _screen->_currentPalette, 768);

	for (int i = 1; i < 768; i += 3)
		_screen->_currentPalette[i] = 0;	
	snd_playSoundEffect(106);
	_screen->fadePalette(_screen->_currentPalette, 90, &_updateFunctor);
	memcpy(_screen->_currentPalette, _screen->getPalette(1), 768);
	
	for (int i = 0; i < 768; i += 3) {
		_screen->_currentPalette[i] = _screen->_currentPalette[i + 1] = 0;
		_screen->_currentPalette[i + 2] += (((int8)_screen->_currentPalette[i + 2]) >> 1);
		if (_screen->_currentPalette[i + 2] > 63)
			_screen->_currentPalette[i + 2] = 63;
	}
	snd_playSoundEffect(106);
	_screen->fadePalette(_screen->_currentPalette, 90, &_updateFunctor);
	
	memcpy(_screen->_currentPalette, _screen->getPalette(1), 768);
	_screen->fadePalette(_screen->_currentPalette, 30, &_updateFunctor);	

	return 0;
}

int KyraEngine_v2::o2_customChat(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_customChat(%p) ('%s', %d, %d)", (const void *)script, stackPosString(0), stackPos(1), stackPos(2));
	strcpy((char*)_unkBuf500Bytes, stackPosString(0));
	_chatText = (char*)_unkBuf500Bytes;
	_chatObject = stackPos(1);

	_chatVocHigh = _chatVocLow = -1;
	objectChatInit(_chatText, _chatObject, _vocHigh, stackPos(2));
	playVoice(_vocHigh, stackPos(2));
	return 0;
}

int KyraEngine_v2::o2_customChatFinish(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_customChatFinish(%p) ()", (const void *)script);
	_text->restoreScreen();
	_chatText = 0;
	_chatObject = -1;
	return 0;
}

int KyraEngine_v2::o2_processPaletteIndex(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_processPaletteIndex(%p) (%d, %d, %d, %d, %d, %d)", (const void *)script, stackPos(0), stackPos(1), stackPos(2), stackPos(3), stackPos(4), stackPos(5));
	uint8 *palette = _screen->getPalette(0);
	const int index = stackPos(0);
	const bool updatePalette = (stackPos(4) != 0);
	const int delayTime = stackPos(5);
	palette[index*3+0] = (stackPos(1) * 0x3F) / 100;
	palette[index*3+1] = (stackPos(2) * 0x3F) / 100;
	palette[index*3+2] = (stackPos(3) * 0x3F) / 100;
	if (updatePalette) {
		if (delayTime > 0)
			_screen->fadePalette(palette, delayTime, &_updateFunctor);
		else
			_screen->setScreenPalette(palette);
	}
	return 0;
}

int KyraEngine_v2::o2_getBoolFromStack(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_getBoolFromStack(%p) ()", (const void *)script);
	return stackPos(0) ? 1 : 0;
}

int KyraEngine_v2::o2_setVocHigh(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_setVocHigh(%p) (%d)", (const void *)script, stackPos(0));
	_vocHigh = stackPos(0);
	return _vocHigh;
}

int KyraEngine_v2::o2_getVocHigh(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_getVocHigh(%p) ()", (const void *)script);
	return _vocHigh;
}

int KyraEngine_v2::o2_zanthiaChat(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_zanthiaChat(%p) ('%s', %d)", (const void *)script, stackPosString(0), stackPos(1));
	objectChat(stackPosString(0), 0, _vocHigh, stackPos(1));
	return 0;
}

int KyraEngine_v2::o2_isVoiceEnabled(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_isVoiceEnabled(%p) ()", (const void *)script);
	return speechEnabled() ? 1 : 0;
}

int KyraEngine_v2::o2_isVoicePlaying(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_isVoicePlaying(%p) ()", (const void *)script);
	return snd_voiceIsPlaying() ? 1 : 0;
}

int KyraEngine_v2::o2_stopVoicePlaying(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_stopVoicePlaying(%p) ()", (const void *)script);
	snd_stopVoice();
	return 0;
}

int KyraEngine_v2::o2_getGameLanguage(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_getGameLanguage(%p) ()", (const void *)script);
	return _lang;
}

int KyraEngine_v2::o2_dummy(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2_dummy(%p) ()", (const void *)script);
	return 0;
}

#pragma mark -

int KyraEngine_v2::o2t_defineNewShapes(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2t_defineNewShapes(%p) ('%s', %d, %d, %d, %d, %d, %d)", (const void *)script, stackPosString(0),
			stackPos(1), stackPos(2), stackPos(3), stackPos(4), stackPos(5), stackPos(6));

	strcpy(_newShapeFilename, stackPosString(0));
	_newShapeLastEntry = stackPos(1);
	_newShapeWidth = stackPos(2);
	_newShapeHeight = stackPos(3);
	_newShapeXAdd = stackPos(4);
	_newShapeYAdd = stackPos(5);
	//word_324EB = stackPos(6); <- never used

	return 0;
}

int KyraEngine_v2::o2t_setCurrentFrame(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2t_setCurrentFrame(%p) (%d, %d)", (const void *)script, stackPos(0), stackPos(1));
	_newShapeAnimFrame = stackPos(0);
	_newShapeDelay = stackPos(1);
	_temporaryScriptExecBit = true;
	return 0;
}

int KyraEngine_v2::o2t_playSoundEffect(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2t_playSoundEffect(%p) (%d)", (const void *)script, stackPos(0));
	snd_playSoundEffect(stackPos(0));
	return 0;
}

int KyraEngine_v2::o2t_fadeScenePal(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2t_fadeScenePal(%p) (%d, %d)", (const void *)script, stackPos(0), stackPos(1));
	fadeScenePal(stackPos(0), stackPos(1));
	return 0;
}

int KyraEngine_v2::o2t_setShapeFlag(ScriptState *script) {
	debugC(3, kDebugLevelScriptFuncs, "o2t_setShapeFlag(%p) (%d)", (const void *)script, stackPos(0));
	if (_flags.isTalkie)
		_newShapeFlag = stackPos(0);
	return 0;
}

} // end of namespace Kyra




