/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 07:24:36 by gozon             #+#    #+#             */
/*   Updated: 2024/12/23 07:45:14 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_data	*prepare_shell(char **envp)
{
	t_data	*data;

	data = init_data();
	if (!data)
		return (NULL);
	if (!dup_env_array(envp, data))
		return (clear_data(data), NULL);
	return (data);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	(void)av;
	if (ac > 1)
	{
		ft_printf("minshell doesn't accept any arguments");
		return (0);
	}
	data = prepare_shell(envp);
	if (!data)
		return (1);
	mini_loop(data);
	clear_data(data);
	return (data->exit_code);
}
