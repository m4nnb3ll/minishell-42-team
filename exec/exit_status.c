/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:49:57 by oakerkao          #+#    #+#             */
/*   Updated: 2023/06/01 16:56:59 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status(void)
{
	if (g_minishell.error_code == CMD_NOT_FOUND \
			|| g_minishell.error_code == NO_SUCH_FILE_PROGRAM)
		g_minishell.exit_s = 127;
	else if (g_minishell.error_code == NO_SUCH_FILE_FILE \
			|| g_minishell.error_code == PERMISSION_DENIED_FILE \
			|| g_minishell.error_code == AMBIGUOUS \
			|| g_minishell.error_code == CD_NO_SUCH_FILE \
			|| g_minishell.error_code == HOME_NOT_SET \
			|| g_minishell.error_code == TOO_MANY_ARGS)
		g_minishell.exit_s = 1;
	else if (g_minishell.error_code == PERMISSION_DENIED_PROGRAM)
		g_minishell.exit_s = 126;
	else if (g_minishell.error_code == NUMERIC_REQUI)
		g_minishell.exit_s = 255;
}
