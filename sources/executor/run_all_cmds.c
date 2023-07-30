/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_all_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:06:26 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/30 19:13:26 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*merge_keyvalue(t_env *env)
{
	char	*str;
	char	*final_str;

	str = ft_strjoin(env->key, "=");
	final_str = ft_strjoin(str, env->value);
	free(str);
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
		kill_mini("Minishell");
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

void	usebuiltin(t_data *data, t_fd fd)
{
	int	new_stdout;
	int	bool_ex;

	bool_ex = 0;
	if (fd.in != -2)
		close(fd.in);
	new_stdout = dup(1);
	if (new_stdout == -1)
		kill_mini("Minishell: dup1");
	if (fd.out != -2)
		bool_ex = dup2(fd.out, 1);
	if (bool_ex == -1)
		kill_mini("Minishell: dup2");
	if (bool_ex != -1)
		g_ret_val = data->cmds->builtin(data);
	else
		g_ret_val = 1;
	if (fd.out != -2)
		close(fd.out);
	close (1);
	if (dup2(new_stdout, 1) == -1)
		kill_mini("Minishell: critical error:");
	close(new_stdout);
}

void	ft_run_all_cmds(t_data *data, t_simple_cmds *snake)
{
	t_fd			fd;

	fd.in = -2;
	while (snake)
	{
		ft_env_underscore(data, snake);
		ft_init_fd(&fd);
		if (snake->next)
			if (pipe(fd.pipe) == -1)
				kill_mini("Minishell: pipe");
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
