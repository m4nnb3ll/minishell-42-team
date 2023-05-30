/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:11:56 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/30 16:00:54 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*buff;

	buff = NULL;
	buff = getcwd(buff, 0);
	if (buff)
		printf("%s\n", buff);
	else
	{
		printf("error\n");
		g_minishell.exit_s = 1;
	}
	g_minishell.exit_s = 0;
}
