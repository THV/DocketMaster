/*
 * Filename: graphmgr.h
 * Project: DocketMaster
 *
 * Description: This is the module manages the data type that handles
 * processing the court events for the DocketMaster application program for
 * attorneys.  The events are stored in a directed network graph type.  This
 * module and the associated header file contain the various functions required
 * to create, maintain, modify, and search the database of court events.  
 *
 * Version: 1.0.20
 * Created: 10/24/2011
 * Last Modified: Mon Dec 14 00:33:43 2020
 *
 * Author: Thomas H. Vidal (THV), thomashvidal@gmail.com
 * Organization: Dark Matter Computing
 *  
 * Copyright: Copyright (c) 2011-2020, Thomas H. Vidal
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Usage: Used by the DocketMaster application to create a searchable database
 * of court events and dependencies that can be scheduled on a trial calendar. 
 *
 * File Format: 
 * Restrictions: 
 * Error Handling: 
 * References: 
 *
 * Notes: This header file contains the data structures and prototypes for the
 * graph data-type manager, which is used to store all court event information
 * (such as event deadlines and scheduling rules) and manage information.  All
 * calculations performed on the court event information are declared in the
 * eprocessor.h file.
 */

#ifndef _GRAPHMGR_H_INCLUDED_
#define _GRAPHMGR_H_INCLUDED_

/* #include "../rule processor/ruleprocessor.h"
 */

/*-----------------------------------------------------------------------------
 * Parameterized macros 
 *----------------------------------------------------------------------------*/

#define SET_FLAG(x,y) ((x) |= (y))
    /* SET_BIT sets the bit in x corresponding to the event flag passed by
    the y parameter. Intended to be used with the flag constants declared
    below. */

#define CLEAR_FLAG(x,y) ((x) &= ~(y))
    /* CLEAR_BIT takes x and clears from x ALL the bits that are set in y.
    Intended to be used with the flag constants declared below. */

#define TEST_FLAG(x,y) ((x) & (y))
    /* TEST_BIT tests a single bit to see if it's "on." This will not test to
    see if MULTIPLE bits are set. */

#define TEST_MULTIPLEFLAGS(x,y) ((x) & ~(y))
    /* TEST_MULTIPLEFLAGS tests whether bits IN ADDITION TO the relevant bit
    are set */

/*-----------------------------------------------------------------------------
 * Symbolic Constants 
 *----------------------------------------------------------------------------*/

/* Magic number used in the Dependency data type to indicate that a
countperiod_deft is invalid.  Count periods will always be positive so any
non-positive number would work.  Zero will not work because that could indicate
a legitimate countperiod.  */

const char NOT_PARTY_SENSITIVE = -126;

/* Event Flags */

/* True if the event is the beginning of a chain of events. */
const int CHAINHEAD = (1<<0);

/* True if count type is calendar days, false if it's court days */
const int CALENDARYDAYS = (1<<1);

/* True if the event counts back from the trigger date or false if the event
counts forward to the trigger date */
const int COUNTBACK = (1<<2);

/* True if the event is built up by computing intermediate dates: e.g.,
obtain discovery cut-off date, then calculate last day to serve interrogatories.
It's false if the event simply sums all the intermediate notice periods and
calculates the event's date: e.g., summary judgment must be filed 110 days
before trial if served by hand (30 days befor trial date + 75 days for notice +
5 extra days for mailing). */
const int BUILDSEGMENTS = (1<<3);

/* True if event requires "notice to" or "service on" other parties */
const int NTCRQD = (1<<4);

/* True if the event has special rules for extra days for service */
const int CUSTOMSERVICE = (1<<5);

/* True if the event is a motion */
const int MOTIONEVENT = (1<<6);

/* True if the event automatically recomputes when a trigger date is changed */
const int AUTORECOMPUTES = (1<<7);


/* Symbolic Constants: Count Units Flags */

/* True if the counting unit is week days. */
const unsigned char COUNT_DAYS = (1<<0);

/* True if the counting unit is calendar weeks. */
const unsigned char COUNT_WEEKS = (1<<1);

/* True if the counting unit is calendar months. */
const unsigned char COUNT_MONTHS = (1<<2);

/* True if the counting unit is calendar quarters. */
const unsigned char COUNT_QUARTERS = (1<<3);

/* True if the counting unit is calendar years. */
const unsigned char COUNT_YEARS = (1<<4);

/* Symbolic Constants: Dependency Flags (for the edge data type) */ 

