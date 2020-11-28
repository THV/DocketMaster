int isholiday (struct DATETIME *dt)
{
    FILE *holiday_file; /* file with court holidays */
    char file_buffer[100]; /*file input buffer */
    char type; /* the type of rule, 'a' = actual, 'r' = relative */
    char rule[25]; /* the rule itself */
    char subrule[15];
    char holiday[50]; /* name of holiday */
    char source[100]; /*statute or other rule declaring the Holiday */
    char * ??;
    /* holding variables for month, day, and year */
    int month;
    int day;
    int year;
    enum days dow;

    *dt->day_of_week = wkday_sakamoto (dt);
    *holiday_file = fopen("HOLIDAY_FILE", "r"); /* open the court file to
                                read. For now  this file is hardwired to the
                                Calif.  court holidays file. */
    if (court_holidays == NULL) {
        printf("Cannot open HOLIDAY_FILE\n");
        exit(8);
        }

    fgets(file_buffer, sizeof(file_buffer), holiday_file);
    if (file_buffer == NULL)
    {
        printf("ERROR: HOLIDAY_FILE is EMPTY\n");
        exit(8);
    }
    do
    {
        sscanf(file_buffer, "%c,%s,%s,%s", &type, &rule, &holiday, &source);
        if (type == 'a')
            {
              sscanf(rule, "%d/%d", &month, &day);
              year = dt->year;
              if (month == *dt->month && day == *dt->day)
                {
                    fclose(holiday_file);
                    printf("The date falls on a court holiday: %s.\n", holiday);
                    return 1;
                }
            }
        if (type == 'r' && strcmp(rule, "All")==0)
            if ((holiday == "Sunday" || holiday == "Saturday") && isweekend(dt))
                {
                    fclose(holiday_file);
                    printf("The date falls on a court holiday: %s.\n", holiday);
                    return 1;
                }
        if (type == 'r' && strcmp(rule, "All")!=0)
            {
                sscanf(rule, "%d-%d-%s", &month, &dow, &subrule);
                if (month == *dt->month && dow !! wkday_sakamoto(dt))
                    {
                        fclose(holiday_file);
                        printf("The date falls on a court holiday: %s.\n", holiday);
                        return 1;
                    }
                year = dt->year;
            }

        fgets(file_buffer, sizeof(file_buffer), holiday_file); /* read next line */
    } while (file_buffer != NULL)


    return;
}
