/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lookup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:48:15 by gozon             #+#    #+#             */
/*   Updated: 2024/12/12 13:03:18 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	replace_string(char **str1, char *str2)
{
	free(*str1);
	*str1 = str2;
}

int	is_directory(char *file)
{
	int	fd;

	fd = open(file, O_DIRECTORY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	find_bin(char **cmd, char **path)
{
	char	*bin;
	int		i;

	if (ft_strnstr(*cmd, "/", ft_strlen(*cmd)))
	{
		if (access(*cmd, X_OK))
			return (perror(*cmd), 127);
		if (is_directory(*cmd))
			return (ft_printf("%s: is a directory\n"), 126);
		return (0);
	}
	i = 0;
	while (path[i])
	{
		bin = strjoin_three(path[i], "/", *cmd);
		if (!bin)
			return (perror("malloc"), -1);
		if (!access(bin, X_OK))
			return (replace_string(cmd, bin), 0);
		free(bin);
		i++;
	}
	ft_printf("%s: command not found\n", *cmd);
	return (127);
}

int	command_lookup(t_command *command,t_data *data)
{
	int	exit_code;

	while ()
}
