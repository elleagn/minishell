/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:34:15 by gozon             #+#    #+#             */
/*   Updated: 2025/01/10 10:05:07 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*generate_file_name(int i)
{
	char	*filename;
	char	*number;

	number = ft_itoa(i);
	if (!number)
		return (NULL);
	filename = ft_strjoin(".heredoc_", number);
	if (!filename)
		return (NULL);
	while (!access(filename, F_OK))
	{
		i += 1;
		free(filename);
		free(number);
		number = ft_itoa(i);
		if (!number)
			return (NULL);
		filename = ft_strjoin(".heredoc_", number);
		if (!filename)
			return (free(number), NULL);
	}
	free(number);
	return (filename);
}

int	fill_file(int fd, char *limiter)
{
	char	*str;
	int		len;

	len = ft_strlen(limiter);
	str = get_next_line(STDIN_FILENO);
	while (ft_strncmp(str, limiter, len))
	{
		if (write(fd, str, ft_strlen(str)) == -1)
			return (-1);
		free(str);
		str = get_next_line(STDIN_FILENO);
	}
	free(str);
	return (0);
}

char	*here_doc(t_token *lim)
{
	char	*filename;
	int		fd;

	filename = generate_file_name(lim->position);
	if (!filename)
		return (NULL);
	fd = open(filename, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		return (free(filename), NULL);
	if (fill_file(fd, lim->literal))
	{
		close(fd);
		unlink(filename);
		return (free(filename), NULL);
	}
	close(fd);
	return (filename);
}
