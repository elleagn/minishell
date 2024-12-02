/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouillebobby <nouillebobby@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:33:23 by gozon             #+#    #+#             */
/*   Updated: 2024/11/29 11:10:03 by nouillebobb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	print_args(char **args, int n_opt)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (write(1, args[i], ft_strlen(args[i])) < 0)
			return (1);
		i++;
		if (args[i])
		{
			if (write(1, " ", 1) < 0)
				return (1);
		}
	}
	if (!n_opt)
	{
		if (write(1, "\n", 1) < 0)
			return (1);
	}
	return (0);
}

int	mini_echo(char **args, char **env)
{
	int	n_opt;

	(void)env;
	n_opt = 0;
	if (!args || !args[0])
		return (1);
	if (!ft_strncmp(args[1], "-n", 3))
		n_opt = 1;
	return (print_args(&args[1 + n_opt], n_opt));
}

int	main(int ac, char **av)
{
	if (ac)
		return (mini_echo(&av[1], NULL));
}
