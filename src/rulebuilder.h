/*
 * Filename: rulebuilder.h
 * Project: DocketMaster
 *
 * Description: This module manages the opening, verifying, and closing of rule
 * and event files.
 *
 * Version: 1.0.20
 * Created: 01/29/2012 01:01:11 PM
 * Last Modified: Fri Dec 18 23:52:08 2020
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

#ifndef  _BUILDER_H__INC
#define  _BUILDER_H__INC

/*-----------------------------------------------------------------------------
 * HEADER FILE INCLUDES 
 *----------------------------------------------------------------------------*/
#include "datetools.h"
#include <stdio.h>

/*-----------------------------------------------------------------------------
 * EXPORTED SYMBOLIC CONSTANTS 
 *----------------------------------------------------------------------------*/
enum FILETYPE {H_FILE, E_FILE, LOCAL_RUL_FILE};

/*-----------------------------------------------------------------------------
 * TYPE DEFINITIONS
 *----------------------------------------------------------------------------*/

FILE *HOLIDAY_FILE;

struct HolidayNode *holidayhashtable[13];
    /* !VARIABLE DEFINITION! This is THE instance of jurisdictions' set of
     * holiday rules.
     */

         /* :WARNING:01/29/2012 02:19:07 PM:THV: FOR DATA-HIDING PURPOSES MAKE
          * SURE THE holidayhashtable IS ONLY ACCESSIBLE TO FUNCTIONS THAT HAVE
          * A RIGHT TO ACCESS IT.  AS DECLARED HERE, IT MAY BE ACCESSIBLE
          * EVERYWHERE.
          */

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

void resetfile (FILE *infile);


void initializelist(struct HolidayNode *holidayhashtable[]);
struct HolidayNode * addholidayrule(struct HolidayNode *list,
                                    struct HolidayRule *holiday);
void closerules(struct HolidayNode *holidayhashtable[]);
int processevent(struct DateTime *dt, struct CourtEventNode  *eventnode);

#ifdef UNDEF 
#define UNDEF /* presently the remainder of this source file is removed from
compilation for testing. */

/*  The following enum is to implement the AVL tree structures used in this
    processing program. */

enum bf /* bf = balance factor */
{
    equal = 0, /* Tree is empty or both left and right subtrees have same
                height. */
    left = 1, /* Left subtree has height that is one greater than the height
                of the tree's right subtree. */
    right = 2, /* Right subtree has height that is one greater than the height
                  of the tree's left subtree. */
};

initialize_tree(struct HolidayNode);
isempty (use a different name)
SizeofResource
retrieveroot
retreieveleft
retrieveright
search
insert
deletenode
height
copyto
traverseinorder
rotation (left, right, dbl) /* dbl = double */

#endif /* UNDEF */

#endif   /* ----- #ifndef _BUILDER_H__INC  ----- */
