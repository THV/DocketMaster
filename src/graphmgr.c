/****************************************************************************
* graphmanager.c                                                            *
*                                                                           *
* Author: Thomas Vidal                                                      *
*                                                                           *
* Purpose: This is the module that handles processing the court events for  *
* the DocketMaster application program for attorneys.  The events are       *
* stored in a directed network graph type.  This module and the associated  *
* header file contain the various functions required to create, maintain,   *
* modify, and search the database of court events.                          *
*                                                                           *
* Usage: Used by the DocketMaster application to create a searchable        *
* database of court events and dependencies that can be scheduled on a      *
* trial calendar.                                                           *
*                                                                           *
* Revision History: [no notes as of 10/24/2011].                            *
*                                                                           *
* Error Handling: If the program detects errors, describe what the program  *
*                   does with them.                                         *
*                                                                           *
* Notes:    insert any additional notes.                                    *
****************************************************************************/

#include "graphmgr.h"
#include <stdlib.h>



/****************************************************************************
*****************************************************************************
** Function definitions -- graph manager                                   **
**                                                                         **
*****************************************************************************
****************************************************************************/


/****************************************************************************
**************************   FUNCTION DEFINITION   **************************
* Name: init_eventgraph                                                     *
*                                                                           *
* Description: Initializes the vertex list (court events).                  *
*                                                                           *
* Arguments: Takes a pointer to eventgraph.                                 *
*                                                                           *
* Returns: No return value.  This function initializes the court events     *
* list only.  It does not need to initialize the matrix because entries are *
* irrelevant until vertices have been inserted into the graph.              *
*                                                                           *
****************************************************************************/

void init_eventgraph(struct eventgraph* graph)
{
    graph->eventlist = NULL;
    graph->listsize = 0;
    graph->numedges = 0;

    graph->dependencymatrix.trigger_rows = graph->listsize;
    graph->dependencymatrix.triggeredby_cols = graph->listsize;
    graph->dependencymatrix.rowptr = NULL;
    graph->dependencymatrix.matrixptr = NULL;

    return;
}

/****************************************************************************
**************************   FUNCTION DEFINITION   **************************
* Name: isemptycourtevents                                                  *
*                                                                           *
* Description: Determines whether the vertex list contains values or is     *
* empty.                                                                    *
*                                                                           *
* Arguments: Takes a pointer to eventgraph.                                 *
*                                                                           *
* Returns: If the vertex list is empty, function returns zero.  Otherwise,  *
* it returns a nonnegative number.                                          *
*                                                                           *
****************************************************************************/

int isemptygraph(struct eventgraph* graph)
{
    if (graph->eventlist == NULL)
        return 1;
    else
        return 0;
}

/****************************************************************************
**************************   FUNCTION DEFINITION   **************************
* Name: copyeventgraph                                                      *
*                                                                           *
* Description: Copies the graph of court events into a new eventgraph.      *
* copyto graph contains a distinct copy of the graph.                       *
*                                                                           *
* Arguments: Takes pointers to two eventgraphs: one existing; the other     *
* empty.                                                                    *
*                                                                           *
* Returns: 1 if the copy is successful, zero if it fails.                   *
*                                                                           *
****************************************************************************/

int copyeventgraph (struct eventgraph* copyfrom, struct eventgraph* copyto)
{
    return 0;
}

/****************************************************************************
**************************   FUNCTION DEFINITION   **************************
* Name: numberofevents                                                      *
*                                                                           *
* Description: Counts the number of events in the event list.               *
*                                                                           *
* Arguments: Takes a pointer to an eventgraph.                              *
*                                                                           *
* Returns: The number of events in the eventgraph.                          *
*                                                                           *
****************************************************************************/

int numberofevents (struct courteventnode* list)
{
    struct courteventnode *cur_pos; /* current position */
    int count = 0; /* the count */

    cur_pos = list;

    while (cur_pos != NULL)
    {
        count++;
        cur_pos = cur_pos->nextevent;
    }

    return count;
}

/****************************************************************************
**************************   FUNCTION DEFINITION   **************************
* Name: numberofdependencies                                                *
*                                                                           *
* Description: Counts the number of dependencies in the adjacencymatrix.    *
*                                                                           *
* Arguments: Takes a pointer to an eventgraph.                              *
*                                                                           *
* Returns: The number of dependencies (arcs) in the eventgraph.             *
*                                                                           *
* Note: currently this only counts the TRIGGERING dependencies, not the     *
* triggered dependencies.  The triggering dependencies are the "true"       *
* dependencies.                                                             *
****************************************************************************/

