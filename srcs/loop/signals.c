/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:36:27 by gozon             #+#    #+#             */
/*   Updated: 2025/01/10 13:16:17 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_signal(int stdin_fd, char *input, int *init_readline)
{
	if (g_flag == 0)
	{
		*init_readline = 0;
		return (0);
	}
	if (g_flag == SIGQUIT)
	{
		g_flag = 0;
		return (0);
	}
	g_flag = 0;
	rl_on_new_line();
	if (!*init_readline)
	{
		rl_redisplay();
		ft_printf("^C\n");
	}
	*init_readline = 1;
	if (dup2(stdin_fd, 0) < 0)
		return (-1);
	free(input);
	return (1);
}
