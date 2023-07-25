/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_all_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:06:26 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/25 17:19:07 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_fd(t_fd *fd)
{
	fd->pipe[0] = -2;
	fd->pipe[1] = -2;
	fd->redirection[0] = -2;
	fd->redirection[1] = -2;
	fd->out = -2;
}

char	*merge_keyvalue(t_env *env)
{
	char	*str;
	char	*final_str;

	str = ft_strjoin(env->key, "=");
	if (!str)
		exit(1);
	final_str = ft_strjoin(str, env->value);
	free(str);
	if (!final_str)
		exit(1);
	return (final_str);
}

char	**redesign_env(t_env *env)
{
	char	**new_env;
	t_env	*size;
	int		i;

	i = 0;
	size = env;
	while (size && ++i)
		size = size->next;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		exit(1);
	new_env[i] = NULL;
	i = 0;
	size = env;
	while (env)
	{
		new_env[i++] = merge_keyvalue(env);
		env = env->next;
	}
	return (new_env);
}

void	ft_executer_child(t_simple_cmds *cmds, t_env *env, t_fd *fd, t_data *data)
{
	char	**final_env;
	char	*path;

	close(fd->pipe[0]);
	if (fd->in != -2)
		if (dup2(fd->in, 0) == -1)
			kill_mini("Minishell");
	if (fd->out != -2)
		if (dup2(fd->out, 1) == -1)
			kill_mini("Minishell");
	if (!(cmds->tab[0]))
		exit(0);
	if (cmds->builtin)
		exit(cmds->builtin(data));
	final_env = redesign_env(env);
	path = parse(final_env, cmds->tab[0]);
	if (!path)
	{
		write(2, "Minishell: ", 11);
		write(2, cmds->tab[0], ft_strlen(cmds->tab[0]));
		write(2, ": command not found\n", 20);
		exit (127);
	}
	execve(path, cmds->tab, final_env);
	perror("execve");
	exit(1);
}

int	ft_create_child(t_simple_cmds *cmds, t_env *env, t_fd *fd, t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		kill_mini("fork");
	if (pid == 0)
		ft_executer_child(cmds, env, fd, data);
	if (fd->in != -2)
		close(fd->in);
	if (fd->out != -2)
		close(fd->out);
	fd->in = fd->pipe[0];
	return (pid);
}

void	ft_final_fd(t_fd *fd)
{
	if (fd->pipe[1] != -2)
		fd->out = fd->pipe[1];
	if (fd->redirection[OUT] != -2)
	{
		if (fd->pipe[1] != -2)
			close(fd->pipe[1]);
		fd->out = fd->redirection[OUT];
	}
	if (fd->redirection[IN] != -2)
	{
		if (fd->in != -2)
			close(fd->in);
		fd->in = fd->redirection[IN];
	}
}

void	usebuiltin(t_data *data, t_fd fd)
{
	int	new_stdout;
	int	bool_ex;

	bool_ex = 0;
	if (fd.in != -2)
		close(fd.in);
	new_stdout = dup(1);
	if (fd.out != -2)
		bool_ex = dup2(fd.out, 1);
	if (bool_ex != -1)
		ret_val = data->cmds->builtin(data);
	else
		ret_val = 1;
	if (fd.out != -2)
		close(fd.out);
	close (1);
	if (dup2(new_stdout, 1) == -1)
		kill_mini("Minishell: critical error:");
	close(new_stdout);
}

void	ft_run_all_cmds(t_data *data)
{
	t_fd			fd;
	t_simple_cmds	*snake;

	fd.in = -2;
	snake = data->cmds;
	while (snake)
	{
		ft_init_fd(&fd);
		if (snake->next)
		{
			if (pipe(fd.pipe) == -1)
			{
				perror("pipe");
				exit(1);
			}
		}
		redirection_hub(snake->redirections, snake, data, fd.redirection);
		ft_final_fd(&fd);
		if (snake->end == 1)
		{
			if (fd.out != -2)
				close(fd.out);
			if (fd.in != -2)
				close(fd.in);
		}
		else if (snake->builtin && snake->next == NULL && snake->prev == NULL)
			usebuiltin(data, fd);
		else
			snake->pid = ft_create_child(snake, data->env, &fd, data);
		snake = snake->next;
	}
}
