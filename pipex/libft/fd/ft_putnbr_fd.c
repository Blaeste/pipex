/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:21:14 by eschwart          #+#    #+#             */
/*   Updated: 2025/02/24 14:25:48 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	int		len;

	len = 0;
	if (fd < 0)
		return (0);
	nb = n;
	if (nb < 0)
	{
		len += ft_putchar_fd('-', fd);
		nb *= -1;
	}
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd);
	len += ft_putchar_fd(nb % 10 + '0', fd);
	return (len);
}
