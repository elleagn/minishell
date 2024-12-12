/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 08:40:46 by gozon             #+#    #+#             */
/*   Updated: 2024/12/10 09:55:08 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests.h>

int	main(void)
{
	t_command	*command;
	char		*av1[] = {"echo", "hello", NULL};
	char		*av2[] = {"echo", "-n", "hello", "\n", NULL};
	int			fd;
	t_redir		*redir;

	command = init_comand();
	if (!command)
		return (1);
	printf("---------- NO REDIRS ----------\n");
	command->av = av1;
	mini_echo(command, NULL);
	command->av = av2;
	mini_echo(command, NULL);
	printf("---------- REDIRS ---------");
	fd = open("out", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	command->redirs = init_redir();
	redir = command->redirs;
	if (!redir)
		return (1);
	redir->type = GREATER;
	redir->fd = fd;
	mini_echo(command, NULL);
	close(fd);
	fd = open("out", O_CREAT | O_APPEND | O_WRONLY, 0644);
	redir->next = init_redir();
	redir = redir->next;
	if (!redir)
		return (1);
	redir->type = GREATERGREATER;
	redir->fd = fd;
	redir->next = init_redir();
	redir = redir->next;
	if (!redir)
		return (1);
	redir->type = LESS;
	redir->fd = fd;
	mini_echo(command, NULL);
	close(fd);
	fd = open("out", O_CREAT | O_APPEND | O_WRONLY, 0644);
	redir->next = init_redir();
	redir = redir->next;
	if (!redir)
		return (1);
	redir->type = GREATERGREATER;
	redir->fd = fd;
	mini_echo(command, NULL);
	close(fd);
	free(command);
	return (0);
}
