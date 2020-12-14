/*
 *
 *       Filename: datetools.h
 *
 *    Description: This header file contines the data structures and
 *                 prototypes for the datetools module.
 *
 *        Version: 0.0
 *        Created: 08/18/2011 14:24:55
 *  Last Modified: Sat Dec 12 15:00:07 2020
 *       Compiler: gcc
 *
 *         Author: Thomas H. Vidal (THV), thomashvidal@gmail.com
 *   Organization: Dark Matter Computing
 *  
 *      Copyright: (c) 2011-2020 - Thomas H. Vidal
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
 *
 */

#ifndef _DATETOOLS_H_INCLUDED_
#define _DATETOOLS_H_INCLUDED_

/*-----------------------------------------------------------------------------
 * Data Types
 *----------------------------------------------------------------------------*/

/* SYMBOLIC CONSTANTS */

#define WEEKDAYS 7 
#define MINNUMTTLWKS 4 /* All months have at least 4 weeks. */
#define LEAP 1

/* Days of the week */
enum days {
    Sunday = 0,
    Monday = 1,
    Tuesday = 2,
    Wednesday = 3,
    Thursday = 4,
    Friday = 5,
    Saturday = 6,
    alldays = 8, /* added for use with the rule functions */
    noday = 9    /* neither is used for actual calendar dates */
};

/* the months of the year -- NOT USED AS YET.
enum months {
    January = 0;
    February = 1;
    March = 2;
    April = 3;
    May = 4;
    June = 5;
    July = 6;
    August = 7;
    September = 8;
    October = 9;
    November = 10;
    December = 11;
    allmonths = 12;

} */


/* EXPORTED DATA TYPES */

/*
 * array of months. The array starts with zero, which will never be used, so
 * that subscripts match the actual calendar months 1=january, etc.
 */

    /* TODO Convert to unsigned char to minimize memory usage? */
    /* TODO Consdider using an enum and dropping the extra 13th element. */

