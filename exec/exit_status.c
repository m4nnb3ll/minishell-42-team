/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:49:57 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/30 15:57:54 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status(void)
{
	if (g_minishell.error_code == CMD_NOT_FOUND || g_minishell.error_code == NO_SUCH_FILE_PROGRAM)
		g_minishell.exit_s = 127;
	else if (g_minishell.error_code == NO_SUCH_FILE_FILE \
			|| g_minishell.error_code == PERMISSION_DENIED_FILE \
			|| g_minishell.error_code == AMBIGUOUS)
		g_minishell.exit_s = 1;
	else if (g_minishell.error_code == PERMISSION_DENIED_PROGRAM)
		g_minishell.exit_s = 126;
}
