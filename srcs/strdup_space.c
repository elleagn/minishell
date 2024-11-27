/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozon <gozon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:58:12 by gozon             #+#    #+#             */
/*   Updated: 2024/11/26 15:09:44 by gozon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	space_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

char	*space_strdup(const char *str)
{
	char	*dup;
	int		i;
	int		len;

	if (!str)
		return (NULL);
	len = space_strlen(str);
	dup = malloc((len + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		dup[i] = str[i];
		i++;
	}
	return (dup);
}

int	main(int ac, char **av)
{
	(void)ac;
	printf("%s\n", space_strdup(av[1]));
	return (0);
}
