/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoung <sjoung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:53:01 by sjoung            #+#    #+#             */
/*   Updated: 2025/04/16 12:17:13 by sjoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*ptr;
	size_t	len;

	if (size != 0 && num > (size_t)-1 / size)
	{
		return (0);
	}
	len = num * size;
	ptr = (void *)malloc(len);
	if (!ptr)
	{
		return (0);
	}
	ft_bzero(ptr, len);
	return (ptr);
}
