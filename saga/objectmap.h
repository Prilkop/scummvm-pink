/* ScummVM - Scumm Interpreter
 * Copyright (C) 2004-2005 The ScummVM project
 *
 * The ReInherit Engine is (C)2000-2003 by Daniel Balsom.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header$
 *
 */

// Object map / Object click-area module header file

#ifndef SAGA_OBJECTMAP_H_
#define SAGA_OBJECTMAP_H_

#include "saga/stream.h"

namespace Saga {


class HitZone {
private:
	struct ClickArea {
		int pointsCount;
		Point *points;
	};
public:
	
	HitZone(MemoryReadStreamEndian *readStream);
	~HitZone();

	int getSceneNumber() const {
		return _nameNumber;
	}
	int getActorsEntrance() const {
		return _scriptNumber;
	}
	int getScriptNumber() const {
		return _scriptNumber;
	}
	int getRightButtonVerb() const {
		return _rightButtonVerb;
	}
	int getFlags() const {
		return _flags;
	}
	int getDirection() const {
		return ((_flags >> 4) & 0xF);
	}
	void draw(SURFACE *ds, int color);	
	bool hitTest(const Point &testPoint);
private:
	int _flags;				// HitZoneFlags
	int _clickAreasCount;
	int _rightButtonVerb;
	int _nameNumber;
	int _scriptNumber;

	ClickArea *_clickAreas;
};


class ObjectMap {
public:
	ObjectMap(SagaEngine *vm) : _vm(vm) {
		_hitZoneList = NULL;
		_hitZoneListCount = 0;

	}
	~ObjectMap(void) {
		freeMem();
	}
	void load(const byte *resourcePointer, size_t resourceLength);
	void freeMem(void);

	void draw(SURFACE *drawSurface, const Point& testPoint, int color, int color2);
	int hitTest(const Point& testPoint);
	const HitZone * getHitZone(int index) const {
		if ((index < 0) || (index >= _hitZoneListCount)) {
			error("ObjectMap::getHitZone wrong index 0x%X", index);
		}
		return _hitZoneList[index];
	}

	void cmdInfo(void);

private:
	SagaEngine *_vm;

	int _hitZoneListCount;
	HitZone **_hitZoneList;
};

} // End of namespace Saga

#endif
