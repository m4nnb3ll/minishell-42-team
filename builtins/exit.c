/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:41:56 by oakerkao          #+#    #+#             */
/*   Updated: 2023/06/02 11:53:08 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit_arg(char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	if (is_number(str + i) == 0 || is_valid(str + i, sign) == 0)
	{
		g_minishell.error_code = NUMERIC_REQUI;
		g_minishell.error_file = str;
		error_msg();
		exit(g_minishell.exit_s);
	}
	return (ft_atoi(str));
}

void	ft_exit(char **args)
{
	int	exit_value;

	exit_value = g_minishell.exit_s;
	if (args[1])
	{
		if (check_exit_arg(args[1]) && !args[2])
		{
			exit_value = check_exit_arg(args[1]);
			g_minishell.exit_s = exit_value;
			exit(exit_value);
		}
		if (args[2])
		{
			g_minishell.error_code = TOO_MANY_ARGS;
			error_msg();
			return ;
		}
	}
	ft_clear_minishell();
	exit(exit_value);
}
