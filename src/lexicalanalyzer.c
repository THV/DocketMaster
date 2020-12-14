/*
 * Filename: lexicalanalyzer.c
 *
 * Description: This module processes all the file data for the docketmaster
 *    		   program.  It converts a stream of characters into the various
 *    		   tokens. 
 *
 * Version: 1.0.20
 * Created: 0x/xx/2011 09:56:56 PM
 * Last Modified: Sun Dec 13 21:15:26 2020
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
 * File Format: 
 * Restrictions: 
 * Error Handling: 
 * References: 
 * Notes: 
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

/* #####   HEADER FILE INCLUDES   ########################################### */

#include <string.h>
#include "lexicalanalyzer.h"
#include "ruleprocessor.h"


/* #####   SYMBOLIC CONSTANTS -  LOCAL TO THIS SOURCE FILE   ################ */


/* #####   PROTOTYPES  -  LOCAL TO THIS SOURCE FILE   ####################### */

void gettokens (char *record, (*tokenize)(void *, void *, void *));
    /* Parses record into fields */

void gethtokens (char *r, char *f, struct holidayrule *hstruct);
    /* Populates holiday rule structure with fields extracted from the record */

void getevtokens (char *r, char *f, struct courtevent *estruct);
    /* Populates court event structure with fields extracted from the record */

char * ftotok (char *string, char fdelim, char tdelim);
    /* Convert fields in record to tokens */


/* #####   FUNCTION DEFINITIONS  -  EXPORTED FUNCTIONS   #################### */


/* 
 * Description:  This function parses the holiday file and creates the array
 * of linked lists. Each array element represents the holidays
 * of a particular month.  The holidays are "attached" to the
 * array via a linked list. 
 *
 * Parameters:  File handle to the holidays file.
 *
 * Returns:  Zero if successful.  Function will return a non-zero error
 * code on specified errors, but this functionality has not been
 * coded as yet.
 *
 * Algorithm:  Function reads the file character by character, inputting the
 * parsed data into the appropriate fields of a temporary holiday rule, which
 * is of type holiday rule. The temporary variable is then passed to the
 * addholiday function, which stores the new rule in the appropriate index
 * of the holidayhashtable array. The temp rule is then zeroed out and
 * the loop iterates again until it reaches EOF.
 *
 * File format: Version 1.0 of the Court Holiday Rules File is an ASCII text
 * file in a CSV format. The first line contains the file name and version
 * information.  The second line contains the table column names: Month; Rule
 * Type; Rule; Holiday; and Authority.  Month is the month to which the rule
 * applies.  Currently the * number 13 (#defined as ALLMONTHS) is the code for
 * a holiday * rule that occurs in every month.  For example, in California,
 * Saturdays and Sundays are treated as holidays. The file is organized by
 * months to facilitate searching.  If a date is being analyzed to determine if
 * it lands on holiday, the month is checked first. If there are no holidays
 * for a particular * month, the checking function can exit early.
 *
 * Rule type is a letter code: W = weekend; A = absolute; R = relative.  A
 * weekend rule are rules for Saturdays and * Sundays. Absolute rules are
 * those that apply to a specific day of the month: January 1; July 4;
 * December 25; etc. Relative rules are those that happen according to a
 * specific formula: the last Thursday of November; the last Monday of
 * May; the first Monday in September; etc.
 *
 * The Rule is a code that consists of two digits in the case of an absolute
 * rule.  The two digits reflect the day on which * the holiday falls: 01;
 * 11; 31; etc.  For weekend or relative rules, the code is two single digits
 * separated by a hyphen. The first number is the day of the week (Sunday= 0, 
 * Saturday = 6); the second number is the week number. The week number has two
 * special values: 8, which means the holiday occurs every week; 9, which means
 * the holiday occurs on the very last week of the month.
 *
 * The holiday field contains the holiday name.  The authority field identifies
 * the statutory (or other) legal authority for the rule.
 */


