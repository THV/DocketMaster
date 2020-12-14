/*
 * =============================================================================
 *
 *       Filename: ruleprocessor.h
 *    Description: This module processes the court holiday rules, and
 *                 litigation events.  It creates two balanced binary search
 *                 trees to hold the data for the court rules and court events.
 *
 *        Version: 1.0.20
 *        Created: 08/18/2011
 *  Last Modified: Sun Dec 13 17:55:32 2020
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

#ifndef _RULEPROCESSOR_H_INCLUDED_
#define _RULEPROCESSOR_H_INCLUDED_

#include "./datetools.h" 


/****************************************************************************
* Symbolic Constants                                                        *
*                                                                           *
****************************************************************************/

#define MONTHS 13 /* Month is defined as 13 to account for the code for a
                    holiday that applies to all months, e.g., Sundays. */

                    /* FIXME (Thomas#1#): Update definition of MONTHS.
                    There are 12 months in a calendar year.  I should somehow
                    use a different term to implement the magic code for
                    ALLMONTHS.  Maybe use "MONTHCODES" or something like that.
                    This way, I would always have the correct constant of 12
                    months. Perhaps set allmonths to 0.  That way if I use
                    an array with 13 elements, Jan would start at 1 and
                    December would end at 12??  */

#define ALLMONTHS 13 /* This is the magic number for a holiday rule that applies
                        to every month of the year, e.g., weekends. */


#define LASTWEEK 9 /* This is the magic number for a holiday rule that applies
                    to the last x-day of a certain month */


/****************************************************************************
* Data Type Declarations: re holiday rules                                  *
*                                                                           *
****************************************************************************/

/* The holiday rules are maintained in a chained hash table data structure.  The
hash table is built up in three pieces.  The first piece is a structure to hold
data for a court holiday rule.  The second piece is a node to create the linked
list of holiday rules.  The third piece is an array of nodes indexed to the
months of the year.  Each pointer is the first node of a linked list of
holidaynodes.  Each element holds the rules for the applicable month.  There are
13 elements in the array becaues the final element applies to the linked lists
of rules that apply to every month, like weekend rules.  The hash function is
thus the months of the year.  */

struct holidayrule
{
    int month;
    char ruletype; /* holds one of three possible values: 'w' for a weekend
                    rule, 'r' for a relative rule, and 'a' for an absolute
                    rule */
    int wkday; /* the day of the wk to which the rule applies. if the rule is
                    relative. */
    int wknum; /* the week number to which the rule applies if the rule is
                    relative. */
    int day; /* the day of the holiday if the ruletype is 'a' */
    char holidayname[40]; /* the title of the holiday */
    char authority[100]; /* the statutory authority for the holiday */
};

/* structure for linked list to hold court holidays */
struct holidaynode
{
    struct holidayrule rule; /* the rule contained in this node */
    struct holidaynode *nextrule; /* pointer to the next item in the list */
};

/* The hash table itself: an array to hold an individual holiday-node linked
list for each month of the year + the ALLMONTHS rules */
extern struct holidaynode *holidayhashtable[13];

 /* :WARNING:01/29/2012 02:19:07 PM:THV: FOR DATA-HIDING PURPOSES MAKE SURE
  * THE holidayhashtable IS ONLY ACCESSIBLE TO FUNCTIONS THAT HAVE A RIGHT
  * TO ACCESS IT.  AS DECLARED HERE, IT MAY BE ACCESSIBLE EVERYWHERE. */

/****************************************************************************
* Data Type Definitions                                                     *
*                                                                           *
****************************************************************************/

/*------------------------------------------------------------------------------
 *  Data Type Definitions - Court Events
 *----------------------------------------------------------------------------*/

/* This data type is to store the class action settlement events.  The data
 * type is a simple linked list.
 */

typedef struct CourtEvent
{
    int event_id; /* Holds the event id number */
    int event_text[200]; /* Holds the name/text of the event */
    int trigger_event; /* Holds the event id number of the triggering event */
    int count; /*  Number to count. Positive means it comes AFTER the trigger,
   		   negative means it comes BEFORE the trigger. */
    enum units {days, weeks, months, quarters, years} count_pd;
    		/* The interval to count */
    char authority[100]; /* the authority for the event */
};

/* structure for linked list to hold court events */
typedef struct EventNode
{
    CourtEvent event; /* the event contained in this node */
    struct DATETIME event_date; /* the date of the event */
    struct EventNode *nextevent; /* pointer to the next item in the list */
};


/****************************************************************************
*****************************************************************************
* Function prototypes                                                       *
*                                                                           *
*****************************************************************************
****************************************************************************/

void initializelist(struct holidaynode *holidayhashtable[]);
struct holidaynode * addholidayrule(struct holidaynode *list,
                                    struct holidayrule *holiday);
void closerules(struct holidaynode *holidayhashtable[]);
void printholidayrules(struct holidaynode *holidayhashtable[]);

/* process holiday rule function: no comment block for this function yet. */

int processhrule (struct DATETIME *dt, struct holidaynode *rulenode);

/* search holiday rules function */

int isholiday (struct DATETIME *dt);


/* 
 * ===  FUNCTION  ==============================================================
 *          Name:  processevent
 *   Description:  
 *     Arguments:  
 *       Returns:  
 *     Algorithm:  
 *    References:  
 * 	   Notes:  
 * =============================================================================
 */
int processevent(struct DATETIME *dt, struct *eventnode);

/* 
 * ===  FUNCTION  ==============================================================
 *          Name:  displayschedule
 *   Description:  displays the scheduled chain of events
 *     Arguments:  pointer to eventnode
 *       Returns:  No return value
 *     Algorithm:  --
 *    References:  --
 * 	   Notes:  --
 * =============================================================================
 */

void displayschedule(struct *eventnode)

#ifdef UNDEF /* presently the remainder of this source file is removed from
compilation for testing. */

/*  The following enum is to implement the AVL tree structures used in this
    processing program. */

enum bf /* bf = balance factor */
{
    equal = 0, /* Tree is empty or both left and right subtrees have same
                height. */
    left = 1, /* Left subtree has height that is one greater than the height
                of the tree's right subtree. */
    right = 2, /* Right subtree has height that is one greater than the height
                  of the tree's left subtree. */
};


initialize_tree(struct holidaynode);
isempty (use a different name)
SizeofResource
retrieveroot
retreieveleft
retrieveright
search
insert
deletenode
height
copyto
traverseinorder
rotation (left, right, dbl) /* dbl = double */

#endif /* UNDEF */

#endif	/* _RULESPROCESSOR_H_INCLUDED_ */
