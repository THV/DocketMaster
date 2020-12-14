/*
 *       Filename: builder.h
 *
 *    Description: This module manages the opening, verifying, and closing of
 *                 rule and event files.
 *
 *        Version: 1.0.20
 *        Created: 08/18/2011
 *  Last Modified: Sun Dec 13 17:55:17 2020
 *
 *         Author: Thomas H. Vidal (THV), thomashvidal@gmail.com
 *   Organization: Dark Matter Computing
 *  
 *      Copyright: Copyright (c) 2011-2020, Thomas H. Vidal
 *        License: This file is part of DocketMaster.
 *
 *                 DocketMaster is free software: you can redistribute it
 *                 and/or modify it under the terms of the GNU General
 *                 Public License as published by the Free Software Foundation,
 *                 version 2 of the License.
 *
 *                 DocketMaster is distributed in the hope that it will be
 *                 useful,but WITHOUT ANY WARRANTY; without even the implied
 *                 warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *                 PURPOSE.  See the GNU General Public License for
 *                 more details.
 *
 *                 You should have received a copy of the GNU General Public
 *                 License along with DocketMaster.  If not, see
 *                 <https://www.gnu.org/licenses/>.
 *
 *	        Usage:  
 *    File Format: 
 *   Restrictions: 
 * Error Handling: 
 *     References: 
 *          Notes: 
 * 
 * SPDX-License-Identifier: GPL-2.0-only
 ===============================================================================
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

EventGraph jurisdevents; /* !VARIABLE DEFINITION! This is THE instance of the
			    EventGraph for the particular jurisdiction's list
			    of events.  */ 


/* #####   EXPORTED FUNCTION DECLARATIONS   ################################# */

/* 
 *          Name: buildre
 *   Description: This function builds the applicable rules and
 *   events for the chosen jurisdiction.
 *
 *     Parameters: Presently, the names of the three rules files are passed as
 *     parameters: Holiday File, Events File, and Extras File. 
 *
 *       Returns:  returns 0 if the files were open, -1 if the holiday file
 *       could not be opened or found, -2 if the Events File could not
 *       be opened or found, or -3 if the Extras File cound not be
 *       opened or found. 
 *
 */

int buildre(char *holiday, char *events, char *extras);

/*
 *          Name: getfile
 *   Description: Opens a file for reading.
 *    Parameters: Character string representing the file name.
 *       Returns: File handle (pointer to the file).
 *
 */

FILE * getfile(char *file_name);


/* 
 *          Name: checkfile
 *   Description: Verifies the name and version of an opened file.
 *    Parameters: File handle.
 *       Returns: Returns an enum FILETYPE, which is an integer whose value is
 *       0 if the file is a holiday rules file, 1 if the file is an
 *       events file, and a 2 if the file is a local rules file.
 *
 */

enum FILETYPE checkfile (FILE *in_file, const char *filename, char *fields);

/*
 *          Name: closefile 
 *   Description: Closes a file.
 *    Parameters: File handle (pointer to the file).
 *       Returns: NULL pointer.                      
 *
 */

int closefile(FILE *close_file);

/* 
 *          Name:  resetfile
 *   Description:  returns the file pointer to the beginning of the file.
 *    Parameters:  FILE *
 *       Returns:  Nothing
 */

void resetfile (FILE *infile);

#endif   /* ----- #ifndef _BUILDER_H__INC  ----- */
