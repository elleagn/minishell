/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 07:24:36 by gozon             #+#    #+#             */
/*   Updated: 2025/01/16 10:56:24 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

sig_atomic_t	g_flag;

int	prepare_path(t_data *data)
{
	int		path_index;
	char	**path;
	char	*path_var;

	path_index = find_env_var("PATH", data->env, 1);
	if (path_index >= 0)
	{
		path_var = data->env[path_index];
		path = ft_split(&path_var[5], ':');
		if (!path)
			return (perror("minishell"), 1);
		data->path = path;
	}
	return (0);
}

int	event(void)
{
	return (EXIT_SUCCESS);
}

void	prepare_signals(void)
{
	rl_event_hook = event;
	sigint_interactive();
	ignore_signal(SIGQUIT);
}

t_data	*prepare_shell(char **envp)
{
	t_data	*data;

	data = init_data();
	if (!data)
		return (NULL);
	if (!dup_env_array(envp, data))
		return (clear_data(data), NULL);
	if (prepare_path(data))
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
	prepare_signals();
	data = prepare_shell(envp);
	if (!data)
		return (1);
	mini_loop(data);
	exit_code = data->exit_code;
	clear_data(data);
	return (exit_code);
}
