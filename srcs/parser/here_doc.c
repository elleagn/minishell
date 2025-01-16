/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:34:15 by gozon             #+#    #+#             */
/*   Updated: 2025/01/16 11:07:43 by gozon            ###   ########.fr       */
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

char	*get_stdin(t_data *data, char *limiter)
{
	char	*input;

	input = readline("> ");
	if (!g_flag && !input)
		ft_printf("minishell: warning: here-document at line %i delimited by "
			"end-of-file (wanted `%s')\n", data->line, limiter);
	if (g_flag)
	{
		g_flag = 0;
		data->exit_code = 130;
		if (dup2(data->stdin_fd, 0))
		{
			data->exit_code = -1;
			perror("minishell");
		}
		free(input);
		return (NULL);
	}
	return (input);
}

int	fill_file(int fd, char *limiter, t_data *data)
{
	char	*str;
	int		len;
	int		line;

	len = ft_strlen(limiter) + 1;
	line = 0;
	while (1)
	{
		str = get_stdin(data, limiter);
		if (!str)
		{
			data->line += line;
			return (data->exit_code);
		}
		line += 1;
		if (!ft_strncmp(str, limiter, len))
			break ;
		if (write(fd, str, ft_strlen(str)) == -1 || write(fd, "\n", 1) == -1)
			return (free(str), -1);
		free(str);
	}
	free(str);
	data->line += line;
	return (0);
}

char	*here_doc(t_token *lim, t_data *data)
{
	char	*filename;
	int		fd;

	(void)data;
	filename = generate_file_name(lim->position);
	if (!filename)
		return (NULL);
	fd = open(filename, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		return (free(filename), NULL);
	if (fill_file(fd, lim->literal, data))
	{
		close(fd);
		unlink(filename);
		return (free(filename), NULL);
	}
	close(fd);
	return (filename);
}
