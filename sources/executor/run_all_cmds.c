/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_all_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:06:26 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/19 16:57:05 by gduchesn         ###   ########.fr       */
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

void	ft_executer_child(char **cmds, t_env *env, t_fd *fd)
{
	char	**final_env;
	char	*path;

	if (fd->in != -2)
		if (dup2(fd->in, 0) == -1)
			exit(1);
	if (fd->out != -2)
		if (dup2(fd->out, 1) == -1)
			exit(1);
	if (!(*cmds))
		exit(0);
	final_env = redesign_env(env);
	path = parse(final_env, cmds[0]);
	if (!path)
	{
		perror("path not find");
		exit (1);
	}
	execve(path, cmds, final_env);
	perror("execve");
	exit(1);
}

int	ft_create_child(char **cmds, t_env *env, t_fd *fd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
		ft_executer_child(cmds, env, fd);
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
		if (fd->in != 2)
			close(fd->in);
		fd->in = fd->redirection[IN];
	}
}

void	usebuiltin(t_data *data, t_fd fd)
{
	int	new_stdout;

	if (fd.in != -2)
		close(fd.in);
	new_stdout = dup(1);
	if (fd.out != -2)
		if (dup2(fd.out, 1) == -1)
			exit (18);
	data->cmds->builtin(data);
	if (fd.out != -2)
		close(fd.out);
	close (1);
	dup2(new_stdout, 1);
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
		redirection_hub(snake->redirections, data, fd.redirection);
		ft_final_fd(&fd);
		if (snake->builtin && snake->next == NULL)
			usebuiltin(data, fd);
		else
			snake->pid = ft_create_child(snake->tab, data->env, &fd);
		snake = snake->next;
	}
}