int numberofdependencies (struct adjacencymatrix* dependencies)
{
    int row, col, count;

    count = 0;
    for (row = 0; row < dependencies->trigger_rows; row++)
    {
        for (col = 0; col < dependencies->triggeredby_cols; col++)
        {
            if (dependencies->rowptr[row][col].dependencyhandle != NULL  &&
                TEST_FLAG(dependencies->rowptr[row][col].dependencyflag,
                          TRIGGERS))
                    count++;
        }
    }

    return count;
}

/****************************************************************************
**************************   FUNCTION DEFINITION   **************************
* Name: searchforevent                                                      *
*                                                                           *
* Description: Determines whether a particular event (vertex) is in the     *
* event list.                                                               *
*                                                                           *
* Arguments: Takes a string pointer containing the vertex to search for,    *
* and pointer to the court event list to search.                             *
*                                                                           *
* Returns: If the graph contains a vertex that is equal to the serch string,*
* the function returns a pointer to the position of the event. Otherwise,   *
* function returns NULL.                                                    *
*                                                                           *
* Note: function is currently keyed to search only the shorttitle member of *
* the eventnode.                                                            *
****************************************************************************/

struct courteventnode* searchforevent (char *eventname,
                                       struct courteventnode* list)
{

    struct courteventnode *cur_pos; /* current position */
    char *searchstring, *eventstring;

    cur_pos = list;
    searchstring = eventname;
    eventstring = list->eventdata.shorttitle;

    while (cur_pos != NULL)
    {
        if (searchstring != NULL && eventstring != NULL &&
               *searchstring == *eventstring)
        {
            searchstring++;
            eventstring++;
        }
        else if (searchstring == NULL && eventstring == NULL)
        {
            return cur_pos; /* found a match */
        }
        else
        {
                cur_pos = cur_pos->nextevent;
                searchstring = eventname;
                eventstring = list->eventdata.shorttitle;
                continue;
        }
    }

    return cur_pos;
}

/****************************************************************************
**************************   FUNCTION DEFINITION   **************************
* Name: searchfordependency                                                 *
*                                                                           *
* Description: Determines whether a particular dependency relationship      *
* exists.                                                                   *
*                                                                           *
* Arguments: Takes pointers to two vertices and a pointer to the eventgraph *
* to search.                                                                *
*                                                                           *
* Returns: If the graph contains an a dependency relationship between       *
* event1 and event2, the function returns a pointer to the position of the  *
* dependency. Otherwise, function returns NULL.                             *
*                                                                           *
* Note: The order of vertices is important. It will determine whether       *
* vertex1 (event1) is triggeredby vertex2 (event2).                         *
****************************************************************************/

struct dependency* searchfordependency (struct courteventnode *event1,
                                        struct courteventnode *event2,
                                        struct eventgraph* graph)
{
    struct dependency* dependencyfound;

    if (graph->dependencymatrix.rowptr[event1->eventposn][event2->eventposn].dependencyhandle
        != NULL)
    {
        dependencyfound = &graph->dependencymatrix.rowptr[event1->eventposn][event2->eventposn];
        /* SYNTAX QUESTION: I am not sure if the & gives me the addres of graph,
        or the address of the dependency, like I believe it should.  Must
        test. */
    }
    else if (graph->dependencymatrix.rowptr[event2->eventposn][event1->eventposn].dependencyhandle
             != NULL)
    {
        dependencyfound = &graph->dependencymatrix.rowptr[event2->eventposn][event1->eventposn];
    } else
        dependencyfound = NULL;

    return dependencyfound;
}

/****************************************************************************
**************************   FUNCTION DEFINITION   **************************
* Name: insertevent                                                         *
*                                                                           *
* Description: Adds new court event (vertex) to the list of events.         *
*                                                                           *
* Arguments: Takes a pointer to courtevent and a pointer to the eventgraph  *
* in which the new event is to be added.                                    *
*                                                                           *
* Returns: Zero if the insert fails, or a nonnegative number if the insert  *
* is successful.                                                            *
*                                                                           *
****************************************************************************/

