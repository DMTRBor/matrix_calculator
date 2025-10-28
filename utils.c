#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mymat.h"
#include "utils.h"


/* array of valid matrix names */
static char* mat_valid_names[] = {
    "MAT_A",
    "MAT_B",
    "MAT_C",
    "MAT_D",
    "MAT_E",
    "MAT_F"
};


/**
 * This function prints a user message with
 * detailed instructions how to use the main
 * program and what it does.
 */
void program_description() {
	printf("This is a matrix calculator program!\n");
    printf("You're given 6 matrices, A - F to perform different matrix operations.\n");
	printf("You can control the program and perform operations on matrices by sending the commands:\n");
	printf("1. read_mat MAT_A, <num1>, <num2>, ..., <numN> (N inputs)\n");
	printf("2. print_mat MAT_A\n");
	printf("3. add_mat MAT_A, MAT_B, MAT_C (result stored in MAT_C)\n");
	printf("4. sub_mat MAT_A, MAT_B, MAT_C (result stored in MAT_C)\n");
	printf("5. mul_mat MAT_A, MAT_B, MAT_C (result stored in MAT_C)\n");
	printf("6. mul_scalar MAT_A, <scalar>, MAT_B (result stored in MAT_B)\n");
	printf("7. trans_mat MAT_A, MAT_B (result stored in MAT_B)\n");
	printf("8. stop (exit the program)\n\n");
}


/**
 * This function receives a 2D matrix and
 * initializes it's cells with zeros,
 * avoiding possible garbage values, that
 * possibly could this matrix contain.
 */
void clear_mat(mat m) {
    int row = 0;
    int col = 0;

    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            m[row][col] = 0;
        }
    }
}


/**
 * This function receives a pointer to
 * 2D matrix and prints it's contents
 * (double values) in a matrix form, i.e
 * rows and columns.
 */
void print_mat(mat* m) {
    int row = 0;
    int col = 0;

    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            printf("%7.2f\t", (*m)[row][col]);
        }
        printf("\n");  /* next row in new line */
    }
    
    printf("\n");
}


/**
 * This function receives a pointer to an array of
 * characters that contains the command arguments and
 * another pointer to an array of characters that
 * conatains the delimiters, tokenizes the arguments
 * and counts them. The function also prints the command
 * entered by the user. The function returns the number of
 * command arguments (including the command).
 */
int count_input_args(char *args, const char *delimiters) {
    int args_count = 0;

    while (args != NULL) {  /* parse until no arguments left */
        args_count++;
		printf("%s ", args);  /* print command argument */
        args = strtok(NULL, delimiters);  /* next argument */
    }
	printf("\n");

    return args_count;
}


/**
 * This function receives a pointer to an array
 * of characters that represents a string with a
 * command name, checks which command of the 
 * available commands is it and reurns an enum
 * that corresponds to this command. If the received
 * string does not correspond to any known command,
 * error enum value returned.
 */
command get_command(char *cmd) {
    if (strcmp(cmd, "print_mat") == STR_EQUAL)
        return PRINT_MAT;
    if (strcmp(cmd, "read_mat") == STR_EQUAL)
        return READ_MAT;
    if (strcmp(cmd, "add_mat") == STR_EQUAL)
        return ADD_MAT;
    if (strcmp(cmd, "sub_mat") == STR_EQUAL)
        return SUB_MAT;
    if (strcmp(cmd, "mul_mat") == STR_EQUAL)
        return MUL_MAT;
    if (strcmp(cmd, "mul_scalar") == STR_EQUAL)
        return MUL_SCALAR;
    if (strcmp(cmd, "trans_mat") == STR_EQUAL)
        return TRANS_MAT;
    if (strcmp(cmd, "stop") == STR_EQUAL)
        return STOP;
    return ERROR;
}


