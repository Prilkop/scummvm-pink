/* ScummVM - Scumm Interpreter
 * Copyright (C) 2004 The ScummVM project
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
/*
 Description:   
 
    Graphics maniuplation routines - private header file

 Notes: 
*/

#ifndef SAGA_GFX_H_
#define SAGA_GFX_H_

namespace Saga {

#define R_CURSOR_W 7
#define R_CURSOR_H 7

#define R_CURSOR_ORIGIN_X 4
#define R_CURSOR_ORIGIN_Y 4

#define R_CLAMP(a, min, max) \
    (a = (a < (min)) ? (min) : ((a > max) ? (max) : a ))

#define R_CLAMP_RECT( rect, xmin, xmax, ymin, ymax ) \
            R_CLAMP( rect->x1, xmin, xmax ); \
            R_CLAMP( rect->x2, xmin, xmax ); \
            R_CLAMP( rect->y1, ymin, ymax ); \
            R_CLAMP( rect->y2, ymin, ymax )

} // End of namespace Saga

#endif				/* R_GFX_H_ */
/* end "r_gfx_h_ */
