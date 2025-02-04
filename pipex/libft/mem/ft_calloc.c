/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:38:59 by eschwart          #+#    #+#             */
/*   Updated: 2025/01/28 12:42:52 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;

	if (nmemb != 0 && size > __SIZE_MAX__ / nmemb)
		return (NULL);
	str = (char *)malloc(nmemb * size);
	if (str == NULL)
		return (NULL);
	ft_memset(str, 0, nmemb * size);
	return ((void *)str);
}
