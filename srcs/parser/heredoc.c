 #include <minishell.h>

 //add structure to store heredoc
 t_heredoc *init_and_fill_heredoc(t_token *delimiter)
 {
	t_heredoc *heredoc;
	if (!delimiter) return (NULL);
	heredoc = init_heredoc();
	if (!heredoc) return (NULL);
	heredoc->delimiter = ft_strdup(delimiter->literal);
	if (!heredoc->delimiter)
	 return (perror("minishell"), clear_heredoc(heredoc), NULL);
	return (heredoc);
}
/* ** Add heredoc to the command
** If the command has no heredocs, add the heredoc to the command
** Else, add the heredoc to the last heredoc
*/
void add_heredoc(t_command *cmd, t_heredoc *heredoc)
{
	t_heredoc *current;
	if (!cmd->heredocs)
	{
		cmd->heredocs = heredoc;
		return ;
	}
	current = cmd->heredocs;
	while (current->next)
		current = current->next;
		current->next = heredoc;
}
/*
** Handle heredoc token
** If the next token is NULL, return 0
** Init and fill the heredoc structure with the next token
** If the heredoc is NULL, return 0
** Add the heredoc to the command
** Set the token to the next token
*/

int	handle_heredoc(t_command *current, t_token **token)
{
	t_heredoc	*heredoc;

	if (!(*token)->next)
		return (0);
	heredoc = init_and_fill_heredoc((*token)->next);
	if (!heredoc)
		return (0);
	add_heredoc(current, heredoc);
	*token = (*token)->next;
	return (1);
}