/* True if Dependency event TRIGGERS this event; false if the Dependency event
is TRIGGERED BY this event. */
const unsigned char TRIGGERS = (1<<0);

/* True if this Dependency is a deadline; false if the Dependency is "early."
I.e., a deadline Dependency is the very last day an event can be scheduled or
that an act may be performed.  The early Dependency sets the earliest date an
event can be scheduled or an act performed. */
const unsigned char DEADLINE = (1<<1);

/* True if this event comes BEFORE the Dependency event; false if this event
comes AFTER the Dependencyevent. */
const unsigned char BEFOREDEPENDENCY = (1<<2);

/* True if this event has separate dependencies/counts for plfs and defts. */
const unsigned char PARTYSENSITIVE = (1<<3);

/* True if this event has multiple options, even though only one of which will
apply.  For example, rule might be: x must be served 10 days after trial setting
conference or 70 days before trial, which ever is closest to the trial date. */
const unsigned char MULTIPLEOPTIONS = (1<<4);

/* True if the choice of the appropriate option is the one closest to the
Dependency date where there are multiple Dependency option and only one of which
will apply.  For example, rule might be: x must be served 10 days after trial
setting conference or 70 days before trial, which ever is closest to the trial
date. */
const unsigned char CLOSEST = (1<<5);

/*-----------------------------------------------------------------------------
 * Data Type Declarations: re service of process "extra day" rules 
 *----------------------------------------------------------------------------*/

/* The following flags are TRUE if the count type is court days, FALSE if the
count type is calendar days. */

const unsigned char IN_STATE_MAIL_COURT = (1<<0);
const unsigned char OUT_OF_STATE_MAIL_COURT = (1<<1);
const unsigned char OUT_OF_COUNTRY_MAIL_COURT = (1<<2);
const unsigned char EXPRESS_MAIL_COURT = (1<<3);
const unsigned char FAX_SERVICE_COURT = (1<<4);
const unsigned char ELECTRONIC_SERVICE_COURT = (1<<5);

typedef struct{
    unsigned char counttypeflags; /* count type is a series of flags that
    indicate whether the particular service-type's extra days are calendar days
    or court days. */
    unsigned char in_state_maildays;
    unsigned char out_of_state_maildays;
    unsigned char out_of_country_maildays;
    unsigned char express_mail_days;
    unsigned char fax_servicedays;
    unsigned char electronic_servicedays;
} ExtraServiceDays;


/*
 * Data Type Declarations: the court-events directed network graph type.
 *
 * Court events will be stored in a directed graph.  The verticies will be
 * the events, the edges will be the Dependency events (the (a) "triggered
 * by" events and (b) "triggers" events. A "triggered by" event is one
 * that is triggered by another.  A "triggers" event is one that triggers
 * one or more events.)
 *
 * The data type is built up by its components.  Ultimately, the directed
 * graph is a struct containing a linked list of court events, and a 2D
 * matrix of dependencies.  The rows of the matrix identify events that
 * trigger the events in each of the cols of that row.  The cols identify
 * events that are triggered by the events identified at each row in the
 * col.
 *
 * The first declaration is of the vertex data type.  Second is the edge
 * data type.  After that, the node data-type for the linked list of court
 * events is declared.  Third, the matrix data type for the adjacency
 * matrix of dependencies is declared.  Finally, the graph is declared
 * as a struct containing a court-event list and a Dependency matrix.
 */

/*-----------------------------------------------------------------------------
 * Vertex data type - Court Events. 
 *----------------------------------------------------------------------------*/

