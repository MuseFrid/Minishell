#ifndef EXECUTOR_H
# define EXECUTOR_H

# define IN 0
# define OUT 1

typedef struct s_fd
{
	int	pipe[2];
	int	redirection[2];
	int	in;
	int	out;
}	t_fd;

int		ft_create_child(char **cmds, t_env *env, t_fd *fd);
void	ft_run_all_cmds(t_data *data);
void 	redirection_hub(t_arg *redirection, t_data *data, int fd[2]);
int		heredoc_handler(t_arg *snake, t_data *data);
char	*parse(char **envp, const char *cmd);
void	wait_child(t_data *data);

#endif
