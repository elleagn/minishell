/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_export_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:31:31 by gozon             #+#    #+#             */
/*   Updated: 2024/12/11 10:10:38 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests.h>

int	main(void)
{
	t_command	*command;
	t_data		*data;
//	char		*av1[] = {"env", "hello", NULL};
	char		*av2[] = {"env", "PATATE=patate", NULL};
	char		*av3[] = {"env", "patate", NULL};
	char		*av4[] = {"env", "PLOUF=plouf", "PLOP=plop", NULL};
	char		*av5[] = {"env", NULL};
	char		*av6[] = {"unset", "PLOUF", "BLBL", NULL};
	char		*av7[] = {"env", "1BLBL", "BL$BL", NULL};
	char		*env[] = {"BLBL=bl", "BLBLBL=bl", NULL};
	// int			fd;
	// t_redir		*redir;

	command = init_comand();
	data = init_data();
	if (!command)
		return (1);
	printf("---------- NO ARGUMENTS NO ENV ----------\n");
	command->av = av5;
	mini_export(command, data);
	mini_unset(command, data);
	printf("---------- EXPORT NO ARGUMENTS ENV ----------\n");
	dup_env_array(env, data);
	mini_export(command, data);
	write(1, "---------- EXPORT -------\n", 27);
	command->av = av2;
	mini_export(command, data);
	command->av = av3;
	mini_export(command, data);
	command->av = av4;
	mini_export(command, data);
	command->av = av5;
	mini_env(command, data);
	write(1, "---------- UNSET -------\n", 26);
	command->av = av6;
	mini_unset(command, data);
	command->av = av5;
	mini_env(command, data);
	write(1, "---------- INVALID -------\n", 28);
	command->av = av7;
	mini_export(command, data);
	free(command);
	clear_data(data);
	return (0);
}
