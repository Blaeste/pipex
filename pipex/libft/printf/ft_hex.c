/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:19:09 by eschwart          #+#    #+#             */
/*   Updated: 2025/01/28 11:21:32 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_hex(unsigned long long n, const char format)
{
	int		len;
	char	*base;

	len = 0;
	if (format == 'x')
		base = "0123456789abcdef";
	else if (format == 'X')
		base = "0123456789ABCDEF";
	if (n >= 16)
	{
		len += ft_hex(n / 16, format);
		len += ft_hex(n % 16, format);
	}
	else
		len += ft_putchar(base[n % 16]);
	return (len);
}
