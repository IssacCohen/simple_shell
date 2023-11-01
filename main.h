#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* environ macro */
extern char **environ;

/**
 * struct sep_list_s - Single linked list node to store separators
 * @sep: The separator (;, |, or &)
 * @next: Pointer to the next node in the linked list
 * Description: This data structure represents a single
 *              linked list node
 *              used to store separators in the shell.
 */
typedef struct sep_list_s
{
	char sep;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_ls_s - Single linked list node to store
 *                    command lines
 * @line: The command line
 * @next: Pointer to the next node in the linked list
 *
 * Description: This data structure represents a single
 *              linked list node
 *              used to store command lines in the shell.
 */
typedef struct line_ls_s
{
	char *line;
	struct line_ls_s *next;
} line_list;

/**
 * struct shell_dt - Contains relevant data
 *                     for the shell during runtime
 * @argv: The argument vector (command-line arguments)
 * @input: The command line input provided by the user
 * @args: The tokens extracted from the command line
 * @stat: The last status of the shell
 * @counter: The line counter for tracking the number of lines processed
 * @_env: The environment variables
 * @pid: The process ID of the shell
 */
typedef struct shell_dt
{
	char **argv;
	char *input;
	char **args;
	int stat;
	int counter;
	char **_env;
	char *pid;
} shll_comm;

/**
 * struct rvar_ls - Single linked list node to store variables
 * @len_var: Length of the variable
 * @val: Value of the variable
 * @len_val: Length of the value
 * @next: Pointer to the next node in the linked list
 *
 * Description: This data structure represents a single linked
 *              list node
 *              used to store variables in the shell.
 */
typedef struct rvar_ls
{
	int len_var;
	char *val;
	int len_val;
	struct rvar_ls *next;
} r_var;

/**
 * struct builtin_s - Builtin command structure
 * @commname: The name of the command builtin (e.g., cd, exit, env)
 * @f: Pointer to the function associated with the command
 *
 * Description: This structure represents a builtin command in the shell.
 * It contains the name of the command and a pointer to the function that
 * implements the command functionality.
 */
typedef struct builtin_s
{
	char *commname;
	int (*f)(shll_comm *datash);
} builtin_t;

/* Linked lists functions */
sep_list *add_node_en(sep_list **head, char sep);
void free_sp_ls(sep_list **head);
line_list *add_ln_nd_end(line_list **head, char *line);
void free_line_ls(line_list **head);
r_var *add_var_nd(r_var **head, int lvar, char *var, int lval);
void free_value_ls(r_var **head);

/* String functions protytypes */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _strspn(char *s, char *accept);
char *_strdup(const char *s);
int _strlen(const char *s);
int compare_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);
void rev_string(char *s);
int get_length(int n);
char *conv_itoa(int n);
int _atoi(char *s);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);

/* Error handling functions prototypes */
int dupl_chars(char *input, int i);
int sep_oper_error(char *input, int i, char last);
int first_character(char *input, int *i);
void disp_syn_err(shll_comm *data_sh, char *input, int i, int bool);
int ch_syn_err(shll_comm *data_sh, char *input);
char *without_cmt(char *in);
void looping_shll(shll_comm *datash);

/* read_line function protytype */
char *read_line(int *i_eof);

/* Environmant variables function protytypes */
int verify_vars(r_var **h, char *in, char *st, shll_comm *data);
char *rpl_inp(r_var **head, char *input, char *new_input, int nlen);
char *get_environ(const char *name, char **_env);
int display_env(shll_comm *datash);
char *cp_info(char *name, char *value);
void set_env(char *name, char *value, shll_comm *datash);
int _setenv(shll_comm *datash);
int _unsetenv(shll_comm *datash);
int compare_envname(const char *name_env, const char *name_ptr);
void verify_env(r_var **h, char *in, shll_comm *data);
char *replace_str(char *input, shll_comm *datash);

/* Split functions protytypes */
char *swp_character(char *input, int bool);
void move_nxt(sep_list **list_s, line_list **list_l, shll_comm *datash);
int split_cmds(shll_comm *datash, char *input);
void add_nd(sep_list **head_s, line_list **head_l, char *input);
char **splt_ln(char *input);

/* get_line functions protytypes */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void get_ln(char **lineptr, size_t *n, char *buffer, size_t j);

/* Execute functions protytypes */
int execute_line(shll_comm *datash);
int check_error_command(char *dir, shll_comm *datash);
int command_exec(shll_comm *datash);
int check_cdir(char *path, int *i);
char *_whch(char *cmd, char **_env);
int is_exec(shll_comm *datash);

/* cd functions protypes */
void chandir_dor(shll_comm *datash);
void cd_to_dist(shll_comm *datash);
void changedir_prev(shll_comm *datash);
void changedir_to_home(shll_comm *datash);
int changedir_shell(shll_comm *datash);

/* main functions protytypes*/
void empty_data(shll_comm *datash);
void set_datashell(shll_comm *datash, char **av);

/* built-in functions prototypes */
int (*get_bltn(char *cmd))(shll_comm *datash);
int exit_sh(shll_comm *datash);

/* Error handling functions prototypes */
int get_err(shll_comm *datash, int eval);
void get_sigint(int sig);
char *error_get_alias(char **args);
char *err_environ(shll_comm *datash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *err_path126(shll_comm *datash);
char *conc_err_msg(shll_comm *, char *, char *, char *);
char *err_gcd(shll_comm *datash);
char *error_404(shll_comm *datash);
char *err_shell_exit(shll_comm *datash);

/* Help functions prototypes */
void disp_help_env(void);
void disp_help_setenv(void);
void display_unsetenv(void);
void disp_help_general(void);
void disp_help_exit(void);
void disp_help(void);
void disp_help_alias(void);
void disp_help_cd(void);
int get_hlp(shll_comm *datash);

#endif
