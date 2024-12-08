/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 08:10:09 by gozon             #+#    #+#             */
/*   Updated: 2024/12/08 08:21:00 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_pwd(t_command *command, t_data *data)
{
	int		out_fd;
	char	buffer[4096];

	(void)data;
	out_fd = find_out_fd(command);
	if (out_fd < 0)
		return (1);
	ft_bzero(buffer, 4096);
	getcwd(buffer, 4096);
	if (write(out_fd, buffer, ft_strlen(buffer)) < 0)
		return (1);
	return (0);
}
