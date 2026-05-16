/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:49:47 by sjoung            #+#    #+#             */
/*   Updated: 2026/05/16 21:50:33 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*((unsigned char *)s1 + i) > *((unsigned char *)s2 + i))
			return (1);
		else if (*((unsigned char *)s1 + i) < *((unsigned char *)s2 + i))
			return (-1);
		i++;
	}
	return (0);
}
