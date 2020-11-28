/****************************************************************************
* Header File Title: - datetools.h                                          *
*                                                                           *
* Author: Thomas Vidal (c) 2011                                             *
*                                                                           *
* Purpose: This header file contines the data structures and prototypes for *
*          the datetools module.                                            *
*                                                                           *
****************************************************************************/

#ifndef _DATETOOLS_H_INCLUDED_
#define _DATETOOLS_H_INCLUDED_

/*******************************************************************************
* Data Type Declarations                                                       *
*                                                                              *
*******************************************************************************/

/* SYMBOLIC CONSTANTS */

#define WEEKDAYS 7 /* Seven days in a week */
#define MINNUMTTLWKS 4 /* Minimum number of total weeks.  All months have at
                          least 4 weeks.  Some months have an extra week. */
#define LEAP 1

/* the days of the week */
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

/* array of months the array starts with zero, which will never be used, so that
    subscripts match the actual calendar months 1=january, etc.  */
    /* TODO (Thomas#4#): Convert to unsigned char to minimize memory usage? */

static int montharray[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

/* array of total days of each. Again, starting with zero so subscripts will
match up with months.  This is a 2D array to account for leap years.  */
/* TODO (Thomas#4#): Convert to unsigned char to minimize memory usage? */

static int daysinmonths[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31,
                                30, 31},
                                {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31,
                                30, 31}};

/* A datatype to contain the date and time aspects of an event. It might be
    preferable to break this into a struct for date, a struct for time, and
    then combine them as necessary.                                           */

struct DATETIME
{
    int year;
    int month;
    int day;
    int jdn; /* the Julian Day number for the relevant date */
    enum days day_of_week;

};

/****************************************************************************
*****************************************************************************
* Function prototypes                                                       *
*                                                                           *
*****************************************************************************
****************************************************************************/


/****************************************************************************
***************************   FUNCTION DECLARATION   ************************
* wkday_sakamoto.                                                           *
*                                                                           *
* Usage/Limitations: This function calculates the day of the week based on  *
*   Sakamoto's formula.  The formula is accurate for any date in the range  *
*   September 14, 1752–December 31, 9999                                    *
*                                                                           *
* Source. Text copied from Wikipedia.                                       *
*                                                                           *
* Explanation.                                                              *
*                                                                           *
* Sakamoto's code in C is as follows:                                       *
*   int dow(int y, int m, int d)                                            *
*      {                                                                    *
*       static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};              *
*       y -= m < 3;                                                         *
*       return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;                  *
*      }                                                                    *
*                                                                           *
*   In the above, y, m and d are, respectively the year (e.g., 1988), month *
*   (1-12) and day of the month (1-31).  The function returns 0 = Sunday,   *
*   1 = Monday, etc.  As the algorithm performs no range checks on the      *
*   function arguments, unreasonable dates will produce erroneous results   *
*   or run-time errors.                                                     *
*                                                                           *
*   I have modified the function to work with my data type                  *
*                                                                           *
* References. Devised by Tomohiko Sakamoto[1] in 1993.                      *
****************************************************************************/

int wkday_sakamoto (struct DATETIME *dt);

/****************************************************************************
***************************   FUNCTION DECLARATION   ************************
* Name: printwkday                                                          *
*                                                                           *
* Description: Prints the weekday corresponding to a day of the enum days.  *
*                                                                           *
* Arguments: Takes an integer corresponding to a day of the week.           *
*                                                                           *
* Return: Nothing.  It just prints the day.                                 *
*                                                                           *
*****************************************************************************
****************************************************************************/

void printwkday (int day);

/****************************************************************************
***************************   FUNCTION DECLARATION   ************************
* Name: isweekend                                                           *
*                                                                           *
* Description: calculates whether a certain date falls on a Saturday or     *
*   Sunday.  This founction was designed early on in development.  Because  *
*   most courts treat weekends as holidays, this function is not currently  *
*   used.  The weeked rules are simply part of the Holiday rules processing *
*   tools                                                                   *
*                                                                           *
* Arguments: Takes a pointer to a DATETIME structure.                       *
*                                                                           *
* Return: Returns an integer equal to zero if the date is NOT a weekend, or *
*   a 1 if the date IS a weekend.                                           *
*                                                                           *
*****************************************************************************
****************************************************************************/

int isweekend (struct DATETIME *dt);


/****************************************************************************
***************************   FUNCTION DECLARATION   ************************
* Name: isleapyear                                                          *
*                                                                           *
* Description: calculates whether a year is a leap year or not              *
*                                                                           *
* Arguments: Takes a pointer to a DATETIME structure.                       *
*                                                                           *
* Return: Returns an integer equal to zero if the year is NOT a leap year,  *
*   or a 1 if the year IS a leap year.                                      *
*                                                                           *
*****************************************************************************
****************************************************************************/

