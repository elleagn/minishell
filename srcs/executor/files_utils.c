/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:07:10 by gozon             #+#    #+#             */
/*   Updated: 2025/01/07 16:39:37 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	open_file(t_type type, char *filename)
{
	int	fd;

	if (type == LESS || type == LESSLESS)
			fd = open(filename, O_RDONLY);
	if (type == GREATER)
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (type == GREATERGREATER)
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_printf("minishell: ");
		perror(filename);
	}
	if (type == LESSLESS)
		unlink(filename);
	return (fd);
}
