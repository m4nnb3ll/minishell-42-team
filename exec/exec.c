/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:07:56 by oakerkao          #+#    #+#             */
/*   Updated: 2023/06/01 13:16:35 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(void)
{
	// t_node		*tree;
	// t_node		*tmp;
	t_context	ctx;
	int	child;
	int	i;
	int	status;

	g_minishell.exec.path = NULL;
	g_minishell.exec.args = NULL;
	g_minishell.index = 0;
	g_minishell.in_pipe = 0;
	ctx.fd[0] = 0;
	ctx.fd[1] = 1;
	ctx.fd_close = NULL;
	ctx.here_doc = NULL;
	status = -1;
	i = 0;
	traverse_tree(g_minishell.ast, &ctx);
	child = exec_node(g_minishell.ast, &ctx);
	while (i < child - 1)
	{
		wait(&status);
		i++;
	}
	waitpid(g_minishell.last_pid, &status, 0);	
	if (WIFEXITED(status))
		g_minishell.exit_s = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_minishell.exit_s = 128 + WTERMSIG(status);
	close_parent_here_doc(&ctx);
	ft_clear_ast(&g_minishell.ast);
}

int	exec_node(t_node *tree, t_context *ctx)
{
	if (!tree)
		return (0);
	if (tree->type == N_PIPE)
		return (exec_pipe(tree, ctx));
	else if (tree->type == N_CMD)
		return (exec_child(tree, ctx));
	else if (tree->type == N_AND)
		return (exec_and(tree, ctx));
	else if (tree->type == N_OR)
		return (exec_or(tree, ctx));
	else
		printf("exec_error\n");
	return (0);
}

int	exec_and(t_node *tree, t_context *ctx)
{
	int	i;

	i = 0;
	i += exec_node(tree->left, ctx);
	if (g_minishell.exit_s == 0)
		i += exec_node(tree->right, ctx);
	return (i);
}

int	exec_or(t_node *tree, t_context *ctx)
{
	int	i;

	i = 0;
	i += exec_node(tree->left, ctx);
	if (g_minishell.exit_s != 0)
		i += exec_node(tree->right, ctx);
	return (i);
}
