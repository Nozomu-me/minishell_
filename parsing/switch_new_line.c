/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_new_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:37:04 by abdel-ke          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/04/23 11:27:10 by amouassi         ###   ########.fr       */
=======
/*   Updated: 2021/04/23 11:28:24 by abdel-ke         ###   ########.fr       */
>>>>>>> b85221a3644e4c127c945039e58d0a6a58227a75
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*inverse_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] < 0)
			line[i] *= -1;
		i++;
	}
	return (line);
}

char	*dollar_d_quote(t_mini *mini, char *line, int i, int j)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(line, j + 1, ft_strlen(line + j + 1));
	line[j - 1] = 0;
	tmp2 = ft_strjoin(line, tmp);
	free (tmp);
	free(line);
	line = tmp2;
	return (line);
}

char	*delete_quote_off(t_mini *mini, char *line, int *i, int *j)
{
	if (line[*j - 1] == '$')
		line = dollar_d_quote(mini, line, *i, *j);
	if (line[*j] == '\\')
	{
		mini->cp ++;
		line[(*i)++] = line[++(*j)];
	}
	else
	{
		if (line[*j] == '"' && mini->cp % 2 == 0)
			mini->smbl->d_quote = ON;
		else if (line[*j] == '\'' && mini->cp % 2 == 0)
			mini->smbl->s_quote = ON;
		else
			line[(*i)++] = line[*j];
	}
	return (line);
}

char	*delete_quote_on(t_mini *mini, char *line, int *i, int *j)
{
	if (mini->smbl->d_quote == ON)
	{
		if (line[*j] == '"')
			mini->smbl->d_quote = OFF;
		else if (line[*j] == '\\' && (line[(*j) + 1] == '\\'
				|| line[(*j) + 1] == '`'))
			line[(*i)++] = line[++(*j)];
		else if (line[*j] == '\\' && line[(*j) + 1] < 0 && line[(*j) + 1]
			!= '\'' * -1)
			line[(*i)++] = line[++(*j)];
		else
			line[(*i)++] = line[*j];
	}
	else if (mini->smbl->s_quote == ON)
	{
		while (line[*j] != '\'')
			line[(*i)++] = line[(*j)++];
		mini->smbl->s_quote = OFF;
	}
	return (line);
}

char	*reverse_cmd(t_mini *mini, char *line, int i, int j)
{
	mini->cp = 0;
	while (line[++j])
	{
		if (mini->smbl->d_quote == OFF && mini->smbl->s_quote == OFF)
			line = delete_quote_off(mini, line, &i, &j);
		else
			line = delete_quote_on(mini, line, &i, &j);
		if (line[j] != '\\')
		{
			mini->cp = 0;
		}
	}
	line[i] = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] < 0)
			line[i] *= -1;
		i++;
	}
	return (inverse_line(line));
}
