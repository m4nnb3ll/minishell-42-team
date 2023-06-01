/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:38:01 by oakerkao          #+#    #+#             */
/*   Updated: 2023/06/01 11:50:29 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipe(t_node *tree, t_context *ctx)
{
	int			p[2];
	t_context	lctx;
	t_context	rctx;
	int		i;

	i = 0;
	g_minishell.in_pipe = 1;
	lctx = *ctx;
	rctx = *ctx;
	if (pipe(p) == -1)
		return (0);
	// left_child 
	lctx.fd[1] = p[1];
	add_list(&(lctx.fd_close), new_list(p[0]));
	add_list(&(lctx.fd_close), new_list(p[1]));
	i += exec_node(tree->left, &lctx);

	// right_child
	rctx.fd[0] = p[0];
	add_list(&(rctx.fd_close), new_list(p[0]));
	add_list(&(rctx.fd_close), new_list(p[1]));
	i += exec_node(tree->right, &rctx);

	//close_parent
	close(p[1]);
	close(p[0]);
	return (i);
}
