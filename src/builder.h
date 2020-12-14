/*
 * =============================================================================
 *
 *       Filename: builder.h
 *
 *    Description: This module manages the opening, verifying, and closing
 *    		   of rule and event files.
 *
 *        Version: 1.0
 *        Created: 01/29/2012 01:01:11 PM
 *  Last Modified: Tue 28 Feb 2012 11:42:42 PM PST
 *       Compiler: gcc
 *
 *         Author: Thomas H. Vidal (THV), thomasvidal@hotmail.com
 *   Organization: Dark Matter Software
 *
 *      Copyright: Copyright (c) 2012, Thomas H. Vidal
 *
 *	    Usage: 
 *    File Format: 
 *   Restrictions: 
 * Error Handling: 
 *     References: 
 *          Notes: 
 * =============================================================================
 */


#ifndef  _BUILDER_H__INC
#define  _BUILDER_H__INC


/* #####   HEADER FILE INCLUDES   ########################################### */
#include <stdio.h>

/* #####   EXPORTED MACROS   ################################################ */

/* #####   EXPORTED SYMBOLIC CONSTANTS   #################################### */

enum FILETYPE {H_FILE, E_FILE, LOCAL_RUL_FILE};

/* #####   EXPORTED TYPE DEFINITIONS   ###################################### */

/* #####   EXPORTED DATA TYPES   ############################################ */

/* #####   EXPORTED VARIABLES   ############################################# */
FILE *HOLIDAY_FILE;

struct holidaynode *holidayhashtable[13]; /* !VARIABLE DEFINITION! This is THE
					      instance of jurisdictions' set
					      of holiday rules. */

/* #####   EXPORTED FUNCTION DECLARATIONS   ################################# */

/* 
 * ===  FUNCTION  ==============================================================
 *          Name:  buildre
 *
 *   Description:  This function builds the applicable rules and
 *   		   events for the chosen jurisdiction.
 *
 *     Arguments:  Presently, the names of the three rules files are passed as
 *     		   parameters: Holiday File, Events File, and Extras File. 
 *
 *       Returns:  returns 0 if the files were open, -1 if the holiday file
 *       	   could not be opened or found, -2 if the Events File could not
 *       	   be opened or found, or -3 if the Extras File cound not be
 *       	   opened or found. 
 *     Algorithm:  
 *    References:  
 *  	   Notes:  
 * =============================================================================
 */

int buildre(char *holiday, char *events, char *extras);

/****************************************************************************
**************************   FUNCTION DECLARATION   *************************
* Name: getfile                                                             *
*                                                                           *
* Description: Opens a file for reading.                                    *
*                                                                           *
* Arguments: Character string representing the file name.                   *
*                                                                           *
* Returns: File handle (pointer to the file).                               *
*                                                                           *
****************************************************************************/

FILE * getfile(char *file_name);


/* 
 * ===  FUNCTION  ==============================================================
 *          Name:  checkfile
 *   Description:  Verifies the name and version of an opened file.
 *     Arguments:  File handle, name of the file, and char * which the field
 *     		   names will be copied into.
 *       Returns:  Returns an enum FILETYPE, which is an integer whose value is
 *       	   0 if the file is a holiday rules file, 1 if the file is an
 *       	   events file, and a 2 if the file is a local rules file.
 *     Algorithm:  
 *    References:  
 *  	   Notes:  
 * =============================================================================
 */

enum FILETYPE checkfile (FILE *in_file, const char *filename, char *fields);


/****************************************************************************
**************************   FUNCTION DECLARATION   *************************
* Name: closefile                                                           *
*                                                                           *
* Description: Closes a file.                                               *
*                                                                           *
* Arguments: File handle (pointer to the file).                             *
*                                                                           *
* Returns: NULL pointer.                                                    *
*                                                                           *
****************************************************************************/

int closefile(FILE *close_file);

/* 
 * ===  FUNCTION  ==============================================================
 *          Name:  resetfile
 *   Description:  returns the file pointer to the beginning of the file.
 *     Arguments:  FILE *
 *       Returns:  Nothing
 *     Algorithm:   
 *    References:   
 * 	   Notes:   
 * =============================================================================
 */
void resetfile (FILE *infile)
{
#endif   /* ----- #ifndef _BUILDER_H__INC  ----- */
