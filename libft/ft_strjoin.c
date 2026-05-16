/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:29:52 by sjoung            #+#    #+#             */
/*   Updated: 2026/05/16 21:51:16 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size1;
	size_t	size2;
	char	*join;

	if (!s1 || !s2)
	{
		return (0);
	}
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	join = malloc(sizeof(char) * (size1 + size2 + 1));
	if (!join)
		return (0);
	ft_memcpy(join, s1, size1);
	ft_memcpy(join + size1, s2, size2 + 1);
	return (join);
}
