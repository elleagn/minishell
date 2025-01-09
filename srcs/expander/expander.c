/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:51:40 by lcluzan           #+#    #+#             */
/*   Updated: 2025/01/09 16:07:02 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	expander(t_command *cmd, t_data *data)
{
	t_command	*current;
	char		*resolved_path;

	current = cmd;
	while (current)
	{
		if (!expand_redirections(current->redirs, data))
			return (0);
		if (!expand_command_args(current, data))
			return (0);
		if (current->builtin < 0 && current->av && current->av[0])
		{
			resolved_path = find_in_path(current->av[0], data);
			if (!resolved_path)
			{
				ft_printf("minishell: %s: command not found\n", current->av[0]);
				return (0);
			}
			free(current->av[0]);
			current->av[0] = resolved_path;
		}
		current = current->next;
	}
	print_command(cmd);
	return (1);
}