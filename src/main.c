#include <stdio.h>
#include <stdlib.h>
#include "..\datetime\datetools.h"
#include "..\lexical analyzer\lexicalanalyzer.h"
#include "..\rule processor\ruleprocessor.h"
#include "..\datetime\datetools.h"


void usage(char *);
void testsuite_dates(void);
void testsuite_checkholidays(void);
void holidayprinttest(struct DATETIME *dt);
void testsuite_courtdays(void);

/*******************************************************************************
********************************************************************************
********** MAIN PROGRAM BEGINS BELOW.                                 **********
**********                                                            **********
**********                                                            **********
********************************************************************************
*******************************************************************************/

int main(int argc, char *argv[])
{
    char *program_name;
    char *holidays_filename;
    char *events_filename;
    char *extras_filename;

    /* initialize file names */
    program_name = argv[0];
    holidays_filename = NULL;
    events_filename = NULL;
    extras_filename = NULL;

    /* Process the commandline arguments */
    while ((argc > 1) && (argv[1][0] == '-'))
    {
        switch (argv[1][1])
        {
            case 'H': /* fall through */
            case 'h':
                holidays_filename = &argv[1][2];
                break;
            case 'E': /* fall through */
            case 'e':
                events_filename = &argv[1][2];
                break;
            case 'X': /* fall through */
            case 'x':
                extras_filename = &argv[1][2];
                break;
            default:
                fprintf(stderr, "Bad option %s\n", argv[1]);
                usage(program_name);
        }
        ++argv;
        --argc;
    }
    getrulesfiles(holidays_filename, events_filename, extras_filename);
    testsuite_dates();
    testsuite_checkholidays();
    testsuite_courtdays();

    /* testsuite(); */
    return 0;
}

void usage(char *program_name)
{
    fprintf(stderr, "Uasge is %s -f[filename 1] -f[filename...]\n",
            program_name);
    exit(8);
}

