/*
 *       Filename: builder.c
 *
 *    Description: This module manages the opening, verifying, and closing of
 *                 rule and event files.
 *
 *        Version: 1.0.20
 *        Created: 08/18/2011
 *  Last Modified: Sun Dec 13 17:55:54 2020
 *
 *         Author: Thomas H. Vidal (THV), thomashvidal@gmail.com
 *   Organization: Dark Matter Computing
 *  
 *      Copyright: Copyright (c) 2011-2020, Thomas H. Vidal
 *        License: This file is part of DocketMaster.
 *
 *                 DocketMaster is free software: you can redistribute it
 *                 and/or modify it under the terms of the GNU General
 *                 Public License as published by the Free Software Foundation,
 *                 version 2 of the License.
 *
 *                 DocketMaster is distributed in the hope that it will be
 *                 useful,but WITHOUT ANY WARRANTY; without even the implied
 *                 warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *                 PURPOSE.  See the GNU General Public License for
 *                 more details.
 *
 *                 You should have received a copy of the GNU General Public
 *                 License along with DocketMaster.  If not, see
 *                 <https://www.gnu.org/licenses/>.
 *
 *	        Usage:  
 *    File Format: 
 *   Restrictions: 
 * Error Handling: 
 *     References: 
 *          Notes: 
 * 
 * SPDX-License-Identifier: GPL-2.0-only
 */

/* #####   HEADER FILE INCLUDES   ########################################### */
#include <stdio.h>
#include <string.h>
#include "builder.h"
/*  #include "ruleprocessor.h" --> this is included in the header file */ 
#include "graphmgr.h"
#include "eprocessor.h"

/* #####   VARIABLES  -  LOCAL TO THIS SOURCE FILE   ######################## */

EventGraph jurisdevents; /* declared in builder.h */

/* #####   FUNCTION DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ############# */

/* 
 *          Name:  buildre
 *
 *   Description:  This function builds the applicable rules and
 *   events for the chosen jurisdiction.
 *
 *     Algorithm:  
 *    References:  
 *  	   Notes:  
 */

int buildre(char *holiday, char *events, char *extras)
{
    enum FILETYPE filetype; /* variable to store the type of file being read */
    char fields[MAXNUMFIELDS][MAXFIELDLEN]; /* the list of field names */
    extern FILE *HOLIDAY_FILE;
    extern FILE *EVENT_FILE;

    /* Build Holiday Rules */

    HOLIDAY_FILE = getfile(holiday); 
    /* check filetype, version, and row headers */
    if (checkfile(HOLIDAY_FILE) == H_FILE) {
	    initializelist(holidayhashtable);
    	parseholidays(HOLIDAY_FILE); 	
	    closefile(HOLIDAY_FILE); 
    } else {

    	/* TODO: code what happens on failure */

    }

    /*  Build the Court Events */
    EVENT_FILE = getfile(events); 
    checkfile(EVENT_FILE); 
    init_eventgraph(&jurisdevents);
    parseevents(EVENT_FILE); 
    closefile(EVENT_FILE);

    /* Build the Other Rules: Local Rules, Local-Local Rules, Etc. */
    /*  EXTRAS_FILE = getfile(extras); / open the extras file
        temporary commented out while developing eventprocessor*/

    printholidayrules(holidayhashtable);
    return 0;
}


FILE * getfile(char *file_name)
{
    FILE *in_file;
    if ((in_file = fopen(file_name, "r")) == NULL) {
        fprintf(stderr, "ERROR: File Name: %s does not exist ", file_name);
        fprintf(stderr, "or cannot be opened!\n\n\n");
        /* usage(); */
    }
    return in_file;
}		/* -----  end of function getfile  ----- */


/* 
 *   Description:  Verifies the name and version of an opened file.
 *     Algorithm:  
 *    References:  
 *  	   Notes:  
 */

enum FILETYPE checkfile (FILE *in_file, const char *filename,
                         char *fields[MAXNUMFIELDS][])
{
    char headers[MAXRECORDLENGTH]; /* buffer to read the file headers */
    char *name = NULL; /* pointer to file name */
    char *vers = NULL; /* pointer to file version */
    int index = 0; /* loop counter */

    /* read first line of file */
    fgets(headers, sizeof(headers), in_file); /* get the first line */
    if (headers == NULL)    /* if there is no line, the file is empty,
                                    return an error */
    {
        printf("ERROR: %s is EMPTY\n", filename);
        exit(8);
    } else {
        name = &headers[0];
        index = 1;
        while (headers[index] != '\n')
        {
            if (headers[index] == FIELDDELIM)
            {
                headers[index] = '\0'; /* file is CSV, to covert field delimiter
                                          to end of string character */
                if (vers == NULL)
                {
                    vers = &headers[index+1];
                    /* printf("## DEBUG ## Version = %s\n",vers); */
                }
            }
            index++; 
            if ((headers[index] == FIELDDELIM) &&
                    (headers[index+1] == FIELDDELIM))
                headers[index] = '\0';
        }
        /* printf("## DEBUG ## Version = %s\n",vers); */
        if(strcmp(name, "Court Holiday Rules File") == 0) {
		xxx;
	} else if (strcmp(name, "Court Events File") == 0) {
		asdfasdf
	}
	} else {
            printf("ERROR: This is not a rules file: %s.\n", filename);
            exit(8);
        }

        if(strcmp(vers, "V1.0") != 0)
        {
            printf("ERROR: This is not the correct version"
            	   " of the court rules file: %s.\n", filename);
            exit(8);
        }
    }

    /*  Get the field names and store them in the fields array of strings */

    fgets(headers, sizeof(headers), in_file); /* gets the next line of the file
            which should contain the CSV field names. */
    
    strcpy(fields[index], ftotok(headers, FIELDDELIM, TDELIM));
    index++;

    while(headers) { /* When headers = NULL then loop terminates */
        strcpy(fields[index], ftotok('\0', FIELDDELIM, TDELIM));
        index++;
    }

    return 0;
}

int closefile(FILE *close_file)
{
    if( fclose(infile) == EOF ) { 
    fprintf ( stderr, "Couldn't close file '%s'; %s\n",
	    infile_file_name, strerror(errno) );
    exit (EXIT_FAILURE);
    }
    return 0;
}		/* -----  end of function closefile  ----- */

/* 
 *   Description:  returns the file pointer to the beginning of the file.
 *     Algorithm:   
 *    References:   
 * 	   Notes:   
 */

void resetfile (FILE *infile)
{
  fseek(infile, 0L, SEEK_SET);
  clearerr(infile);

  return;
    
}		/* -----  end of function resetfile  ----- */
