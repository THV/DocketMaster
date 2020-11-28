/****************************************************************************
* Module Title: - lexical analyzer                                          *
*                                                                           *
* Author: Thomas Vidal (c) 2011                                             *
*                                                                           *
* Purpose: This module processes all the file data for the docketmaster     *
*   program.  It converts a stream of characters into the various tokens.   *
*                                                                           *
* Usage: [Short explanation of how to run the program.]                     *
*                                                                           *
*                                                                           *
* File Format: Comma Separated Values.  Fields: Type, Rule, Holiday,        *
*   Source. The rule field is organized as Month-DayOfWeek-Number.  The     *
*   "number" sub-field of the rule can contain (1) the week number          *
*   e.g., 4 for the 4th week, (2) the word "all" for every week-            *
*   day of the month (e.g., all Saturdays), (3) "last" for the              *
*   last week-day (e.g., last Monday), or (4) "first" for the               *
*   first week-day (e.g., first Tuesday).                                   *
*                                                                           *
* Restrictions:  List any limits or restrictions that apply to the program. *
*                   E.g., "the data file must be formatted correctly," or   *
*                   the "program does not check for input errors."          *
*                                                                           *
* Revision History: Section contains a list indicating who modified the     *
*                   program, when, and what changes were made. (Unless      *
*                   source control software is used.                        *
*                                                                           *
* Error Handling: If the program detects errors, describe what the program  *
*                   does with them.                                         *
*                                                                           *
* Notes:    insert any additional notes.                                    *
****************************************************************************/

#include "lexicalanalyzer.h"
#include "..\rule processor\ruleprocessor.h"
#include <string.h>

/* Global variable declarations */
struct holidaynode *holidaylist[13];

/****************************************************************************
**************************   FUNCTION DEFINITION   **************************
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

int getrulesfiles(char *holiday, char *events, char *extras)
{
    extern FILE *HOLIDAY_FILE;

    HOLIDAY_FILE = getfile(holiday); /* open the holiday file */
    /* EVENT_FILE = getfile(events); / open the events file /
    EXTRAS_FILE = getfile(extras); / open the extras file
        temporary commented out while debugging parseholidays module */

    parseholidays(HOLIDAY_FILE);
    printholidayrules(holidaylist);
    return 0;
}

