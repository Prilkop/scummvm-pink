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
 
	Palette animation module header file

 Notes: 
*/

#ifndef SAGA_PALANIM_H
#define SAGA_PALANIM_H

#include "reinherit.h"

namespace Saga {

#define PALANIM_CYCLETIME 100

typedef struct PALANIM_ENTRY_tag {

	uint pal_count;
	uint color_count;
	uint cycle;

	uchar *pal_index;
	R_COLOR *colors;

} PALANIM_ENTRY;

typedef struct PALANIM_DATA_tag {

	int loaded;
	uint entry_count;

	PALANIM_ENTRY *entries;

} PALANIM_DATA;

} // End of namespace Saga

#endif

