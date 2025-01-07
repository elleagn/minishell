#include <minishell.h>


int	main(void)
{
	access("xshosh", F_OK);
	perror(NULL);
	return (0);
}
