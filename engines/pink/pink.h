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
 * $URL: https://scummvm.svn.sourceforge.net/svnroot/scummvm/scummvm/trunk/engines/tucker/tucker.h $
 * $Id: tucker.h 40759 2009-05-21 13:02:56Z thebluegr $
 *
 */

#ifndef PINK_ENGINE_H
#define PINK_ENGINE_H

#include "engines/engine.h"

#include "orbfile.h"

namespace Common {
	template<class T> class Array;
}

namespace Video {
	class FlicDecoder;
}

namespace Pink {
	class CGame;
	class CModule;
	class CPage;
}

namespace Pink {

class PinkEngine: public Engine {
public:
	PinkEngine(OSystem *system);
	virtual ~PinkEngine();

	virtual Common::Error run();

private:
	Common::Error init();
	void draw(Common::Array<Video::FlicDecoder *> **layers, size_t layerscount);

	OrbFile _orbFile;

	CGame *_game;
	CModule *_module;
	CPage *_page;
};
} // namespace Pink

#endif //PINK_ENGINE_H
