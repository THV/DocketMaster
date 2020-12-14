/*
 * =============================================================================
 *
 *       Filename: eprocessor.h / "Event Processor Module"
 *
 *    Description: Processes court events. (1) this module takes input from
 *    		   the lexical analyzer to build the EventGraph.  (2) it takes
 *    		   input from the input manager to (a) report back the number of
 *    		   events and/or the number of depedencies; (b) search for
 *    		   events; (c) to compute the date for a particular event; or to
 *    		   compute the date for a chain of events.
 *
 *        Version: 1.0
 *        Created: 02/03/2012 07:05:40 AM
 *  Last Modified: Fri 03 Feb 2012 08:31:55 AM PST
 *       Compiler: gcc
 *
 *         Author: Thomas H. Vidal (THV), thomasvidal@hotmail.com
 *   Organization: Dark Matter Software
 *
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
#include "graphmgr.h"

/* #####   EXPORTED MACROS   ################################################ */

/* #####   EXPORTED SYMBOLIC CONSTANTS   #################################### */

/* #####   EXPORTED TYPE DEFINITIONS   ###################################### */

/* #####   EXPORTED DATA TYPES   ############################################ */

/* #####   EXPORTED VARIABLES   ############################################# */

/* #####   EXPORTED FUNCTION DECLARATIONS   ################################# */

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
 *  	   	   making the entire graph manager public.  Another way to
 *  	   	   implement this would have been to make the other functions
 *  	   	   of the graph data type private to the graphmgr.c file (i.e.,
 *  	   	   remove their declarations from the graphmgr.h file) and keep
 *  	   	   this function declaration in the graphmgr.h file.
 * =============================================================================
 */

extern int numberofevents (CourtEventNode *list);


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

extern int numberofdependencies (Adjacencymatrix* dependencies);


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

extern CourtEventNode* searchforevent (char *eventname, CourtEventNode* list);


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

extern Dependency* searchfordependency (CourtEventNode *event1, CourtEventNode
					*event2, EventGraph *graph);

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

extern void followchain (CourtEvent* startingvertex, EventGraph* graph);

