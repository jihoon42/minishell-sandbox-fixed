/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:46:32 by sjoung            #+#    #+#             */
/*   Updated: 2025/04/12 15:37:27 by sjoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

void	*ft_bzero(void *s, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t len);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t num, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t len);

#endif
