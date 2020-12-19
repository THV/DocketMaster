/*
 * =============================================================================
 *
 *       Filename: timetools.h
 *
 *    Description: This header file contines the data structures and
 *                 prototypes for the timetools module.
 *
 *        Version: 0.0
 *        Created: 08/20/2011 10:33:55
 *  Last Modified: Wed Dec 16 14:29:28 2020
 *
 *         Author: Thomas H. Vidal (THV), thomashvidal@gmail.com
 *   Organization: Dark Matter Computing
 *  
 *      Copyright: (c) 2020 - Thomas H. Vidal
 *        License: This file is part of libdatetimetools library.
 *
 *                 libdatetimetools is free software: you can redistribute it
 *                 and/or modify it under the terms of the GNU Lesser General
 *                 Public License as published by the Free Software Foundation,
 *                 version 3 of the License.
 *
 *                 libdatetimetools is distributed in the hope that it will be
 *                 useful,but WITHOUT ANY WARRANTY; without even the implied
 *                 warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *                 PURPOSE.  See the GNU Lesser General Public License for
 *                 more details.
 *
 *                 You should have received a copy of the GNU General Public
 *                 License along with libdatetimetools.  If not, see
 *                 <https://www.gnu.org/licenses/>.
 *
 *	        Usage: 
 *    File Format: 
 *   Restrictions: 
 * Error Handling: 
 *     References: 
 *          Notes: 
 * 
 * SPDX-License-Identifier: LGPL-3.0-only
 =============================================================================
 */

/* function prototypes */
/* void parsetime (char input[], int *h, int *m, int *s); not used right now*/
int summin (int h, int m, int s);
void min2time (int min, int *h, int *m, int *s);

