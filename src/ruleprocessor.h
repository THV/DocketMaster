/****************************************************************************
* Header File Title: - ruleprocessor.h                                      *
*                                                                           *
* Author: Thomas Vidal (c) 2011                                             *
*                                                                           *
* Purpose: This header file contines the data structures and prototypes for *
*          the datetools module.                                            *
*                                                                           *
****************************************************************************/

#ifndef _RULEPROCESSOR_H_INCLUDED_
#define _RULEPROCESSOR_H_INCLUDED_

#include "..\datetime\datetools.h"
#include "..\graph manager\graphmgr.h"

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

/****************************************************************************
* Data Type Declarations: re service of process "extra day" rules           *
*                                                                           *
****************************************************************************/

struct extraservicedays
{
    unsigned char in_state_maildays;
    unsigned char out_of_state_maildays;
    unsigned char out_of_country_maildays;
    unsigned char express
}


/****************************************************************************
* Data Type Definitions                                                     *
*                                                                           *
****************************************************************************/

/* define the graph type for court events? see graphmgr.c */

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