int isleapyear(struct DATETIME *dt);


/****************************************************************************
***************************   FUNCTION DECLARATION   ************************
* Name: jdncvrt                                                             *
*                                                                           *
* Description: converts a Gregorian calendar date to a Julian Day Number    *
*   (JDN).  The purpose of using the JDN is to create a unique number for   *
*   a day that we can use to make date calculations, such as the number of  *
*   days between two dates or the number of days before or after a          *
*   specified date. This function does the opposite of the jdn2greg         *
*   function.                                                               *
*                                                                           *
* Arguments: Takes a pointer to a DATETIME structure.                       *
*                                                                           *
* Return: Returns an integer with the Julian Date.  Usually this number is  *
*         not stored for "permanent use" but is used as an argument for     *
*         anothe function, such as the date_offset function.                *
*                                                                           *
* References: This algorithm was published onlne by Aesir Research.  It was *
*             found at http://mysite.verizon.net/aesir_research/            *
*             date/jdalg2.htm. Aesir research of Onset Massachusetts        *
*             conducts research into AI, consumer electronics, scientific   *
*             instrumentations, optics, and mathematical algorithms.        *
*                                                                           *
*                                                                           *
* Notes:   The algorithm referenced several interim variables, but it was   *
*   not clear to me what the variables referenced.  Thus, I have retained   *
*   the variable names used by Aesir without change.  These  variables are  *
*   not used in any place other than the function. So I felt it acceptable  *
*   to use the names "as is." The algorithm is saved in the research        *
*   subfolder titled "Julian Day Number - Algorithm Forms.txt"              *
*                                                                           *
*   The algorithm results in a Julian Day Number, when tested with Jan. 1,  *
*   2000, of 2,451,544.  Wikipedia lists the JDN for that date as 2,454,545,*
*   and the Julian Date Calculator at www.convertalot.com lists it as       *
*   2451544.5.                                                              *
*                                                                           *
*   I believe these differences are the result of the fact that pure Julian *
*   Day Numbers go from noon to noon, and account for the time of day.  The *
*   0.5 difference does not appear to create any cumulative error that      *
*   spills over to other dates, so this does not present an issue for this  *
*   function or other functions that use the JDN.                           *
*                                                                           *
*****************************************************************************
****************************************************************************/

int jdncnvrt (struct DATETIME *dt);

/****************************************************************************
***************************   FUNCTION DECLARATION   ************************
* Name: jdn2greg                                                            *
*                                                                           *
* Description: Converts a Julian Day Number to the Gregorian calendar date. *
*   The purpose of using the JDN is to create a unique number for a day     *
*   that we can use to make date calculations, such as the number of days   *
*   between two dates or the number of days before or after a specified     *
*   date. This function does the opposite of the jdncvrt function.          *
*                                                                           *
* Arguments:  Takes an integer representing a JDN and a pointer to a        *
*   DATETIME structure.                                                     *
*                                                                           *
* Return: Does not return a value, but stores the value of the Gregorian    *
*   calendar date into the DATETIME structure that is passed to the         *
*   function through the pointer.                                           *
*                                                                           *
* References: This algorithm was published onlne by "Ask Dr. Math" at       *
*   http://mathforum.org/library/drmath/view/51907.html. Dr. Math           *
*   referenced two algorithms: Jean Meeus's algorithm in "Astronomical      *
*   Formulae for Calculators"; or the Fliegel-Van Flandern algorithm given  *
*   in the Astronomical Almanac.  I used the Meeus version, which should    *
*   work for any positive Julian date.                                      *
*                                                                           *
* Notes:   The algorithm referenced several interim variables, but it was   *
*   not clear to me what the variables referenced.  Thus, I have retained   *
*   the variable names used by Dr. Math without change. These variables are *
*   not used in any place other than the function. So I felt it acceptable  *
*   to use the names "as is." The algorithms are stored in the research     *
*   subfolder titled "Dr Math re Julian to Calendar Date Conversion.txt"    *                                                      *
*                                                                           *
*   For some inexplicable reason, the formula when used exactly as          *
*   described by Dr. Math results in a calculation that is one day short of *
*   the actual JDN resulting from the jdncvrt function.  Consequently, I    *
*   added a "+1" constant to the formula.                                   *
*                                                                           *
*   I believe the difference may be a result of the use of the greatest     *
*   integer (the floor function in C) in his algorithm, but my use of       *
*   simple integer math.  I am not sure.  Needless to say, the algorithm    *
*   appears to produce accurate results using my correction factor.         *
*****************************************************************************
****************************************************************************/

void jdn2greg (int jdn, struct DATETIME *calc_date);

/****************************************************************************
***************************   FUNCTION DECLARATION   ************************
* date_difference - calculates the number of days between two dates.        *
*                                                                           *
* Arguments: The starting date and ending date, both in the form of         *
*   pointers to a DATETIME struct.                                          *
*                                                                           *
* Return: Returns an integer with the number of days between the two dates. *
*                                                                           *
****************************************************************************/

