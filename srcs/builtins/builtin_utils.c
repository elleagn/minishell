/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 07:32:20 by gozon             #+#    #+#             */
/*   Updated: 2024/12/09 12:44:44 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	find_env_var(char *name, char **env, int strict)
{
	int	i;
	int	len;

	i = 0;
	if (strict == 1)
		len = ft_strlen(name);
	else
	{
		while (name[len] && name[len] != '=')
			len++;
	}
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*strjoin_three(char const *s1, char const *s2, char const *s3)
{
	char	*res;
	int		len1;
	int		len2;
	int		len3;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	res = malloc((len1 + len2 + len3 + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s1, len1 + 1);
	ft_strlcat(res, s2, len1 + len2 + 1);
	ft_strlcat(res, s3, len1 + len2 + len3 + 1);
	return (res);
}

int	find_out_fd(t_command *command)
{
	t_redir	*redirs;
	int		out_fd;

	if (!command)
		return (-1);
	redirs = command->redirs;
	out_fd = command->pipe[1];
	while (redirs)
	{
		if (redirs->type == GREATER || redirs->type == GREATERGREATER)
			out_fd = redirs->fd;
		redirs = redirs->next;
	}
	return (out_fd);
}

// int	main(int ac, char **av, char **envp)
// {
// 	char	name[]="LANGUAGE";
// 	char	name1[]="USER";
// 	char	name2[]="SHLVL";
// 	char	name3[]="HOME";
// 	char	name4[]="BLBL";
// 	char	name5[]="BLBL=";
// 	char	name6[]="HOME=";

// 	(void)ac;
// 	(void)av;
// 	ft_printf("%s: %i\n", name, find_env_var(name, envp));
// 	ft_printf("%s: %i\n", name1, find_env_var(name1, envp));
// 	ft_printf("%s: %i\n", name2, find_env_var(name2, envp));
// 	ft_printf("%s: %i\n", name3, find_env_var(name3, envp));
// 	ft_printf("%s: %i\n", name4, find_env_var(name4, envp));
// 	ft_printf("%s: %i\n", name5, find_env_var(name5, envp));
// 	ft_printf("%s: %i\n", name6, find_env_var(name6, envp));
// 	return (0);
// }