int insertevent (struct courtevent* eventinfo, struct courteventnode *eventlist)
{
    struct courteventnode *new_event; /* pointer to new court event */
    struct courteventnode *temphead; /* pointer to head of event list */

    new_event = malloc(sizeof(struct courtevent)); /* creates a new node */

    /* copy the data into the new node */
    new_event->eventdata.eventflags = eventinfo->eventflags;
    strcpy(new_event->eventdata.eventitle, eventinfo->eventitle);
    strcpy(new_event->eventdata.shorttitle, eventinfo->shorttitle);
    
    new_event->eventdata.customservicerule.counttypeflags =
        eventinfo->customservicerule.counttypeflags;
    new_event->eventdata.customservicerule.in_state_maildays =
        eventinfo->customservicerule.in_state_maildays;
    new_event->eventdata.customservicerule.out_of_state_maildays =
        eventinfo->customservicerule.out_of_state_maildays;
    new_event->eventdata.customservicerule.out_of_country_maildays =
        = eventinfo->customservicerule.out_of_country_maildays;
    new_event->eventdata.customservicerule.express_mail_days =
        eventinfo->customservicerule.express_mail_days;
    new_event->eventdata.customservicerule.fax_servicedays =
        eventinfo->customservicerule.fax_servicedays;
    new_event->eventdata.customservicerule.electronic_servicedays =
        eventinfo->customservicerule.electronic_servicedays;
    
    new_event->eventdata.countunits = eventinfo->countunits;
    new_event->eventdata.ntcpd1 = eventinfo->ntcpd1;
    strcpy(new_event->eventdata.ntc_dependency1,eventinfo->ntc_dependency1);
    new_event->eventdata.ntcpd2 = eventinfo->ntcpd2;
    strcpy(new_event->eventdata.ntc_dependency2,eventinfo->ntc_dependency2);
    new_event->eventdata.late_early = eventinfo->late_early;
    strcpy(new_event->eventdata.eventcategory,eventinfo->eventcategory);
    strcpy(new_event->eventdata.authority, eventinfo->authority);
    strcpy(new_event->eventdata.description, eventinfo->description);
    
    /* place the new node in the appropriate place in the ordered list.
    if the list is presently NULL, then this item is added in first position. */
    
    if (eventlist = NULL || strcmp(eventinfo->shorttitle, ) <= )
    {
        new_event->nextevent = eventlist; /* makes the new node point to the
                                            current first node */
        eventlist = new_event; /* makes the new node the first node */
        eventlist->eventposn = 1;
    }
    else
    {
        temphead = eventlist; /* point the temporary head to the start of the
                                event list. */
        
    strcmp (char *s1, char *s2)
    
    strcmp (char *s1, char *s2)
    }
    
    
    
    
    
    return 0;
}

/****************************************************************************
**************************   FUNCTION DEFINITION   **************************
* Name: insertdependency                                                    *
*                                                                           *
* Description: Adds new dependency between two events to the dependency     *
* matrix.                                                                   *
*                                                                           *
* Arguments: Takes a pointer to dependency and a pointer to the eventgraph  *
* in which the new dependency is to be added.                               *
*                                                                           *
* Returns: Zero if the insert fails, or a nonnegative number if the insert  *
* is successful.                                                            *
*                                                                           *
****************************************************************************/

int insertdependency (struct dependency newdep, struct eventgraph* graph)
{
    return 0;
}

/****************************************************************************
**************************   FUNCTION DEFINITION   **************************
* Name: deleteevent                                                         *
*                                                                           *
* Description: Removes a court event (vertex) from the list of events.      *
*                                                                           *
* Arguments: Takes a pointer to courtevent that is already in the list and  *
* a pointer to the eventgraph itself.                                       *
*                                                                           *
* Returns: Zero if the delete fails, or a nonnegative number if the delete  *
* is successful.                                                            *
*                                                                           *
****************************************************************************/

int deleteevent  (struct courtevent* delevent, struct eventgraph* graph)
{
    return 0;
}

/****************************************************************************
**************************   FUNCTION DEFINITION   **************************
* Name: deletedependency                                                    *
*                                                                           *
* Description: Removes a dependency (edge) from the list of events.         *
*                                                                           *
* Arguments: Takes a pointer to dependency that is already in the matrix    *
* and a pointer to the eventgraph itself.                                   *
*                                                                           *
* Returns: Zero if the delete fails, or a nonnegative number if the delete  *
* is successful.                                                            *
*                                                                           *
****************************************************************************/

int deletedependency (struct dependency* deldep, struct eventgraph* graph)
{
    return 0;
}

/* consider adding: findneighbors */

