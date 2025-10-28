#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "mymat.h"
#include "utils.h"


/**
 * For detailed project structure, see README file. 
 */


/**
 * This is the main program - the matrix operations
 * calculator within a "command line"-like interface.
 * This function prints to user the instructions how
 * to use the calculator and opens an interface for
 * user interaction with the program. The user is required
 * to enter the command and the inputs required to perform
 * the calculation as instructed. If illegal inputs will be
 * entered, an appropriate handling will be applied for each
 * invalid user input and it will inform the user about the
 * error. The program could be stopped by entering the stop
 * command, on user demand.
*/
int main()
{
    /* variables declarations */
    mat MAT_A, MAT_B, MAT_C, MAT_D, MAT_E, MAT_F;
    /* pointer to array to store 2D matrices */
    mat *mats_arr[NUM_OF_MATS] = { NULL };
    /* array to store indices of matrices for calculation -
       the max number of used matrices is 3 */
    int mats_ids[NUM_OF_USED_MATS] = { INVALID_ARR_INDEX,
                                       INVALID_ARR_INDEX,
                                       INVALID_ARR_INDEX };
    char user_input[MAX_INPUT_LEN];
    char *args;
    char *args_dup;
    char *args_temp;
    int input_len;
    int args_count;
    int arg_id;
    int mat_id;
    int is_arg_valid = FALSE;
    double scalar;
    int read_row;
    int read_col;
    int is_num_inserted = NO_NUM_INSERTED;

    /* initialize matrices with zeros */
    clear_mat(MAT_A);
    clear_mat(MAT_B);
    clear_mat(MAT_C);
    clear_mat(MAT_D);
    clear_mat(MAT_E);
    clear_mat(MAT_F);

	/* program description user message */
	program_description();
    
    while (TRUE) {
        /* mark new line for user to enter input */
        printf(INPUT_LINE_SYM);

        if (fgets(user_input, sizeof(user_input), stdin) != NULL) {
            /* get full input length for further usage */
            input_len = strlen(user_input);
            /* cut new line */
            user_input[strcspn(user_input, "\n")] = NULL_TERMINATOR;
            /* copy for further usage */
            args_temp = strdup(user_input);

            /* tokenize using defined delimiters */
            args = strtok(user_input, CMD_DELIMITERS);
            args_count = count_input_args(args, CMD_DELIMITERS);

            /* validate command */
            args_dup = strtok(args_temp, CMD_DELIMITERS);
            command cmd = get_command(args_dup);

            /* unknown command */
            if (cmd == ERROR) {
                if (args_dup[strlen(args_dup) - 1] == ',')
                    printf(ILLEGAL_COMMA_MSG);
                else
                    printf(ERROR_CMD_MSG);
                continue;
            }

            /* validate number of arguments */
            if (!is_args_count_valid(cmd, args_dup, args_count, input_len)) {
                continue;
            }

            /* stop if "stop" called in valid way */
            if (cmd == STOP) {
                break;
            }

            /* parse command arguments with delimiters */
            args_dup = strtok(NULL, CMD_DELIMITERS);
            arg_id = 0;
            mat_id = 0;
            read_row = 0;
            read_col = 0;
    
            while (args_dup != NULL) {
                is_arg_valid = validate_arg(cmd, args_dup, arg_id, args_count);
                /* invalid argument detected - exit */
                if (!is_arg_valid)
                    break;
                else {  /* valid argument - */
                    is_num_inserted = apply_arg(cmd,
                                                args_dup,
                                                mats_arr,
                                                &MAT_A, &MAT_B, &MAT_C, &MAT_D, &MAT_E, &MAT_F,
                                                &scalar, read_row, read_col,
                                                mats_ids,
                                                mat_id);
                    
                    /* insert num in selected input matrix cell */
                    if (is_num_inserted) {
                        if (read_col == (SIZE - 1)) {
                            read_row++;
                            read_col = 0;
                        }
                        else {
                            read_col++;
                        }
                    }
                    else
                        mat_id++;
                }
                /* parse next argument */
                args_dup = strtok(NULL, CMD_DELIMITERS);
                arg_id++;
            }
            
            /* valid arguments - perform matrix calculation */
            if (is_arg_valid) {
                apply_operation(cmd, mats_arr, scalar, mats_ids);
            }

            /* free allocated memory for temporary storage */
            free(args_temp);
        }
		else {  /* invalid input characters */
			printf(EOF_OR_ERROR_MSG);
			return STATUS_CODE_ERR;
		}
    }

    return STATUS_CODE_OK;
}
