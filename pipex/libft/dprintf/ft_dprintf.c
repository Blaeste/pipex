/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:04:55 by eschwart          #+#    #+#             */
/*   Updated: 2025/02/24 14:25:03 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_formats(va_list args, const char format, int fd)
{
	int	print_l;

	print_l = 0;
	if (format == 'd' || format == 'i')
		print_l = ft_putnbr_fd(va_arg(args, int), fd);
	else if (format == 'c')
		print_l = ft_putchar_fd(va_arg(args, int), fd);
	else if (format == 's')
		print_l = ft_putstr_fd(va_arg(args, char *), fd);
	else if (format == 'x')
		print_l = ft_hex_fd(va_arg(args, unsigned int), format, fd);
	else if (format == 'X')
		print_l = ft_hex_fd(va_arg(args, unsigned int), format, fd);
	else if (format == 'p')
		print_l = ft_putptr_fd(va_arg(args, void *), fd);
	else if (format == 'u')
		print_l = ft_putnbru_fd(va_arg(args, unsigned int), fd);
	else if (format == '%')
		return (ft_putchar_fd('%', fd));
	return (print_l);
}

int	ft_dprintf(int fd, const char *src, ...)
{
	size_t	i;
	va_list	args;
	int		print_l;

	i = 0;
	print_l = 0;
	if (fd < 0)
		return (-1);
	va_start(args, src);
	if (!src)
		return (va_end(args), -1);
	while (src[i])
	{
		if (src[i] == '%')
		{
			if (src[i + 1] == '\0')
				return (-1);
			print_l += ft_formats(args, src[++i], fd);
		}
		else
			print_l += ft_putchar_fd(src[i], fd);
		i++;
	}
	va_end(args);
	return (print_l);
}
