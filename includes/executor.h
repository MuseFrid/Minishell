/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:47:25 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/29 18:49:09 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define IN 0
# define OUT 1
# define HEREDOC_FILE "/tmp/.tmp_heredoc"

typedef struct s_fd
{
	int	pipe[2];
	int	redirection[2];
	int	in;
	int	out;
}	t_fd;

int		ft_create_child(t_simple_cmds *cmds,
			t_env *env, t_fd *fd, t_data *data);
void	ft_executer_child(t_simple_cmds *cmds,
			t_env *env, t_fd *fd, t_data *data);
void	ft_run_all_cmds(t_data *data, t_simple_cmds *snake);
void	redirection_hub(t_arg *redirection,
			t_simple_cmds *cmds, t_data *data, int fd[2]);
int		heredoc_handler(t_arg *snake, t_data *data, t_simple_cmds *cmds);
char	*parse(char **envp, const char *cmd);
char	**redesign_env(t_env *env);
void	wait_child(t_data *data);
void	ft_init_fd(t_fd *fd);
void	ft_final_fd(t_fd *fd);

#endif
