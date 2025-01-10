/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 08:10:09 by gozon             #+#    #+#             */
/*   Updated: 2025/01/10 19:08:00 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_pwd(t_command *command, t_data *data)
{
	int		out_fd;
	char	buffer[4096];

	(void)data;
	if (command->av[1])
	{
		if (write(2, "minishell: pwd: too many arguments\n", 36) < 0)
			return (perror("minishell"), -1);
		return (1);
	}
	out_fd = find_out_fd(command);
	ft_bzero(buffer, 4096);
	if (!getcwd(buffer, 4096) || write(out_fd, buffer, ft_strlen(buffer)) < 0
		|| write(out_fd, "\n", 1) < 0)
		return (perror("minishell"), -1);
	return (0);
}

int	mini_cd(t_command *command, t_data *data)
{
	char	buf[4096];
	char	*pwd;

	if (!command->av[1])
		return (0);
	if (command->av[2])
	{
		if (write(2, "minishell: cd: too many arguments\n", 35) < 0)
			return (perror("minishell"), -1);
		return (1);
	}
	if (chdir(command->av[1]) < 0)
		return (perror("minishell: cd"), 1);
	ft_bzero(buf, 4096);
	if (!getcwd(buf, 4096))
		return (perror("minishell"), -1);
	pwd = strjoin_three("PWD", "=", buf);
	if (!pwd)
		return (-1);
	return (add_var(pwd, data));
}
