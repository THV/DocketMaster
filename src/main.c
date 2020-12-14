/*
 * =============================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 * Version: 1.0.20
 * Created: 8/18/2011
 * Last Modified: Mon Dec 14 00:05:25 2020
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
 * Description:  
 * Parameters:  Commandline arguments: argc, *argv[] 
 * Returns:  0 on success, error otherwise 
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
 * Description:  Called when there is an error on the commandline
 * Parameters:  Char pointer to the program's name
 * Returns:  Exit 8
 * Algorithm:  
 * References:   
 * Notes:   
 */

void usage(char *program_name)
{
    fprintf(stderr, "Uasge is %s -f[filename 1] -f[filename...]\n",
            program_name);
    exit(8);
}