int parsefile (FILE *infile, const char *filename,
        const char *fields[MAXNUMFIELDS][], void *datastruct)
{
    char currecord[MAXRECORDLENGTH]; /* single record input buffer */
    int curfield = 0; /* index to current field name */

    /* check filetype, version, and row headers */
    ftype = checkfile(infile, filename, fields);
 
   if (ftype == H_FILE) {
       
    /* lexically analyze the rules and build the array of linked lists.
        After running the checkfile function, the file should be
        on the line with the first rule.  */

        while ((fgets(currecord, sizeof(currecord), infile)) != EOF) {
	    
            /* The while-loop starts by reading in a record */

  	        /* Send the record to the Tokenizer: */
            *c = ftotok (*string, char fdelim, char tdelim);
            tokenize (*currecord, fields[curfield], htokens,
                (*holidayhashtable[]) datastruct);
            curfield++;
        }
    } else if (ftype == E_FILE) {
        while ((fgets(currecord, sizeof(currecord), infile)) != EOF) {

            gettokens (*currecord, fields[curfield], htokens,
                    (struct *eventnode) datastruct);

            curfield++;
        }
    }
    return 0;
}


/* 
 * Description:  Parses CSV record into fields
 * Parameters:  
 * Returns:  
 * Algorithm:  
 * References:  
 * Notes:  
 */

void gettokens (char *record, char* fieldn, (*tokenize)(void *, void *, void *))
{
    char *token;

    /* Get and display the first token or indicate no tokens. */
    if (record != NULL && *record != '\0') {
        token = ftotok(record, FDELIMITER, TDELIMITER);
        if (token != NULL) {
            tokenize(a, b, c);
        } else {
            return NULL;
        }
    } else if (record == NULL) {
        errorprocessor(NULSTRING);
    } else if (*record == NULCHAR) {
        return NULCHAR;
    }

    /* Get and display the remaining tokens in the record */
    while (token != NULL) {
        token = ftotok('\0', FDELIMITER, TDELIMITER);
        if (token != NULL) {
            tokenize(a, b, c);
        }
    }
}
    struct holidayrule temprule; /* store data for the rule until it is
                                    inserted into the binary tree */
    struct holidayrule *tempptr; /* pointer to the temprule */

     char *token;

    *token = ftotok(record, FIELDDELIM, TSTRINGDELIM);
    tokenize(/* add token to datastructure */);

    while(record) {
        *token = ftotok('\0', FIELDDELIM, TSTRINGDELIM);
        tokenize(/* add token to datastructure */);
    }

	return;
}		/* -----  end of function gettokens  ----- */

/*
 * Description:  Convert field to token
 *
 * Parameters:  Takes a character string, a field delimiter, and a text string
 * delimiter.
 *
 * Returns:  a pointer to a string containing the token or a null pointer.
 *
 * Algorithm:  The function first clears a set of token status flags.  Then the
 * function checks to determine whether this is the first time it was called
 * with a particular string.  If so, cur_char and prevpsn are set to the
 * beginnigng of the string.  Otherwise, cur_car is set to prevpsn.
 *
 * Next, the function starts a while loop that iterates until the flag
 * TOKEN_FOUND has been set.  As the loop iterates, cur_char is advanced along
 * the string.  The guts of the while loop is a case statement that processes
 * the tokens.
 *
 *
 * Notes: On the first call of the function on a particular record the user
 * must pass the string containing the record to tokenize.  On subsequent
 * calls, only a null string should be passed.  The function sets up a static
 * pointer to the next token in the record.
 */

