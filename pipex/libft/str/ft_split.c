/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:04:10 by eschwart          #+#    #+#             */
/*   Updated: 2025/01/28 12:43:51 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	*free_result(char **result, size_t j)
{
	while (j > 0)
	{
		j--;
		free(result[j]);
	}
	free (result);
	return (NULL);
}

static int	count_w(char const *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*malloc_w(char const *s, char c)
{
	size_t	i;
	char	*word;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s, i + 1);
	return (word);
}

static char	**ft_split2(char const *s, char c, char **result)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			result[j] = malloc_w(&s[i], c);
			if (!result[j])
				return (free_result(result, j), NULL);
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	result[j] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (count_w(s, c) + 1));
	if (!result)
		return (NULL);
	result = ft_split2(s, c, result);
	return (result);
}
