/*
 * Filename: eprocessor.c / "Event Processor Module"
 *
 * Description: Processes court events. (1) this module takes input from
 * the lexical analyzer to build the EventGraph.  (2) it takes input from
 * the input manager to (a) report back the number of events and/or the
 * number of depedencies; (b) search for events; (c) to compute the date
 * for a particular event; or to compute the date for a chain of events.
 *
 * Version: 1.0.20
 * Created: 02/03/2012 07:26:12 AM
 * Last Modified: Sun Dec 13 20:21:17 2020
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
 * Usage: included in, and called from, the lexical analyzer and input
 * manager.
 *
 * File Format: At this time, the event processor does not access any files.
 *
 * Restrictions: 
 * Error Handling: 
 * References: 
 * Notes: 
 * 
 * SPDX-License-Identifier: GPL-2.0-only
 */



/* #####   HEADER FILE INCLUDES   ########################################### */
#include "eprocessor.h"

/* #####   FUNCTION DEFINITIONS  -  EXPORTED FUNCTIONS   #################### */

/* 
 * Description:  Counts the number of events in the event list.
 * 
 * Algorithm:  
 * 
 * References:  
 *
 * Notes:  This is an essential function of the EventGraph. It is declared/
 * defined separately from the graph manager so that this functionality can
 * be accessible to the "public" without making the entire graph manager public.
 */

int numberofevents (CourtEventNode* list)
{
    CourtEventNode *cur_pos; /* current position */
    int count = 0; /* the count */

    cur_pos = list;

    while (cur_pos != NULL)
    {
        count++;
        cur_pos = cur_pos->nextevent;
    }

    return count;
}

/* 
 * Description:  Counts the number of dependencies in the Adjacencymatrix.
 *
 * Parameters:  Takes a pointer to an adjacency matrix.
 * Returns:  The number of dependencies (arcs) in the EventGraph.
 *
 * References:  
 *
 * Notes:  Currently this only counts the TRIGGERING dependencies, not the
 * triggered dependencies.  The triggering dependencies are the "true"
 * dependencies.
 *
 * This is an essential function of the EventGraph. It is declared/defined
 * separately from the graph manager so that this functionality can be
 * accessible to the "public" without making the entire graph manager
 * public.  Another way to implement this would have been to make the
 * other functions of the graph data type private to the graphmgr.c file
 * (i.e., remove their declarations from the graphmgr.h file) and keep
 * this function declaration in the graphmgr.h file.
 */

int numberofdependencies (AdjacencyMatrix* dependencies)
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

/* 
 * Name:  searchforevent
 * Description:  Determines whether a particular event (vertex) is in the
 * event list. 
 *
 * Parameters:  Takes a string pointer containing the vertex to search for,
 * and pointer to the court event list to search.
 *
 * Returns:  If the graph contains a vertex that is equal to the serch
 * string the function returns a pointer to the position of the
 * event. Otherwise function returns NULL.
 * 
 * References:  
 *
 * Notes:  Function is currently keyed to search only the shorttitle  member
 * of the eventnode.
 *
 * This is an essential function of the EventGraph. It is declared/defined
 * separately from the graph manager so that this functionality can be
 * accessible to the "public" without making the entire graph manager public.
 * Another way to implement this would have been to make the other functions
 * of the graph data type private to the graphmgr.c file (i.e.,
 * remove their declarations from the graphmgr.h file) and keep
 * this function declaration in the graphmgr.h file.
 */


CourtEventNode* searchforevent (char *eventname,CourtEventNode* list)
{

    CourtEventNode *cur_pos; /* current position */
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

/* 
 * Description:  Determines whether a particular dependency relationship
 * exists. 
 *
 * Parameters:  Takes pointers to two vertices and a pointer to the EventGraph
 * to search. 
 *
 * Returns:  If the graph contains an a dependency relationship between event1
 * and event2, the function returns a pointer to the position of the
 * dependency. Otherwise, function returns NULL. 
 * 
 * Notes:  The order of vertices is important. It will determine whether
 * vertex1 (event1) is triggeredby vertex2 (event2).
 *
 * This is an essential function of the EventGraph. It is declared/defined
 * separately from the graph manager so that this functionality can be
 * accessible to the "public" without making the entire graph manager public.
 * Another way to implement this would have been to make the other functions
 * of the graph data type private to the graphmgr.c file (i.e., remove
 * their declarations from the graphmgr.h file) and keep this function
 * declaration in the graphmgr.h file.
 */

Dependency* searchfordependency (CourtEventNode *event1, CourtEventNode *event2,
				 EventGraph* graph)
{
    Dependency* dependencyfound;

    if (graph->dependencymatrix.rowptr[event1->eventposn][event2->eventposn].dependencyhandle
        != NULL)
    {
        dependencyfound = &graph->dependencymatrix.rowptr[event1->eventposn][event2->eventposn];
        /* SYNTAX QUESTION: I am not sure if the & gives me the addres of graph,
         * or the address of the Dependency, like I believe it should.  Must 
         * test.
         */
    }
    else if (graph->dependencymatrix.rowptr[event2->eventposn][event1->eventposn].dependencyhandle
             != NULL)
    {
        dependencyfound = &graph->dependencymatrix.rowptr[event2->eventposn][event1->eventposn];
    } else
        dependencyfound = NULL;

    return dependencyfound;
}

/* 
 * Description:  Function starts at a certain vertex and traverses through all
 * events along the chain.  In the context of the CourtEvents,
 * it starts with a triggering event and visits all the events triggered by
 * that event.
 *
 * Parameters:  Takes a pointer to the starting vertex and the EventGraph.
 *
 * Returns:  None.
 *
 * Notes:  This is an essential function of the EventGraph. It is
 * declared/defined separately from the graph manager so that this
 * functionality can be accessible to the "public" without making the
 * entire graph manager public.  Another way to implement this would have
 * been to make the other functions of the graph data type private to the
 * graphmgr.c file (i.e., remove their declarations from the graphmgr.h
 * file) and keep this function declaration in the graphmgr.h file.
 */

void followchain (CourtEvent* startingvertex, EventGraph* graph)
{

}

/* #####   FUNCTION DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ############# */
