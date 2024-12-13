/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lookup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:48:15 by gozon             #+#    #+#             */
/*   Updated: 2024/12/13 13:29:42 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_directory(char *file)
{
	int	fd;

	fd = open(file, O_DIRECTORY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	check_builtin(char *cmd)
{
	char	*cmd;

	if (!ft_strncmp(cmd, "echo", 5))
		return (0);
	if (!ft_strncmp(cmd, "env", 4))
		return (1);
	if (!ft_strncmp(cmd, "export", 7))
		return (2);
	if (!ft_strncmp(cmd, "unset", 6))
		return (3);
	if (!ft_strncmp(cmd, "cd", 3))
		return (4);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (5);
	if (!ft_strncmp(cmd, "exit", 5))
		return (6);
	return (-1);
}

int	test_command(t_command *command, t_data *data)
{
	char	*bin;
	int		i;
	char	*cmd;
	char	**path;

	i = 0;
	path = data->path;
	cmd = command->av;
	command->builtin = check_builtin(cmd);
	if (command->builtin)
		return (0);
	while (path[i])
	{
		bin = strjoin_three(path[i], "/", *cmd);
		if (!bin)
			return (perror("minishell"), -1);
		if (!access(bin, X_OK))
			return (replace_string(cmd, bin), 0);
		free(bin);
		i++;
	}
	ft_printf("minishell: %s: command not found\n", *cmd);
	return (127);
}

int	find_bin(t_command *command, t_data *data)
{
	char	*bin;
	char	**cmd;
	char	**path;

	path = data->path;
	cmd = command->av;
	if (ft_strnstr(*cmd, "/", ft_strlen(*cmd)))
	{
		if (access(*cmd, X_OK))
			return (perror(*cmd), 126);
		if (is_directory(*cmd))
			return (ft_printf("%s: is a directory\n"), 126);
		return (0);
	}
	return (test_command(command, data));
}

int	command_lookup(t_command *command, t_data *data)
{
	int	exit_code;

	while (command)
	{
		if (!command->status)
		{
			exit_code = find_bin(command, data);
			if (exit_code == -1)
				return (-1);
			else
				command->status = exit_code;
		}
	}
	return (0);
}
