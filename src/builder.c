/*
 * =============================================================================
 *
 *       Filename: builder.c
 *
 *    Description: This module manages the opening, verifying, and closing of
 *                 rule and event files.
 *
 *        Version: 1.0.20
 *        Created: 08/18/2011
 *  Last Modified: Sat Nov 28 22:29:56 2020
 *       Compiler: gcc
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
 ===============================================================================
 */

/* #####   HEADER FILE INCLUDES   ########################################### */
#include <stdio.h>
#include "ruleprocessor.h"
#include "graphmgr.h"
#include "eprocessor.h"

/* #####   MACROS  -  LOCAL TO THIS SOURCE FILE   ########################### */

/* #####   SYMBOLIC CONSTANTS -  LOCAL TO THIS SOURCE FILE   ################ */

/* #####   TYPE DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ################# */

/* #####   DATA TYPES  -  LOCAL TO THIS SOURCE FILE   ####################### */

/* #####   VARIABLES  -  LOCAL TO THIS SOURCE FILE   ######################## */

extern EventGraph jurisdevents; /* declared in build.h */

/* #####   PROTOTYPES  -  LOCAL TO THIS SOURCE FILE   ####################### */

/* #####   FUNCTION DEFINITIONS  -  EXPORTED FUNCTIONS   #################### */

/* #####   FUNCTION DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ############# */

/* 
 * ===  FUNCTION  ==============================================================
 *          Name:  buildre
 *
 *   Description:  This function builds the applicable rules and
 *   		   events for the chosen jurisdiction.
 *
 *     Arguments:  Presently, the names of the three rules files are passed as
 *     		   parameters: Holiday File, Events File, and Extras File. 
 *
 *       Returns:  returns 0 if the files were open, -1 if the holiday file
 *       	   could not be opened or found, -2 if the Events File could not
 *       	   be opened or found, or -3 if the Extras File cound not be
 *       	   opened or found. 
 *     Algorithm:  
 *    References:  
 *  	   Notes:  
 * =============================================================================
 */

int buildre(char *holiday, char *events, char *extras)
{
    enum FILETYPE filetype;
    extern FILE *HOLIDAY_FILE;
    extern FILE *EVENT_FILE;

    /* Build Holiday Rules */

    HOLIDAY_FILE = getfile(holiday); /* open the holiday file */
    /* check filetype, version, and row headers */
    if (checkfile(HOLIDAY_FILE) == H_FILE) {
     	
    	/* initialize the array of linked lists for the holidays */
	initializelist(holidayhashtable);
	
	/* Parse the holiday rules */
    	parseholidays(HOLIDAY_FILE); 	
	
	/* close the file */
	closefile(HOLIDAY_FILE); 
    } else {

    	/* TODO: code what happens on failure */

    }

    /*  Build the Court Events */
    EVENT_FILE = getfile(events); /* open the events file */
    checkfile(EVENT_FILE); /* check filetype, version, and row headers */
    init_eventgraph(jurisdevents); /* initialize the directed network graph */ 
    parseevents(EVENT_FILE); /* process the events */ 
    closefile(EVENT_FILE);

    /* Build the Other Rules: Local Rules, Local-Local Rules, Etc. */
    /*  EXTRAS_FILE = getfile(extras); / open the extras file
        temporary commented out while developing eventprocessor*/

    printholidayrules(holidayhashtable);
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
}		/* -----  end of function getfile  ----- */


/* 
 * ===  FUNCTION  ==============================================================
 *          Name:  checkfile
 *   Description:  Verifies the name and version of an opened file.
 *     Arguments:  File handle.
 *       Returns:  Returns an enum FILETYPE, which is an integer whose value is
 *       	   0 if the file is a holiday rules file, 1 if the file is an
 *       	   events file, and a 2 if the file is a local rules file.
 *     Algorithm:  
 *    References:  
 *  	   Notes:  
 * =============================================================================
 */

enum FILETYPE checkfile (FILE *in_file, char *filename)
{
    char headers[500]; /* buffer to read the file headers */
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
    fgets(headers, sizeof(headers), in_file); /* gets the next line of the file
            which should contain the CSV headers. Right now nothing happens
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

int closefile(FILE *close_file)
{
    if( fclose(infile) == EOF ) { /* close input file   */
    fprintf ( stderr, "Couldn't close file '%s'; %s\n",
	    infile_file_name, strerror(errno) );
    exit (EXIT_FAILURE);
    }
    return 0;
}		/* -----  end of function closefile  ----- */

/* 
 * ===  FUNCTION  ==============================================================
 *          Name:  resetfile
 *   Description:  returns the file pointer to the beginning of the file.
 *     Arguments:  FILE *
 *       Returns:  Nothing
 *     Algorithm:   
 *    References:   
 * 	   Notes:   
 * =============================================================================
 */

void resetfile (FILE *infile)
{
  fseek(infile, 0L, SEEK_SET);
  clearerr(infile);

  return;
    
}		/* -----  end of function resetfile  ----- */