typedef struct{
    unsigned char eventflags; /* the possible values are defined above as
    symbolic flag constants. */

    char eventitle[75]; /* full name */

    char shorttitle[50]; /* short title? Maybe use as key field? */
    /* int eventid; :NOTE:01/29/2012 08:54:50 AM:THV:DO NOT USE??? possibly
     * use to code an event id for the event. Other idea: use this to store a
     * pointer to the event itself.  E.g. struct CourtEvent *eventid ???
     */

    ExtraServiceDays customservicerule; /* custom rule applicable to
    this event for extra service days applicable to the event */

    unsigned char countunits; /* counting period: days, weeks, months, quarters,
                            years, etc. consider making this an enum or a
                            string constant. Countunits can only be one unit
                            type.  The appropriate values are declared above
                            as flag constants. */

    char ntcpd1;    /* holds the notice count period for the event */
    char ntc_dependency1[50]; /* holds the event name of any notice dependency
                                applicable to the event */
    /* some events have two dependencies, only one of which will be applicable.
    The following members add a second notice period, a second dependency, and a
    variable to compute which of the two resulting dates will be used: earlier
    or later. */

    /* TODO (Thomas#5#): Is it possible that some events could have 3 or more
    notice-dependencies?  If so, figure out a way to make this handle an
    arbitrary amount of notice-dependencies.  Maybe add it as a 3rd dimension to
    the matrix? */

    char ntcpd2; /* the second notice period */
    char ntc_dependency2[50]; /* the second notice dependency */
    char late_early; /* the flag to determine whether we pick the earlier or the
    later of the two resulting dates. */

    char eventcategory[25]; /* court event category: trial, case management,
                            motion, discovery, etc.  Consider making this an
                            enum or a string constant */

    char authority[100]; /* string to hold the authority for the rule. */

    char description[250]; /* string array to hold the text that will print out
                            describing the rule's application to the user after
                            dates are calculated and output. */

    /* linked-list triggers; linked list of events that the instant event
                            triggers. This field might be removed as an element
                            and changed to be an edge of the directed graph data
                            type.  MAY NOT BE NECESSARY BECAUSE THIS INFORMATION
                            MAY BE STORED IN THE MATRIX ALREADY.  */
} CourtEvent;

/*-----------------------------------------------------------------------------
 * Edge data type - Dependency Events. 
 *----------------------------------------------------------------------------*/
typdef struct {
    CourtEvent *dependencyhandle; /* pointer to dependent event */

    CourtEvent *dependencyhandle_deft; /* pointer to dependent event if
    there is a separate dependency for defendants.  This will be NULL if the
    PARTYSENSITIVE flag is clear. */

    unsigned char dependencyflag; /* dependency flag */

    /* Note that there is no count units member.  This struct assumes that the
    countperiod uses the same count units as the event itself.  */

    char countperiod; /* number of time-units to count to/from the dependency
        date whether the count is forward to the dependency or backward from
        the dependency depends on whether the BEFOREDEPENDENCY flag is set or
        clear. */

    char countperiod_deft; /* number of time-units to count for the defendant,
    if there is a separate dependency for defendants.  This will be -126 if the
    PARTYSENSITIVE flag is clear. */

    /* NOTE (Thomas#1#):WHAT IF DEPENDENCY RULE APPLIES ONLY IN CERTAIN TYPES OF
    LAWSUITS? ADD MEMBERS TO ADDRESS THAT ISSUE. IN THE CASE OF MULTIPLE
    DEPENDENCIES, SHOULD THIS HAVE A POINTER OR A LINKED LIST TO ALL OF THEM...
    OR WILL IT BE COVERED "ORGANICALLY" BY THE MATRIX OF DEPENDENCIES? */
} Dependency;

/*-----------------------------------------------------------------------------
 * List data type to store all the verticies (court events) 
 *----------------------------------------------------------------------------*/

typedef struct{
    CourtEvent eventdata; /* the event information contained in this
                                    node */
    int eventposn; /* the position this event has in the list of events. This
                    will be important to search dependencies at O(1) time. */
    CourtEventNode *nextevent; /* pointer to the next event */
} CourtEventNode;

/*-----------------------------------------------------------------------------
 * Adjacency Matrix data type to store all the edge information and cross-
 * reference the edges to the event list.
 *----------------------------------------------------------------------------*/

typedef struct{
    int trigger_rows; /* rows = triggering dependencies */
    int triggeredby_cols; /* cols = triggered-by dependencies */
    /* rows and cols will be set at run-time after the number of events in the
    event list is determined. */
    Dependency **rowptr; /* pointer to a pointer to a Dependency-struct,
    which will be the rows of our 2D array. This will point to the [0][0]
    element of the matrix.  */
    Dependency *matrixptr; /* pointer to a Dependency-struct, which will
    point to entire contiguous block of memory.  I.e., the simulated array. */
} Adjacencymatrix;


/*-----------------------------------------------------------------------------
 * Graph Data Type re Court Events. 
 *----------------------------------------------------------------------------*/

typedef struct EventGraph {
    CourtEventNode *eventlist;
    Adjacencymatrix dependencymatrix;
    int listsize; /* number of vertices */
    int numedges; /* number of edges */
};


/*-----------------------------------------------------------------------------
 * Function prototypes -- graph manager 
 *----------------------------------------------------------------------------*/

