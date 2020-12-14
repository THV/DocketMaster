/*
 * =============================================================================
 *
 *       Filename:  testsuite.h
 *
 *    Description:  Header file for testsuite.c.  Testsuite.c creates a number
 *    		    of functions for testing the docketmaster program.
 *
 *        Version:  1.0
 *        Created:  01/29/2012 11:10:47 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thomas H. Vidal (THV), thomasvidal@hotmail.com
 *   Organization:  Dark Matter Software
 *
 *      Copyright:  Copyright (c) 2012, Thomas H. Vidal
 *
 *	    Usage:
 *    File Format:
 *   Restrictions:
 * Error Handling:
 *     References:
 *          Notes:
 * =============================================================================
 */

#ifndef _TESTSUITE_H_INCLUDED_
#define _TESTSUITE_H_INCLUDED_

/* #####   HEADER FILE INCLUDES   ########################################### */

/* #####   EXPORTED MACROS   ################################################ */

/* #####   EXPORTED SYMBOLIC CONSTANTS   #################################### */

/* #####   EXPORTED TYPE DEFINITIONS   ###################################### */

/* #####   EXPORTED DATA TYPES   ############################################ */

/* #####   EXPORTED VARIABLES   ############################################# */

/* #####   EXPORTED FUNCTION DECLARATIONS   ################################# */

void testsuite_dates(void);
void testsuite_checkholidays(void);
void holidayprinttest(struct DATETIME *dt);
void testsuite_courtdays(void);

#endif	/* _TESTSUITE_H_INCLUDED_ */


