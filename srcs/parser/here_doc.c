/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:34:15 by gozon             #+#    #+#             */
/*   Updated: 2025/01/14 13:05:04 by gozon            ###   ########.fr       */
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

char	*get_stdin(t_data *data, char *limiter, int *init_readline)
{
	char	*input;

	input = readline("> ");
	if (!g_flag && !input)
		ft_printf("minishell: warning: here-document at line %i delimited by "
			"end-of-file (wanted `%s')\n", data->line, limiter);
	data->exit_code = check_signal(data, init_readline);
	return (input);
}

int	fill_file(int fd, char *limiter, t_data *data)
{
	char	*str;
	int		len;
	int		init_readline;
	int		line;

	len = ft_strlen(limiter) + 1;
	init_readline = 0;
	line = 0;
	str = get_stdin(data, limiter, &init_readline);
	while (str && ft_strncmp(str, limiter, len))
	{
		line += 1;
		if (write(fd, str, ft_strlen(str)) == -1 || write(fd, "\n", 1) == -1)
			return (-1);
		free(str);
		str = get_stdin(data, limiter, &init_readline);
	}
	free(str);
	data->line += line;
	return (data->exit_code);
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
