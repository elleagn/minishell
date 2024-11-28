/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcluzan <lcluzan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:58:12 by gozon             #+#    #+#             */
/*   Updated: 2024/11/28 13:19:19 by lcluzan          ###   ########.fr       */
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

int	delim_strlen(const char *str, char delimiter)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != delimiter)
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

char	*space_strdup(const char *str, char delimiter)
{
	char	*dup;
	int		i;
	int		len;

	if (!str)
		return (NULL);
	len = 0;
	while (str[len] && str[len] != delimiter)
		len++;
	dup = malloc((len + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}

int	main(int ac, char **av)
{
	(void)ac;
	printf("%s\n", space_strdup(av[1]));
	return (0);
}
