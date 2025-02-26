/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:17:05 by eschwart          #+#    #+#             */
/*   Updated: 2025/02/24 14:24:34 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_hex_fd(unsigned long long n, const char format, int fd)
{
	int		len;
	char	*base;

	if (fd < 0)
		return (0);
	len = 0;
	if (format == 'x')
		base = "0123456789abcdef";
	else if (format == 'X')
		base = "0123456789ABCDEF";
	if (n >= 16)
	{
		len += ft_hex_fd(n / 16, format, fd);
		len += ft_hex_fd(n % 16, format, fd);
	}
	else
		len += ft_putchar_fd(base[n % 16], fd);
	return (len);
}
