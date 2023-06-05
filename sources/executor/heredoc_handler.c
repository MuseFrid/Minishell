/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:26:59 by gduchesn          #+#    #+#             */
/*   Updated: 2023/05/26 18:51:40 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_child(int fd, char *word, t_data *data)
{
	char	*str;

	//redesign word (remove quotes)
	while (1)
	{
		str = readline("> ");
		if (str && !ft_strcmp_strict(str, word))
			break ;
		//expand $
		write(fd, str, ft_strlen(str));
		free(str);
	}
	close(fd);
	lst_clear_arg(data->cmds->redirections);
	lst_clear_arg(data->cmds->test_red);
	int	i;
	i = 0;
	if (data->cmds->tab)
	{
		while (data->cmds->tab[i])
			free(data->cmds->tab[i++]);
		free(data->cmds->tab);
	}
	free_all(data);
	exit(0);
}

char	*create_tmp_file(int *fd, int i, char *name)
{
	char	*new_name;

	if (*fd != -2)
	{
		close(*fd);
		if (unlink(name) == -1)
			return (NULL);
		ft_free((void **) &name);
	}
	name = ft_itoa(i);
	if (!name)
		return (NULL);
	new_name = ft_strjoin(".tmp", name);
	ft_free((void **)&name);
	if (!new_name)
		return (NULL);
	*fd = open(new_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*fd == -1)
		ft_free((void **)&new_name);
	return (new_name);
}

int	heredoc_handler(t_arg *snake, t_data *data)
{
	int	id;
	int	fd;
	int	i;
	char	*name;

	i = 0;
	fd = -2;
	name = NULL;
	while (snake)
	{
		if (snake->is_token == D_LOWER)
		{
			name = create_tmp_file(&fd, i, name);
			if (!name)
				return (-3);
			id = fork();
			if (id == -1)
				exit(1);
			if (id == 0)
				heredoc_child(fd, snake->word, data);
			waitpid(id, 0, 0);
			//printf("waitpid %d\n", waitpid(id, 0, 0));
			//printf("parent : %d\n", id);
			i++;
		}
		snake = snake->next;
	}
	return (fd);
}
