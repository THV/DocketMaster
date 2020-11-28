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
* Name: parseholidays                                                       *
*                                                                           *
* Description: This function parses the holiday file and creates the array  *
*   of linked lists. Each array element represents the holidays of a        *
*   a particular month.  The holidays are "attached" to the array via a     *
*   linked list.                                                            *
*                                                                           *
* Arguments: File handle to the holidays file.                              *
*                                                                           *
* Returns: Zero if successful.  Function will return a non-zero error code  *
*   on specified errors, but this functionality has not been coded as yet.  *
*                                                                           *
* Algorithm: Function reads the file character by character, inputting the  *
* parsed data into the appropriate fields of a temporary holiday rule,      *
* which is of type holiday rule. The temporary variable is then passed to   *
* the addholiday function, which stores the new rule in the appropriate     *
* index of the holidayhashtable array. The temp rule is then zeroed out and *
* the loop iterates again until it reaches EOF.                             *
*                                                                           *
* File format: Version 1.0 of the Court Holiday Rules File is an ASCII text *
* file in a CSV format. The first line contains the file name and version   *
* information.  The second line contains the table column names: Month;     *
* Rule Type; Rule; Holiday; and Authority. Month is the month to which the  *
* rule applies.  Currently the number 13 (#defined as ALLMONTHS) is the     *
* code for a holiday rule that occurs in every month.  For example, in      *
* California, Saturdays and Sundays are treated as holidays. The file is    *
* organized by months to facilitate searching.  If a date is being analyzed *
* to determine if it lands on holiday, the month is checked first. If       *
* there are no holidays for a particular month, the checking function can   *
* exit early.                                                               *
*                                                                           *
* Rule type is a letter code: W = weekend; A = absolute; R = relative.  A   *
* weekend rule are rules for Saturdays and Sundays.  Absolute rules are     *
* those that apply to a specific day of the month: January 1; July 4;       *
* December 25; etc.  Relative rules are those that happen according to a    *
* specific formula: the last Thursday of November; the last Monday of May;  *
* the first Monday in September; etc.                                       *
*                                                                           *
* The Rule is a code that consists of two digits in the case of an absolute *
* rule.  The two digits reflect the day on which the holiday falls: 01; 11; *
* 31; etc.  For weekend or relative rules, the code is two single digits    *
* separated by a hyphen.  The first number is the day of the week (Sunday=  *
* 0, Saturday = 6); the second number is the week number. The week number   *
* has two special values: 8, which means the holiday occurs every week; 9,  *
* which means the holiday occurs on the very last week of the month.        *
*                                                                           *
* The holiday field contains the holiday name.  The authority field         *
* identifies the statutory (or other) legal authority for the rule.         *
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
