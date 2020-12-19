/*
 * Filename: utilities.h
 * Project: DocketMaster
 *
 * Description: contains a variety of utility functions used by the docket
 * master program (and its derivatives).
 *
 * Version: 1.0.20
 * Created: 03/11/2012 11:42:50 AM
 * Last Modified: Wed Dec 16 14:28:06 2020
 *
 * Author: Thomas H. Vidal (THV), thomashvidal@gmail.com
 * Organization: Dark Matter Computing
 *  
 * Copyright: Copyright (c) 2011-2020, Thomas H. Vidal
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Usage: 
 * File Format: 
 * Restrictions: 
 * Error Handling: 
 * References: 
 * Notes: 
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

