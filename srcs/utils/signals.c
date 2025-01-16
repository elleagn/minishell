/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:11:01 by gozon             #+#    #+#             */
/*   Updated: 2025/01/10 13:50:37 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	signal_handler(int signum)
{
	(void)signum;
	g_flag = 1;
	// write(STDERR_FILENO, "\n", 1);
	// rl_replace_line("", 0);
	// rl_on_new_line();
	rl_done = 1;
}
