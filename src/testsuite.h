/*
 * Filename:  testsuite.h
 *
 * Description:  Header file for testsuite.c.  Testsuite.c creates a number of
 * functions for testing the docketmaster program.
 *
 * Version: 1.0.20
 * Created:  01/29/2012 11:10:47 AM
 * Last Modified: Sun Dec 13 22:28:38 2020
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
 * Usage: 
 * File Format: 
 * Restrictions: 
 * Error Handling: 
 * References: 
 * Notes:
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef _TESTSUITE_H_INCLUDED_
#define _TESTSUITE_H_INCLUDED_

void testsuite_dates(void);
void testsuite_checkholidays(void);
void holidayprinttest(struct DATETIME *dt);
void testsuite_courtdays(void);

#endif	/* _TESTSUITE_H_INCLUDED_ */

