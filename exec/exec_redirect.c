/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:32:29 by oakerkao          #+#    #+#             */
/*   Updated: 2023/06/01 18:00:53 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	out(char *file, t_context *ctx)
{
	int		fd;

		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{
			check_write(file);
			return ;
		}
		ctx->fd[1] = fd;
		return ;
}

void	in(char *file, t_context *ctx)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		check_read(file);
		return ;
	}
	ctx->fd[0] = fd;
}

void	append(char *file, t_context *ctx)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		check_write(file);
		return ;
	}
	ctx->fd[1] = fd;
}

int	quotes_check(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if ((str[0] == '\'' || str[0] == '"') && (str[len - 1] == '\'' || str[len - 1] == '"'))
		return (1);
	return (0);
}

void	here_doc(char *delimiter, t_context *ctx)
{
	char	*red;
	char	**expanded;
	int		p[2];
	int	quoted;

	quoted = quotes_check(delimiter);
	pipe(p);
	while (1)
	{
		red = readline("> ");
		if (!red)
		{
			printf("EOF\n");
			break ;
		}
		if (ft_strcmp(red, delimiter) == 0)
			break ;
		if (quoted == 0)
		{
			expanded = expander(red);
			while (*expanded)
			{
				ft_putstr_fd(*expanded, p[1]);	
				expanded++;
			}
			ft_putstr_fd("\n", p[1]);
		}
		else
		{
			ft_putstr_fd(red, p[1]);
			ft_putstr_fd("\n", p[1]);
		}
	}
	add_list(&(ctx->here_doc), new_list(p[0]));
	close(p[1]);
}
