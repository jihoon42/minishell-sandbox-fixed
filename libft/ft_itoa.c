/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoung <sjoung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:08:13 by sjoung            #+#    #+#             */
/*   Updated: 2026/05/21 23:30:20 by sjoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	size_t	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*p;
	int		size;
	int		i;

	size = ft_len(n);
	p = malloc(sizeof(char) * (size + 1));
	if (p == 0)
		return (0);
	if (n == 0)
		*p = '0';
	else if (n < 0)
		*p = '-';
	i = size;
	while (n != 0)
	{
		if (n < 0)
			*(p + --i) = (~(n % 10) + 1) + 48;
		else
			*(p + --i) = (n % 10) + 48;
		n /= 10;
	}
	*(p + size) = '\0';
	return (p);
}
