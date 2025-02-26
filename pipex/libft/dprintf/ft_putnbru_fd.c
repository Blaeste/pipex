/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbru_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:19:42 by eschwart          #+#    #+#             */
/*   Updated: 2025/02/24 14:24:25 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbru_fd(unsigned int n, int fd)
{
	long	nb;
	int		len;

	if (fd < 0)
		return (0);
	nb = n;
	len = 0;
	if (nb > 9)
	{
		len += ft_putnbru_fd(nb / 10, fd);
		len += ft_putnbru_fd(nb % 10, fd);
	}
	else
		len += ft_putchar_fd(nb + '0', fd);
	return (len);
}