char * ftotok (char *string, char fdelim, char tdelim)
{
    unsigned char flags;
    char *cur_char; /* character pointer to cycle through the string */
        char *tokenptr; /* Pointer to current token in the record
                           string */

    static char *prevpsn; /* Previous position in the string from the last
                             call to this function. */

    CLEAR_ALLFLAGS(flags); /* clear the flags. */

    if (string != '\0') { /* If this is the first time the string is processed */
        cur_char = prevpsn = string; /* point to the beginning of the string */

        SET_FLAG(flags, BEGIN_FIELD); /* Set the BEGIN_FIELD flag because the
                                          first field does not lead off with a
                                         delimiter. */
    } else { /* On subsequent calls, start at the previous position. */
        cur_char = prevpsn;
    }

    while (TEST_FLAG(flags, TOKEN_FOUND) == 0) {

        switch (*cur_char) {
            case FDELIMITER:
                /* If this is the first field delimiter found in the string,
                 * it is likely the start of a field.  If it's a subsequent
                 * one, it could be a character used within the text string. */

                if (TEST_FLAG(flags,BEGIN_FIELD) == 0 &&
                        TEST_FLAG(flags, BEGIN_TSTRING) == 0) {
                    
                    /* this is the first field delimiter found and we are not
                     * in a text string, so advance cur_char and set the 
                     * BEGIN_FIELD flag. */

                    cur_char++; /* point to the next char after fdelim */
                    SET_FLAG(flags,BEGIN_FIELD);
                } else if (TEST_FLAG(flags, BEGIN_TSTRING) != 0) {
                    /* We are in the middle of a text field, so ignore the 
                     * field delimiter. */

                    cur_char++;
                } else
                    /* There are two field delimiters back-to-back, which
                     * indicates and empty field. */

                    return EMPTYFIELD; /* the field does not contain data */
                break;
            case TDELIMITER:
                if (TEST_FLAG(flags, BEGIN_FIELD) == 0) {
                    /* If we are not inside a field, but we have reached a
                     * text delimiter, the file is not properly formatted. */
                    errorprocessor(NOFDELIM);
                }
                if (TEST_FLAG(flags, BEGIN_TSTRING) == 0) {
                    *cur_char = '\0'; /* terminate the string */
                    cur_char++; /* cur_char now points to first char of
                                   token. */
                    SET_FLAG(flags, BEGIN_TSTRING);
                    tokenptr = cur_char; /* Set the tokenpointer to the begin of
                                            the token. */
                    cur_char++;
                } else { /* we are at the end of the token */
                    *cur_char = '\0'; /* terminate the token string */
                    SET_FLAG(flags, TOKEN_FOUND);
                    CLEAR_FLAG(flags, BEGIN_FIELD);
                    prevpsn = cur_char+1; /* point prevpsn to the next
                                      field delimter. */
                }
                break;
            case NEWLINE:
                if (string == NULL) {
                    if (TEST_FLAG(flags, BEGIN_FIELD) != 0)
                        errorprocessor(NOTDELIM);
                    else if (TEST_FLAG(flags, BEGIN_TSTRING))
                        errorprocessor(NOTDELIM);
                    else
                        return NULL;
                } else {
                    errorprocessor(NULSTRING);
                }
                break;
            case NULCHAR:
                if (string == NULL) {
                    if (TEST_FLAG(flags, BEGIN_FIELD) != 0)
                        errorprocessor(NOTDELIM);
                    else if (TEST_FLAG(flags, BEGIN_TSTRING))
                        errorprocessor(NOTDELIM);
                } else {
                    errorprocessor(NULSTRING);
                }
                break;
            default:
                if(TEST_FLAG(flags, BEGIN_TSTRING) == 0) {
                    errorprocessor(NOTDELIM);
                } else {
                    cur_char++;
                }
                break;
        }
    }

return tokenptr;
}		/* -----  end of function ftotok  ----- */


/* 
 * Description:  Extract holiday-rule tokens from a record and populate the
 * holiday hash table with the parsed rules.
 *
 * Parameters:  A string containing a record filled with input fields used to
 * populate the hash table; a string containing the list of field names, and a
 * pointer to the holiday hash table. 
 *
 * Returns:  Nothing.
 * Algorithm:  
 * References:  
 * Notes:  
 */