int date_difference (struct DATETIME *date1, struct DATETIME *date2);

/****************************************************************************
***************************  FUNCTION DECLARATION    ************************
* date_offset - calculates the date after adding or subtracting a specified *
*   number days. The algorithm EXCLUDES the first date, but counts the end  *
*   date.                                                                   *
*                                                                           *
* Arguments: The starting date, the number of calender days to count, and a *
*   pointer to another DATETIME struct to store the result.                 *
*                                                                           *
* Return: Returns an integer which is the result of calculating the number  *
*   of days between the two dates.                                          *
****************************************************************************/

void date_offset (struct DATETIME *orig_date, struct DATETIME *calc_date,
                  int numdays);

/****************************************************************************
**************************  FUNCTION DECLARATION   **************************
* Name: courtday_offset                                                     *
*                                                                           *
* Description: calculates the number of courtdays between two dates. Court  *
*   days exclude weekends and holidays.  So the offset does not count those *
*   days.                                                                   *
*                                                                           *
* Arguments: The starting date, the number of court days to count, and a    *
*   pointer to another DATETIME struct to store the result.                 *
*                                                                           *
* Return: No return, but the function changes the value of the variable     *
*   calc_date (the resulting date) through use of the pointer.              *
*                                                                           *
* Algorithm: Function uses two nested while loops.  The outer one counts    *
* up or down by numdays.  The inner while-loop cycles through each day      *
* starting with the day after the original date.  It tests whether the day  *
* falls on a holiday.  If the day falls on a holliday, the inner loop  is   *
* incremented, but the outerloop is not. Thus, this function could be       *
* modified to report back not only the resulting court day, but the number  *
* of actual calendar days between the two dates.                            *
****************************************************************************/


void courtday_offset (struct DATETIME *orig_date, struct DATETIME *calc_date,
                  int numdays);

/****************************************************************************
**************************  FUNCTION DECLARATION   **************************
* Name: courtday_count [not programmed yet.]                                *
*                                                                           *
* Description: Counts court days.                                           *
*                                                                           *
* Arguments: The starting date and ending date, both in the form of         *
*   pointers to a DATETIME struct.                                          *
*                                                                           *
* Returns: describe the return value of the function                        *
*                                                                           *
* Other sections. algorithms, file formats, references, notes, etc.         *
****************************************************************************/

void courtday_count (struct DATETIME *orig_date, struct DATETIME *calc_date,
                  int numdays);

/****************************************************************************
***************************  FUNCTION DECLARATION   *************************
* Name: islastxdom                                                          *
*                                                                           *
* Description: calculates whether a particular date is in the last x day    *
*               of the month.  (E.g., the last Tuesday of February.)        *
*                                                                           *
* Arguments: Takes a DATETIME struct.                                       *
*                                                                           *
* Returns: An integer 0 = not in last week; 1 = is in last week             *
*                                                                           *
* Algorithm: Step one is to simply test the day# of the argument date.      *
*   If the number is less than WEEKDAYS * (MINNUMTTLWKS-1) (i.e., 22),then  *
*   it cannot possibly be in the last week and function returns.  If not,   *
*   Step 2 begins. The job is simply to (1) determine the last week of the  *
*   date-argument's month, (2) identify the last Xday of the month, and (3) *
*   compare the last Xday with the argument's Xday. If they are the same,   *
*   the argument date is the last Xday of the month.                        *
*                                                                           *
*****************************************************************************
****************************************************************************/

int islastxdom (struct DATETIME *dt);

/****************************************************************************
***************************  FUNCTION DECLARATION   *************************
* Name: islastweek                                                          *
*                                                                           *
* Description: calculates whether a particular date is in the last week     *
*               of the month.                                               *
*                                                                           *
* Arguments: Takes a DATETIME struct.                                       *
*                                                                           *
* Returns: An integer 0 = not in last week; 1 = is in last week             *
*                                                                           *
* Algorithm: Step one is to simply test the day# of the argument date.      *
*   If the number is less than WEEKDAYS * (MINNUMTTLWKS-1) (i.e., 22),then  *
*   it cannot possibly be in the last week and function returns.  If not,   *
*   Step 2 begins. Calling function knows that the day of the week of the   *
*   date argument (let's call that Xday) matches the day of the week of a   *
*   specific holiday. This function's job is simply to (1) determine the    *
*   last week of date-argument's month, (2) identify the last Xday of the   *
*   month, and (3) compare the last Xday with the argument's Xday. If they  *
*   are the same, the argument date is the last Xday of the month.          *
*                                                                           *
*****************************************************************************
****************************************************************************/

int islastweek (struct DATETIME *dt);
#endif	/* _DATETOOLS_H_INCLUDED_ */
