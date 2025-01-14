/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 08:14:38 by gozon             #+#    #+#             */
/*   Updated: 2025/01/14 10:00:39 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	full_cleanup(t_command *command, t_data *data)
{
	rl_clear_history();
	clear_command_list(command);
	clear_data(data);
}

void	critical_exit(t_command *command, t_data *data)
{
	pid_t	pid;

	pid = command->pid;
	full_cleanup(command, data);
	if (pid == -1)
		exit(EXIT_FAILURE);
	exit(CRITICAL_ERROR);
}