/**
 * This function receives:
 * - command to apply
 * - argument to be applied with command
 * - pointer to pointer to 2D array of doubles
 * - pointers to 6 2D matrices, a to f
 * - pointer to double scalar variable
 * - matrix row number
 * - matrix column number
 * - an array of indices of matrices a to f (0-min, 5-max)
 * - matrix index number (6 matrices, 0-min, 5-max)
 * and applies the argument according to command definition:
 * - if the received argument is a matrix name, add it's
 *   corresponding index number to array of matrix indices.
 * - if the command is "mul_scalar", cast the argument to
 *   floating point number and assign the value to pointer
 *   to scalar variable.
 * - if the command is "read_mat", cast the argument to
 *   floating point number and assign the value to matrix
 *   cell at row and column received.
 * The function returns a code that represents if num inserted
 * in a matrix or not, i.e "read_mat" inserted a number in matrix.
 */
int apply_arg(command cmd,
              char *arg,
              mat** mats_arr,
              mat* a,
              mat* b,
              mat* c,
              mat* d,
              mat* e,
              mat* f,
              double *scalar,
              int row,
              int col,
              int mats_ids[],
              int mat_id) {

    int name_id;

    /* matrix name argument received */
    for (name_id = 0; name_id < (sizeof(mat_valid_names) / sizeof(char*)); name_id++) {
        if (strcmp(arg, mat_valid_names[name_id]) == STR_EQUAL){
            mats_ids[mat_id] = name_id;

            switch (name_id) {
                case MAT_A:
                    mats_arr[name_id] = a;
                    break;
                case MAT_B:
                    mats_arr[name_id] = b;
                    break;
                case MAT_C:
                    mats_arr[name_id] = c;
                    break;
                case MAT_D:
                    mats_arr[name_id] = d;
                    break;
                case MAT_E:
                    mats_arr[name_id] = e;
                    break;
                case MAT_F:
                    mats_arr[name_id] = f;
                    break;
            }

            return NO_NUM_INSERTED;
        }
    }
    
    /* scalar argument received */
    if (cmd == MUL_SCALAR) {
        *scalar = atof(arg);
        return NO_NUM_INSERTED;
    }

    /* insert element in matrix */
    if (cmd == READ_MAT) {
        /* only a single matrix used - first mat index stored at index 0 */
        (*mats_arr[mats_ids[0]])[row][col] = atof(arg);
        return NUM_INSERTED;
    }

	return NO_NUM_INSERTED;
}


/**
 * This function receives:
 * - command to apply
 * - pointer to pointer to 2D array of doubles
 * - a scalar double
 * - an array of indices of matrices a to f (0-min, 5-max)
 * and applies the matrix operation selected in command, using
 * the matrices in corresponding indices.
 */
void apply_operation(command cmd, mat** mats_arr, double scalar, int mats_ids[]) {
    switch (cmd) {
        case PRINT_MAT:
            print_mat(mats_arr[mats_ids[0]]);
            break;
        case ADD_MAT:
            add_mat(mats_arr[mats_ids[0]], mats_arr[mats_ids[1]], mats_arr[mats_ids[2]]);
            break;
        case SUB_MAT:
            sub_mat(mats_arr[mats_ids[0]], mats_arr[mats_ids[1]], mats_arr[mats_ids[2]]);
            break;
        case MUL_MAT:
            mul_mat(mats_arr[mats_ids[0]], mats_arr[mats_ids[1]], mats_arr[mats_ids[2]]);
            break;
        case MUL_SCALAR:
            mul_scalar(mats_arr[mats_ids[0]], scalar, mats_arr[mats_ids[2]]);
            break;
        case TRANS_MAT:
            trans_mat(mats_arr[mats_ids[0]], mats_arr[mats_ids[1]]);
            break;
		default:
			break;
    }
}


/**
 * This function receives a pointer to array of characters
 * and the length of this array of characters and checks if
 * it contains consecutive commas. The function returns a code
 * True if the string contains consecutive commas or code False
 * if it doesn't.
 */
