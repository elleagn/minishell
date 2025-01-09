/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:54:51 by lcluzan           #+#    #+#             */
/*   Updated: 2025/01/09 12:55:08 by lcluzan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*find_in_path(const char *cmd, t_data *data)
{
char	*full_path;
char	*temp;
int		i;

// If cmd contains '/' it's already a path, just duplicate it
if (ft_strchr(cmd, '/'))
	return (ft_strdup(cmd));

// Try each directory in PATH
i = 0;
while (data->path && data->path[i])
{
	// Build full path
	temp = ft_strjoin(data->path[i], "/");
	full_path = ft_strjoin(temp, cmd);
	free(temp);

	// Check if executable exists
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	i++;
}
return (NULL);
}
