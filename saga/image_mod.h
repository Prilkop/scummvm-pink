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
 
    SAGA Image resource management routines

 Notes: 
*/

#ifndef SAGA_IMAGE_MOD_H_
#define SAGA_IMAGE_MOD_H_

namespace Saga {

int
IMG_DecodeBGImage(const uchar * image_data,
    size_t image_size,
    uchar ** output_buf, size_t * output_buf_len, int *w, int *h);

const uchar *IMG_GetImagePal(const uchar * image_data, size_t image_size);

} // End of namespace Saga

#endif				/* R_IMAGE_MOD_H_ */
/* end "r_image_mod.h" */
