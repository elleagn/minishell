/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 08:15:36 by gozon             #+#    #+#             */
/*   Updated: 2024/12/16 09:42:17 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(void)
{
	char		*av[]={"./Makefile", "Makefile", NULL};
	char		*path[] = {"/usr/bin", NULL};
	t_command	*command;
	int			exit_code;
	t_data		*data;

	command = init_comand();
	data = init_data();
	command->av = av;
	av[0] = ft_strdup(av[0]);
	data->path = path;
	write(1, "---------- ONE COMMAND, NO REDIR, NO BUILTIN ----------\n", 56);
	executor(command, data);
	free(av[0]);
	free(command);
	exit_code = data->exit_code;
	free(data);
	return (exit_code);
}
