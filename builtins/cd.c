/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 12:19:12 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/31 16:57:00 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwd(void)
{
	t_env	*current;
	char	*str;

	str = getcwd(NULL, 0);
	current = get_node("PWD");
	if (str && current)
		current->value = str;
}

void	change_old_pwd(void)
{
	t_env	*old;
	t_env	*current;

	old = get_node("OLDPWD");
	current = get_node("PWD");
	if (old && current)
		old->value = current->value;
}

void	change_to_home(void)
{
	t_env	*home;
	t_env	*current;

	change_old_pwd();
	home = get_node("HOME");
	current = get_node("PWD");
	if (home && current)
	{
		current->value = home->value;
		chdir(home->value);
		g_minishell.exit_s = 0;
	}
	else
	{
		g_minishell.error_code = HOME_NOT_SET;
		error_msg();
	}
}

void	cd(char *path)
{
	if (!path)
	{
		change_to_home();
		return ;
	}
	if (chdir(path) == -1)
	{
		g_minishell.error_code = CD_NO_SUCH_FILE;
		g_minishell.error_file = path;
		error_msg();
		return ;
	}
	change_old_pwd();
	change_pwd();
	g_minishell.exit_s = 0;
}
