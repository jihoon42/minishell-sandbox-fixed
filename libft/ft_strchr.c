/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoung <sjoung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:06:33 by sjoung            #+#    #+#             */
/*   Updated: 2026/05/21 23:30:20 by sjoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include<stdio.h>
//#include <string.h>

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c && *s)
		++s;
	if (*s)
	{
		return ((char *)s);
	}
	else if ((char)c == '\0' && 0 == (char)c)
	{
		return ((char *)s);
	}
	else
	{
		return (0);
	}
}
/*
int	main(void)
{
	char	*s = "Bonjour";

	printf("%p\n", strchr(s, 'b'));
	printf("my func-> %p\n\n", ft_strchr(s, 'b'));

	printf("%p\n", strchr(s, 'j'));
	printf("%p\n\n", ft_strchr(s, 'j'));
	
	printf("%p\n", strchr(s, 's'));
	printf("%p\n\n", ft_strchr(s, 's'));
	
	printf("%p\n", strchr(s, '\0'));
	printf("%p\n\n", ft_strchr(s, '\0'));

	char	*s1 = "";
	printf("%p\n", strchr(s1, '\0'));
	printf("%p\n\n", ft_strchr(s1, '\0'));
}
*/
