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
 */

#ifndef SHERLOCK_GRAPHICS_H
#define SHERLOCK_GRAPHICS_H

#include "common/rect.h"
#include "graphics/surface.h"

namespace Sherlock {

class Surface : public Graphics::Surface {
protected:
	virtual void addDirtyRect(const Common::Rect &r) {}
public:
    Surface(uint16 width, uint16 height);
    ~Surface();

	void blitFrom(const Graphics::Surface &src, const Common::Point &pt);
	void transBlitFrom(const Graphics::Surface &src, const Common::Point &pt);

	void fillRect(int x1, int y1, int x2, int y2, byte color);
};

} // End of namespace Sherlock

#endif
