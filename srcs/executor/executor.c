/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:18:17 by gozon             #+#    #+#             */
/*   Updated: 2024/12/12 14:33:15 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_subshells(t_command *command_list, t_data *data)
{
}

int	executor(t_command *cmdlist, t_data *data)
{
	int	error_code;

	if (setup_files(cmdlist))
		return (-1);
	if (command_lookup(cmdlist, data))
		return (-1);
	if (!cmdlist->next && cmdlist->builtin)
		error_code = handle_builtin(cmdlist, data);
	else
		error_code = handle_subshells(cmdlist, data);
	if (error_code == -1)
		return (-1);
	else
		data->exit_code = 
}