int has_consecutive_commas(char *arg, int input_len) {
    int i = 0;

    while (i < input_len) {
        if (arg[i] == ',') {
            i++;
            /* skip whitespaces */
            while (isspace(arg[i])) {
                i++;
            }
            /* consecutive commas found  */
            if (arg[i] == ',') {
                return TRUE;
            }
        }
        else {
            i++;  /* go to next character */
        }
    }

    return FALSE;  /* no consecutive commas */
}


/**
 * This function receives a pointer to array of characters
 * that represents user input arguments that may conatain extraneous
 * characters and the length of the input arguments string, checks if
 * this is a consecutive comma or not and prints an appropriate
 * message - consecutive comma message or extraneous text message.
 */
void print_extra_args_reason(char *arg, int input_len) {
    if (has_consecutive_commas(arg, input_len)) {
        printf(CONSECUTIVE_COMMAS_MSG);
    }
    else
        printf(EXTRA_ARG_MSG);
}


/**
 * This function receives:
 * - command selected
 * - pointer to characters array with arguments received
 * - received arguments amount, counted previously
 * - total user's input length
 * and checks if the amount of arguments received in user input
 * is correct. If the amount of arguments for the received command
 * is correct, i.e there are no extra arguments or missing arguments,
 * True code returned. Otherwise, an appropriate message printed and
 * False code returned.
 */
int is_args_count_valid(command cmd, char *arg, int args_count, int input_len) {
    switch (cmd) {
        case PRINT_MAT:
            if (args_count < PRINT_MAT_ARGS) {
                printf(MISSING_ARG_MSG);
                return FALSE;
            }
            else if (args_count > PRINT_MAT_ARGS) {
                print_extra_args_reason(arg, input_len);
                return FALSE;
            }
            break;
        case READ_MAT:
            if (args_count < MIN_READ_MAT_ARGS) {
                printf(MISSING_ARG_MSG);
                return FALSE;
            }
            /* ignore extraneous args - at least 1 required */
            break;
        case ADD_MAT:
            if (args_count < ADD_MAT_ARGS) {
                printf(MISSING_ARG_MSG);
                return FALSE;
            }
            else if (args_count > ADD_MAT_ARGS) {
                print_extra_args_reason(arg, input_len);
                return FALSE;
            }
            break;
        case SUB_MAT:
            if (args_count < SUB_MAT_ARGS) {
                printf(MISSING_ARG_MSG);
                return FALSE;
            }
            else if (args_count > SUB_MAT_ARGS) {
                print_extra_args_reason(arg, input_len);
                return FALSE;
            }
            break;
        case MUL_MAT:
            if (args_count < MUL_MAT_ARGS) {
                printf(MISSING_ARG_MSG);
                return FALSE;
            }
            else if (args_count > MUL_MAT_ARGS) {
                print_extra_args_reason(arg, input_len);
                return FALSE;
            }
            break;
        case MUL_SCALAR:
            if (args_count < MUL_SCALAR_ARGS) {
                printf(MISSING_ARG_MSG);
                return FALSE;
            }
            else if (args_count > MUL_SCALAR_ARGS) {
                print_extra_args_reason(arg, input_len);
                return FALSE;
            }
            break;
        case TRANS_MAT:
            if (args_count < TRANS_MAT_ARGS) {
                printf(MISSING_ARG_MSG);
                return FALSE;
            }
            else if (args_count > TRANS_MAT_ARGS) {
                print_extra_args_reason(arg, input_len);
                return FALSE;
            }
            break;
        case STOP:
            if (args_count > STOP_ARGS) {
                print_extra_args_reason(arg, input_len);
                return FALSE;
            }
            break;
		default:
			return TRUE;
    }

    return TRUE;
}


/**
 * This function receives a pointer to an array of
 * characters that represents a command argument, and
 * checks if the array of characters is a string
 * representation of floating point number. If it's a
 * floating point number, True code returned, otherwise,
 * False code returned.
 */
