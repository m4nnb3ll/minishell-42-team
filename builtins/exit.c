/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 10:41:56 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/30 16:00:41 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error_msg(char *str)
{
	char	*error_msg;

	error_msg = ft_strjoin("minishell: exit: ", str);
	error_msg = ft_strjoin(error_msg, ": numeric argument required\n");
	ft_putstr_fd(error_msg, 2);
}

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
		g_minishell.exit_s = 0;
		exit_error_msg(str);
		g_minishell.exit_s = 255;
		exit(g_minishell.exit_s);
	}
	return (ft_atoi(str));
}

void	ft_exit(char **args)
{
	int	exit_value;

	exit_value = 0;
	if (args[1])
	{
		if (args[2])
		{
			g_minishell.exit_s = 1;
			printf("minishell: exit: too many arguments\n");
			g_minishell.exit_s = 1;
			exit(g_minishell.exit_s);
		}
		exit_value = check_exit_arg(args[1]);
		g_minishell.exit_s = exit_value;
		exit(exit_value);
	}
	ft_clear_minishell();
	exit(exit_value);
}
