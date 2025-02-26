/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:46:32 by eschwart          #+#    #+#             */
/*   Updated: 2025/01/28 12:44:07 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_l;
	size_t	i;
	size_t	j;
	char	*joined;

	if (!s1 || !s2)
		return (0);
	total_l = ft_strlen(s1) + ft_strlen(s2);
	joined = (char *)malloc(sizeof(char) * (total_l + 1));
	if (!joined)
		return (0);
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		joined[i + j] = s2[j];
		j++;
	}
	joined[i + j] = '\0';
	return (joined);
}
