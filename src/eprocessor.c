/*
 * =============================================================================
 *
 *       Filename: eprocessor.c / "Event Processor Module"
 *
 *    Description: Processes court events. (1) this module takes input from
 *    		   the lexical analyzer to build the EventGraph.  (2) it takes
 *    		   input from the input manager to (a) report back the number of
 *    		   events and/or the number of depedencies; (b) search for
 *    		   events; (c) to compute the date for a particular event; or to
 *    		   compute the date for a chain of events.
 *
 *        Version: 1.0
 *        Created: 02/03/2012 07:26:12 AM
 *  Last Modified: Fri 03 Feb 2012 08:27:59 AM PST
 *       Compiler: gcc
 *
 *         Author: Thomas H. Vidal (THV), thomasvidal@hotmail.com
 *   Organization: Dark Matter Software
 *      Copyright: Copyright (c) 2012, Thomas H. Vidal
 *
 *	    Usage: included in, and called from, the lexical analyzer and input
 *	    	   manager.
 *    File Format: At this time, the event processor does not access any files.
 *   Restrictions: 
 * Error Handling: 
 *     References: 
 *          Notes: 
 * =============================================================================
 */

/* #####   HEADER FILE INCLUDES   ########################################### */
#include "eprocessor.h"

/* #####   MACROS  -  LOCAL TO THIS SOURCE FILE   ########################### */

/* #####   SYMBOLIC CONSTANTS -  LOCAL TO THIS SOURCE FILE   ################ */

/* #####   TYPE DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ################# */

/* #####   DATA TYPES  -  LOCAL TO THIS SOURCE FILE   ####################### */

/* #####   VARIABLES  -  LOCAL TO THIS SOURCE FILE   ######################## */

/* #####   PROTOTYPES  -  LOCAL TO THIS SOURCE FILE   ####################### */

/* #####   FUNCTION DEFINITIONS  -  EXPORTED FUNCTIONS   #################### */

/* 
 * ===  FUNCTION  ==============================================================
 *          Name:  numberofevents
 *   Description:  Counts the number of events in the event list.
 *     Arguments:  Takes a pointer to an EventGraph. 
 *       Returns:  The number of events in the EventGraph.
 *     Algorithm:  
 *    References:  
 *  	   Notes:  This is an essential function of the EventGraph. It is
 *  	   	   declared/defined separately from the graph manager so that
 *  	   	   this functionality can be accessible to the "public" without
 *  	   	   making the entire graph manager public.
 * =============================================================================
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
 * ===  FUNCTION  ==============================================================
 *          Name:  numberofdependencies
 *   Description:  Counts the number of dependencies in the Adjacencymatrix.
 *     Arguments:  Takes a pointer to an adjacency matrix.
 *       Returns:  The number of dependencies (arcs) in the EventGraph.
 *     Algorithm:  
 *    References:  
 *  	   Notes:  Currently this only counts the TRIGGERING dependencies, not
 *  	   	   the triggered dependencies.  The triggering dependencies are
 *  	   	   the "true" dependencies.
 *
 *  	   	   This is an essential function of the EventGraph. It is
 *  	   	   declared/defined separately from the graph manager so that
 *  	   	   this functionality can be accessible to the "public" without
 *  	   	   making the entire graph manager public.  Another way to
 *  	   	   implement this would have been to make the other functions
 *  	   	   of the graph data type private to the graphmgr.c file (i.e.,
 *  	   	   remove their declarations from the graphmgr.h file) and keep
 *  	   	   this function declaration in the graphmgr.h file.
 * =============================================================================
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
 * ===  FUNCTION  ==============================================================
 *          Name:  searchforevent
 *   Description:  Determines whether a particular event (vertex) is in the
 *   		   event list. 
 *
 *     Arguments:  Takes a string pointer containing the vertex to search for,
 *     		   and pointer to the court event list to search.
 *
 *       Returns:  If the graph contains a vertex that is equal to the serch
 *       	   string the function returns a pointer to the position of the
 *       	   event. Otherwise function returns NULL.
 *     Algorithm:  
 *    References:  
 *  	   Notes:  Function is currently keyed to search only the shorttitle
 *  	   	   member of the eventnode.
 *
 *  	   	   This is an essential function of the EventGraph. It is
 *  	   	   declared/defined separately from the graph manager so that
 *  	   	   this functionality can be accessible to the "public" without
 *  	   	   making the entire graph manager public.  Another way to
 *  	   	   implement this would have been to make the other functions
 *  	   	   of the graph data type private to the graphmgr.c file (i.e.,
 *  	   	   remove their declarations from the graphmgr.h file) and keep
 *  	   	   this function declaration in the graphmgr.h file.
 * =============================================================================
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
 * ===  FUNCTION  ==============================================================
 *          Name:  searchfordependency
 *   Description:  Determines whether a particular dependency relationship
 *   		   exists. 
 *     Arguments:  Takes pointers to two vertices and a pointer to the
 *     		   EventGraph to search. 
 *       Returns:  If the graph contains an a dependency relationship between
 *       	   event1 and event2, the function returns a pointer to the
 *       	   position of the dependency. Otherwise, function returns NULL. 
 *     Algorithm:  
 *    References:  
 *  	   Notes:  The order of vertices is important. It will determine whether
 *  	   	   vertex1 (event1) is triggeredby vertex2 (event2).
 *
 *		   This is an essential function of the EventGraph. It is
 *  	   	   declared/defined separately from the graph manager so that
 *  	   	   this functionality can be accessible to the "public" without
 *  	   	   making the entire graph manager public.  Another way to
 *  	   	   implement this would have been to make the other functions
 *  	   	   of the graph data type private to the graphmgr.c file (i.e.,
 *  	   	   remove their declarations from the graphmgr.h file) and keep
 *  	   	   this function declaration in the graphmgr.h file.
 * =============================================================================
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
        or the address of the Dependency, like I believe it should.  Must
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

/* 
 * ===  FUNCTION  ==============================================================
 *          Name:  followchain
 *   Description:  Function starts at a certain vertex and traverses through all
 *   		   events along the chain.  In the context of the CourtEvents,
 *   		   it starts with a triggering event and visits all the events
 *   		   triggered by that event.
 *     Arguments:  Takes a pointer to the starting vertex and the EventGraph.
 *       Returns:  None.
 *     Algorithm:  
 *    References:  
 *  	   Notes:  This is an essential function of the EventGraph. It is
 *  	   	   declared/defined separately from the graph manager so that
 *  	   	   this functionality can be accessible to the "public" without
 *  	   	   making the entire graph manager public.  Another way to
 *  	   	   implement this would have been to make the other functions
 *  	   	   of the graph data type private to the graphmgr.c file (i.e.,
 *  	   	   remove their declarations from the graphmgr.h file) and keep
 *  	   	   this function declaration in the graphmgr.h file.
 * =============================================================================
 */

void followchain (CourtEvent* startingvertex, EventGraph* graph)
{

}

/* #####   FUNCTION DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ############# */

