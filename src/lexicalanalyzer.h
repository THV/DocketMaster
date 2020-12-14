/*
 * Filename: lexicalanalyzer.h
 * Project: DocketMaster
 *
 * Description: The lexical analyzer module reads a data file and adds the
 * tokens derived from the file into the rules, holidays, and events data
 * structures.
 *
 * Version: 1.0.20
 * Created: 10/24/2011
 * Last Modified: Mon Dec 14 00:36:54 2020
 *
 * Author: Thomas H. Vidal (THV), thomashvidal@gmail.com
 * Organization: Dark Matter Computing
 *  
 * Copyright: Copyright (c) 2011-2020, Thomas H. Vidal
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Usage: The calling module kicks off the routines in this module by sending
 * the data file, file name, filetype, field names, and the appropriate data
 * structure.
 *
 * File Format: All the data files read in as of now are CSV files.
 *
 * Restrictions: This module does not handle the opening, closing, or checking
 * the data files.  That work is done in the builder module.  This module
 * expects to receive a proper file type, with proper fields, and the
 * appropriate data structure to store the tokens in.
 *
 * Error Handling: 
 *
 * Notes: TODO Instead of passing one data structure type, pass a
 *                 a void pointer to the data type??? 
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

/*
 * Description: This function parses the holiday file and creates the array of
 * linked lists. Each array element represents the holidays of a a particular
 * month.  The holidays are "attached" to the array via a linked list.
 *
 * Parameters: File handle to the holidays file.
 *
 * Returns: Zero if successful.  Function will return a non-zero error code on
 * specified errors, but this functionality has not been coded as yet.
 *
 * Notes The holiday field contains the holiday name.  The authority field
 * identifies the statutory (or other) legal authority for the rule.
 */

int parsefile (FILE *infile, const char *filename, FILETYPE ftype, const
               char *fields[], void *datastruct);
/* 
 * ELIMINATE void *datastruct, lexical analyzer has no need to access
 * this variable.
 *
 */

/* 
 * Description: This function parses the holiday file and creates a linked
 * list, each node is a court event.
 * 
 * Parameters: File handle to events file 
 *
 * Returns: Zero if successful.  Function will return a non-zero error code on
 * specified errors, but this functionality has not been coded as yet. 
 *
 * Notes:   
 */

int parseevents(FILE *events);

/*-----------------------------------------------------------------------------
 * WARNING: UNDEVELOPED "DRAFT" FUNCTIONS 
 *----------------------------------------------------------------------------*/
/* closerules (frees the memory allocated to the rule trees)
loadholidays(); THIS FUNCTION BELONGS IN THE BUILDER MODULE. */

#endif	/* _LEXICALANALYZER_H_INCLUDED_ */
