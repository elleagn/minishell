/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:59:37 by lcluzan           #+#    #+#             */
/*   Updated: 2025/01/09 12:59:38 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5))
		return (0);
	if (!ft_strncmp(cmd, "env", 4))
		return (1);
	if (!ft_strncmp(cmd, "export", 7))
		return (2);
	if (!ft_strncmp(cmd, "unset", 6))
		return (3);
	if (!ft_strncmp(cmd, "cd", 3))
		return (4);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (5);
	if (!ft_strncmp(cmd, "exit", 5))
		return (6);
	return (-1);
}

void	add_arg(t_command *cmd, char *arg)
{
	int		i;
	char	**new_av;

	i = 0;
	while (cmd->av && cmd->av[i])
		i++;
	new_av = malloc(sizeof(char *) * (i + 2));
	if (!new_av)
		return ;
	i = 0;
	while (cmd->av && cmd->av[i])
	{
		new_av[i] = cmd->av[i];
		i++;
	}
	new_av[i] = ft_strdup(arg);
	new_av[i + 1] = NULL;
	free(cmd->av);
	cmd->av = new_av;
	if (i == 0)
		cmd->builtin = check_builtin(new_av[0]);
}
