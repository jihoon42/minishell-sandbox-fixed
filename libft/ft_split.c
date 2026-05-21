/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoung <sjoung@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:37:07 by sjoung            #+#    #+#             */
/*   Updated: 2026/05/21 23:30:20 by sjoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
#include <stdlib.h>

static size_t	word_counter(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!s || !*s)
		return (0);
	while (*(s + i))
	{
		if (*(s + i) == c)
		{
			i++;
		}
		else
		{
			count++;
			while (*(s + i) && *(s + i) != c)
				i++;
		}
	}
	return (count);
}

static char	*make_word(char const *s, char c)
{
	size_t	size;
	size_t	i;
	char	*word;

	i = 0;
	size = 0;
	while (*(s + size) && *(s + size) != c)
		size++;
	word = (char *)malloc((size + 1) * sizeof(char));
	if (!word)
		return (0);
	while (*(s + i) && *(s + i) != c)
	{
		*(word + i) = *(s + i);
		i++;
	}
	*(word + i) = '\0';
	return (word);
}

static void	free_str(char **str, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(*(str + i));
		i++;
	}
	free(str);
}

char	**ft_split2(char **str, char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (*(s + i))
	{
		if (*(s + i) != c)
		{
			*(str + j) = make_word(s + i, c);
			if (!*(str + j))
			{
				free_str(str, j);
				return (0);
			}
			while (*(s + i) && *(s + i) != c)
				i++;
			j++;
		}
		else
			i++;
	}
	*(str + j) = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	size_t	size;
	char	**str;

	if (!s)
		return (0);
	size = word_counter(s, c);
	str = (char **)malloc(sizeof(char *) * (size + 1));
	if (!str)
		return (0);
	return (ft_split2(str, s, c));
}
/*
int	main(void)
{
	char **words = ft_split("The quick brown fox jumps", ' ');
	int word_count = 0;

	// NULL 포인터를 만날 때까지 단어 수 계산
	while (words[word_count] != NULL) {
	    word_count++;
	}

	printf("단어 수: %d\n", word_count);

	// 모든 단어 출력 및 메모리 해제
	for (int i = 0; words[i] != NULL; i++) {
	    printf("단어 %d: %s\n", i+1, words[i]);
	    free(words[i]);
	}
	free(words);

}
*/
