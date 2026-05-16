/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:32:59 by sjoung            #+#    #+#             */
/*   Updated: 2026/05/16 21:51:08 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*copy;

	len = ft_strlen(s) + 1;
	i = 0;
	copy = (char *)malloc(len);
	if (copy)
	{
		while (*(s + i))
		{
			*(copy + i) = *(s + i);
			i++;
		}
		*(copy + i) = '\0';
	}
	return (copy);
}
