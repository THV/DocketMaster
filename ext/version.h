/*
 * =============================================================================
 *
 *       Filename:  version.h
 *
 *    Description:  This header file contines the version information for the
 *                  libdatetimetools library.
 *
 *        Version:  0.0
 *        Created:  11/25/2020 20:58:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Thomas H. Vidal (THV), thomashvidal@gmail.com
 *   Organization:  Dark Matter Computing
 *  
 *      Copyright:  (c) 2011-2020 - Thomas H. Vidal
 *        License:  This file is part of libdatetimetools library.
 *
 *                  libdatetimetools is free software: you can redistribute it
 *                  and/or modify it under the terms of the GNU Lesser General
 *                  Public License as published by the Free Software Foundation,
 *                  version 3 of the License.
 *
 *                  libdatetimetools is distributed in the hope that it will be
 *                  useful,but WITHOUT ANY WARRANTY; without even the implied
 *                  warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *                  PURPOSE.  See the GNU Lesser General Public License for
 *                  more details.
 *
 *                  You should have received a copy of the GNU General Public
 *                  License along with libdatetimetools.  If not, see
 *                  <https://www.gnu.org/licenses/>.
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

#ifndef VERSION_H
#define VERSION_H

	//Date Version Types
	static const char DATE[] = "20";
	static const char MONTH[] = "10";
	static const char YEAR[] = "2011";
	static const char UBUNTU_VERSION_STYLE[] = "11.10";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 1;
	static const long MINOR = 0;
	static const long BUILD = 19;
	static const long REVISION = 50;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 231;
	#define RC_FILEVERSION 1,0,19,50
	#define RC_FILEVERSION_STRING "1, 0, 19, 50\0"
	static const char FULLVERSION_STRING[] = "1.0.19.50";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 19;
	

#endif //VERSION_H
