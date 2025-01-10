/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:36:27 by gozon             #+#    #+#             */
/*   Updated: 2025/01/10 14:44:05 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_signal(t_data *data, int *init_readline)
{
	if (g_flag == 0)
	{
		*init_readline = 0;
		return (0);
	}
	g_flag = 0;
	data->exit_code = 130;
	rl_on_new_line();
	if (!*init_readline)
	{
		rl_redisplay();
		ft_printf("^C\n");
	}
	*init_readline = 1;
	if (dup2(data->stdin_fd, 0) < 0)
		return (-1);
	return (130);
}
