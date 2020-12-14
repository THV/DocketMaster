/*
 * File: rule processor
 *
 * Description: This module processes the court holiday rules, and litigation
 * events.  It creates two balanced binary search trees to hold the data 
 * for the court rules and court events.
 *
 * Version: 1.0.20
 * Created: 
 * Last Modified: Sun Dec 13 21:30:30 2020
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
 *
 * File Formats: 
 * Restrictions:
 * Error Handling:
 * Notes:
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ruleprocessor.h"

void initializelist(struct holidaynode *holidayhashtable[])
{
    int monthctr; /* counter to loop through months */

    for(monthctr = 0; monthctr < MONTHS; monthctr++)
    {
        holidayhashtable[monthctr] = NULL;
    }
    return;
}
struct holidaynode * addholidayrule(struct holidaynode *list,
                                    struct holidayrule *holiday)
{
    struct holidaynode *new_hrule; /* pointer to new holiday rule */

    new_hrule = malloc(sizeof(struct holidaynode)); /* creates a new node */

    /* copy the data into the new node */
    new_hrule->rule.month = holiday->month;
    new_hrule->rule.ruletype = holiday->ruletype;
    new_hrule->rule.wkday  = holiday->wkday;
    new_hrule->rule.wknum = holiday->wknum;
    new_hrule->rule.day = holiday->day;
    strcpy(new_hrule->rule.holidayname, holiday->holidayname);
    strcpy(new_hrule->rule.authority, holiday->authority);
    new_hrule->nextrule = list; /* makes the new node point to the current
                                    first node */
    list = new_hrule; /* makes the new node the first node */

    return list;
}
void closerules(struct holidaynode *holidayhashtable[])
{
    struct holidaynode *tempnode;
    int monthctr; /* counter to loop through months */

    for(monthctr = 0; monthctr < MONTHS; monthctr++)
    {
        while (holidayhashtable[monthctr] != NULL)
            /* checks to see if list is empty */
        {
            tempnode = holidayhashtable[monthctr];
            /* sets a temporary pointer to the first node so we don't
                lose it. */
            holidayhashtable[monthctr] = holidayhashtable[monthctr]->nextrule;
            /* makes the next node the new first node */
            free(tempnode); /* frees the memory allocated to the former first
                                node */
        }
    }
    return;
}

void printholidayrules(struct holidaynode *holidayhashtable[])
{
    struct holidaynode *tempnode;
    int monthctr; /* counter to loop through months */

    for(monthctr = 0; monthctr < MONTHS; monthctr++)
    {
        tempnode = holidayhashtable[monthctr];
        /* sets a temporary pointer to the first node so we traverse
            the list. */

        printf("-------------------------------------------------------\n");
        if (tempnode != NULL)
        {
            switch (monthctr)
            {
            case 0: /* January rules */
                printf("This holiday rules for January are as follows:\n");
                break;
            case 1:
                printf("This holiday rules for February are as follows:\n");
                break;
            case 2:
                printf("This holiday rules for March are as follows:\n");
                break;
            case 3:
                printf("This holiday rules for April are as follows:\n");
                break;
            case 4:
                printf("This holiday rules for May are as follows:\n");
                break;
            case 5:
                printf("This holiday rules for June are as follows:\n");
                break;
            case 6:
                printf("This holiday rules for July are as follows:\n");
                break;
            case 7:
                printf("This holiday rules for August are as follows:\n");
                break;
            case 8:
                printf("This holiday rules for September are as follows:\n");
                break;
            case 9:
                printf("This holiday rules for October are as follows:\n");
                break;
            case 10:
                printf("This holiday rules for November are as follows:\n");
                break;
            case 11:
                printf("This holiday rules for December are as follows:\n");
                break;
            case 12:
                printf("This holiday rules that apply to all months");
                printf(" are as follows:\n");
                break;
            default:
                printf("\n\n\n ERROR BAD MONTH.\n");
                break;
            }
        }
        else
        {
            switch (monthctr)
            {
            case 0: /* January rules */
                printf("No holidays in January.\n");
                break;
            case 1:
                printf("No holidays in February.\n");
                break;
            case 2:
                printf("No holidays in March.\n");
                break;
            case 3:
                printf("No holidays in April.\n");
                break;
            case 4:
                printf("No holidays in May.\n");
                break;
            case 5:
                printf("No holidays in June.\n");
                break;
            case 6:
                printf("No holidays in July.\n");
                break;
            case 7:
                printf("No holidays in August.\n");
                break;
            case 8:
                printf("No holidays in September.\n");
                break;
            case 9:
                printf("No holidays in October.\n");
                break;
            case 10:
                printf("No holidays in November.\n");
                break;
            case 11:
                printf("No holidays in December.\n");
                break;
            case 12:
                printf("No holidays in apply to all months.");
                break;
            default:
                printf("\n\n\n ERROR BAD MONTH.\n");
                break;
            }
        }
        while (tempnode != NULL) /* checks to see if list is empty */
        {
            printf("The applicable holiday is %s.\n",
                   tempnode->rule.holidayname);
            printf("The applicable ruletype is %c.\n",
                   tempnode->rule.ruletype);
            if ((tempnode->rule.ruletype != 'a') &&
                    (tempnode->rule.ruletype != 'A'))
            {
                printf("The applicable weekday is %d.\n",
                       tempnode->rule.wkday);
                printf("The applicable weeknumber is %d.\n",
                       tempnode->rule.wknum);
            }
            else
            {
                printf("The Day is %d.\n", tempnode->rule.day);
            }
            printf("The governing authority is %s.\n",
                   tempnode->rule.authority);
            printf("\n");
            /* move to the next node */
            tempnode = tempnode->nextrule;
        }

    }
    return;
}

