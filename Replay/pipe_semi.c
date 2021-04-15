/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_semi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 10:27:30 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/15 10:48:06 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*check_semi_off(t_symbol *smbl, char *line, int i)
{
	if (count_back(line + (i - 1)))
		line[i] *= -1;
	else if (redirection(smbl))
	{
		ft_error(smbl, "1=>syntax error near unexpected token `;'");
		off_flags(smbl);
	}
	else
	{
		if (smbl->semi == ON)
		{
			ft_error(smbl, "2=>syntax error near unexpected token `;'");
			smbl->semi = OFF;
		}
		else if (smbl->pipe == ON)
		{
			ft_error(smbl, "3=>syntax error near unexpected token `;'");
			off_flags(smbl);
		}
		else
			smbl->semi = ON;
	}
	return (line);
}

char	*check_semicolone(t_symbol *smbl, char *line, int i)
{
	if (smbl->d_quote == OFF && smbl->s_quote == OFF)
		line = check_semi_off(smbl, line, i);
	else
	{
		if (smbl->d_quote == ON || smbl->s_quote == ON)
			line[i] *= -1;
		else
		{
			if (smbl->semi == OFF)
				smbl->semi = ON;
			else
				ft_error(smbl, "3=>syntax error near unexpected token `;'");
		}
	}
	return (line);
}

char	*check_pipe_off(t_symbol *smbl, char *line, int i)
{
	if (count_back(line + (i - 1)))
		line[i] *= -1;
	else if (redirection(smbl))
	{
		ft_error(smbl, "1=>syntax error near unexpected token `|'");
		off_flags(smbl);
	}
	else
	{
		if (smbl->pipe == ON)
		{
			ft_error(smbl, "2=>syntax error near unexpected token `|'");
			smbl->pipe = OFF;
		}
		else if (smbl->semi == ON)
		{
			ft_error(smbl, "3=>syntax error near unexpected token `|'");
			off_flags(smbl);
		}
		else
			smbl->pipe = ON;
	}
	return (line);
}

char	*check_pipe(t_symbol *smbl, char *line, int i)
{
	if (smbl->d_quote == OFF && smbl->s_quote == OFF)
		check_pipe_off(smbl, line, i);
	else
	{
		if (smbl->d_quote == ON || smbl->s_quote == ON)
			line[i] *= -1;
		else
		{
			if (smbl->pipe == OFF)
				smbl->pipe = ON;
			else
				ft_error(smbl, "4=>syntax error near unexpected token `|'");
		}
	}
	return (line);
}

int	check_flags(t_symbol *smbl)
{
	int	sum;

	sum = smbl->d_great + smbl->less + smbl->great + smbl->semi + smbl->pipe;
	return (sum);
}
