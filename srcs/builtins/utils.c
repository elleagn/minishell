/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 07:32:20 by gozon             #+#    #+#             */
/*   Updated: 2024/12/09 08:31:17 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	find_env_var(char *name, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, ft_strlen(name))
			&& env[i][ft_strlen(name)] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	find_out_fd(t_command *command)
{
	t_redir	*redirs;
	int		out_fd;

	if (!command)
		return (-1);
	redirs = command->redirs;
	out_fd = command->pipe[1];
	while (redirs)
	{
		if (redirs->type == GREATER || redirs->type == GREATERGREATER)
			out_fd = redirs->fd;
		redirs = redirs->next;
	}
	return (out_fd);
}

// int	main(int ac, char **av, char **envp)
// {
// 	char	name[]="LANGUAGE";
// 	char	name1[]="USER";
// 	char	name2[]="SHLVL";
// 	char	name3[]="HOME";
// 	char	name4[]="BLBL";

// 	(void)ac;
// 	(void)av;
// 	ft_printf("%s: %i\n", name, find_env_var(name, envp));
// 	ft_printf("%s: %i\n", name1, find_env_var(name1, envp));
// 	ft_printf("%s: %i\n", name2, find_env_var(name2, envp));
// 	ft_printf("%s: %i\n", name3, find_env_var(name3, envp));
// 	ft_printf("%s: %i\n", name4, find_env_var(name4, envp));
// 	return (0);
// }