/*
 * Description: Initializes the vertex list (court events).
 *
 * Parameters: Takes a pointer to EventGraph.
 *
 * Returns: No return value.  This function initializes the court events
 * list only.  It does not need to initialize the matrix because entries are 
 * irrelevant until vertices have been inserted into the graph.
 */

void init_eventgraph(EventGraph* graph);

/*
 * Description: Determines whether the vertex list contains values or is
 * empty
 *
 * Parameters: Takes a pointer to EventGraph.
 *
 * Returns: If the vertex list is empty, function returns zero.  Otherwise,
 * it returns a nonnegative number.
 */

int isemptygraph(EventGraph* graph);

/*
 * Description: Copies the graph of court events into a new EventGraph.
 * copyto graph contains a distinct copy of the graph.
 *
 * Parameters: Takes pointers to two EventGraphs: one existing; the other
 * empty.
 *
 * Returns: 1 if the copy is successful, zero if it fails.
 */

int copyeventgraph (EventGraph* copyfrom, EventGraph* copyto);

/*
 * Description: Adds new court event (vertex) to the list of events.
 *
 * Parameters: Takes a pointer to CourtEvent and a pointer to the EventGraph
 * in which the new event is to be added.
 *
 * Returns: Zero if the insert fails, or a nonnegative number if the insert
 * is successful.
 */

CourtEventNode* insertevent (CourtEvent* eventinfo, CourtEventNode *eventlist);

/*
 * Description: Adds new Dependency between two events to the Dependency
 * matrix.
 *
 * Parameters: Takes a pointer to Dependency and a pointer to the EventGraph
 * in which the new Dependency is to be added.
 *
 * Returns: Zero if the insert fails, or a nonnegative number if the insert
 * is successful.
 */

int insertdependency (Dependency newdep, EventGraph* graph);

/*
 * Description: Removes a court event (vertex) from the list of events.
 *
 * Parameters: Takes a pointer to CourtEvent that is already in the list and
 * a pointer to the EventGraph itself.
 *
 * Returns: Zero if the delete fails, or a nonnegative number if the delete
 * is successful.
 */

int deleteevent  (CourtEvent* delevent, EventGraph* graph);

/*
 * Description: Removes a Dependency (edge) from the list of events.
 *
 * Parameters: Takes a pointer to Dependency that is already in the matrix
 * and a pointer to the EventGraph itself.
 *
 * Returns: Zero if the delete fails, or a nonnegative number if the delete
 * is successful.
 */

int deletedependency (Dependency* deldep, EventGraph* graph);

/* consider adding: findneighbors */

/*
 * Description: Replaces one event already in this list of events with a
 * different event.
 *
 * Parameters: Takes a pointer to CourtEvent to be added to the EventGraph
 * and a pointer to the old event to be replaced.
 *
 * Returns: Zero if the replace fails, or a nonnegative number if the
 * replace is successful.                                                    
 *
 */

int replaceevent (CourtEvent* newvertex, CourtEvent* oldvertex);

/*
 * Description: Function visits all the nodes in the EventGraph in a breadth
 * first manner. [WHAT WILL FUNCTION DO WHEN IT VISITS THE NODES?]
 *
 * Parameters: Takes a pointer to the EventGraph
 *
 * Returns: None.
 */

void traverse (EventGraph* graph); /* breadth first */

/* consider adding: isconnected */

/* consider adding: findshortestpath */

/*-----------------------------------------------------------------------------
 * Function prototypes -- matrix manager 
 *----------------------------------------------------------------------------*/
int initializeadjacencymatrix (EventGraph* graph);
void closeadjacencymatrix (void);


/*-----------------------------------------------------------------------------
 * Function prototypes -- utility functions 
 *----------------------------------------------------------------------------*/

/*
 * Description: Compares two character strings and returns negative, zero,
 * or positive if s1 is lexicographically less than, equal to, or greater
 * than s2.  The value is obtained by subtracting the characters at the
 * first position where s1 and s2 disagree. Function copied from K&R 2d at
 * 106.
 *
 * Parameters: Two character strings
 *
 * Returns: See description.
 */

int eventcmp (const char *s1, const char *s2);

#ifdef UNDEF /* presently the remainder of source file has been removed from
    compilation for testing. */

/*-----------------------------------------------------------------------------
 * Function prototypes -- list manager 
 *----------------------------------------------------------------------------*/

initializeorderedlist
isempty
sizeoforderedlist
retrieve
searchorderedlist
insertitem
deleteitem
/* copy to new list ?? */
traverselist

#endif /* UNDEF */

#endif	/* _GRAPHMGR_H_INCLUDED_ */
