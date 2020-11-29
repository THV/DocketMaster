/*
 * ============================================================================
 *
 *       Filename: exportmgr.c
 *
 *    Description: This module contains the functions that control exporting 
 *    		       calendar items to Outlook or other calendar programs.
 *
 *        Version: 1.0.20
 *        Created: 01/14/2012 08:40:58 PM
 *  Last Modified: Sat Nov 28 22:31:12 2020
 *       Compiler: gcc
 *
 *         Author: Thomas H. Vidal (THV), thomashvidal@gmail.com
 *   Organization: Dark Matter Computing
 *  
 *      Copyright: Copyright (c) 2012-2020, Thomas H. Vidal
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
 *	        Usage: Used by DocketMaster Program
 *    File Format: Saves calendar data in outlook iCalendar format.
 *   Restrictions:   
 * Error Handling:   
 *     References: Refer to internet mail consortium website re materials re
 *     		       personal data interchange:
 *     		       http://www.imc.org/pdi/pdiproddev.html,
 *     		       iCalendar obj std: http://www.rfc-editor.org/info/rfc5545
 *     		       iCalendar TIP: RFC # 5546: http://www.rfc-editor.org/info/rfc5546  
 *
 *          Notes: This module will be expanded as necessary to cover other
 *          	   calendar formats, if necessary.  At present, it appears
 *          	   most computer calendars and smartphone (android, iPhone,
 *          	   and Blackberry) support iCalendar.
 *
 * SPDX-License-Identifier: GPL-2.0-only
 * ============================================================================
 */


/* #####   HEADER FILE INCLUDES   ########################################## */
#include <stdlib.h>
#include <errno.h>
#include "exportmgr.h"

/* #####   MACROS  -  LOCAL TO THIS SOURCE FILE   ########################## */

/* #####   SYMBOLIC CONSTANTS -  LOCAL TO THIS SOURCE FILE   ############### */

/* #####   TYPE DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ################ */

/* #####   DATA TYPES  -  LOCAL TO THIS SOURCE FILE   ###################### */

/* #####   VARIABLES  -  LOCAL TO THIS SOURCE FILE   ####################### */

/* #####   PROTOTYPES  -  LOCAL TO THIS SOURCE FILE   ###################### */

/* #####   FUNCTION DEFINITIONS  -  EXPORTED FUNCTIONS   ################### */
int write_cal_items (FILE exp_file);
{
	BEGIN:VEVENT
       DTSTAMP:19980309T231000Z
       UID:guid-1.example.com
       ORGANIZER:mailto:mrbig@example.com
       ATTENDEE;RSVP=TRUE;ROLE=REQ-PARTICIPANT;CUTYPE=GROUP:
        mailto:employee-A@example.com
       DESCRIPTION:Project XYZ Review Meeting
       CATEGORIES:MEETING
       CLASS:PUBLIC
       CREATED:19980309T130000Z
       SUMMARY:XYZ Project Review
       DTSTART;TZID=America/New_York:19980312T083000
       DTEND;TZID=America/New_York:19980312T093000
       LOCATION:1CP Conference Room 4350
}



/* #####   FUNCTION DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ############ */


/* 
 * ===  FUNCTION  ==============================================================
 *          Name:  newexportfile
 *   Description:  opens a new text file to store and save the exported
 *   		   calendar entries.
 *     Arguments:  None at present (perhaps update the function to save the file
 *     		   with a customized name and/or path)
 *       Returns:  FILE pointer
 *    References:   
 *  	   Notes:   
 * =============================================================================
 */
FILE * newexportfile (void)
{
    time_t curtimesec; /* current time in seconds */;
    struct tim *curtime; /* pointer to struct tm defined in time.h */
    char exportfilename[25]; /* file name for the export file */
    char tempstring[10]; /* string for holding intermediate values */
    FILE *out_file; /* temporary file pointer */


    /*  create the file name */
    curtimesec = time (NULL);
    *curtime = localtime (&curtimesec);
    sprintf(exportfilename, "%d", tm_year);
    sprintf(tempstring, "%d", tm_month);
    strcat(exportfilename, tempstring);
    sprintf(tempstring, "%d", tm_mday);
    strcat(exportfilename, tempstring);
    strcat(exportfilename, _EXPORTFILENAME);

    /* Open the new file */
    out_file = fopen(exportfilename, w); /*  opens the file for writing */

    /* Error Handling */
    if (out_file == NULL)
    {
	 /* :TODO:01/18/2012 11:40:49 PM:THV: Add more robust error handling */
	printf("## ERROR ## Cannot open exportfile!");
	printf("## ERROR ## Error Number: %s\n", strerror(errno));
	return out_file;
    }
    else
    {
	return out_file; /*  return the FILE* to the new file */
    }
}


/* 
 * ===  FUNCTION  ==============================================================
 *          Name:  writeheaders
 *   Description:  
 *     Arguments:   
 *       Returns:   
 *     Algorithm:   
 *    References:   
 *  	   Notes:   
 * =============================================================================
 */

int writeheaders (FILE exp_file)
{

       BEGIN:VCALENDAR
       PRODID:-//RDU Software//NONSGML HandCal//EN
       VERSION:2.0
 

}


/* 
 * ===  FUNCTION  ==============================================================
 *          Name:  addtz
 *   Description:  Add timezone to vcalendar file.
 *     Arguments:   
 *       Returns:   
 *     Algorithm:   
 *    References:   
 *  	   Notes:   
 * =============================================================================
 */

int addtz(FILE exp_file)
{

      BEGIN:VTIMEZONE
       TZID:America/New_York
       BEGIN:STANDARD
       DTSTART:19981025T020000
       TZOFFSETFROM:-0400
       TZOFFSETTO:-0500
       TZNAME:EST
       END:STANDARD
       BEGIN:DAYLIGHT
       DTSTART:19990404T020000
       TZOFFSETFROM:-0500
       TZOFFSETTO:-0400
       TZNAME:EDT
       END:DAYLIGHT
       END:VTIMEZONE
 

}


/* 
 * ===  FUNCTION  ==============================================================
 *          Name:  getuid
 *   Description:  Create a unique UID
 *     Arguments:   
 *       Returns:   
 *     Algorithm:   
 *    References:   
 *  	   Notes:   
 * =============================================================================
 */

int getuid(void)
{

}

/* 
 * ===  FUNCTION  ==============================================================
 *          Name:  writeenders
 *   Description:  
 *     Arguments:   
 *       Returns:   
 *     Algorithm:   
 *    References:   
 *  	   Notes:   
 * =============================================================================
 */

int writeenders (FILE exp_file)
{

       END:VEVENT
       END:VCALENDAR


}


/* 
 * ===  FUNCTION  ==============================================================
 *          Name:  closeexportfile
 *   Description:  
 *     Arguments:   
 *       Returns:   
 *     Algorithm:   
 *    References:   
 *  	   Notes:   
 * =============================================================================
 */

int closexportfile (FILE exp_file)
{

}
