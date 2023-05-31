/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:22:19 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/31 16:11:06 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// error codes
// 0 ->success->0
// 1 ->command not found->127
// 21 ->no such file or directory "file"->1
// 22 ->no such file or directory "program"->127
// 31 ->permission denied for file->1
// 32 ->permission denied for program->126
// 4 ->ambiguous redirection->1
// 5 ->not a valid identifier->1
// 5 ->quit program ctrl+\->131

// problems i foudn
// i don't find space inside of doublequotes

void	error_script()
{
	if (g_minishell.error_code == CMD_NOT_FOUND)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(g_minishell.error_file, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else if (g_minishell.error_code == NO_SUCH_FILE_FILE \
			|| g_minishell.error_code == NO_SUCH_FILE_PROGRAM)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(g_minishell.error_file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (g_minishell.error_code == PERMISSION_DENIED_FILE \
			|| g_minishell.error_code == PERMISSION_DENIED_PROGRAM)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(g_minishell.error_file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (g_minishell.error_code == AMBIGUOUS)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(g_minishell.error_file, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
	}
}

void	error_msg()
{
	error_script();
	exit_status();
}
