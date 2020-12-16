/*
 * Filename:  testsuite.h
 * Project: DocketMaster
 *
 * Description:  Header file for testsuite.c.  Testsuite.c creates a number of
 * functions for testing the docketmaster program.
 *
 * Version: 1.0.20
 * Created:  01/29/2012 11:10:47 AM
 * Last Modified: Wed Dec 16 14:28:05 2020
 *
 * Author: Thomas H. Vidal (THV), thomashvidal@gmail.com
 * Organization: Dark Matter Computing
 *  
 * Copyright: Copyright (c) 2011-2020, Thomas H. Vidal
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Usage: 
 * File Format: 
 * Restrictions: 
 * Error Handling: 
 * References: 
 * Notes:
 */

#ifndef _TESTSUITE_H_INCLUDED_
#define _TESTSUITE_H_INCLUDED_

void testsuite_dates(void);
void testsuite_checkholidays(void);
void holidayprinttest(struct DateTime *dt);
void testsuite_courtdays(void);

#endif	/* _TESTSUITE_H_INCLUDED_ */

