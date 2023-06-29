/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:50:42 by gduchesn          #+#    #+#             */
/*   Updated: 2023/06/29 19:36:58 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_open(int fd, char *word, t_data *data)
{
	int		dup_fd;
	char	*str;
	
	dup_fd = dup(0);
	if (dup_fd == -1)
		exit(41); //error fonction
	while (1)
	{
		str = readline("> ");
		if (str && !ft_strcmp_strict(str, word))
		{
			free(str);
			break ;
		}
		(void) data;
		//expand $
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	close(0);
	if (dup2(dup_fd, 0) == -1)
		exit(42);
	close(dup_fd);
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
	new_name = ft_strjoin("/tmp/.tmp", name);
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
	char	*name;
	int		i;
	int		fd;

	i = 0;
	fd = -2;
	while (snake)
	{
		if (snake->is_token == D_LOWER)
		{
			name = create_tmp_file(&fd, i, name);
			if (!name)
				return (-3);
			heredoc_open(fd, snake->word, data);
			i++;
		}
		snake = snake->next;
	}
	close(fd);
	fd = open(name, O_RDWR, 0644);
	return (fd);
}
