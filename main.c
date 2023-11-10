#include "shell.h"

/**
 * main - main entry
 * @argc: pointer to argument count
 * @argv: pointer to argument vector
 * Return: 0 (success)
 */
int main(int argc, char **argv)
{
	info_t _info[] = {INFO_INIT};
	int fd = 2;

	asm (
			"mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd)
			);

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argv[0]);
				_eputs(": 0: Cannot open ");
				_puts(argv[1]);
				_eputchar('\n');
				_putchar(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		_info->readfd = fd;
	}
	pop_env_list(_info);
	rd_hist(_info);
	hsh(_info, argv);
	return (EXIT_SUCCESS);
}
