/*
 * Filename: rulebuilder.c
 * Project: DocketMaster
 *
 * Description: This module manages the opening, verifying, and closing of rule
 * and event files.
 *
 * Version: 1.0.20
 * Created: Created: 08/18/2011
 * Last Modified: Sat Dec 19 00:01:16 2020
 *
 * Author: Thomas H. Vidal (THV), thomashvidal@gmail.com
 * Organization: Dark Matter Computing
 *  
 * Copyright: Copyright (c) 2011-2020, Thomas H. Vidal
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Usage:  
 * File Format: 
 * Restrictions: 
 * Error Handling: 
 * References: 
 * Notes: 
 */

/* #####   HEADER FILE INCLUDES   ########################################### */
#include "builder.h"
#include "graphmgr.h"
#include "eprocessor.h"
#include "lexicalanalyzer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* #####   VARIABLES  -  LOCAL TO THIS SOURCE FILE   ######################## */

struct EventGraph jurisdevents; /* !VARIABLE DEFINITION! This is THE instance
                                 * of the EventGraph for the particular
                                 * jurisdiction's list of events.
                                 */ 

/* #####   FUNCTION DEFINITIONS  -  EXPORTED FUNCTIONS   #################### */

/* 
 *  Description:  This function builds the applicable rules and
 *  events for the chosen jurisdiction.
 *
 * Parameters:  Presently, the names of the three rules files are passed as
 * parameters: Holiday File, Events File, and Extras File. 
 *
 * Returns:  returns 0 if the files were open, -1 if the holiday file could
 * not be opened or found, -2 if the Events File could not be opened or found,
 * or -3 if the Extras File cound not be opened or found. 
 *
 * Algorithm:  
 * References:  
 * Notes:  
 *
 */

