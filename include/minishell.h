/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 06:01:59 by olmohame          #+#    #+#             */
/*   Updated: 2024/08/01 06:46:16 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <dirent.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <unistd.h>

# define D_GREEN	"\033[32;1m"
# define D_BLUE 	"\033[34;1m"
# define X			"\033[0;0m"

# define CD 		"minishell: cd: "
# define ENV		"env: "
# define E_EXIT		"minishell: exit: "
# define MS			"minishell: "
# define EXPORT		"minishell: export: "
# define NUM		": numeric argument required\n"
# define NO_FILE 	": No such file or directory\n"
# define BAD_FD		": Bad file descriptor\n"
# define MF			"Malloc failed.\n"
# define OP            ": option(s) not supported\n"
# define IG_MSG		"pwd: ignoring non-option arguments\n"

typedef struct s_pipe
{
	char	*path_name;
	int		num_cmd;
	int		num_children;
	int		*pids;
	char	**cmd_paths;
	int		**pipes;
}				t_pipe;

typedef struct s_param
{
	ssize_t	i;
	ssize_t	start_index;
	int		open_red;
	int		accept;
	char	prev_red;
	char	out_quo;
	int		status;
	int		new_status;
}				t_param;

typedef struct s_sub
{
	char			*str;
	char			**cmd_arr;
	int				op_in;
	int				op_out;
	int				op;
	int				fd_in;
	int				fd_out;
	char			*fname_in;
	char			*fname_out;
	int				invalid_expansion;
	struct s_sub	*prev;
	struct s_sub	*next;
}				t_sub;

typedef struct s_shell
{
	size_t	num_temp;
	int		doc_failed;
	int		delim_quoted;
	size_t	extra_rem;
	t_sub	*subs;
	char	**declare_env;
	char	**curr_envp;
	t_pipe	*st_pipe;
	int		execution_status;
	int		unlink_file;
	bool	should_exit;
	int		exit_code;
	char	*homepath;
	char	*the_prompt;
}				t_shell;

extern int	g_signal_status;
int			close_pipes(t_pipe *st_pipe, int id, int is_start);
int			find_var(t_shell **mshell, char *key);
int			new_pipe(t_shell **mshell);
int			is_valid_filepath(t_shell *mshell, t_pipe *st_pipe, t_sub *sub, \
				int id);
int			build_path(t_shell *mshell, t_pipe *st_pipe, t_sub *sub, int id);
char		*here_doc_err(t_shell **shell, char *del);
void		process_exit_code(t_shell *mshell, int i);
int			pick_fds(t_shell **shell, int get_input_fd, t_sub *sub, int id);
void		set_inout(t_shell **shell, t_pipe *st_pipe, t_sub *sub, int id);
void		executer(t_shell *mshell);
void		lstadd_back(t_sub **lst, t_sub *newnode);
int			add_sub(t_sub **head, char *str, long start, long end);
void		lstclear(t_sub **lst);
int			dc_count(t_sub **lst);
int			has_mixed_spaces(char *str);
int			spaces(char *str);
int			build_subs(t_shell *mshell, char *str);
void		expand_filename(t_shell **shell, t_sub	*sub, char **file);
int			read_redirections(t_shell **shell, t_sub **lst);
int			is_quoted(char *str, long ind);
int			is_expandable(char *str, long ind);
int			check_expansion(t_sub *sub, char *err_msg, int *syn_err);
size_t		sh_strclen(char *str);
void		sh_del(char **strings_arr, ssize_t num_strings);
size_t		sh_count(char *str);
char		**sh_split(char *str);
size_t		count_elements(char **list_str);
int			has_expandable_variable(char *str);
void		rebuild_cmd(t_shell *shell, t_sub **sub, \
								ssize_t *num_tokens, ssize_t *i);
void		clean_sequence(t_shell *shell, t_sub **sub, \
								ssize_t old_i, ssize_t i);
void		order_list(t_sub **sub, ssize_t	num_tokens);
int			clean_token(char **str, t_shell *shell);
void		init_expansion_param(t_param *param);
int			expand_token(char **list_str, int expand, t_sub *sub,
				t_shell *shell);
void		expand_and_clean(char **str, int expand, \
				t_sub *sub, t_shell *shell);
void		creat_cmd_list(t_sub **lst, t_shell *shell);
void		ft_strcpy(char *dest, char *src);
void		ft_strncpy(char *dest, char *src, size_t n);
int			expand_var(char **str, t_param *param, char **new_token, \
				t_shell *shell);
char		*fill_doc(t_shell **shell, char *delim);
char		*prep_msg(t_shell **shell, char *str, char *cmd, char *err);
int			validate_infile(t_shell **shell, char *file, int *syn_err);
int			validate_outfile(t_shell **shell, char *file, \
											int append, int *syn_err);
void		is_valid_fd(t_shell **shell, t_sub *sub, int id, int fd);
void		wrapp_dup2(t_shell **shell, t_sub *sub, int id);
void		close_files_sub(t_sub *sub, int is_parent);
int			close_files(t_sub **lst, int is_parent, int all);
int			del_tokens(t_sub *sub);
int			reset_shell(t_shell **shell);
int			exit_msg(t_shell **shell, char *str, int free_flag, int status);
int			del_gen(int **mat, int num_fields);
int			execute_builtin_cmd(t_shell *mshell, t_pipe *st_pipe, t_sub *subs, \
				int id);
bool		is_builtin_cmd(const char *command);
void		child_process_builtin(t_shell *mshell, t_pipe *st_pipe, \
				t_sub *sub, int id);
void		exec_cd_home(t_shell *mshell);
void		exec_cd_oldpwd(t_shell *mshell);
void		exec_cd_tilde(t_shell *mshell);
void		handle_cd_else(t_shell *mshell, t_sub *subs);
void		exec_cd(t_shell *mshell, t_sub *subs);
void		display_env(t_shell *mshell, t_sub *subs);
char		*ft_getcwd(char *var, char **env, char **path, t_shell *mshell);
void		display_pwd(t_shell *mshell);
void		display_echo(t_sub *subs);
int			is_dir(const char *name);
bool		has_otherthan_n(char *str);
int			is_only_exit(t_shell *mshell, t_sub *subs);
int			exec_exit(t_shell *mshell, t_sub *subs);
int			find_equal(char *var, int *found);
int			count_env_vars(char **env);
void		export_declare(char **env);
char		**find_and_delete_if_exist(char **env, char *cmdargs);
void		exec_export(t_shell *mshell, char **cmdargs);
int			check_special_char(char c);
int			check_first_char(char c);
int			check_brace(char c);
int			validate_identifier(char *before_eq, char *original_str);
int			check_identifier(t_shell *mshell, char *str);
void		exec_unset(t_shell *mshell, t_sub *subs);
int			check_some_conditions(t_shell *mshell, char *str);
char		**del_var_declare(char **env, char *var_only);
char		*replace_this(t_param *param, char *str, t_shell *shell);
void		bi_strcpy(char *dest, char *src);
void		bi_strncpy(char *dest, char *src, size_t n);
char		*custom_getenv(t_shell *shell, const char *name);
int			is_valid_env(char **env);
char		**env_cpy(char **env);
void		free_env(char **str);
char		*get_prompt(char **env);
void		print_variable_with_quotes(char *var);
char		**add_var(char **env, char *var, t_shell *mshell);
char		**env_excluding_var(char **env, char *var);
int			found_in_env(char *var, char **env, char **path);
void		getcwd_err_msg(void);
void		update_shlvl(char **env);
void		signal_handler_main(int sig);
void		check_global_var(t_shell *mshell);
void		set_signal_main(t_shell *mshell);
void		sig_handler_pipex_and_heredoc(int sig);
void		set_signal_heredoc(void);
int			status_for_signal(int sig_num);
void		update_termios(int set_echoctl);
void		error_msg(char *pre, char *str, char *cmd, t_shell *mshell);
void		prefix_with_msg(char *env_var, t_shell *shell, char *prefix);
void		free_prefix(char *prefix, char *value);
void		check_arg_two(t_shell *mshell, t_sub *subs);
int			check_isdigit(char *str);
void		print_err(char *part_one, char *part_two, char *part_three);
char		*arg_err_msg(char *pre, char *str, char *cmd, t_shell *mshell);
size_t		get_var_length(char *var_start, char **var_end);
int			close_output(t_shell *mshell, t_sub *sub, int index, \
				int *dupe_stdout);
void		close_inout(t_shell *mshell, t_sub *sub, int index, \
				int *dupe_stdout);			
int			close_input(t_pipe *st_pipe, t_sub *sub, int index);
int			check_first_char1(char c);
void		varname_without_firstchar(char **var_name, t_shell *shell);
char		*extract_var_name_and_value(t_shell *shell, char *var_start, \
				size_t var_len);
void		cd_update_in_env1(t_shell *mshell, char *path);
void		exit_free_assign(t_shell *mshell, char **temp_env, char c);
int			find_index(char **env, char *var_with_equal);
void		bi_close_all_pipes(t_pipe *st_pipe);
int			bi_set_output(t_pipe *st_pipe, t_sub *sub, int index, \
				int *dupe_stdout);

#endif
