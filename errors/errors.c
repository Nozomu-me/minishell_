/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 19:36:50 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/13 19:37:29 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    error_pwd(char  *str, int err)
{
	ft_putstr(str);
	strerror(err);
}

void    error_cd(char *path, int err)
{
	ft_putstr("minishell: cd: ");
	ft_putstr(path); 
	ft_putstr(": ");
	ft_putstr(strerror(err));
	ft_putstr("\n");
}

void	error_export(char *str)
{
	ft_putstr("export: '");
	ft_putstr(str);
	ft_putstr("': not a valid identifier\n");
}