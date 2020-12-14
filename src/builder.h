/*
 * Filename: builder.h
 *
 * Description: This module manages the opening, verifying, and closing of rule
 * and event files.
 *
 * Version: 1.0.20
 * Created: 01/29/2012 01:01:11 PM
 * Last Modified: Sun Dec 13 21:41:09 2020
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
 *
 * File Format: 
 * Restrictions: 
 * Error Handling: 
 * References: 
 * Notes:
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef  _BUILDER_H__INC
#define  _BUILDER_H__INC

/*-----------------------------------------------------------------------------
 * HEADER FILE INCLUDES 
 *----------------------------------------------------------------------------*/
#include <stdio.h>

/*-----------------------------------------------------------------------------
 * EXPORTED SYMBOLIC CONSTANTS 
 *----------------------------------------------------------------------------*/
enum FILETYPE {H_FILE, E_FILE, LOCAL_RUL_FILE};

/*-----------------------------------------------------------------------------
 * EXPORTED VARIABLES 
 *----------------------------------------------------------------------------*/

FILE *HOLIDAY_FILE;

struct holidaynode *holidayhashtable[13]; /* !VARIABLE DEFINITION! This is THE
					      instance of jurisdictions' set
					      of holiday rules. */

/*-----------------------------------------------------------------------------
 * EXPORTED FUNCTION DECLARATIONS 
 *----------------------------------------------------------------------------*/

/* 
 * Description:  This function builds the applicable rules and events for the
 * chosen jurisdiction.
 *
 * Parameters:  Presently, the names of the three rules files are passed as
 * parameters: Holiday File, Events File, and Extras File. 
 *
 * Returns:  returns 0 if the files were open, -1 if the holiday file could not
 * be opened or found, -2 if the Events File could not be opened or found, or
 * -3 if the Extras File cound not be
 */

int buildre(char *holiday, char *events, char *extras);

/*
 * Description: Opens a file for reading.
 * Parameters: Character string representing the file name.
 * Returns: File handle (pointer to the file).
 */

FILE * getfile(char *file_name);


/* 
 * Description:  Verifies the name and version of an opened file.
 *
 * Parameters:  File handle, name of the file, and char * which the field names
 * will be copied into.
 *
 * Returns:  Returns an enum FILETYPE, which is an integer whose value is 0 if
 * the file is a holiday rules file, 1 if the file is an events file, and a 2
 * if the file is a local rules file.
 */

enum FILETYPE checkfile (FILE *in_file, const char *filename, char *fields);


/*
 * Description: Closes a file.
 * Parameters: File handle (pointer to the file).
 * Returns: NULL pointer.
 */

int closefile(FILE *close_file);

/* 
 * Description:  returns the file pointer to the beginning of the file.
 * Parameters:  FILE *
 * Returns:  Nothing
 */

void resetfile (FILE *infile)
{
#endif   /* ----- #ifndef _BUILDER_H__INC  ----- */