void testsuite_dates(void)
{
    struct DATETIME testdate;
    int truefalse;

    testdate.day = 22;
    testdate.month = 2;
    testdate.year = 2010;

    printf("\n\n#TEST# dd/mm/yy = %d/%d/%d.\n", testdate.day, testdate.month,
           testdate.year);
    printf("Is that the last Xday of %d?\n", testdate.month);
    truefalse = islastxdom(&testdate);
    if(truefalse)
        printf("Yes.  It is the last xday of the month of %d.\n", testdate.month);
    else
        printf("No.  It is NOT last xday of the month of %d.\n", testdate.month);

    printf("Is that date in the last week of the month?\n");
    truefalse = islastweek(&testdate);
    if(truefalse)
        printf("Yes.  It is in the last week of %d.\n", testdate.month);
    else
        printf("No.  It is NOT in the last week of %d.\n", testdate.month);


    testdate.day = 24;
    testdate.month = 11;
    testdate.year = 2011;

    printf("\n\n#TEST# dd/mm/yy = %d/%d/%d.\n", testdate.day, testdate.month,
           testdate.year);
    printf("Is that the last Xday of %d?\n", testdate.month);
    truefalse = islastxdom(&testdate);
    if(truefalse)
        printf("Yes.  It is the last xday of the month of %d.\n", testdate.month);
    else
        printf("No.  It is NOT the last xday of the month of %d.\n", testdate.month);

    printf("Is that date in the last week of the month?\n");
    truefalse = islastweek(&testdate);
    if(truefalse)
        printf("Yes.  It is in the last week of %d.\n", testdate.month);
    else
        printf("No.  It is NOT in the last week of %d.\n", testdate.month);


    testdate.day = 17;
    testdate.month = 11;
    testdate.year = 2011;

    printf("\n\n#TEST# dd/mm/yy = %d/%d/%d.\n", testdate.day, testdate.month,
           testdate.year);
    printf("Is that the last Xday of %d?\n", testdate.month);
    truefalse = islastxdom(&testdate);
    if(truefalse)
        printf("Yes.  It is the last xday of the month of %d.\n", testdate.month);
    else
        printf("No.  It is NOT last xday of the month of %d.\n", testdate.month);

    printf("Is that date in the last week of the month?\n");
    truefalse = islastweek(&testdate);
    if(truefalse)
        printf("Yes.  It is in the last week of %d.\n", testdate.month);
    else
        printf("No.  It is NOT in the last week of %d.\n", testdate.month);


    testdate.day = 24;
    testdate.month = 10;
    testdate.year = 2011;

    printf("\n\n#TEST# dd/mm/yy = %d/%d/%d.\n", testdate.day, testdate.month,
           testdate.year);
    printf("Is that the last Xday of %d?\n", testdate.month);
    truefalse = islastxdom(&testdate);
    if(truefalse)
        printf("Yes.  It is the last xday of the month of %d.\n", testdate.month);
    else
        printf("No.  It is NOT the last xday of the month of %d.\n", testdate.month);

    printf("Is that date in the last week of the month?\n");
    truefalse = islastweek(&testdate);
    if(truefalse)
        printf("Yes.  It is in the last week of %d.\n", testdate.month);
    else
        printf("No.  It is NOT in the last week of %d.\n", testdate.month);

    testdate.day = 31;
    testdate.month = 10;
    testdate.year = 2011;

    printf("\n\n#TEST# dd/mm/yy = %d/%d/%d.\n", testdate.day, testdate.month,
           testdate.year);
    printf("Is that the last Xday of %d?\n", testdate.month);
    truefalse = islastxdom(&testdate);
    if(truefalse)
        printf("Yes.  It is the last xday of the month of %d.\n", testdate.month);
    else
        printf("No.  It is NOT the last xday of the month of %d.\n", testdate.month);

    printf("Is that date in the last week of the month?\n");
    truefalse = islastweek(&testdate);
    if(truefalse)
        printf("Yes.  It is in the last week of %d.\n", testdate.month);
    else
        printf("No.  It is NOT in the last week of %d.\n", testdate.month);

    testdate.day = 22;
    testdate.month = 11;
    testdate.year = 2011;

    printf("\n\n#TEST# dd/mm/yy = %d/%d/%d.\n", testdate.day, testdate.month,
           testdate.year);
    printf("Is that the last Xday of %d?\n", testdate.month);
    truefalse = islastxdom(&testdate);
    if(truefalse)
        printf("Yes.  It is the last xday of the month of %d.\n", testdate.month);
    else
        printf("No.  It is NOT the last xday of the month of %d.\n", testdate.month);

    printf("Is that date in the last week of the month?\n");
    truefalse = islastweek(&testdate);
    if(truefalse)
        printf("Yes.  It is in the last week of %d.\n", testdate.month);
    else
        printf("No.  It is NOT in the last week of %d.\n", testdate.month);


    testdate.day = 29;
    testdate.month = 11;
    testdate.year = 2011;

    printf("\n\n#TEST# dd/mm/yy = %d/%d/%d.\n", testdate.day, testdate.month,
           testdate.year);
    printf("Is that the last Xday of %d?\n", testdate.month);
    truefalse = islastxdom(&testdate);
    if(truefalse)
        printf("Yes.  It is the last xday of the month of %d.\n", testdate.month);
    else
        printf("No.  It is NOT the last xday of the month of %d.\n", testdate.month);

    printf("Is that date in the last week of the month?\n");
    truefalse = islastweek(&testdate);
    if(truefalse)
        printf("Yes.  It is in the last week of %d.\n", testdate.month);
    else
        printf("No.  It is NOT in the last week of %d.\n", testdate.month);

    testdate.day = 30;
    testdate.month = 10;
    testdate.year = 2011;

    printf("\n\n#TEST# dd/mm/yy = %d/%d/%d.\n", testdate.day, testdate.month,
           testdate.year);
    printf("Is that the last Xday of %d?\n", testdate.month);
    truefalse = islastxdom(&testdate);
    if(truefalse)
        printf("Yes.  It is the last xday of the month of %d.\n", testdate.month);
    else
        printf("No.  It is NOT the last xday of the month of %d.\n", testdate.month);

    printf("Is that date in the last week of the month?\n");
    truefalse = islastweek(&testdate);
    if(truefalse)
        printf("Yes.  It is in the last week of %d.\n", testdate.month);
    else
        printf("No.  It is NOT in the last week of %d.\n", testdate.month);

    /* test the isleapyear function */
    printf("\n\n##############################################");
    printf("\nLeap Year Function Test.\n");

    testdate.day = 1;
    testdate.month = 1;
    testdate.year = 1600;
    printf("\n\n#TEST# mm/dd/yy = %d/%d/%d.\n", testdate.month, testdate.day,
           testdate.year);
    truefalse = isleapyear(&testdate);
    if(truefalse)
        printf("Yes, %d is a leap year.\n", testdate.year);
    else
        printf("No, %d is a leap year.\n", testdate.year);


    testdate.day = 1;
    testdate.month = 1;
    testdate.year = 2000;
    printf("\n\n#TEST# mm/dd/yy = %d/%d/%d.\n", testdate.month, testdate.day,
           testdate.year);
    truefalse = isleapyear(&testdate);
    if(truefalse)
        printf("Yes, %d is a leap year.\n", testdate.year);
    else
        printf("No, %d is not a leap year.\n", testdate.year);

    testdate.jdn = jdncnvrt(&testdate);
    printf("\n\n#test# 1/1/2000 has a JDN of %d", testdate.jdn);

    testdate.day = 1;
    testdate.month = 1;
    testdate.year = 1700;
    printf("\n\n#TEST# mm/dd/yy = %d/%d/%d.\n", testdate.month, testdate.day,
           testdate.year);
    truefalse = isleapyear(&testdate);
    if(truefalse)
        printf("Yes, %d is a leap year.\n", testdate.year);
    else
        printf("No, %d is not a leap year.\n", testdate.year);


    testdate.day = 1;
    testdate.month = 1;
    testdate.year = 1800;
    printf("\n\n#TEST# mm/dd/yy = %d/%d/%d.\n", testdate.month, testdate.day,
           testdate.year);
    truefalse = isleapyear(&testdate);
    if(truefalse)
        printf("Yes, %d is a leap year.\n", testdate.year);
    else
        printf("No, %d is not a leap year.\n", testdate.year);


    testdate.day = 1;
    testdate.month = 1;
    testdate.year = 2100;
    printf("\n\n#TEST# mm/dd/yy = %d/%d/%d.\n", testdate.month, testdate.day,
           testdate.year);
    truefalse = isleapyear(&testdate);
    if(truefalse)
        printf("Yes, %d is a leap year.\n", testdate.year);
    else
        printf("No, %d is not a leap year.\n", testdate.year);


    testdate.day = 1;
    testdate.month = 1;
    testdate.year = 2108;
    printf("\n\n#TEST# mm/dd/yy = %d/%d/%d.\n", testdate.month, testdate.day,
           testdate.year);
    truefalse = isleapyear(&testdate);
    if(truefalse)
        printf("Yes, %d is a leap year.\n", testdate.year);
    else
        printf("No, %d is not a leap year.\n", testdate.year);
}

