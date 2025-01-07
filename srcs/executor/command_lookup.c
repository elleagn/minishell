/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lookup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:48:15 by gozon             #+#    #+#             */
/*   Updated: 2025/01/07 16:38:19 by gozon            ###   ########.fr       */
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

int	test_command(t_command *command, t_data *data)
{
	char	*bin;
	int		i;
	char	**cmd;
	char	**path;

	i = 0;
	path = data->path;
	cmd = command->av;
	while (path[i])
	{
		bin = strjoin_three(path[i], "/", *cmd);
		if (!bin)
			critical_exit(command, data);
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
	char	**cmd;

	cmd = command->av;
	if (!cmd)
		return (ft_printf("minishell:  : command not found\n"), 127);
	if (ft_strnstr(*cmd, "/", ft_strlen(*cmd)) || !data->path)
	{
		if (access(*cmd, F_OK))
			return (write(2, "minishell: ", 12), perror(*cmd), 127);
		if (access(*cmd, X_OK))
			return (write(2, "minishell: ", 12), perror(*cmd), 126);
		if (is_directory(*cmd))
			return (ft_printf("minishell: %s: is a directory\n"), 126);
		return (0);
	}
	return (test_command(command, data));
}

void	command_lookup(t_command *command, t_data *data)
{
	while (command)
	{
		if (!command->exit_code && command->builtin < 0)
			command->exit_code = find_bin(command, data);
		command = command->next;
	}
}
