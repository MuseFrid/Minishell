/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_related.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:16:53 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/31 16:27:54 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_executer_child(t_simple_cmds *cmds,
	t_env *env, t_fd *fd, t_data *data)
{
	char	**final_env;
	char	*path;

	ft_handler_signal(3);
	close(fd->pipe[0]);
	if (fd->in != -2)
		if (dup2(fd->in, 0) == -1)
			kill_mini("Minishell");
	if (fd->out != -2)
		if (dup2(fd->out, 1) == -1)
			kill_mini("Minishell");
	if (!(cmds->tab && cmds->tab[0]))
		exit(0);
	if (cmds->builtin)
		exit(cmds->builtin(data));
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

int	ft_create_child(t_simple_cmds *cmds, t_env *env, t_fd *fd, t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		kill_mini("fork");
	if (pid == 0)
		ft_executer_child(cmds, env, fd, data);
	ft_handler_signal(2);
	if (fd->in != -2)
		close(fd->in);
	if (fd->out != -2)
		close(fd->out);
	fd->in = fd->pipe[0];
	return (pid);
}
