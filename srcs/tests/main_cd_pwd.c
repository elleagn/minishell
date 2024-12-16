#include <tests.h>

int	main(void)
{
	t_command	*command;
	t_data		*data;
	char		*av1[] = {"env", "hello", NULL};
	char		*av2[] = {"env", NULL};
	char		*av3[] = {"cd", "xskmsx", "kxsksm", NULL};
	char		*av4[] = {"env", "Makefile", NULL};
	char		*av5[] = {"env", "srcs", NULL};
	char		*av6[] = {"env", "/home/gozon", NULL};

	command = init_command();
	data = init_data();
	if (!command)
		return (1);
	printf("---------- NO REDIRS ----------\n");
	command->av = av2;
	mini_cd(command, data);
	mini_pwd(command, NULL);
	command->av = av1;
	mini_cd(command, data);
	mini_pwd(command, NULL);
	command->av = av3;
	mini_cd(command, data);
	mini_pwd(command, NULL);
	command->av = av4;
	mini_cd(command, data);
//	printf("%s\n", data->env[0]);
	mini_pwd(command, NULL);
	command->av = av5;
	mini_cd(command, data);
	printf("%s\n", data->env[0]);
	mini_pwd(command, NULL);
	command->av = av6;
	mini_cd(command, data);
	printf("%s\n", data->env[0]);
	mini_pwd(command, NULL);
	return (0);
}