/****************************************************************************
**************************   FUNCTION DEFINITION   **************************
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
* the addholiday
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

int parseholidays (FILE *holidays)
{
    char c; /* single character input buffer */
    struct holidayrule temprule; /* store data for the rule until it is
                                    inserted into the binary tree */
    struct holidayrule *tempptr; /* pointer to the temprule */
    int arrayindex; /* loop counter */

    /* check filetype, version, and row headers */
    checkfile(holidays);

    /* initialize the array of linked lists for the holidays */
    initializelist(holidaylist);

    /* lexically analyze the rules and build the array of linked lists.
        After running the checkfile function, the file should be
        on the line with the first rule.  */

    while ((c=fgetc(holidays)) != EOF)
        {
            /* read in the month, one char has already been read. */
            if (c == '0')
            { /* if c = '0' then the month is september or earlier */
                c = fgetc(holidays); /* read next character */

                /* TODO (Thomas#1#): Add error processing in case the month
                is not listed as a number betweeen 1 and 12. */

                temprule.month = (ASCII2DECIMAL(c));
            } else
            {
                c = fgetc(holidays); /* read next character */
                temprule.month = 10 + (ASCII2DECIMAL(c)); /* add ten reflecting
                                                        the first character read
                                                        and convert the second
                                                        ASCII character to a
                                                        number between 0 and
                                                        9. */

                /* TODO (Thomas#1#): Add error processing in case the first
                digit of the month month is != '1'. */
            }

            /* read in the rule type */
            if ((c=fgetc(holidays))==',')
                temprule.ruletype = fgetc(holidays);
                else
            {
                /* TODO (thomas#1#): Error processing, file is corrupt. */
            }

            /* read in the rule */
            if ((c=fgetc(holidays))==',')
            {
                switch (temprule.ruletype)
                {
                    case 'w':   /* Weekend Rules */
                                /* fall through */
                    case 'W':
                        temprule.wkday = ASCII2DECIMAL(fgetc(holidays));
                        c=fgetc(holidays); /* get rid of the dash */
                        temprule.wknum = ASCII2DECIMAL(fgetc(holidays));
                        break;
                    case 'a':   /* Absolute Rules */
                                /* fall through */
                    case 'A':
                        temprule.wkday = 999; /* temprule.wkday = '\0'; */
                        temprule.wknum = 999; /* temprule.wknum = '\0'; */
                        c = fgetc(holidays);
                        if (c == '0') /* the day is less than 10 */
                        {
                            c = fgetc(holidays);
                            temprule.day = ASCII2DECIMAL(c);
                        }
                        else /* day is greater than 10 */
                        {
                            temprule.day = ASCII2DECIMAL(c);
                            temprule.day = (temprule.day * 10) +
                                ASCII2DECIMAL(fgetc(holidays));
                        }

                        break;
                    case 'r':   /* Relative Rules */
                                /* fall through */
                    case 'R':
                        temprule.wkday = ASCII2DECIMAL(fgetc(holidays));
                        c=fgetc(holidays); /* get rid of the dash */
                        temprule.wknum = ASCII2DECIMAL(fgetc(holidays));
                        break;
                    default:
                        /* TODO (Thomas#1#): Add error processing in case the
                            rule is not in the proper format. */
                        break;
                }
            }
            /* read in the holiday name */
            if ((c=fgetc(holidays)) != ',') /* next char should be ',' */
                ; /* TODO (thomas#1#): Error processing, file is corrupt. */
            arrayindex = 0;
            c=fgetc(holidays);
            while (c != ',')
            {
                temprule.holidayname[arrayindex] = c;
                arrayindex++;
                c=fgetc(holidays);
            }
                /* terminate the string */
            temprule.holidayname[arrayindex] = '\0';

            /* read in the authority for the holiday */
            if ((c == '\n')) /* next char should have beeen a ',' */
                ; /* TODO (thomas#1#): Error processing, file is corrupt. */

            c=fgetc(holidays);
            arrayindex = 0;
            while (c != '\n' && c != EOF)
            {
                temprule.authority[arrayindex] = c;
                arrayindex++;
                c=fgetc(holidays);
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
        holidaylist[temprule.month-1] =
            addholidayrule(holidaylist[temprule.month-1], tempptr);

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

/****************************************************************************
**************************   FUNCTION DEFINITION   **************************
* Name: getfile                                                             *
*                                                                           *
* Description: Opens a file for reading.                                    *
*                                                                           *
* Arguments: Character string representing the file name.                   *
*                                                                           *
* Returns: File handle (pointer to the file).                               *
*                                                                           *
****************************************************************************/

FILE * getfile(char *file_name)
{
    FILE *in_file;
    if ((in_file = fopen(file_name, "r")) == NULL)
    {
        fprintf(stderr, "ERROR: File Name: %s does not exist ", file_name);
        fprintf(stderr, "or cannot be opened!\n\n\n");
        /* usage(); */
    }
    return in_file;
}

/****************************************************************************
**************************   FUNCTION DEFINITION   **************************
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

int checkfile (FILE *in_file)
{
    char headers[100]; /* buffer to read the file headers */
    char *name = NULL; /* pointer to file name */
    char *vers = NULL; /* pointer to file version */
    int index = 0; /* loop counter */

    /* read first line of file */
    fgets(headers, sizeof(headers), in_file); /* get the first line */
    if (headers == NULL)    /* if there is no line, the file is empty,
                                    return an error */
    {
        printf("ERROR: HOLIDAY_FILE is EMPTY\n");
        exit(8);
    } else
    {
        name = &headers[0];
        index = 1;
        while (headers[index] != '\n')
        {
            if (headers[index] == ',')
            {
                headers[index] = '\0'; /* file is CSV, to covert comma to
                                        end of string character */
                if (vers == NULL)
                {
                    vers = &headers[index+1];
                    /* printf("## DEBUG ## Version = %s\n",vers); */
                }
            }
            index++; /* increase the index */
            if ((headers[index] == ',') && (headers[index+1] == ','))
                headers[index] = '\0';
        }
        /* printf("## DEBUG ## Version = %s\n",vers); */
        if(strcmp(name, "Court Holiday Rules File") != 0)
        {
            printf("ERROR: This is not a court rules file.\n");
            exit(8);
        }
        if(strcmp(vers, "V1.0") != 0)
        {
            printf("ERROR: This is not the correct version");
            printf(" of the court rules file.\n");
            exit(8);
        }
    }
    fgets(headers, sizeof(headers), in_file); /* gets the next line of the file
            which should contain the CFV headers. Right now nothing happens
            with data.  It is read and discarded. */
    return 0;
}

/****************************************************************************
**************************   FUNCTION DEFINITION   **************************
* Name: closefile                                                           *
*                                                                           *
* Description: Closes a file.                                               *
*                                                                           *
* Arguments: File handle (pointer to the file).                             *
*                                                                           *
* Returns: NULL pointer.                                                    *
*                                                                           *
****************************************************************************/

FILE * closefile(FILE *close_file)
{
    fclose(close_file);
    return (close_file = NULL);
}

/****************************************************************************
*****************************************************************************
********** WARNING: UNDEVELOPED "DRAFT" FUNCTIONS                     *******
**********                                                            *******
**********                                                            *******
*****************************************************************************
****************************************************************************/

/*

closerules (frees the memory allocated to the rule trees)
loadholidays();
buildrules(EVENTS_FILE, EXTRAS_FILE);

*/
