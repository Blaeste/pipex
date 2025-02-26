/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:09:07 by eschwart          #+#    #+#             */
/*   Updated: 2025/02/24 14:23:34 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	size_t	i;
	int		len;

	len = 0;
	if (!s || fd < 0)
		return (0);
	i = 0;
	while (s[i])
	{
		len += ft_putchar_fd(s[i], fd);
		i++;
	}
	return (len);
}
