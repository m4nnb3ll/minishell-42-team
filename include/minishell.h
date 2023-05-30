/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelayad <abelayad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 01:32:13 by abelayad          #+#    #+#             */
/*   Updated: 2023/05/30 16:12:00 by oakerkao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft.h"
# include "tokenizing.h"
# include "parsing.h"

// ENV START
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// EXEC START
typedef struct s_wait
{
	int	i;
	int	status;
	int	child;
}	t_wait;
typedef struct s_exec
{
	char	*path;
	char	**args;
}	t_exec;

typedef struct s_fd
{
	int			content;
	struct s_fd	*next;
}	t_fd;

typedef struct s_context
{
	int		fd[2];
	t_fd	*fd_close;
	t_fd	*here_doc;
}	t_context;

typedef enum s_error
{
	SUCCESS,
	CMD_NOT_FOUND,
	NO_SUCH_FILE_FILE,
	NO_SUCH_FILE_PROGRAM,
	PERMISSION_DENIED_FILE,
	PERMISSION_DENIED_PROGRAM,
	AMBIGUOUS
} t_error;

// EXEC END
// EXPANDER START
typedef struct s_expand
{
	t_list	*lst;
	t_list	*tmp;
	char	quotes;
	int		i;
}	t_expand;
// EXPANDER END

typedef struct s_minishell
{
	t_token		*tokens;
	t_env		*env_list;
	char		*line;
	int			exit_s;
	int			index;
	bool		sigint;
	t_token		*curr_token;
	t_node		*ast;
	t_exec		exec;
	int			in_pipe;
	int			in_redirect;
	t_error	error_code;
	char	*error_file;
	t_parse_err	parse_err;
}					t_minishell;

extern t_minishell	g_minishell;

// EXECUTION START

// utils
char	*path_getter(char *cmd);
char	**cmd_getter(char *arg);
char	**twod_split(char *str, char c);
void	free_twod_array(char **arr);
void	free_ever();
t_fd	*new_list(int content);
void	add_list(t_fd **lst, t_fd *new);

//functions

void	exec();
int		exec_node(t_node *tree, t_context *ctx);
int		exec_pipe(t_node *tree, t_context *ctx);
int		exec_child(t_node *tree, t_context *ctx);
int		exec_and(t_node *tree, t_context *ctx);
int		exec_or(t_node *tree, t_context *ctx);
int		exec_left(t_node *node, int fd[2]);
int		exec_right(t_node *node, int fd[2]);
void	check_redirection(t_io_node *io, t_context *ctx);

// redirect
void	out(char *file, t_context *ctx);
void	in(char *file, t_context *ctx);
void	append(char *file, t_context *ctx);
void	here_doc(char *delimiter, t_context *ctx);

//builtins
int	is_builtin_child();
void	exec_builtin_parent();
int	is_builtin_parent();
void	exec_builtin_child();
int	is_builtin_child();

// error
void	error_msg();

// exit_code
void	exit_status();

// close_fds
void	close_parent_here_doc(t_context *ctx);
void	exec_dup(t_context *ctx);

// BUILTS-INS START
void	change_pwd(void);
void	change_old_pwd(void);
void	change_to_home(void);
void	cd(char *path);
int		check_flag(char *str);
void	echo(char **cmd);
void	env(void);
void	exit_error_msg(char *str);
int		check_exit_arg(char *str);
void	ft_exit(char **args);
void	export_error_msg(char *identifier);
void	export_list(void);
int		check_key(char *str);
void	export(char **argv);
void	pwd(void);
void	remove_node(char *key);
void	unset(char **args);
int		is_valid(char *str, int sign);
int		is_number(char *str);
int		check_long(unsigned long long res, int sign);

// ENV START
t_env	*new_node(char *key, char *value);
void	add_node(t_env *new);
void	print_env_list(void);
int		env_list_size(t_env *list);
char	*get_key(char *str);
char	*get_value(char *str);
void	get_env_list(char **enviro);
t_env	*get_node(char *key);
void	env_clear(t_env **env);

//exec read write
void	check_exec(char *file);
void	check_program(char *file);
void	check_read(char *file);
void	check_write(char *file);
void	ambiguous_checking(char *file);

// traverse_tree
void	traverse_tree(t_node *tree, t_context *ctx);
void	traverse_pipe(t_node *tree, t_context *ctx);
void	traverse_child(t_node *tree, t_context *ctx);
void	traverse_and(t_node *tree, t_context *ctx);
void	traverse_or(t_node *tree, t_context *ctx);

//expander
char	**expander(char *str);

// CLEARING
void	ft_free_exec(void);
void	ft_clear_minishell(void);

#endif
