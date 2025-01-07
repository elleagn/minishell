/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouillebobby <nouillebobby@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:48:41 by nouillebobb       #+#    #+#             */
/*   Updated: 2025/01/02 16:51:58 by nouillebobb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_command(t_command *cmd)
{
	t_redir	*redir;
	int	i;

	printf("\n=== Command Debug Info ===\n");
	while (cmd)
	{
		printf("Command at %p:\n", (void*)cmd);

		// Print arguments
		printf("Arguments:\n");
		i = 0;
		if (cmd->av)
		{
			while (cmd->av[i])
			{
				printf("  av[%d]: '%s'\n", i, cmd->av[i]);
				i++;
			}
		}
		else
			printf("  No arguments\n");

		// Print redirections
		printf("Redirections:\n");
		redir = cmd->redirs;
		if (!redir)
			printf("  No redirections\n");
		while (redir)
		{
			printf("  Type: ");
			switch(redir->type)
			{
				case LESS:			printf("LESS (<)\n"); break;
				case LESSLESS:		printf("LESSLESS (<<)\n"); break;
				case GREATER:		printf("GREATER (>)\n"); break;
				case GREATERGREATER: printf("GREATERGREATER (>>)\n"); break;
				default:			printf("UNKNOWN\n");
			}
			printf("    Filename: '%s'\n", redir->filename);
			printf("    Backup: '%s'\n", redir->backup);
			printf("    FD: %d\n", redir->fd);
			redir = redir->next;
		}

		// Print pipe information
		printf("Pipe: [%d, %d]\n", cmd->pipe[0], cmd->pipe[1]);

		// Print process info
		printf("PID: %d\n", cmd->pid);
		printf("Builtin: %s\n", cmd->builtin ? "Yes" : "No");
		printf("Exit code: %d\n", cmd->exit_code);

		// Print linking info
		printf("Previous command: %p\n", (void*)cmd->previous);
		printf("Next command: %p\n", (void*)cmd->next);

		printf("\n");
		cmd = cmd->next;
	}
	printf("=== End Debug Info ===\n\n");
}