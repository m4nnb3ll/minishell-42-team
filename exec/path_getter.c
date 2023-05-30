/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_getter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:13:45 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/30 15:53:20 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_cmd(char *cmd, char *path)
{
	int		i;
	char	**splited_path;
	char	*result;
	char	*to_free;

	i = 0;
	splited_path = ft_split(path, ':');
	while (splited_path && splited_path[i])
	{
		to_free = ft_strjoin(splited_path[i], "/");
		result = ft_strjoin(to_free, cmd);
		free(to_free);
		check_exec(result);
		if (g_minishell.error_code == SUCCESS)
		{
			free_twod_array(splited_path);
			return (result);
		}
		free(result);
		i++;
	}
	error_msg();
	free_twod_array(splited_path);
	return (0);
}

char	*check_path(char *cmd, char *env)
{
	char	*result;

	g_minishell.error_file = cmd;
	if (ft_strncmp(cmd, "./", 2) == 0)
	{
		check_program(cmd);
		if (g_minishell.error_code == SUCCESS)
			return (cmd);
		g_minishell.error_file = cmd;
		error_msg();
		return (0);
	}
	check_program(cmd);
	if (g_minishell.error_code == SUCCESS)
		return (ft_strdup(cmd));
	else if (g_minishell.error_code == PERMISSION_DENIED_PROGRAM)
	{
		error_msg();
		return (0);
	}
	result = check_cmd(cmd, env);
	return (result);
}

// you check on the path before you check the existence
char	*path_getter(char *cmd)
{
	char	*path;
	t_env	*tmp;
	int		exist;

	if (!cmd)
		return (NULL);
	tmp = get_node("PATH");
	path = check_path(cmd, tmp->value);
	return (path);
}