/****************************************************************************
**************************   FUNCTION DEFINITION   **************************
* Name: replaceevent                                                        *
*                                                                           *
* Description: Replaces one event already in this list of events with a     *
* different event.                                                          *
*                                                                           *
* Arguments: Takes a pointer to courtevent to be added to the eventgraph    *
* and a pointer to the old event to be replaced.                            *
*                                                                           *
* Returns: Zero if the replace fails, or a nonnegative number if the        *
* replace is successful.                                                    *
*                                                                           *
****************************************************************************/

int replaceevent (struct courtevent* newvertex, struct courtevent* oldvertex)
{
    return 0;
}

/****************************************************************************
**************************   FUNCTION DEFINITION   **************************
* Name: traverse                                                            *
*                                                                           *
* Description: Function visits all the nodes in the eventgraph in a breadth *
* first manner. [WHAT WILL FUNCTION DO WHEN IT VISITS THE NODES?]           *
*                                                                           *
* Arguments: Takes a pointer to the eventgraph                              *
*                                                                           *
* Returns: None.                                                            *
*                                                                           *
****************************************************************************/

void traverse (struct eventgraph* graph)
{

}

/* consider adding: isconnected */

/* consider adding: findshortestpath */

/****************************************************************************
**************************   FUNCTION DEFINITION   **************************
* Name: followchain                                                         *
*                                                                           *
* Description: Function starts at a certain vertex and traverses through    *
* all events along the chain.  In the context of the courtevents, it starts *
* with a triggering event and visits all the events triggered by that event.*
*                                                                           *
* Arguments: Takes a pointer to the starting vertex and the eventgraph      *
*                                                                           *
* Returns: None.                                                            *
*                                                                           *
****************************************************************************/

void followchain (struct courtevent* startingvertex, struct eventgraph* graph)
{

}


/****************************************************************************
**************************   FUNCTION DEFINITION   **************************
* Name: initializeadjacencymatrix                                           *
*                                                                           *
* Description: describe what the function does.                             *
*                                                                           *
* Arguments: Describe the parameters of the function.                       *
*                                                                           *
* Returns: describe the return value of the function                        *
*                                                                           *
* Other sections. algorithms, file formats, references, notes, etc.         *
****************************************************************************/

int initializeadjacencymatrix (struct eventgraph* graph)
{
        /* max_rows and max_columns must be passed as arguments to this function
        so it knows how big of an array to create. */


        int counter; /* loop counting variable */

/* Step 1. Allocate the memory for the array in one contiguous block of
memory.  This is the actual block of memory where the adjacency matrix data will
be stored.  It's the simulated array. */

    graph->dependencymatrix.matrixptr =
        malloc(graph->dependencymatrix.trigger_rows *
               graph->dependencymatrix.triggeredby_cols *
               sizeof(struct dependency));

/* Step 2. Allocate room for the pointers to the rows.  This sets the pointers
to the rows of dependency events. */

    graph->dependencymatrix.rowptr = malloc(graph->dependencymatrix.trigger_rows
                                            * sizeof(struct dependency *));

/* Step 3. 'Point' the pointers.  This points each row pointer to the beginning
of each row. Note the simple pointer arithmetic. */

    for (counter = 0; counter < graph->dependencymatrix.trigger_rows; counter++)
    {
        graph->dependencymatrix.rowptr[counter] =
            graph->dependencymatrix.matrixptr +
            (counter * graph->dependencymatrix.triggeredby_cols);
    }

    return 0;
}


/****************************************************************************
*****************************************************************************
** Function Definitions -- utility functions                               **
**                                                                         **
*****************************************************************************
****************************************************************************/

/****************************************************************************
**************************   FUNCTION DEFINITION   **************************
* Name: strcmp                                                              *
*                                                                           *
* Description: Compares two character strings and returns negative, zero,   *
* or positive if s1 is lexicographically less than, equal to, or greater    *
* than s2.  The value is obtained by subtracting the characters at the      *
* first position where s1 and s2 disagree. Function copied from K&R 2d at   *
* 106.                                                                      *
*                                                                           *
* Arguments: Two character strings                  .                       *
*                                                                           *
* Returns: See description.                                                 *
*                                                                           *
****************************************************************************/

int strcmp (char *s1, char *s2)
{
    for( /* no assignment */; *s1 == *s2; s1++, s2++)
        if (*s1 == '\0')
            return 0;
    return *s1 - *s2;
}