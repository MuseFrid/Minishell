/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_related.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:16:53 by gduchesn          #+#    #+#             */
/*   Updated: 2023/08/01 12:45:37 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	executor_child_dup(t_fd *fd)
{
	close(fd->pipe[0]);
	if (fd->in != -2)
		if (dup2(fd->in, 0) == -1)
			kill_mini("Minishell");
	if (fd->out != -2)
		if (dup2(fd->out, 1) == -1)
			kill_mini("Minishell");
}

void	ft_executer_child(t_simple_cmds *cmds,
	t_env *env, t_fd *fd, t_data *data)
{
	char	**final_env;
	char	*path;

	ft_handler_signal(3);
	executor_child_dup(fd);
	if (!(cmds->tab && cmds->tab[0]))
		exit(0);
	if (cmds->builtin)
	{
		data->cmds = cmds;
		exit(cmds-> builtin(data));
	}
	final_env = redesign_env(env);
	path = parse(final_env, cmds->tab[0]);
	if (!path)
	{
		write_error("Minishell: ", cmds->tab[0], ": command not found\n", NULL);
		exit (127);
	}
	execve(path, cmds->tab, final_env);
	perror("execve");
	exit(1);
}

void	ft_create_child(t_simple_cmds *cmds, t_env *env, t_fd *fd, t_data *data)
{
	cmds->pid = fork();
	if (cmds->pid == -1)
	{
		perror("Minishell: fork: retry");
		return ;
	}
	if (cmds->pid == 0)
		ft_executer_child(cmds, env, fd, data);
	ft_handler_signal(2);
	close_parent_fd(*fd);
	fd->in = fd->pipe[0];
}
