/*
 * =============================================================================
 *
 *       Filename: errorhandler.c
 *
 *    Description: 
 *
 *        Version: 1.0
 *        Created: 03/11/2012 12:49:17 PM
 *  Last Modified: Sun 11 Mar 2012 01:01:45 PM PDT
 *       Compiler: gcc
 *
 *         Author: Thomas H. Vidal (THV), thomasvidal@hotmail.com
 *   Organization: Dark Matter Software
 *      Copyright: Copyright (c) 2012, Thomas H. Vidal
 *
 *	        Usage: 
 *    File Format: 
 *   Restrictions: 
 * Error Handling: 
 *     References: 
 *          Notes: 
 * =============================================================================
 */

#include <stdlib.h>



/* #####   HEADER FILE INCLUDES   ########################################### */

/* #####   MACROS  -  LOCAL TO THIS SOURCE FILE   ########################### */

/* #####   SYMBOLIC CONSTANTS -  LOCAL TO THIS SOURCE FILE   ################ */

/* #####   TYPE DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ################# */

/* #####   DATA TYPES  -  LOCAL TO THIS SOURCE FILE   ####################### */

/* #####   VARIABLES  -  LOCAL TO THIS SOURCE FILE   ######################## */

/* #####   PROTOTYPES  -  LOCAL TO THIS SOURCE FILE   ####################### */

/* #####   FUNCTION DEFINITIONS  -  EXPORTED FUNCTIONS   #################### */

/*
 * ===  FUNCTION  ==============================================================
 *          Name: usage
 *   Description: If the program is invoked with commandline arguments, this
 *                function is called if the arguments are incorrect.
 *     Arguments: A sting containing the program's name.
 *       Returns: Nothing; exits the program.
 *     Algorithm:
 *    References:
 *  	   Notes:
 * =============================================================================
 */
void usage(char *program_name)
{
    fprintf(stderr, "Uasge is %s -g[good test file] -t[no text delimiters"
            " testfile] -b[poorly formatted test file]\n", program_name);
    exit(8);

}		/* -----  end of function usage  ----- */


/*
 * ===  FUNCTION  ==============================================================
 *          Name: errorprocessor
 *   Description: Receives an error code and processes it.
 *     Arguments:
 *       Returns:
 *     Algorithm:
 *    References:
 * 	       Notes:
 * =============================================================================
 */
void errorprocessor(int errcode)
{
    switch (errcode) {
        case NULSTRING:
            fprintf(stderr, "## Error No. %d", errcode);
            exit(EXIT_FAILURE);
            break;
        case BADCOMMANDLINE:
            fprintf(stderr, "## Error No. %d: Bad option.", errcode);
            usage(program_name);
            break;
        case NOFDELIM:
            fprintf(stderr, "## Error No. %d: No, or improper, field delimiters.\n"
                    "## Input file expects fields separated by commas.\n\n",
                    errcode);
            exit(EXIT_FAILURE);
            break;
        case NOTDELIM:
            fprintf(stderr, "## Error No. %d: No, or improper, text delimiters."
                    "\n## Input file expects text fields enclosed with double "
                    "quotes.\n\n", errcode);
            exit(EXIT_FAILURE);
            break;
        case NOERROR: /*  fall through */
        default:
            /* there is no error code or the error code is unknown. */
            fprintf(stderr, "## Unknown Error.");
            exit(EXIT_FAILURE);
            break;
    }
    return;
}		/* -----  end of function errorprocessor  ----- */


/* #####   FUNCTION DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ############# */