int buildre(char *holiday, char *events, char *extras)
{
    enum FILETYPE ftype; /* variable to store the type of file being read */
    char fields[MAXNUMFIELDS][MAXFIELDLEN]; /* the list of field names */
    extern FILE *HOLIDAY_FILE;
    extern FILE *EVENT_FILE;
    
    /* Build Holiday Rules */
    HOLIDAY_FILE = getfile(holiday);  
    initializelist(holidayhashtable);
    parsefile(HOLIDAY_FILE, holiday, ftype, fields, holidayhashtable);
	closefile(HOLIDAY_FILE); 

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

/*
 * Name: getfile
 *
 * Description: Opens a file for reading.
 *
 * Parameters: Character string representing the file name.
 *
 * Returns: File handle (pointer to the file).
 */

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
 * Name:  checkfile
 *
 * Description:  Verifies the name and version of an opened file.
 *
 * Parameters:  File handle, name of the file, and char * which the field
 * names will be copied into.
 *
 * Returns:  Returns an enum FILETYPE, which is an integer whose value is
 * 0 if the file is a holiday rules file, 1 if the file is an events file,
 * and a 2 if the file is a local rules file.
 *
 * Algorithm:  
 * References:  
 * Notes:  
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
    } else
    {
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
            index++; /* increase the index */
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

/*
 * Name: closefile
 *
 * Description: Closes a file.
 *
 * Parameters: File handle (pointer to the file).
 *
 * Returns: NULL pointer.
 *                                                                           
 */

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
 * Name:  resetfile
 * Description:  returns the file pointer to the beginning of the file.
 * Parameters:  FILE *
 * Returns:  Nothing
 * Algorithm:   
 * References:   
 * Notes:   
 */

void resetfile (FILE *infile)
{
  fseek(infile, 0L, SEEK_SET);
  clearerr(infile);

  return;
}		/* -----  end of function resetfile  ----- */


#ifdef UNDEF
#define UNDEF /* presently the remainder of source file has been removed from
                 compilation for testing. */


int loadholidays (struct HolidayNode current_holidays, char holiday_file[])
{
    FILE *holiday_file; /* file with court holidays */
    unsigned char file_buffer[100]; /*file input buffer */
    unsigned char headers[100];
    unsigned char type; /* the type of rule, 'a' = actual, 'r' = relative */
    unsigned char rule[25]; /* the rule itself */
    unsigned char ruletype[15];
    unsigned char holiday[50]; /* name of holiday */
    unsigned char source[100]; /*statute or other rule declaring the Holiday */
    unsigned char *linelocation; /* a variable that points to the current
                                    position of a string */
    int index; /* a variable that points to the current postion of a string */
    /* holding variables for month, day, and year */
    int month;
    int day;
    int year;
    char dow[10];
    char *endoffile;
    int count; /* loop counter */
    int count2;
    /* enum days dow; */


    if (isempty(current_holidays) !=0)
        return -1; /* indicates holidays already loaded */

    /*------------------>            WARNING                  <---------------
     *  this function does not does not re-read the file if the binary tree  
     *  for current_holidays contains data.  If the court or jurisdiction   
     *  changes and the holidays need to be re-read and processed, the binary
     *  tree must be initialized before calling this function.
     */

    /* TODO (Thomas#1#): Address the issue of re-reading the file
    if the court jurisdiction changes, etc. */


    holiday_file = fopen(holiday_file, "r"); /* open the holiday file to read */
    if (holiday_file == NULL)
    {
        printf("Cannot open HOLIDAY_FILE\n");
        exit(8);
    }

    fgets(file_buffer, sizeof(file_buffer), holiday_file);
    if (file_buffer == NULL)
    {
        printf("ERROR: HOLIDAY_FILE is EMPTY\n");
        exit(8);
    }

    /* check to see if we are reading the proper file type */
    sscanf(file_buffer, "%s", headers);
    index = 0;
    do
    {
        if (headers[index] != ',' && headers[index] != '\0')
        {

        }
    }

    fgets(file_buffer, sizeof(file_buffer), holiday_file);


    do
    {
        month = atoi(&file_buffer[0]);
        if (month == 13)
        {
            for(count = 2; count < 100; count++)
            {
                if (file_buffer[count] != ',')
                {
                    rule[count] = file_buffer[count];
                    rule[count+1] = '\0';
                    count++;
                }
                else
                {
                    rule[count] = '\0';
                    break;
                }
            }
        }
        else if (month == dt->month)
        {
            /* add instructions */
            if (month > 10)
                count = 2;
            else
                count = 1;
            ruletype[0] = file_buffer[count];
            ruletype[1] = '\0';
            if (ruletype[0] == 'A')
            {
                day = atoi(&file_buffer[count+1])
                      if (day == dt->day)
                          return 1;

            }
            else
            {
                /* instructions */
            }

        }
    }





    count = 2;
    for(count2 = 0; count < 100; count++)
    {
        if (file_buffer[count] != ',')
        {
            rule[count2] = file_buffer[count];
            rule[count2+1] = '\0';
            count2++;
        }
        else
        {
            rule[count2] = '\0';
            break;
        }
    }
    for(count2 = 0; count < 100; count++)
    {
        if (file_buffer[count] != ',')
        {
            holiday[count2] = file_buffer[count];
            count2++;
        }
        else
        {
            rule[count2] = '\0';
            break;
        }
    }
    count2 = 0;
    while (file_buffer[count] != '\0')
    {
        holiday[count2] = file_buffer[count];
        count2++;
        count++;
    }
    holiday[count2]='\0';
    printf("The type is %c\n", type);
    printf("The rule is: %s\n", rule);
    printf("The Holiday is called: %s\n", holiday);
    printf("The Holiday is set forth in %s\n\n", source);
    if (type != 'a')
    {
        printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
        sscanf(rule, "%d-%s-%s", &month, dow, subrule);
        printf("The Month of this Holiday is %d\n", month);
        printf("The Day of the week of this Holiday is: %s\n", dow);
        printf("The rule is: %s\n",subrule);
        printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
    }
    endoffile = fgets(file_buffer, sizeof(file_buffer), holiday_file);
        /* read next line */
}
while (endoffile != NULL);

fclose(holiday_file);
return 0;
}

#endif /* UNDEF */
