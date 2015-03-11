/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh_built_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarmet <tcarmet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/09 21:31:59 by tcarmet           #+#    #+#             */
/*   Updated: 2015/03/09 21:32:02 by tcarmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	ft_print_env(t_all *all)
{
	t_env	*tmp;

	tmp = all->env;
	while (tmp != NULL)
	{
		ft_putstr(tmp->var);
		ft_putchar('=');
		ft_putendl(tmp->value);
		tmp = tmp->next;
	}
}

int		ft_setenv_check(char **str, t_all *all)
{
	t_env	*tmp;

	tmp = all->env;
	while (tmp != NULL)
	{
		if (ft_strequ(tmp->var, str[1]))
		{
			ft_strdel(&tmp->value);
			tmp->value = ft_strdup(str[2]);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_sh_setenv(char **str, t_all *all)
{
	t_env	*tmp;

	if (!str[1])
		ft_print_env(all);
	else if (str[3])
		ft_sh_error(ARG_ENV, "");
	else if (ft_setenv_check(str, all))
		;
	else if (!str[2])
	{
		tmp = env_fill(str[1], "");
		ft_sh_push(all, tmp);
	}
	else
	{
		tmp = env_fill(str[1], str[2]);
		ft_sh_push(all, tmp);
	}
}

int		ft_sh_unsetenv(char **str, t_all *all)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;

	i = 1;
	while (str[i])
	{
		prev = all->env;
		if (ft_strequ(prev->var, str[i]))
		{
			all->env = prev->next;
			free(prev);
		}
		tmp = prev->next;
		while (tmp != NULL)
		{
			if (ft_strequ(tmp->var, str[i]))
			{
				prev->next = tmp->next;
				free(tmp);
			}
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}