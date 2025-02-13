/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:53:28 by eschwart          #+#    #+#             */
/*   Updated: 2025/01/28 12:43:23 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_formats(va_list args, const char format)
{
	int	print_l;

	print_l = 0;
	if (format == 'd' || format == 'i')
		print_l = ft_putnbr(va_arg(args, int));
	else if (format == 'c')
		print_l = ft_putchar(va_arg(args, int));
	else if (format == 's')
		print_l = ft_putstr(va_arg(args, char *));
	else if (format == 'x')
		print_l = ft_hex(va_arg(args, unsigned int), format);
	else if (format == 'X')
		print_l = ft_hex(va_arg(args, unsigned int), format);
	else if (format == 'p')
		print_l = ft_putptr(va_arg(args, void *));
	else if (format == 'u')
		print_l = ft_putnbru(va_arg(args, unsigned int));
	else if (format == '%')
		return (ft_putchar('%'));
	return (print_l);
}

int	ft_printf(const char *src, ...)
{
	size_t	i;
	va_list	args;
	int		print_l;

	i = 0;
	print_l = 0;
	va_start(args, src);
	if (!src)
		return (va_end(args), -1);
	while (src[i])
	{
		if (src[i] == '%')
		{
			if (src[i + 1] == '\0')
				return (-1);
			print_l += ft_formats(args, src[++i]);
		}
		else
			print_l += ft_putchar(src[i]);
		i++;
	}
	va_end(args);
	return (print_l);
}
