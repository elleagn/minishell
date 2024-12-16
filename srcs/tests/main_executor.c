/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 08:15:36 by gozon             #+#    #+#             */
/*   Updated: 2024/12/16 14:08:29 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(void)
{
	char		*av[]={"echo", "Makefile", NULL};
//	char		*av2[]={"cat", "-e", "Makefile", NULL};
	char		*path[] = {"/usr/bin", NULL};
	t_command	*command;
	int			exit_code;
	t_data		*data;

	command = init_command();
	data = init_data();
	command->av = av;
	av[0] = ft_strdup(av[0]);
//	av2[0] = ft_strdup(av2[0]);
	command->next = init_command();
	//command->next->av = av2;
	data->path = path;
	write(1, "---------- ONE COMMAND, NO REDIR, NO BUILTIN ----------\n", 56);
	executor(command, data);
//	free(av2[0]);
	free(av[0]);
	free(command->next);
	free(command);
	exit_code = data->exit_code;
	free(data);
	return (exit_code);
}
