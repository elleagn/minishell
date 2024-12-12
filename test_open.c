#include <minishell.h>


int main(void)
{
	printf("%i\n", open("srcs", O_WRONLY));
	perror(NULL);
	return (0);
}
