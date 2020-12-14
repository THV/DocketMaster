/*
 * Filename: eprocessor.h / "Event Processor Module"
 *
 * Description: Processes court events. (1) this module takes input from
 * the lexical analyzer to build the EventGraph.  (2) it takes input from
 * the input manager to (a) report back the number of events and/or the
 * number of depedencies; (b) search for events; (c) to compute the date
 * for a particular event; or to compute the date for a chain of events.
 *
 * Version: 1.0.20
 * Created: 02/03/2012 07:05:40 AM
 * Last Modified: Sun Dec 13 20:21:48 2020
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
#include "graphmgr.h"

/* #####   EXPORTED FUNCTION DECLARATIONS   ################################# */

/* 
 * Description:  Counts the number of events in the event list.
 *
 * Parameters:  Takes a pointer to an EventGraph. 
 *
 * Returns:  The number of events in the EventGraph.
 */

extern int numberofevents (CourtEventNode *list);


/* 
 * Description:  Counts the number of dependencies in the Adjacencymatrix.
 *
 * Parameters:  Takes a pointer to an adjacency matrix.
 *
 * Returns:  The number of dependencies (arcs) in the EventGraph.
 *
 * Notes:  Currently this only counts the TRIGGERING dependencies, not the
 * triggered dependencies.  The triggering dependencies are the "true"
 * dependencies.
 */

extern int numberofdependencies (Adjacencymatrix* dependencies);


/* 
 * Description:  Determines whether a particular event (vertex) is in the event
 * list. 
 *
 * Parameters:  Takes a string pointer containing the vertex to search for,
 * and pointer to the court event list to search.
 *
 * Returns:  If the graph contains a vertex that is equal to the serch
 * string the function returns a pointer to the position of the event.
 * Otherwise function returns NULL.
 *
 * Notes:  Function is currently keyed to search only the shorttitle member
 * of the eventnode.
 */

extern CourtEventNode* searchforevent (char *eventname, CourtEventNode* list);


/* 
 * Description:  Determines whether a particular dependency relationship exists. 
 *
 * Parameters:  Takes pointers to two vertices and a pointer to the
 *     		   EventGraph to search. 
 *
 * Returns:  If the graph contains an a dependency relationship between event1
 * and event2, the function returns a pointer to the position of the
 * dependency. Otherwise, function returns NULL. 
 *
 * Notes:  The order of vertices is important. It will determine whether
 * vertex1 (event1) is triggeredby vertex2 (event2).
 */

extern Dependency* searchfordependency (CourtEventNode *event1, CourtEventNode
					*event2, EventGraph *graph);

/* 
 * Description:  Function starts at a certain vertex and traverses through all
 * events along the chain.  In the context of the CourtEvents, it starts with
 * a triggering event and visits all the events triggered by that event.
 *
 * Parameters:  Takes a pointer to the starting vertex and the EventGraph.
 *
 */

extern void followchain (CourtEvent* startingvertex, EventGraph* graph);

