/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 08:14:38 by gozon             #+#    #+#             */
/*   Updated: 2024/12/18 10:48:33 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	full_cleanup(t_command *command, t_data *data)
{
	clear_command_list(command);
	clear_data(data);
}

void	critical_exit(t_command *command, t_data *data)
{
	full_cleanup(command, data);
	if (command->pid == -1)
		exit(EXIT_FAILURE);
	exit(CRITICAL_ERROR);
}
