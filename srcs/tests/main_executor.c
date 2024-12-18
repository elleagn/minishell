/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 08:15:36 by gozon             #+#    #+#             */
/*   Updated: 2024/12/18 11:24:03 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**duplicate_tab(char **tab)
{
	int		size;
	char	**copy;
	int		i;

	size = 0;
	while (tab[size])
		size++;
	copy = ft_calloc(size + 1, sizeof(char *));
	i = 0;
	while (tab[i])
	{
		copy[i] = ft_strdup(tab[i]);
		i++;
	}
	return (copy);
}

int	main(void)
{
	char		*av2[]={"cd", "srcs", NULL};
	char		*av[]={"", NULL};
	char		*path[] = {"/usr/bin", NULL};
	t_command	*command;
	int			exit_code;
	t_data		*data;
//	t_redir		*redir;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	command = init_command();
	data = init_data();
	command->av = duplicate_tab(av);
	command->next = init_command();
	command->next->av = duplicate_tab(av2);
	command->next->previous = command;
//	redir = init_redir();
//	redir->type = GREATER;
//	redir->filename = ft_strdup("out");
//	command->next->redirs = redir;
	data->path = duplicate_tab(path);
	write(1, "---------- ONE COMMAND, NO REDIR, NO BUILTIN ----------\n", 56);
	executor(command, data);
	exit_code = data->exit_code;
	full_cleanup(command, data);
	return (exit_code);
}
