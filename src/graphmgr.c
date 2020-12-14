/*
 * Filename: graphmgr.c
 *
 * Description: This is the module manages the data type that handles
 * processing the court events for the DocketMaster application program for
 * attorneys.  The events are stored in a directed network graph type.
 * This module and the associated header file contain the various functions
 * required to create, maintain, modify, and search the database of court
 * events.  
 *
 * Version: 1.0.20
 * Created: 10/24/2011
 * Last Modified: Mon Dec 14 00:05:50 2020
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
 * Usage: Used by the DocketMaster application to create a searchable database
 * of court events and dependencies that can be scheduled on a trial calendar. 
 *
 * File Format: 
 * Restrictions: 
 * Error Handling: 
 * References: 
 * Notes: [no notes as of 10/24/2011]. 
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "graphmgr.h"
#include <stdlib.h>
#include <string.h>

/*-----------------------------------------------------------------------------
 * Function definitions -- graph manager 
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

void init_eventgraph(EventGraph* graph, int numofevents)
{
    graph->eventlist = NULL;
    graph->listsize = 0;
    graph->numedges = 0;

    /* initialize the dependency matrix */

    graph->dependencymatrix.trigger_rows = numofevents;
    graph->dependencymatrix.triggeredby_cols = numofevents;
    graph->dependencymatrix.rowptr = NULL;
    graph->dependencymatrix.matrixptr = NULL;
    initializeadjacencymatrix (graph);
 


    return;
}

/*
 * Description: Determines whether the vertex list contains values or is
 * empty.
 *
 * Parameters: Takes a pointer to EventGraph.
 *
 * Returns: If the vertex list is empty, function returns zero.  Otherwise,
 * it returns a nonnegative number.
 */

int isemptygraph(EventGraph* graph)
{
    if (graph->eventlist == NULL)
        return 1;
    else
        return 0;
}

/*
 * Description: Copies the graph of court events into a new EventGraph.
 * copyto graph contains a distinct copy of the graph.
 *
 * Parameters: Takes pointers to two EventGraphs: one existing; the other     
 * empty.
 *
 * Returns: 1 if the copy is successful, zero if it fails.
 */

int copyeventgraph (EventGraph* copyfrom, EventGraph* copyto)
{
    return 0;
}

/*
 * Description: Adds new court event (vertex) to the list of events.
 *
 * Parameters: Takes a pointer to CourtEvent and a pointer to the EventGraph  
 * in which the new event is to be added.
 *
 * Returns: Zero if the insert fails, or a nonnegative number if the insert
 * is successful.
 */

CourtEventNode* insertevent (CourtEvent* eventinfo,
                                CourtEventNode *eventlist)
{
    CourtEventNode *new_event; /* pointer to new court event */
    CourtEventNode *temphead; /* pointer to head of event list */

    /* Find the appropriate place in the ordered list to place the new node.
    if the list is presently NULL, then this item is added in first position. */

    temphead = eventlist;
    if (temphead == NULL ||
        eventcmp(eventinfo->shorttitle, temphead->eventdata.shorttitle) <= 0)
    {
         /* create a new node */
        new_event = malloc(sizeof(CourtEvent));

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
            eventinfo->customservicerule.out_of_country_maildays;
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

        /* add the node into the list */
        new_event->nextevent = eventlist;
        eventlist = new_event;
        temphead = eventlist;
    }
    else
    {
        temphead = temphead->nextevent;
        temphead = insertevent (eventinfo, temphead);
    }

    return temphead;
}

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

int insertdependency (Dependency newdep, EventGraph* graph)
{
    return 0;
}

/*
 * Description: Removes a court event (vertex) from the list of events.
 *
 * Parameters: Takes a pointer to CourtEvent that is already in the list and
 * a pointer to the EventGraph itself.
 *
 * Returns: Zero if the delete fails, or a nonnegative number if the delete
 * is successful.
 */

int deleteevent  (CourtEvent* delevent, EventGraph* graph)
{
    return 0;
}

/*
 * Description: Removes a Dependency (edge) from the list of events.
 *
 * Parameters: Takes a pointer to Dependency that is already in the matrix
 * and a pointer to the EventGraph itself.
 *
 * Returns: Zero if the delete fails, or a nonnegative number if the delete
 * is successful.
 */

int deletedependency (Dependency* deldep, EventGraph* graph)
{
    return 0;
}

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
 */

int replaceevent (CourtEvent* newvertex, CourtEvent* oldvertex)
{
    return 0;
}

/*

 * Description: Function visits all the nodes in the EventGraph in a breadth
 * first manner. [WHAT WILL FUNCTION DO WHEN IT VISITS THE NODES?]
 *
 * Parameters: Takes a pointer to the EventGraph
 *
 * Returns: None.
 */

void traverse (EventGraph* graph)
{

}

/* consider adding: isconnected */

/* consider adding: findshortestpath */


/*
 * Description: describe what the function does.
 *
 * Parameters: Describe the parameters of the function.
 *
 * Returns: describe the return value of the function
 *
 * Other sections. algorithms, file formats, references, notes, etc.
 */

int initializeadjacencymatrix (EventGraph* graph)
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
               sizeof(Dependency));

/* Step 2. Allocate room for the pointers to the rows.  This sets the pointers
to the rows of Dependency events. */

    graph->dependencymatrix.rowptr = malloc(graph->dependencymatrix.trigger_rows
                                            * sizeof(Dependency *));

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

/*-----------------------------------------------------------------------------
 * Function Definitions -- utility functions
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

int eventcmp (const char *s1, const char *s2)
{
    for( /* no assignment */; *s1 == *s2; s1++, s2++)
        if (*s1 == '\0')
            return 0;
    return *s1 - *s2;
}
