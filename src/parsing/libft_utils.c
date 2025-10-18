/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devjorginho <devjorginho@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:55:07 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/10/18 13:59:51 by devjorginho      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)ptr;
	i = 0;
	while (i < num)
	{
		p[i] = (unsigned char)value;
		i++;
	}
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*c;
	size_t	total_size;

	total_size = nmemb * size;
	if (size && (total_size / size != nmemb))
		return (NULL);
	c = (void *)malloc(total_size);
	if (!c)
		return (NULL);
	ft_bzero(c, total_size);
	return (c);
}

char	*ft_strchr(const char *str, int c)
{
	size_t		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
		{
			return ((char *)&str[i]);
		}
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	i;

	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || s1[0] == '\0')
		return ((char *)ft_calloc(1, 1));
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && ft_strchr(set, s1[i]))
	{
		i++;
	}
	if (s1[i] == '\0')
		return ((char *)ft_calloc(1, 1));
	while (s1[j] && ft_strchr(set, s1[j]))
	{
		j--;
	}
	str = (char *)ft_calloc(j - i + 2, 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[i], j - i + 2);
	return (str);
}

char	*ft_strdup(const char *s)
{
	char	*dup;

	dup = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, ft_strlen(s));
	return (dup);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*iter;

	iter = (unsigned char *)dest;
	if (!dest && !src)
		return (NULL);
	while (n--)
		*iter++ = *(unsigned char *)src++;
	return (dest);
}
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	full_size;

	if (!s1 || !s2)
		return (NULL);
	full_size = ft_strlen(s1) + ft_strlen(s2);
	str = ft_calloc(full_size + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, full_size);
	ft_strlcat(str, s2, full_size + 1);
	return (str);
}
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	freebytes;
	size_t	i;

	i = 0;
	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	freebytes = size - dlen - 1;
	if (dlen >= size)
		return (size + slen);
	while (src[i] && i < freebytes)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + slen);
}