#ifndef __INPUT__H__
#define __INPUT__H__


#define MAX_INPUT_LEN 200
#define INPUT_LINE_SYM "> "

#define STR_EQUAL 0
#define NULL_TERMINATOR '\0'
#define CMD_DELIMITERS " \t"

/* messages */
#define EOF_OR_ERROR_MSG "EOF/Input error! Abort...\n"
#define MISSING_ARG_MSG "Missing argument\n"
#define CONSECUTIVE_COMMAS_MSG "Multiple consecutive commas\n"
#define EXTRA_ARG_MSG "Extraneous text after end of command\n"
#define ERROR_CMD_MSG "Undefined command name\n"
#define INVALID_MAT_MSG "Undefined matrix name\n"
#define NOT_SCALAR_MSG "Argument is not a scalar\n"
#define NOT_NUMBER_MSG "Argument is not a real number\n"
#define ILLEGAL_COMMA_MSG "Illegal comma\n"
#define MISSING_COMMA_MSG "Missing comma\n"

/* expected number of arguments */
#define PRINT_MAT_ARGS 2
#define MAX_READ_MAT_ARGS (SIZE*SIZE + 1)
#define MIN_READ_MAT_ARGS 3
#define ADD_MAT_ARGS 4
#define SUB_MAT_ARGS 4
#define MUL_MAT_ARGS 4
#define MUL_SCALAR_ARGS 4
#define TRANS_MAT_ARGS 3
#define STOP_ARGS 1

#define INVALID_ARR_INDEX -1


enum {
    NO_NUM_INSERTED,
    NUM_INSERTED
};

enum {
    FALSE,
    TRUE
};

enum {
    STATUS_CODE_OK,
    STATUS_CODE_ERR
};

typedef enum {
    PRINT_MAT,
    READ_MAT,
    ADD_MAT,
    SUB_MAT,
    MUL_MAT,
    MUL_SCALAR,
    TRANS_MAT,
    STOP,
    ERROR
} command;

enum {
    MAT_A,
    MAT_B,
    MAT_C,
    MAT_D,
    MAT_E,
    MAT_F
};


void program_description(void);
command get_command(char *);
void apply_operation(command, mat**, double, int []);
int count_input_args(char *, const char *);
int is_args_count_valid(command, char *, int, int);
int validate_arg(command, char *, int, int);
void print_extra_args_reason(char *, int);
int missing_or_extra_commas(char *, int, int);
int is_mat_name_valid(char *, int, int);
int is_float(char *);
int has_consecutive_commas(char *, int);
int apply_arg(command, char *, mat**, mat*, mat*, mat*, mat*, mat*, mat*, double *, int, int, int [], int);

void clear_mat(mat);
void print_mat(mat*);

#endif
