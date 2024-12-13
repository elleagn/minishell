/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:11:26 by lcluzan           #+#    #+#             */
/*   Updated: 2024/12/13 15:13:54 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	open_append_outfile(t_command *command)
{
	command->output_fd = open(command->redirs->filename, O_WRONLY
			| O_CREAT | O_APPEND, 0644);
	if (command->output_fd == -1)
	{
		perror("minishell");
		exit(1);
	}
}

void	parse_append(t_data *data, t_shell *shell)
{
	t_command	*command;

	command = shell->commands;
	while (command)
	{
		if (command->is_builtin == 0)
		{
			if (command->redirs && command->redirs->type == GREATERGREATER)
				open_append_outfile(command);
		}
		command = command->next;
	}
}
