/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:59:45 by gozon             #+#    #+#             */
/*   Updated: 2024/12/16 10:22:58 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests.h>

int	main(void)
{
	t_command	*command;
	t_data		*data;
	char		*av1[] = {"env", "hello", NULL};
	char		*av2[] = {"env", NULL};
	char		*env[] = {"BLBL=bl", "BLBL=bl", NULL};
	int			fd;
	t_redir		*redir;

	command = init_command();
	data = init_data();
	if (!command)
		return (1);
	printf("---------- NO REDIRS ----------\n");
	command->av = av1;
	mini_env(command, NULL);
	command->av = av2;
	mini_env(command, data);
	dup_env_array(env, data);
	command->av = av2;
	mini_env(command, data);
	printf("---------- REDIRS ---------");
	fd = open("out", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	command->redirs = init_redir();
	redir = command->redirs;
	if (!redir)
		return (1);
	redir->type = GREATER;
	redir->fd = fd;
	mini_env(command, data);
	close(fd);
	// fd = open("out", O_CREAT | O_APPEND | O_WRONLY, 0644);
	// redir->next = init_redir();
	// redir = redir->next;
	// if (!redir)
	// 	return (1);
	// redir->type = GREATERGREATER;
	// redir->fd = fd;
	// redir->next = init_redir();
	// redir = redir->next;
	// if (!redir)
	// 	return (1);
	// redir->type = LESS;
	// redir->fd = fd;
	// mini_echo(command, NULL);
	// close(fd);
	// fd = open("out", O_CREAT | O_APPEND | O_WRONLY, 0644);
	// redir->next = init_redir();
	// redir = redir->next;
	// if (!redir)
	// 	return (1);
	// redir->type = GREATERGREATER;
	// redir->fd = fd;
	// mini_echo(command, NULL);
	// close(fd);
	free(command);
	return (0);
}
