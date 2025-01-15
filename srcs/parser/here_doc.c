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

char	*get_stdin(t_data *data, char *limiter)
{
	char	*input;

	g_global.in_heredoc = 1;
	input = readline("> ");
	g_global.in_heredoc = 0;
	if (!g_global.flag && !input)
		ft_printf("minishell: warning: here-document at line %i delimited by "
			"end-of-file (wanted `%s')\n", data->line, limiter);
	if (g_global.flag)
	{
		g_global.flag = 0;
		data->exit_code = 130;
		dup2(data->stdin_fd, 0); // je vous laisse sécuriser ça, moi je vais dormir wallah
	}
	return (input);
}

int fill_file(int fd, char *limiter, t_data *data)
{
    char *str;
    int len;
    int line;

    len = ft_strlen(limiter) + 1;
    line = 0;
    while (1)
    {
        str = get_stdin(data, limiter);
        if (!str)
            return (data->exit_code);
        if (!ft_strncmp(str, limiter, len))
            break;
        line += 1;
        if (write(fd, str, ft_strlen(str)) == -1 || write(fd, "\n", 1) == -1)
        {
            free(str);
            return (-1);
        }
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