/*
 * Description: describe what the function does.
 *
 * Arguments: Describe the parameters of the function.
 *
 * Returns: describe the return value of the function
 *
 * File Format: Comma Separated Values.  Fields: Type, Rule, Holiday, Source.
 * The rule field is organized as Month-DayOfWeek-Number.  The "number"
 * sub-field of the rule can contain (1) the week number e.g., 4 for the 4th
 * week, (2) the word "all" for every week- day of the month (e.g., all
 * Saturdays), (3) "last" for the last week-day (e.g., last Monday), or (4)
 * "first" for the first week-day (e.g., first Tuesday).
 */

int processhrule (struct DATETIME *dt, struct holidaynode *rulenode)
{

    switch (rulenode->rule.ruletype)
        {
            case 'a': /* fall through */
            case 'A':
                if (rulenode->rule.day == dt->day)
                    return 1;
                break;
            case 'r': /* fall through */
            case 'R':
                if (rulenode->rule.wkday == dt->day_of_week)
                {
                    /* previous line tests to see if day of week matches. */
                    if ((rulenode->rule.wknum == LASTWEEK) && islastxdom(dt))
                    {
                        return 1;
                    }
                    else if (dt->day >= ((rulenode->rule.wknum-1)*WEEKDAYS+1) &&
                            dt->day <= (rulenode->rule.wknum*WEEKDAYS))
                    {
                        /* Prev. line tests to see if the day is in the
                        proper week. The formula "(wknum-1)*7+1" gets the
                        first day of the applicable week; "wknum*7"
                        calculates the last day of the applicable week.  */

                        return 1;
                    }
                    else
                        return 0;
                }
                break;
            case 'w': /* fall through */
            case 'W':
                if(rulenode->rule.wkday == dt->day_of_week)
                    return 1;
                break;
            default:
                /* fall through */
                break;
        }

    return 0;
}

/*
 * Description: describe what the function does.
 *
 * Arguments: Describe the parameters of the function.
 *
 * Returns: describe the return value of the function
 *
 * File Format: Comma Separated Values.  Fields: Type, Rule, Holiday, Source.
 * The rule field is organized as Month-DayOfWeek-Number.  The "number"
 * sub-field of the rule can contain (1) the week number e.g., 4 for the 4th
 * week, (2) the word "all" for every week- day of the month (e.g., all
 * Saturdays), (3) "last" for the last week-day (e.g., last Monday), or (4)
 * "first" for the first week-day (e.g., first Tuesday).
 */

int isholiday (struct DATETIME *dt)
{
    struct holidaynode *tempnode;

    /* First, calculate whether an ALLMONTHS rule applies and whether this date
    falls on a weekend */

    dt->day_of_week = wkday_sakamoto (dt);
    tempnode = holidayhashtable[ALLMONTHS-1];
    while(tempnode != NULL)
        {
            if (processhrule(dt,tempnode) == 1)
                return 1;
            tempnode = tempnode->nextrule;
        }

    /* Second, calculate whether there are any holidays on the month of the
        argument's date */

    tempnode = holidayhashtable[dt->month-1];
    while(tempnode != NULL)
        {
            if (processhrule(dt,tempnode) == 1)
                return 1;
            tempnode = tempnode->nextrule;
        }

    return 0;
}

