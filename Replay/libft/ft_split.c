/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 17:34:46 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/13 10:32:09 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_free(char **tab, int i)
{
	while (i)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

static int	count_word(char const *s, char c)
{
	int		i;
	int		pos;
	int		count;

	i = 0;
	pos = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			pos = 0;
		else
		{
			if (pos == 0)
				count++;
			pos = 1;
		}
		i++;
	}
	return (count);
}

static	char	*put_word(char const *s, char c, int *n)
{
	int		i;
	int		first;
	int		last;
	char	*word;

	i = *n;
	while (s[i] == c)
		i++;
	first = i;
	while (s[i] != c && s[i])
		i++;
	last = i;
	word = (char *)malloc(sizeof(char) * (last - first + 1));
	if (!word)
		return (NULL);
	*n = i;
	i = 0;
	while (first < last)
		word[i++] = s[first++];
	word[i] = '\0';
	return (word);
}

char	**ft_malloc(char const *s, char c)
{
	char	**rslt;

	if (!s)
		return (0);
	rslt = (char **)malloc(sizeof (char *) * (count_word(s, c) + 1));
	if (!rslt)
		return (NULL);
	return (rslt);
}

char	**ft_split(char const *s, char c)
{
	char	**rslt;
	int		i;
	int		count;
	int		count_w;

	rslt = ft_malloc(s, c);
	count = 0;
	i = 0;
	count_w = count_word(s, c);
	while (count < count_w)
	{
		rslt[count++] = put_word(s, c, &i);
		if (!rslt[count])
		{
			ft_free(rslt, i);
			return (NULL);
		}
	}
	rslt[count] = NULL;
	return (rslt);
}
