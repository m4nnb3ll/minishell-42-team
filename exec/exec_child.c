/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:13:52 by oakerkao          #+#    #+#             */
/*   Updated: 2023/06/01 18:00:17 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_content(t_context *ctx)
{
	int		i;
	t_fd	*close_pipe;

	close_pipe = ctx->here_doc;
	i = 0;
	while (1)
	{
		if (i == g_minishell.index)
			break ;
		close_pipe = close_pipe->next;
		i++;
	}
	ctx->fd[0] = close_pipe->content;
	g_minishell.index++;
}

void check_redirection(t_io_node *io, t_context *ctx)
{
	char	**expanded;

	while (io)
	{
		g_minishell.in_redirect = 1;
		g_minishell.error_file = io->value;
		expanded = expander(io->value);
		if (!expanded[0] || expanded[1])
		{
			g_minishell.error_code = AMBIGUOUS;	
			error_msg();
			return ;
		}
		if (io->type == IO_OUT)
			out(expanded[0], ctx);
		else if (io->type == IO_IN)
			in(expanded[0], ctx);
		else if (io->type == IO_APPEND)
			append(expanded[0], ctx);
		else if (io->type == IO_HEREDOC)
			here_doc_content(ctx);
		if (g_minishell.error_code != 0)
		{
			error_msg();
			free_twod_array(expanded);
			return ;
		}
		io = io->next;
		free_twod_array(expanded);
	}
}

int	exec_child(t_node *tree, t_context *ctx)
{
	int	pid;

	g_minishell.error_code = SUCCESS;
	g_minishell.exec.args = expander(tree->args);
	check_redirection(tree->io_list, ctx);
	if (g_minishell.error_code == SUCCESS)
	{
		if (is_builtin_parent() && g_minishell.in_pipe == 0)
		{
			exec_builtin_parent();
			return (0);
		}
		else if (g_minishell.exec.args && g_minishell.exec.args[0] && is_builtin_child() == 0)
		{
			g_minishell.exec.path = path_getter(g_minishell.exec.args[0]);
		}
	}
	g_minishell.last_pid = fork();
	if (g_minishell.last_pid == 0)
	{
		exec_dup(ctx);
		if (g_minishell.error_code != 0)
			free_ever();
		else if (is_builtin_child())
		{
			exec_builtin_child();
			free_ever();
		}	
		else if (g_minishell.exec.path)
		{	
			if (execve(g_minishell.exec.path, g_minishell.exec.args, NULL) == -1)
			{
				if (g_minishell.exit_s == 0)
					g_minishell.exit_s = 1;
				free_ever();
			}
		}
		free_ever();
	}
	/*if (g_minishell.exec.args)
		free_twod_array(g_minishell.exec.args);
	if (g_minishell.exec.path)
		free(g_minishell.exec.path);*/
	return (1);
}
