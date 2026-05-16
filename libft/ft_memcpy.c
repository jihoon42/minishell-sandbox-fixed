/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:48:03 by sjoung            #+#    #+#             */
/*   Updated: 2025/04/12 19:53:47 by sjoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (0);
	while (i < len)
	{
		*((char *)dest + i) = *((char *)src + i);
		i++;
	}
	return (dest);
}
