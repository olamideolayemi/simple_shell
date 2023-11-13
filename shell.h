#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <termios.h>

#define WRITE_BUFFER_SIZE 1024
#define READ_BUFFER_SIZE 1024
#define DELIM " \t\r\n\a"
#define TOKEN_BUFFER 210
#define BUFFER_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/**
 * struct liststr - singly linked list
 * @num: number field
 * @str: string
 * @next: next node points
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 *
 * @arg: a string generated from getline containing arguements
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	int argc;
	char *arg;
	char **argv;
	char **environ;
	int status;
	int env_changed;
	int readfd;
	int histcount;
	int err_num;
	unsigned int line_count;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char cmd_buf;
	int cmd_buf_type;
} info_t;

/**
 * struct builtin - string related function
 * @type: command flag
 * @func: the  function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, \
	0, 0, 0, 0, NULL, NULL, NULL}

/* Points to an array of pointers to strings called the environment */
extern char **environ;

/* str_operators_1 prototypes */
int str_len(char *str);
char *str_st_w(const char *hay, const char *ndl);
char *str_concat(char *dst, char *src);
int str_cmp(char *str1, char *str2);
void _puts(char *str);

/* str_operators_2 prototypes */
int _putchar(char c);
char *_strcpy(char *dst, char *src);
char *dup_str(const char *str);

/* builtin_1.c prototypes */
int _chdir(info_t *info);
int _shellexit(info_t *info);
int _showhelp(info_t *info);
int _showhistory(info_t *info);
int unset_alias(info_t *info, char *str);

/* builtin_2.c prototypes */
int set_alias_cmd(info_t *info, char *str);
int print_alias_cmd(list_t *node);
int _manalias(info_t *info);

/* pr_errors_1.c prototypes */
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
void _eputs(char *str);
int _eputchar(char c);
int _erratoi(char *s);

/* list_1.c prototypes */
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *h);
int del_node_ind(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);



#endif
