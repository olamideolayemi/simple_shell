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
#define TOKEN_BUFFER 510
#define BUFFER_FLUSH -1

/**
 * struct terminal_settings - structure to store settings in the termina
 * @original: original settings
 */
typedef struct terminal_settings
{
	struct termios original;
} terminal_set;


/* Points to an array of pointers to strings called the environment */
extern char **environ;

/*****************************************************/

/* str_operators_1 prototypes */
int _strlen(char *str);
char *starts_with(const char *hay, const char *ndl);
char *_strconcat(char *dst, char *src);
int _strcmp(char *str1, char *str2);
void _puts(char *str);

/* str_operators_2 prototypes */
int _putchar(char c);
char *_strcpy(char *dst, char *src);
char *_dupstr(const char *str);

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

/* shell_loop_1.c prototypes */
int shell_loop(char **argv);
char *shell_getline(void);
int shell_execute(char **av1, char **av2, char **argv, char *cli_arg,
		int line_count);
char **parse_line1(char *cli_arg);
int fork_cmd(char **av, char **argv, int line_count);



#endif
