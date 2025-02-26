/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:17:49 by eschwart          #+#    #+#             */
/*   Updated: 2025/02/24 14:18:59 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putptr_fd(void *ptr, int fd)
{
	int					len;
	unsigned long long	adresse;

	len = 0;
	if (ptr == NULL)
		return (ft_putstr_fd("(nil)", fd));
	adresse = (unsigned long long)ptr;
	len += ft_putstr_fd("0x", fd);
	len += ft_hex_fd(adresse, 'x', fd);
	return (len);
}
