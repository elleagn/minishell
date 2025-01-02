/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_signal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouillebobby <nouillebobby@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 08:03:40 by gozon             #+#    #+#             */
/*   Updated: 2025/01/02 16:52:25 by nouillebobb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests.h>

extern sig_atomic_t	g_flag;
sig_atomic_t g_flag;


void	signal_handler(int signum)
{
	g_flag = 1;
	(void)signum;
	close(0);
}

// int	main(void)
// {
// 	char	*line;
// 	int		std_in;

// 	g_flag = 0;
// 	std_in = dup(0);
// 	signal(SIGINT, signal_handler);
// 	line = readline("Prompt: ");
// 	readline("cndnnjcn");

// 	if (g_flag == 1)
// 	{
// 		rl_on_new_line();
// 		rl_redisplay();
// //		free(line);
// 		dup2(std_in, 0);
// 		ft_printf("^C\n");
// 	}
// //	free(line);
// 	return (0);
// }

int	main(void)
{
	char	*line;
	int		std_in;

	g_flag = 0;
	std_in = dup(0);
	signal(SIGINT, signal_handler);
	line = get_next_line(0);
	while (line)
	{
		free(line);
		line = get_next_line(0);
	}
}