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

#define BUFFER_SIZE 1024
#define DELIM " \t\r\n\a"
#define TOKEN_BUFFER 210
#define BUFFER_FLUSH -1

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, \
	0, 0, 0, 0, NULL, NULL, NULL}

/* Points to an array of pointers to strings called the environment */
extern char **environ;

/* main */
int my_main(int my_argc, char **my_argv);

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
int change_dir(info_t *info);
int exit_shell(info_t *info);
int show_help(info_t *info);
int show_history(info_t *info);
int unset_alias(info_t *info, char *str);

/* builtin_2.c prototypes */
int set_alias_cmd(info_t *info, char *str);
int print_alias_cmd(list_t *node);
int manage_alias(info_t *info);

/* pr_errors_1.c prototypes */
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
void _eputs(char *str);
int _eputchar(char c);
int _erratoi(char *s);


typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

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
} info_t;


#endif
