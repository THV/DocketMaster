/*
 * =============================================================================
 *
 *       Filename:  exportmgr.h
 *
 *    Description:  This module contains the functions that control exporting 
 *    		    calendar items to Outlook or other calendar programs.
 *
 *        Version:  1.0
 *        Created:  01/16/2012 07:16:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thomas H. Vidal (THV), thomasvidal@hotmail.com
 *   Organization:  Dark Matter Software
 *
 *      Copyright:  Copyright (c) 2012, Thomas H. Vidal
 *
 *	    Usage:   Used by DocketMaster Program
 *    File Format:   Saves calendar data in outlook iCalendar format.
 *   Restrictions:   
 * Error Handling:   
 *     References:  Refer to internet mail consortium website re materials re
 *     		    personal data interchange:
 *     		    	http://www.imc.org/pdi/pdiproddev.html,
 *     		    	iCalendar obj std: http://www.rfc-editor.org/info/rfc5545
 *     		    	iCalendar TIP: RFC # 5546: http://www.rfc-editor.org/info/rfc5546  
 *
 *          Notes:
 * =====================================================================================
 */


/* #####   HEADER FILE INCLUDES   ########################################### */
#include <stdio.h>

/* #####   EXPORTED MACROS   ################################################ */

/* #####   EXPORTED SYMBOLIC CONSTANTS   #################################### */
const _EXPORTFILENAME[]="_dktmstr_events";
const _PRODID[]="DocketMaster/v.1.0";

/* #####   EXPORTED TYPE DEFINITIONS   ###################################### */

/* #####   EXPORTED DATA TYPES   ############################################ */

typedef struct VCAL {

       	char PRODID[25];
	char VERSION[] = "2.0";
	char TZID[25];
	char DTSTART[18];
	char TZOFFSETFROM[10];
       	char TZOFFSETTO[10];
       	char TZNAME[5];
       END:STANDARD
       BEGIN:DAYLIGHT
       DTSTART:19990404T020000
       TZOFFSETFROM:-0500
       TZOFFSETTO:-0400
       TZNAME:EDT
       END:DAYLIGHT
       END:VTIMEZONE
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
       END:VEVENT
       END:VCALENDAR
};

/* #####   EXPORTED VARIABLES   ############################################# */

/* #####   EXPORTED FUNCTION DECLARATIONS   ################################# */
FILE * newexportfile (void);
int writeheaders (FILE exp_file);
int write_cal_items (FILE exp_file);
int writeenders (FILE exp_file);
int closexportfile (FILE exp_file);
