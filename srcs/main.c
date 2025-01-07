/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 07:24:36 by gozon             #+#    #+#             */
/*   Updated: 2025/01/07 15:15:25 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**path(t_data *data)
{
	int	path_index;

	
}

t_data	*prepare_shell(char **envp)
{
	t_data	*data;

	data = init_data();
	if (!data)
		return (NULL);
	if (!dup_env_array(envp, data))
		return (clear_data(data), NULL);
	if (!prepare_path(data))
		return (clear_data(data), NULL);
	return (data);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	int		exit_code;

	(void)av;
	if (ac > 1)
	{
		ft_printf("minishell doesn't accept any arguments");
		return (0);
	}
	data = prepare_shell(envp);
	if (!data)
		return (1);
	mini_loop(data);
	exit_code = data->exit_code;
	clear_data(data);
	return (exit_code);
}