void testsuite_checkholidays(void)
{
    struct DATETIME begin_date; /* date to begin date calculations */
    struct DATETIME end_date; /* date to use for end calculations */
    struct DATETIME result_date; /* used to hold new dates resulting from
                                    calculations */
    int day_count; /* number of days before or after a particular deadline */
    char dateinput[11]; /*used to get data from the keyboard */
    char line[80]; /* keyboard buffer */

    printf("\n\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("This function tests our various date algorithms.\n");
    printf("The first date tests a \"weekend\" rule.\n");
    printf("The date is October 8, 2011 (Saturday).\n");
    begin_date.month = 10;
    begin_date.day = 8;
    begin_date.year = 2011;
    holidayprinttest(&begin_date);

    printf("The next date tests a \"weekend\" rule.\n");
    printf("The date is October 9, 2011 (Sunday).\n");
    begin_date.month = 10;
    begin_date.day = 9;
    begin_date.year = 2011;
    holidayprinttest(&begin_date);

    printf("The next date tests an \"absolute\" rule.\n");
    printf("The date is January 1, 2010 (Friday, New Year's Day).\n");
    begin_date.month = 1;
    begin_date.day = 1;
    begin_date.year = 2010;
    holidayprinttest(&begin_date);

    printf("The next date tests an \"absolute\" rule.\n");
    printf("The date is December 25, 2014 (Thursday, Christmas Day).\n");
    begin_date.month = 12;
    begin_date.day = 25;
    begin_date.year = 2014;
    holidayprinttest(&begin_date);

    printf("The next date tests a \"relative\" rule.\n");
    printf("The date is November 24, 2011 (Thursday, Thanksgiving Day).\n");
    begin_date.month = 11;
    begin_date.day = 24;
    begin_date.year = 2011;
    holidayprinttest(&begin_date);

    printf("The next date tests a \"relative\" rule.\n");
    printf("The date is May 28, 2011 (Memorial Day).\n");
    begin_date.month = 5;
    begin_date.day = 28;
    begin_date.year = 2012;
    holidayprinttest(&begin_date);


    printf("\n\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    /* commented out ...
    printf("Test your own dates.\n");
    printf("please enter the beginning date in the format mm/dd/yyyy");
    printf("\n(Press x to end):\n");

    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d/%d/%d", &begin_date.month, &begin_date.day,
           &begin_date.year);
    printf("\nHow many days out is the deadline?");
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d", &day_count);
    date_offset (&begin_date, &end_date,
                  day_count);
    printf("The deadline is: %d/%d/%d.\n", end_date.month, end_date.day,
           end_date.year);
    if (isholiday(&end_date)==0)
        printf("The end date is valid and does not fall on a holiday.\n");
    else
        printf("The end date is NOT valid.  It falls on a holiday.\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    end commented out section. */
    return;
}

void holidayprinttest(struct DATETIME *dt)
{
    printf("%d/%d/%d ", dt->month, dt->day, dt->year);
    if (isholiday(dt) !=0)
        printf("is a holiday.\n\n");
    else
        printf("is NOT a holiday.\n");

    return;

}

void testsuite_courtdays(void)
{
    struct DATETIME begin_date; /* date to begin date calculations */
    struct DATETIME end_date; /* date to use for end calculations */
    struct DATETIME result_date; /* used to hold new dates resulting from
                                    calculations */
    int day_count; /* number of days before or after a particular deadline */
    char dateinput[11]; /*used to get data from the keyboard */
    char line[80]; /* keyboard buffer */

    printf("\n\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("This function tests the courtday counter.\n");
    printf("please enter the beginning date in the format mm/dd/yyyy");
    printf("\n(Press x to end):\n");

    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d/%d/%d", &begin_date.month, &begin_date.day,
           &begin_date.year);
    printf("\nHow many court days out is the deadline?");
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d", &day_count);
    courtday_offset (&begin_date, &end_date,
                  day_count);
    printf("The deadline is: %d/%d/%d.\n", end_date.month, end_date.day,
           end_date.year);
    if (isholiday(&end_date)==0)
        printf("The end date is valid and does not fall on a holiday.\n");
    else
        printf("The end date is NOT valid.  It falls on a holiday.\n");
        
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("Let's calculate the hearing and related dates for a\n");
    printf("C")
    printf("\n\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("Please enter the date you will serve your motion (in mm/dd/yy format):\n");
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d/%d/%d", &begin_date.month, &begin_date.day,
           &begin_date.year);
    printf("\nHow many court days out is the deadline?");
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d", &day_count);
    courtday_offset (&begin_date, &end_date,
                  day_count);
    printf("The deadline is: %d/%d/%d.\n", end_date.month, end_date.day,
           end_date.year);
    if (isholiday(&end_date)==0)
        printf("The end date is valid and does not fall on a holiday.\n");
    else
        printf("The end date is NOT valid.  It falls on a holiday.\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");

    return;
}


#ifdef UNDEF /* presently this entire source file is removed from compilation
                for testing. */

/*
        Add functions to test date validity.

To check if a date is on the calendar:

  if [y,m,d] = d(g(y,m,d))


*/

/* date test */

/* variable declarations */
    struct DATETIME begin_date; /* date to begin date calculations */
    struct DATETIME end_date; /* date to use for end calculations */
    struct DATETIME result_date; /* used to hold new dates resulting from
                                    calculations */
    int day_count; /* number of days before or after a particular deadline */
    char dateinput[11]; /*used to get data from the keyboard */
    char line[80]; /* keyboard buffer */

    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("This is a program to test our various date algorithms.\n");
    printf("please enter the beginning date in the format mm/dd/yyyy");
    printf("\n(Press x to end):\n");

    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d/%d/%d", &begin_date.month, &begin_date.day,
           &begin_date.year);
    printf("/nPlease enter the deadline:");
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d", &day_count);
    date_offset (&begin_date, &end_date,
                  day_count);
    printf("The deadline is: %d/%d/%d.\n", end_date.month, end_date.day,
           end_date.year);
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    day_count = isholiday (&begin_date);

/* END DATE TEST */

void testsuite (void)
{
    struct DATETIME date1; /* variable to test date calculations */
    struct DATETIME date2; /* second variable to test date calculations */
    struct DATETIME date3; /* third test variable to use for date  */
    int numdays = 35; /* this is a variable to test the date offset function.
                         35 is because the difference between 8/18/11 and
                         9/22/11 = 25 days. */

    date1.year = 2011; /* first date is 8/18/2011 */
    date1.month = 8;
    date1.day = 18;   /* A Thursday */

    date2.year = 2011; /* second date is 9/22/2011 */
    date2.month = 9;   /* this second date should be 25 days after date1 */
    date2.day = 22;    /* A Thursday */


    /* test Sakamoto's formula */

    printf("\n\n=============================================\n");
    printf("The first date is %d/%d/%d\n", date1.month, date1.day, date1.year);
    date1.day_of_week = wkday_sakamoto (&date1);
    printf("The day of the week is ");
    printwkday(date1.day_of_week);
    printf(".\n");
    if (isweekend(&date1))
        printf("That day falls on a weekend.\n");
        else printf ("That day falls on a weekday.\n\n");

    printf("The second date is %d/%d/%d\n", date2.month, date2.day, date2.year);
    date2.day_of_week = wkday_sakamoto (&date2);
    printf("The day of the week is ");
    printwkday(date2.day_of_week);
    printf(".\n");
    if (isweekend(&date2))
        printf("That day falls on a weekend.\n\n");
        else printf ("That day falls on a weekday.\n\n");

    /* test date calculations */

            /* Julian date calcs */

    printf("The Julian date for date1 = %d\n\n", jdncnvrt (&date1));
        printf("The Julian date for date2 = %d\n\n", jdncnvrt (&date2));

    /* difference between two dates */

    printf("There are %d days between date1 and date2\n",
           date_difference(&date1, &date2));
    printf("There are %d days between date2 and date1\n",
           date_difference(&date2, &date1));
    printf("=============================================\n\n");
    /* What date is it in x days? */

    date_offset(&date1, &date3, numdays);
    date3.day_of_week = wkday_sakamoto (&date3);
    printf("What is the due date if the filing is due %d days from %d/%d/%d?\n"
           , numdays, date1.month, date1.day, date1.year);
    printf("The due date is");
    printwkday(date3.day_of_week);
    printf(", %d/%d/%d\n", date3.month, date3.day, date3.year);
    printf("The Julian date for date3 = %d\n\n", jdncnvrt (&date3));
    printf("\n\n=============================================\n");

    return;
}
#endif /* UNDEF */