void gethtokens (char *field, char *fieldname, struct holidayrule *hstruct) {

    char *posn; /* the current position of the string */

    posn = field;
    
    if (strcmp(fieldname, HF_MONTH)) {
        /*  Analyze the field to determine the month */
        if (*posn== '0') {
            /* if posn = '0' then the month is september or earlier */
            posn++; /* read next character */

            /* TODO (Thomas#1#): Add error processing in case the month
            is not listed as a number betweeen 1 and 12. */

            *hstruct->month = (ASCII2DECIMAL(*posn));
        } else {
            posn++; /* read next character of filed */
            *hstruct->month = 10 + (ASCII2DECIMAL(*posn));
			/* add ten reflecting the first character read and
			 * convert the second ASCII character to a number
			 * between 0 and 9.
			 * */

            /* TODO (Thomas#1#): Add error processing in case the first
            digit of the month month is != '1'. */
        }
    } else if (strcmp(fieldname, HF_RTYPE)) {
        *hstruct->ruletype = *posn; /* ruletype is a single character */
    } else if (strcmp(fieldname, HF_RULE)) {
        switch (temprule.ruletype) {
            case 'w':   /* Weekend Rules */
                         /* fall through */
            case 'W':
                 *hstruct->wkday = ASCII2DECIMAL(*posn);
                 posn++; /* get rid of the dash */
                 *hstruct->wknum = ASCII2DECIMAL(*posn);
                 break;
            case 'a':   /* Absolute Rules */
                        /* fall through */
            case 'A':
                *hstruct->wkday = 999; /* temprule.wkday = '\0'; */
                *hstruct->wknum = 999; /* temprule.wknum = '\0'; */
                posn++;
                if (posn == '0') { /* the day is less than 10 */
                    posn++;
                    *hstruct->.day = ASCII2DECIMAL(*++posn);
                } else { /* day is greater than 10 */
                   *hstruct->day = ASCII2DECIMAL(*posn);
                   *hstruct->day = (*hstruct->day * 10) + 
                       ASCII2DECIMAL(*++posn);
               }
               break;
            case 'r':   /* Relative Rules */
                        /* fall through */
            case 'R':
                        *hstruct->wkday = ASCII2DECIMAL(*posn);
                        posn++; /* get rid of the dash */
                        *hstruct->wknum = ASCII2DECIMAL(*++posn);
                        break;
           default:
                        /* TODO (Thomas#1#): Add error processing in case the
                            rule is not in the proper format. */
                        break;
                }
    } else if (strcmp(fieldname, HF_HOLIDAY)) {
        while(*posn) {
            *hstruct->holidayname = *posn;
            posn++;
            hstruct->holidayname++;
        }
        *hstruct->holidayname = '\0';    
    }  else if (strcmp(fieldname, HF_AUTHORITY)) {
        while(*posn) {
            *hstruct->authority = *posn;
            posn++;
            hstruct->authority++;
        }
        *hstruct->authority = '\0';    
    }  else {
	    /* Error field name not defined */
    } 

}

void getevtokens (char *r, struct holidayrule *hstruct); 
{
    return 0;
}

/* 
 * Description:  This function parses the holiday file and creates a linked
 * list, each node is a court event.
 *
 * Parameters:  File handle to events file 
 *
 * Returns:  Zero if successful.  Function will return a non-zero error code on
 * specified errors, but this functionality has not been coded as yet. 
 *
 * Algorithm:   
 * References:   
 * Notes:   
 */

