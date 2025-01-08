/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:34:15 by gozon             #+#    #+#             */
/*   Updated: 2025/01/08 17:02:40 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>




char	*here_doc(t_token *lim)
{
	char	*filename;

	filename = generate_file_name(lim);
	if (!filename)
		return (NULL);
	if (get_stdin(filename))
		return (free(filename), NULL);
	return (filename);
}