int is_float(char *arg) {
    /* pointer to end of the string */
    char *end;

    /* skip leading whitespace */
    while (isspace((unsigned char)*arg))
        arg++;
    /* empty or only whitespace */
    if (*arg == NULL_TERMINATOR)
        return FALSE;

    /* try to parse the number */
    strtod(arg, &end);

    /* skip trailing whitespace */
    while (isspace((unsigned char)*end))
        end++;

    /* If the whole string was consumed, it's float */
    if (*end == NULL_TERMINATOR)
        return TRUE;
    
    /* non-float representation string */
    return FALSE;
}


/**
 * This function receives:
 * - a pointer to array of characters that represents a command argument
 * - argument index (in sequence of arguments)
 * - number of arguments
 * and checks if commas missing or illegal commas appear after argument
 * at specific place. If the cases mentioned not appear, False code
 * returned. Otherwise, True code returned.
 */
int missing_or_extra_commas(char *arg, int arg_id, int args_cnt) {
    if (arg[strlen(arg) - 1] == ',') {
        if (arg_id == (args_cnt - 2)) {  /* last argument - no comma required */
            printf(EXTRA_ARG_MSG);
            return TRUE;
        }
        arg[strlen(arg) - 1] = NULL_TERMINATOR;  /* valid comma */
    }
    else {
        if (arg_id != (args_cnt - 2)) {  /* not last argument - error */
            printf(MISSING_COMMA_MSG);
            return TRUE;
        }
    }
    return FALSE;
}


/**
 * This function receives:
 * - command selected
 * - pointer to characters array with arguments received
 * - argument index (in sequence of arguments)
 * - number of arguments
 * and checks, according to requirements, if the argument
 * received from user input is valid. If yes, a True code
 * returned. Otherwise, a False code returned.
 * This validation perforemed after arguments counting and
 * comparison.
 */
int validate_arg(command cmd, char *arg, int arg_id, int args_cnt) {
    /* filter args overflow while calling read_mat */
    /* no need to filter by command, as args counting comparison done before */
    if (arg_id > MAX_READ_MAT_ARGS)
        return FALSE;

    switch (cmd) {
        case PRINT_MAT:
        case ADD_MAT:
        case SUB_MAT:
        case MUL_MAT:
        case TRANS_MAT:
            return is_mat_name_valid(arg, arg_id, args_cnt);
        case READ_MAT:
            if (arg_id == 0) {
                return is_mat_name_valid(arg, arg_id, args_cnt);
            }
            else {
                if (missing_or_extra_commas(arg, arg_id, args_cnt)) {
                    return FALSE;
                }
             
                if (!is_float(arg)) {
                    printf(NOT_NUMBER_MSG);
                    return FALSE;
                }
                return TRUE;
            }
        case MUL_SCALAR:
            if (arg_id == 0 || arg_id == 2) {
                return is_mat_name_valid(arg, arg_id, args_cnt);
            }
            else {
                if (missing_or_extra_commas(arg, arg_id, args_cnt)) {
                    return FALSE;
                }

                if (!is_float(arg)) {
                    printf(NOT_SCALAR_MSG);
                    return FALSE;
                }
                return TRUE;
            }
		default:
			return TRUE;
    }

    return TRUE;
}


/**
 * This function receives:
 * - pointer to characters array with argument
 * - argument index (in sequence of arguments)
 * - number of arguments
 * and checks if the matrix name is valid. If yes,
 * True code returned, otherwise, False code returned.
 */
int is_mat_name_valid(char *arg, int arg_id, int args_cnt) {
    int name_id;

    /* commas should appear after matrix name except last argument */
    if (missing_or_extra_commas(arg, arg_id, args_cnt)) {
        return FALSE;
    }

    /* check for all matrix legal names */
    for (name_id = 0; name_id < (sizeof(mat_valid_names) / sizeof(char*)); name_id++) {
        if (strcmp(arg, mat_valid_names[name_id]) == STR_EQUAL){  /* valid matrix name */
            return TRUE;
        }
    }

    /* matrix name is invalid*/
    printf(INVALID_MAT_MSG);
    return FALSE;
}
