/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:26:59 by gduchesn          #+#    #+#             */
/*   Updated: 2023/05/26 17:01:43 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_child(int fd[2], char *word, t_data *data)
{
	char	*str;

	close(fd[0]);
	while (1)
	{
		str = readline(">");
		write(fd[1], str, ft_strlen(str));
		free(str);
	}
	close(fd[1]);
	free_all(data);
	exit(0);
}

int	heredoc_handler(t_arg *snake, t_data *data)
{
	int		id;
	int		fd[2];
	int		i;

	i = 0;
	fd[0] = -2;
	while (snake)
	{
		if (snake->is_token = D_LOWER)
		{
			if (fd[0] != -2)
				close(fd[0]);
			if (pipe(fd) == -1)
				exit(1);
			id = fork();
			if (id == 0)
				return (heredoc_child(fd, snake->word, data));
			if (errno)
				exit(1);
			close(fd[1]);
			waitpid(id, 0, 0);
		}
		snake = snake->next;
	}
	return (fd[0]);
}