static int montharray[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

/* array of total days of each. Starting with zero so subscripts will
 * match up with months.  This is a 2D array to account for leap years.
 */

    /* TODO Convert to unsigned char to minimize memory usage? */

static int daysinmonths[2][13] = {{0, 31, 28, 31, 30, 31,
                                      30, 31, 31, 30, 31, 30, 31},
                                 {0, 31, 29, 31, 30, 31, 30,
                                     31, 31, 30, 31, 30, 31}};

/* A struct to contain the date and ti`me aspects of an event. */

        /*  TODO It might be preferable to break this into a struct for date,
         *  a struct for time, and
         *  then combine them.
         */

struct DATETIME
{
    int year;
    int month;
    int day;
    int jdn; /* the Julian Day number for the relevant date */
    enum days day_of_week;

};


/*-----------------------------------------------------------------------------
 * EXPORTED FUNCTION DECLARATIONS
 *----------------------------------------------------------------------------*/

/*
 * Name: wkday_sakamoto
 * 
 * Usage/Limitations: This function calculates the day of the week based on
 *   Sakamoto's formula.  The formula is accurate for any date in the range
 *   September 14, 1752–December 31, 9999
 *
 */

int wkday_sakamoto (struct DATETIME *dt);

/*
 * Name: printwkday
 * 
 * Description: Prints the weekday corresponding to a day of the enum days. 
 *
 * Parameters: Takes an integer corresponding to a day of the week.
 *
 * Return: Nothing.  It just prints the day.
 *
 */

void printwkday (int day);

/*
 * Name: isweekend
 *
 * Description: calculates whether a certain date falls on a Saturday or
 * Sunday.  This founction was designed early on in development.  Because
 * most courts treat weekends as holidays, this function is not currently
 * used.  The weeked rules are simply part of the Holiday rules processing
 * tools
 *
 * Parameters: Takes a pointer to a DATETIME structure.
 *
 * Return: Returns an integer equal to zero if the date is NOT a weekend, or
 * a 1 if the date IS a weekend.
 *
 */

int isweekend (struct DATETIME *dt);


/*
 * Name: isleapyear
 *
 * Description: calculates whether a year is a leap year or not
 *
 * Parameters: Takes a pointer to a DATETIME structure.
 *
 * Return: Returns an integer equal to zero if the year is NOT a leap year,
 *  or a 1 if the year IS a leap year.
 *
 */

int isleapyear(struct DATETIME *dt);


/*
 * Name: jdncvrt
 *
 * Description: converts a Gregorian calendar date to a Julian Day Number
 * (JDN).  The purpose of using the JDN is to create a unique number for
 * a day that we can use to make date calculations, such as the number of
 * days between two dates or the number of days before or after a
 * specified date. This function does the opposite of the jdn2greg
 * function.
 *
 * Parameters: Takes a pointer to a DATETIME structure.
 *
 * Return: Returns an integer with the Julian Date.  Usually this number is
 * not stored for "permanent use" but is used as an argument for
 * another function, such as the date_offset function.
 *
 */

int jdncnvrt (struct DATETIME *dt);

/*
 * Name: jdn2greg
 *
 * Description: Converts a Julian Day Number to the Gregorian calendar date.
 *   The purpose of using the JDN is to create a unique number for a day
 *   that we can use to make date calculations, such as the number of days
 *   between two dates or the number of days before or after a specified
 *   date. This function does the opposite of the jdncvrt function.
 *
 * Parameters:  Takes an integer representing a JDN and a pointer to a
 *   DATETIME structure.
 *
 */

void jdn2greg (int jdn, struct DATETIME *calc_date);

/*
 * Name: date_difference
 *
 * Description: calculates the number of calendar days between two dates.
 *
 * Parameters: The starting date and ending date, both in the form of
 *   pointers to a DATETIME struct.
 *
 * Return: Returns an integer which is the result of calculating the number
 *   of calendar days between the two dates.
 *
 */

int date_difference (struct DATETIME *date1, struct DATETIME *date2);

/*
 * Description: calculates the date after adding or subtracting a specified
 *   number days.
 *
 * Usage: The algorithm EXCLUDES the first date, but counts the end date.
 *
 * Parameters: The starting date, the number of calender days to count, and a
 *   pointer to another DATETIME struct to store the result.
 *
 * Return: No return, but the function changes the value of the variable
 *   calc_date (the resulting date) through use of the pointer. The return
 *   value is positive if date1 is before date 2, and negative otherwise.
 */
 
void date_offset (struct DATETIME *orig_date, struct DATETIME *calc_date,
                  int numdays);

/*
 * Name: courtday_offset
 *
 * Description: calculates the number of courtdays between two dates. Court
 *   days exclude weekends and holidays.  So the offset does not count those
 *   days.
 *
 * Parameters: The starting date, the number of court days to count, and a
 *   pointer to another DATETIME struct to store the result.
 *
 * Return: No return, but the function changes the value of the variable
 *   calc_date (the resulting date) through use of the pointer.
 *
 */


void courtday_offset (struct DATETIME *orig_date, struct DATETIME *calc_date,
                  int numdays);

/*
 * Name: courtday_difference
 *
 * Description: Counts court days between two dates.
 *
 * Parameters: The starting date and ending date, both in the form of
 *   pointers to a DATETIME struct.
 *
 * Return: Returns an integer which is the result of calculating the number
 *   of court days between the two dates. Recall cour days exclude weekends
 *   and holidays. The return value is positive if date1 is before date 2,
 *   and negative otherwise.
 *
 */

int courtday_difference (struct DATETIME *date1, struct DATETIME *date2);

/*
 * Name: islastxdom
 *
 * Description: calculates whether a particular date is in the last x day
 *               of the month.  (E.g., the last Tuesday of February.)
 *
 * Parameters: Takes a DATETIME struct.
 *
 * Returns: An integer 0 = not in last week; 1 = is in last week
 *
 */

int islastxdom (struct DATETIME *dt);

/*
 * Name: islastweek
 *
 * Description: calculates whether a particular date is in the last week
 *               of the month.
 *
 * Parameters: Takes a DATETIME struct.
 *
 * Returns: An integer 0 = not in last week; 1 = is in last week
 *
 */

int islastweek (struct DATETIME *dt);
#endif	/* _DATETOOLS_H_INCLUDED_ */
