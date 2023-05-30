/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 10:34:40 by oakerkao          #+#    #+#             */
/*   Updated: 2023/05/30 15:51:18 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_clear(t_env **env)
{
	t_env	*lst;

	lst = *env;
	if (*env == NULL)
		return ;
	while (lst)
	{
		lst = (*env)->next;
		if ((*env)->key)
			free((*env)->key);
		if ((*env)->value)
			free((*env)->value);
		free(*env);
		*env = lst;
	}
}
