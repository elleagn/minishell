/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:33:23 by gozon             #+#    #+#             */
/*   Updated: 2024/12/07 08:03:15 by gozon            ###   ########.fr       */
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

int	mini_echo(t_command *command, t_data *data)
{
	(void)	*data;
}

int	main(int ac, char **av)
{
	if (ac)
		return (mini_echo(&av[1], NULL));
}
