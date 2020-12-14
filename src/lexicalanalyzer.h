/*
 * =============================================================================
 *
 *       Filename: lexicalanalyzer.h
 *
 *    Description: The lexical analyzer module reads a data file and adds the
 *                 tokens derived from the file into the rules, holidays, and
 *                 events data structures.
 *
 *        Version: 1.0
 *        Created: 09/29/2011
 *  Last Modified: Sun 26 Aug 2012 09:14:59 PM PDT
 *       Compiler: gcc
 *
 *         Author: Thomas H. Vidal (THV), thomasvidal@hotmail.com
 *   Organization: Dark Matter Software
 *
 *      Copyright: Copyright (c) 2011, Thomas H. Vidal
 *
 *	        Usage: The calling module kicks off the routines in this module by
 *	               sending the data file, file name, filetype, field names, and
 *	               the appropriate data structure.
 *    File Format: All the data files read in as of now are CSV files.
 *   Restrictions: This module does not handle the opening, closing, or checking
 *                 the data files.  That work is done in the builder module.
 *                 This module expects to receive a proper file type, with
 *                 proper fields, and the appropriate data structure to store
 *                 the tokens in.
 * Error Handling: 
 *     References: 
 *          Notes: TODO Instead of passing one data structure type, pass a
 *                 a void pointer to the data type??? 
 * =============================================================================
 */

#ifndef _LEXICALANALYZER_H_INCLUDED_
#define _LEXICALANALYZER_H_INCLUDED_


/* #####   HEADER FILE INCLUDES   ########################################### */

#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include "errorhandler.h"
/* todo: include ruleprocessor.h and graphmgr.h ??? */

/* #####   EXPORTED MACROS   ################################################ */

/* ASCII2DECIMAL convert an ASCII character into a decimal. Macro does no error
checking (of course!), but anticipates an ascii character between '0'
(ASCII 48) and 9 (ASCII 57). */

#define ASCII2DECIMAL(x) ((x)-48)


/* #####   EXPORTED SYMBOLIC CONSTANTS   #################################### */


/*------------------------------------------------------------------------------
 *  CSV Field Codes
 *----------------------------------------------------------------------------*/

/*  Define field codes for the holiday CSV File */

#define HF_MONTH "Month"
#define HF_RTYPE "Rule Type"
#define HF_RULE "Rule"
#define HF_HOLIDAY "Holiday"
#define HF_AUTHORITY "Authority"

/* Define field coedes for the events CSV File */

#define EF_EVENT "Event"
#define EF_TRIGGER "Trigger"
#define EF_COUNT "Count"
#define EF_CT_PD "Ct Pd"
#define EF_AUTHORITY "Authority"

/*------------------------------------------------------------------------------
 *  Sizes and numbers of records and fields 
 *----------------------------------------------------------------------------*/

#define MAXRECORDLENGTH = 500 /* Maximum Length (in characters of CSV File line,
				 each line consists of one record. */
#define MAXNUMFIELDS = 25 /* Maxinum number of fields in CSV File */
#define MAXFIELDLEN = 25 /* Maximum length (in chars) of name of field */

/*------------------------------------------------------------------------------
 *  Field and Text delimiters
 *----------------------------------------------------------------------------*/

#define FDELIMITER ',' /* Field delimiter for the CSV files */
#define TDELIMITER '\"' /* Text string delimiter for the CSV files */
#define NEWLINE '\n' /*  Newline */
#define NULCHAR '\0' /* nul string */
#define EMPTYFIELD '\0'

/*------------------------------------------------------------------------------
 *  Token processing flags
 *----------------------------------------------------------------------------*/

/* True if the first field delimiter is reached. */
const unsigned char BEGIN_FIELD = (1<<0);

/* True if the first text delimiter is reached. */
const unsigned char BEGIN_TSTRING = (1<<1);

/* True if the end text delimter is reached. */
const unsigned char END_TSTRING = (1<<2);

/* True if the token was found */
const unsigned char TOKEN_FOUND = (1<<7);


/* #####   EXPORTED DATA TYPES   ############################################ */

extern FILE *HOLIDAY_FILE;
extern FILE *EVENT_FILE;
extern FILE *EXTRAS_FILE;
extern EventNode eventlist; 


/* #####   EXPORTED FUNCTION DECLARATIONS   ################################# */

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

int parsefile (FILE *infile, const char *filename, FILETYPE ftype, const
               char *fields[], void *datastruct);
/* 
 * ELIMINATE void *datastruct, lexical analyzer has no need to access
 * this variable.
 *
 * */

/* 
 * ===  FUNCTION  ==============================================================
 *          Name:  parseevents
 *   Description:  This function parses the holiday file and creates a linked
 *   		   list, each node is a court event.
 *     Arguments:  File handle to events file 
 *       Returns:  Zero if successful.  Function will return a non-zero error
 *       	   code on specified errors, but this functionality has not been
 *       	   coded as yet. 
 *     Algorithm:   
 *    References:   
 * 	   Notes:   
 * =============================================================================
 */
int parseevents(FILE *events);

/****************************************************************************
*****************************************************************************
********** WARNING: UNDEVELOPED "DRAFT" FUNCTIONS                     *******
**********                                                            *******
**********                                                            *******
*****************************************************************************
****************************************************************************/

/* closerules (frees the memory allocated to the rule trees)
loadholidays(); THIS FUNCTION BELONGS IN THE BUILDER MODULE. */

#endif	/* _LEXICALANALYZER_H_INCLUDED_ */
