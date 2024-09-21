/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:56:40 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/30 17:23:26 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/dir.h>

extern int		g_exit_status;

enum e_type
{
	WORD,
	W_SPACE = ' ',
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HERE_DOC,
	PIPE,
	ENV,
	SQUOTE,
	DQUOTE,
	EX_STATUS,
};

enum e_state
{
	GENERAL,
	IN_SQUOTE,
	IN_DQUOTE,
};

typedef struct s_free
{
	void			*adress;
	struct s_free	*next;
}			t_free;

typedef struct s_global
{
	int				exit_status;
	int				interrupted;
	t_free			*free;
	struct s_data	*data;
	struct s_exec	*exec;
}			t_global;

typedef struct s_compo
{
	char			*content;
	enum e_type		type;
	enum e_state	state;
	struct s_compo	*next;
	struct s_compo	*prev;
}			t_compo;

typedef struct s_cmd
{
	char			**args;
	int				in_file;
	int				out_file;
	t_compo			*token;
	struct s_cmd	*next;
}			t_cmd;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				check_parse;
	int				check;
	struct s_env	*next;
}			t_env;

	/*parsing struct*/
typedef struct s_data
{
	t_cmd			*cmd;
	t_env			*envp;
	t_compo			*tokens;
	t_list			*lst_cmd;
	t_list			*lst_err;
	t_list			*here_doc_name;
	char			*delim;
	char			*expend;
	int				exp_status;
	int				in;
	int				out;
	char			*name;
	int				pid;
	int				error;
	char			**env_tab;
	struct s_exec	*exec;
}			t_data;

	/*execution struct*/
typedef struct s_exec
{
	char	**n_env;
	int		i;
	int		*tube;
	int		id;
	int		nb_pipe;
	int		size;
	int		fork;
	char	*command;
	char	**str;
	char	**cd_str;
	t_compo	*token;
	t_cmd	*cmd;
	t_env	*env;
	t_list	*lst;
	t_env	*tmp;
}			t_exec;

	/*lexer_utils*/
bool	is_special(char c);
t_compo	*new_comp(char *content, int i, enum e_state state, enum e_type type);
void	add_to_list(t_compo **lst, t_compo *new);
void	free_list(t_compo *list);

	/*lexer*/
int		get_word(t_compo **list, char *line, enum e_state state);
void	get_quote(t_compo **list, char *line, enum e_state *state);
int		get_redirection(t_compo **list, char *line, int i, enum e_state state);
int		get_env(t_compo **list, char *line, enum e_state state);
t_compo	*lexer(char *line);

	/*syntax check*/
bool	check_syntax(t_compo *tokenes_lst);
t_compo	*skip_spaces(t_compo *node, int direction);
bool	is_redir(enum e_type type);

	/*parsing utils*/
void	create_cmd(t_data *data);
t_cmd	*ft_cmdnew(int in, int out, t_list *lst_cmd);
void	ft_cmdadd_back(t_cmd **cmd, t_cmd *new);
int		ft_cmdsize(t_cmd *lst);
void	ft_cmd_clear(t_cmd **lst);
t_env	*new_env(char *name, char *value);
void	add_env(t_env **env, t_env *new);
int		env_len(t_env *env);
char	**list_to_tab(t_env **env);
void	modify_token_content(t_compo **token, char *tmp, t_env *env);
void	add_token_to_list(t_data *data, char *str);

	/*parsing*/
void	parse(t_data *data, t_compo *token);
char	*parse_cmd(t_data *data, t_compo **token);
char	*parse_quote(t_data *data, t_compo **tok, enum e_type type);
char	*parse_env(t_data *data, t_compo **token);
char	*parse_word(t_compo **token);

	/*redirections*/
void	in_file(t_data *data, char *str);
void	out_file(t_data *data, char *str);
void	append(t_data *data, char *str);
void	child_here_doc(t_data *data, t_compo **token, char **str);
void	here_doc(t_data *data, t_compo **token);
char	*get_file_name(void);
char	*get_delimiter(t_compo **token, int *i, t_data *data);
char	*get_quote_delimiter(t_compo **lex, enum e_type type);
void	process_line(t_data *data, t_compo **tmp, int fd, int i);
void	write_to_file(int fd, t_compo *tmp);
char	*update_content(char *content, char *line);
void	init_here_doc_var(int *i, char **content, t_data *data,
			t_compo **token);
void	redir_error(t_data *data, char *str);
void	print_redir_error(t_list *lst, t_data *data);

	/*builtins*/
int		builtins(t_exec *exec, t_data *data);
void	echo(t_exec *exec);
int		fenv(t_exec *exec);
int		cd( char *path, t_exec *exec);
void	ft_exit(t_exec *exec, t_data *data);
void	unset(t_exec *exec);
void	pwd(t_exec *exec);

	/*export*/
void	export(t_exec *exec);
int		parss_export_variable(t_env *new, t_env *env_list, int i);
int		check_(t_env *new, int check_parse, int *i);
t_env	*find_env(t_env *env_list, char	*name);
void	ft_env_add_back(t_env **lst, t_env *new);
void	print_export(t_exec *exec);
int		check_special_char(t_env *new, int len, int i);
void	*concatenat_variable(t_env *new, t_env *env_list);
void	check_not_valid(t_exec *exec, int i);
int		check_non_valid(t_env *new);

	/*execution*/
void	execute(t_data *data, t_exec *exec);
void	execute_cmds(t_exec *exec, t_data *data);
void	exec_cmd(t_exec *exec, char *path, t_data *data);
char	*get_command(t_exec *exec, char *path);
char	*get_path(t_env *env);
void	check_if_dir(t_exec *exec, t_data *data);
void	create_pipes(t_exec *exec);
void	check_access(t_data *data, t_exec *exec);
void	wait_procces(int pid);
void	unlink_here_doc_name(t_list *list);
void	create_env(t_exec *exec, char **env);

	/*signals*/
void	exc_sig(int sig);
void	signalhanlder(int sig);

	/*error*/
void	ft_error(char *str);
void	exec_error(char *cmd);

	/*free*/
void	ft_close(t_cmd *val);
void	close_pipes(t_exec *exec);
void	close_right_ends(t_exec *exec);
void	cleanup(t_data *data, t_exec *exec);
void	ft_free_env(t_env **env);
void	ft_free2d(char **str);
void	free_here_doc(t_data *data, char *str);
void	ft_lstremove(t_env **begin_list, void *data_ref, t_exec *exec);

/*t_global	*global_static(void);*/
#endif