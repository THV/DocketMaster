/*
 * =============================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  August 2011
 *  Last Modified: Thu 23 Feb 2012 11:07:07 PM PST
 *       Compiler:  gcc
 *
 *         Author:  Thomas H. Vidal (THV), thomasvidal@hotmail.com
 *   Organization:  Dark Matter Software
 *
 *      Copyright:  Copyright (c) 2011, Thomas H. Vidal
 *
 *	    Usage:
 *    File Format:
 *   Restrictions:
 * Error Handling:
 *     References:
 *          Notes:
 * =============================================================================
 */


/* #####   HEADER FILE INCLUDES   ########################################### */

#include <stdio.h>
#include <stdlib.h>
#include "builder.h"
#include "datetools.h"
#include "lexicalanalyzer.h"
#include "ruleprocessor.h"
#include "datetools.h"


/* #####   MACROS  -  LOCAL TO THIS SOURCE FILE   ########################### */

/* #####   SYMBOLIC CONSTANTS -  LOCAL TO THIS SOURCE FILE   ################ */

/* #####   TYPE DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ################# */

/* #####   DATA TYPES  -  LOCAL TO THIS SOURCE FILE   ####################### */

/* #####   VARIABLES  -  LOCAL TO THIS SOURCE FILE   ######################## */

FILE *HOLIDAY_FILE;

struct holidaynode *holidayhashtable[13]; /* !VARIABLE DEFINITION! This is THE
					      instance of the jurisdiction's set
					      of holiday rules. */

EventNode eventlist; /* !VARIABLE DEFINITION! This is THE instance ofthe Event
			list for a federal class action settlement list of
			events.  */ 


/* #####   PROTOTYPES  -  LOCAL TO THIS SOURCE FILE   ####################### */

void usage(char *);

/* #####   FUNCTION DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ############# */



/* 
 * ===  FUNCTION  ==============================================================
 *          Name:  main
 *   Description:  
 *     Arguments:  Commandline arguments: argc, *argv[] 
 *       Returns:  0 on success, error otherwise 
 *     Algorithm:  
 *    References:  
 *  	   Notes:  
 * =============================================================================
 */

int main(int argc, char *argv[])
{
    char *program_name;
    char *holidays_filename;
    char *events_filename;
    char *extras_filename;

    /* initialize file names */
    program_name = argv[0];
    holidays_filename = NULL;
    events_filename = NULL;
    extras_filename = NULL;

    /* Process the commandline arguments */
    while ((argc > 1) && (argv[1][0] == '-'))
    {
        switch (argv[1][1])
        {
            case 'H': /* fall through */
            case 'h':
                holidays_filename = &argv[1][2];
                break;
            case 'E': /* fall through */
            case 'e':
                events_filename = &argv[1][2];
                break;
            case 'X': /* fall through */
            case 'x':
                extras_filename = &argv[1][2];
                break;
            default:
                fprintf(stderr, "Bad option %s\n", argv[1]);
                usage(program_name);
        }
        ++argv;
        --argc;
    }
    buildre(holidays_filename, events_filename, extras_filename);
    testsuite_dates();
    testsuite_checkholidays();
    testsuite_courtdays();

    /* testsuite(); */
    return 0;
}


/* 
 * ===  FUNCTION  ==============================================================
 *          Name:  usage
 *   Description:  Called when there is an error on the commandline
 *     Arguments:  Char pointer to the program's name
 *       Returns:  Exit 8
 *     Algorithm:  
 *    References:   
 *  	   Notes:   
 * =============================================================================
 */

void usage(char *program_name)
{
    fprintf(stderr, "Uasge is %s -f[filename 1] -f[filename...]\n",
            program_name);
    exit(8);
}
