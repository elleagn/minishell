/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshells.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:07:06 by gozon             #+#    #+#             */
/*   Updated: 2024/12/13 11:30:53 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute_command(t_command *command, t_data *data)
{
	int	in;
	int	out;

	if (command->builtin)
		exit(command->builtin(command, data));
	out = find_out_fd(command);
	in = find_in_fd(command);
	if (dup2(in, 0) || dup2(out, 1))
	{
		close_all_files(command);
		exit(EXIT_FAILURE);
	}
	close_all_files(command);
	execve(*(command->av), command->av, data->env);
	exit(EXIT_FAILURE);
}