#ifdef UNDEF /* presently the remainder of source file has been removed from
    compilation for testing. */


int loadholidays (struct holidaynode current_holidays, char holiday_file[])
{
    FILE *holiday_file; /* file with court holidays */
    unsigned char file_buffer[100]; /*file input buffer */
    unsigned char headers[100];
    unsigned char type; /* the type of rule, 'a' = actual, 'r' = relative */
    unsigned char rule[25]; /* the rule itself */
    unsigned char ruletype[15];
    unsigned char holiday[50]; /* name of holiday */
    unsigned char source[100]; /*statute or other rule declaring the Holiday */
    unsigned char *linelocation; /* a variable that points to the current
                                    position of a string */
    int index; /* a variable that points to the current postion of a string */
    /* holding variables for month, day, and year */
    int month;
    int day;
    int year;
    char dow[10];
    char *endoffile;
    int count; /* loop counter */
    int count2;
    /* enum days dow; */


    if (isempty(current_holidays) !=0)
        return -1; /* indicates holidays already loaded */

    /*------------------>            WARNING                  <---------------
     *  this function does not does not re-read the file if the binary tree  
     *  for current_holidays contains data.  If the court or jurisdiction   
     *  changes and the holidays need to be re-read and processed, the binary
     *  tree must be initialized before calling this function.
     */

    /* TODO (Thomas#1#): Address the issue of re-reading the file
    if the court jurisdiction changes, etc. */


    holiday_file = fopen(holiday_file, "r"); /* open the holiday file to read */
    if (holiday_file == NULL)
    {
        printf("Cannot open HOLIDAY_FILE\n");
        exit(8);
    }

    fgets(file_buffer, sizeof(file_buffer), holiday_file);
    if (file_buffer == NULL)
    {
        printf("ERROR: HOLIDAY_FILE is EMPTY\n");
        exit(8);
    }

    /* check to see if we are reading the proper file type */
    sscanf(file_buffer, "%s", headers);
    index = 0;
    do
    {
        if (headers[index] != ',' && headers[index] != '\0')
        {

        }
    }

    fgets(file_buffer, sizeof(file_buffer), holiday_file);


    do
    {
        month = atoi(&file_buffer[0]);
        if (month == 13)
        {
            for(count = 2; count < 100; count++)
            {
                if (file_buffer[count] != ',')
                {
                    rule[count] = file_buffer[count];
                    rule[count+1] = '\0';
                    count++;
                }
                else
                {
                    rule[count] = '\0';
                    break;
                }
            }
        }
        else if (month == dt->month)
        {
            /* add instructions */
            if (month > 10)
                count = 2;
            else
                count = 1;
            ruletype[0] = file_buffer[count];
            ruletype[1] = '\0';
            if (ruletype[0] == 'A')
            {
                day = atoi(&file_buffer[count+1])
                      if (day == dt->day)
                          return 1;

            }
            else
            {
                /* instructions */
            }

        }
    }





    count = 2;
    for(count2 = 0; count < 100; count++)
    {
        if (file_buffer[count] != ',')
        {
            rule[count2] = file_buffer[count];
            rule[count2+1] = '\0';
            count2++;
        }
        else
        {
            rule[count2] = '\0';
            break;
        }
    }
    for(count2 = 0; count < 100; count++)
    {
        if (file_buffer[count] != ',')
        {
            holiday[count2] = file_buffer[count];
            count2++;
        }
        else
        {
            rule[count2] = '\0';
            break;
        }
    }
    count2 = 0;
    while (file_buffer[count] != '\0')
    {
        holiday[count2] = file_buffer[count];
        count2++;
        count++;
    }
    holiday[count2]='\0';
    printf("The type is %c\n", type);
    printf("The rule is: %s\n", rule);
    printf("The Holiday is called: %s\n", holiday);
    printf("The Holiday is set forth in %s\n\n", source);
    if (type != 'a')
    {
        printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
        sscanf(rule, "%d-%s-%s", &month, dow, subrule);
        printf("The Month of this Holiday is %d\n", month);
        printf("The Day of the week of this Holiday is: %s\n", dow);
        printf("The rule is: %s\n",subrule);
        printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
    }
    endoffile = fgets(file_buffer, sizeof(file_buffer), holiday_file);
        /* read next line */
}
while (endoffile != NULL);

fclose(holiday_file);
return 0;
}

#endif /* UNDEF */
