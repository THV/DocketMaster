/****************************************************************************
* Header File Title: - lexicalanalyzer.h                                    *
*                                                                           *
* Author: Thomas Vidal (c) 2011                                             *
*                                                                           *
* Purpose: This header file contines the data structures and prototypes for *
*          the lexical analyzer module.                                     *
*                                                                           *
****************************************************************************/

#ifndef _LEXICALANALYZER_H_INCLUDED_
#define _LEXICALANALYZER_H_INCLUDED_
#include <stdio.h>
#include <stdlib.h>

/****************************************************************************
* Paramaterized Macros                                                      *
*                                                                           *
****************************************************************************/

/* ASCII2DECIMAL convert a ASCII character into a decimal. Macro does no error
checking (of course!), but anticipates an ascii character between '0'
(ASCII 48) and 9 (ASCII 57). */

#define ASCII2DECIMAL(x) ((x)-48)

/****************************************************************************
* Data Type Definitions & Declarations                                      *
*                                                                           *
****************************************************************************/

FILE *HOLIDAY_FILE;
extern FILE *EVENT_FILE;
extern FILE *EXTRAS_FILE;

/****************************************************************************
* Function prototypes                                                       *
*                                                                           *
*****************************************************************************
****************************************************************************/

/****************************************************************************
**************************   FUNCTION DECLARATION   *************************
* Name: getrulesfiles                                                       *
*                                                                           *
* Description: This function opens and analyzes the applicable rules for    *
*   the chosen jurisdiction.                                                *
*                                                                           *
* Arguments: The names of the three rules files are passed as parameters:   *
*   Holiday File, Events File, and Extras File.                             *
*                                                                           *
* Returns: returns 0 if the files were open, -1 if the holiday file could   *
*   not be opened or found, -2 if the Events File could not be opened       *
*   or found, or -3 if the Extras File cound not be opened or found.        *
*                                                                           *
****************************************************************************/

int getrulesfiles(char *holiday, char *events, char *extras);

/****************************************************************************
**************************   FUNCTION DECLARATION   *************************
* Name: parseholidays                                                       *
*                                                                           *
* Description: This function parses the holiday file and creates the AVL    *
*   binary search trees for the holidays.                                   *
*                                                                           *
* Arguments: File handle to the holidays file.                              *
*                                                                           *
* Returns: ??? return a zero if successful?                                 *
*                                                                           *
* Other sections. algorithms, file formats, references, notes, etc.         *
****************************************************************************/

int parseholidays (FILE *holidays);

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

/****************************************************************************
**************************   FUNCTION DECLARATION   *************************
* Name: checkfile                                                           *
*                                                                           *
* Description: Verifies the name and version of an opened file.             *
*                                                                           *
* Arguments: File handle.                                                   *
*                                                                           *
* Returns: Nothing right now, but may change to return an int or char       *
*   reflecting the type of opened filed.                                    *
*                                                                           *
****************************************************************************/

int checkfile (FILE *in_file);

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

FILE * closefile(FILE *close_file);

/****************************************************************************
*****************************************************************************
********** WARNING: UNDEVELOPED "DRAFT" FUNCTIONS                     *******
**********                                                            *******
**********                                                            *******
*****************************************************************************
****************************************************************************/

/* closerules (frees the memory allocated to the rule trees)
loadholidays(); */

#endif	/* _LEXICALANALYZER_H_INCLUDED_ */
