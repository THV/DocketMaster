/*
 * Filename: utilities.h
 *
 * Description: contains a variety of utility functions used by the docket
 * master program (and its derivatives).
 *
 * Version: 1.0.20
 * Created: 03/11/2012 11:42:50 AM
 * Last Modified: Sun Dec 13 22:31:53 2020
 *
 * Author: Thomas H. Vidal (THV), thomashvidal@gmail.com
 * Organization: Dark Matter Computing
 *  
 * Copyright: Copyright (c) 2011-2020, Thomas H. Vidal
 *
 * License: This file is part of DocketMaster.
 *
 * DocketMaster is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation,
 * version 2 of the License.
 *
 * DocketMaster is distributed in the hope that it will be
 * useful,but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with DocketMaster.  If not, see
 * <https://www.gnu.org/licenses/>.
 *
 * Usage: 
 * File Format: 
 * Restrictions: 
 * Error Handling: 
 * References: 
 * Notes: 
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef _UTILITIES_H_INCLUDED_
#define _UTILITIES_H_INCLUDED_


/*-----------------------------------------------------------------------------
 * HEADER FILE INCLUDES 
 *----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * PARAMETERIZED MACROS
 *----------------------------------------------------------------------------*/

#define SET_FLAG(x,y) ((x) |= (y))
    /* SET_BIT sets the bit in x corresponding to the event flag passed by
    the y parameter. Intended to be used with the flag constants declared
    below. */

#define CLEAR_FLAG(x,y) ((x) &= ~(y))
    /* CLEAR_BIT takes x and clears from x ALL the bits that are set in y.
    Intended to be used with the flag constants declared below. */

#define TEST_FLAG(x,y) ((x) & (y))
    /* TEST_BIT tests a single bit to see if it's "on." This will not test to
    see if MULTIPLE bits are set. */

#define TEST_MULTIPLEFLAGS(x,y) ((x) & ~(y))
    /* TEST_MULTIPLEFLAGS tests whether bits IN ADDITION TO the relevant bit
    are set */

#define CLEAR_ALLFLAGS(x) ((x) &= 0)
    /* CLEARS_ALLFLAGS zeros out the flag variable. */

#endif	/* _UTILITIES_H_INCLUDED_ */