int parseevents(FILE *events)
{
    char posn; /* single character input buffer */
    struct courtevent tempevent; /* store data for the event until it is
                                    inserted into the linked list */
    struct courtevent *tempptr; /* pointer to the courtevent */
    int arrayindex; /* loop counting variable */

    /* check filetype, version, and row headers */
    checkfile(events);

    /* initialize the array of linked lists for the holidays */
    initevents(eventlist);

    /* lexically analyze the events and build the linked list.
        After running the checkfile function, the file should be
        on the line with the first rule.  */

    while ((posn=fgetc(events)) != EOF)
        {
            /* read in the event id. */
            if (posn == '\"')
            { /* if posn = \" then we are at the beginning of a field */
                posn = fgetc(events); /* read next character */
		if (posn == '0') {
		    tempevent.event_id = (ASCII2DECIMAL(fgetc(events)))
		} else {
                    posn = fgetc(events); /* read next character */
		    tempevent.event_id = ((ASCII2DECIMAL(C)*10) +
			    		 (ASCII2DECIMAL(fgetc(events))))

		    /* add x * ten reflecting the first character read and
		     * convert the second ASCII character to a number between 0
		     * and 9.
		     */
            	}
	    }

            /* read in the event text */
            if ((posn=fgetc(events))==',' && posn=fgetc(events)=='\"') {
	    	arrayindex = 0;
            	posn=fgetc(events);
            	while (posn != '\"') {
	            tempevent.eventtext[arrayindex] = posn;
                    arrayindex++;
                    posn=fgetc(events);
        	}
                /* terminate the string */
            	tempevent.eventtext[arrayindex] = '\0';
}
                else
            {
                /* TODO (thomas#1#): Error processing, file is corrupt. */
            }

            /* read in the trigger event */
/* THIS IS WHERE I STOPPED WORKING AT 9:55 P.M. ON 2/16/12 */

            if ((posn=fgetc(events)) != ',') { /* next char should be ',' */
                /* TODO (thomas#1#): Error processing, file is corrupt. */
	    } else {
                posn = fgetc(events); /* read next character */
		if (posn == '-') {
		    tempevent.trigger_event = (ASCII2DECIMAL(fgetc(events)))
		} else {
                    posn = fgetc(events); /* read next character */
		    tempevent.trigger_event = ((ASCII2DECIMAL(C)*10) +
			    		 (ASCII2DECIMAL(fgetc(events))))

		    /* add x * ten reflecting the first character read and
		     * convert the second ASCII character to a number between 0
		     * and 9.
		     */


	    }

            /* read in the authority for the event */
            if ((posn == '\n')) /* next char should have beeen a ',' */
                ; /* TODO (thomas#1#): Error processing, file is corrupt. */

            posn=fgetc(holidays);
            arrayindex = 0;
            while (posn != '\n' && posn != EOF)
            {
                temprule.authority[arrayindex] = posn;
                arrayindex++;
                posn=fgetc(holidays);
            }
                /* terminate the string */
            temprule.authority[arrayindex] = '\0';

        /* add the rule to the array of linked lists note month has to be
            subtracted by one.  because the array counts from 0-12, but the
            rule file uses number 1 to 13 for human readability.  Remember, 13
            is the code for a rule that applies to ALL months (e.g.( weekends */

        /* TODO (Thomas#3#): Consider a more elegant means of addressing
            the call to addholidayrule() to avoid having to remember to subtract
            1 from the month number. Add error processing in case the month
                is not listed as a number betweeen 1 and 12. */

        tempptr = &temprule;
        holidayhashtable[temprule.month-1] =
            addholidayrule(holidayhashtable[temprule.month-1], tempptr);

        /* re-initialize temprule */
        temprule.month = 0;
        temprule.ruletype = '\0';
        temprule.wkday = 0;
        temprule.wknum = 0;
        temprule.day = 0;
        temprule.holidayname[0] = '\0';
        temprule.authority[0] = '\0';
    }
    return 0;
}
/* #####   FUNCTION DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ############# */


/*-----------------------------------------------------------------------------
 * WARNING: UNDEVELOPED "DRAFT" FUNCTIONS 
 *----------------------------------------------------------------------------*/

/*

closerules (frees the memory allocated to the rule trees)
loadholidays();
buildrules(EVENTS_FILE, EXTRAS_FILE);

*/
