/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:50:42 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/25 18:44:24 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmp_delimiter(char c)
{
	static char	delimiter[] = END_VAR_ENV;
	int			i;

	i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*find_env_variable(char *str, int i, int j, t_data data)
{
	while (data.env)
	{
		if ((j - i - 1) == (int)ft_strlen(data.env->key)
				&& !ft_strncmp((str + i + 1), data.env->key, (j - i - 1)))
		{
		//	printf("j - i = %d / str + i + 1 = %s\n", j - i, str + i + 1);
		//	printf("seems to work\n");
			return (data.env->value);
		}
		data.env = data.env->next;
	}
	return (ft_strdup(""));
}

char	*heredoc_expand(t_data data, char *str)
{
	int		i;
	int		j;
	char	*env_value;
	char	*start;
	char	*tmp;

	i = 0;
	while (19)
	{
		while (str[i] && str[i] != '$')
			i++;
		if (str[i] != '$')
			break ;
		j = (i + 1);
		while ((str[j] && !cmp_delimiter(str[j]))
			&& !(j - 1 == i && ft_isdigit(str[j])))
			j++;
		if (str[j] && str[j] == '?')
			env_value = ft_itoa(ret_val);
		else if (!(j - 1 == i && ft_isdigit(str[j])))
			env_value = find_env_variable(str, i, j, data);
		else if (++j)
			env_value = ft_strdup("");
		if (!env_value)
			exit(10);
		tmp = ft_strndup(str, i);
		start = ft_strjoin(tmp, env_value);
		free(tmp);
		if (!start)
			exit (10);
		tmp = ft_strjoin(start, (str + j));
		if (!tmp)
			exit (10);
		free(str);
		str = tmp;
		i = 0;
	}
	return (str);
}

void	heredoc_open(int fd, char *word, t_data *data, t_simple_cmds *cmds)
{
	int		dup_fd;
	char	*str;
	int		bool_quotes;
	
	str = NULL;
	dup_fd = dup(0);
	bool_quotes = fix_word(&word);
	if (dup_fd == -1)
		exit(41); //error fonction
	while (1)
	{
		str = readline("> ");
		if (!str || (str && !ft_strcmp_strict(str, word)))
        {
			if (close(0) == -1 && !str)
				cmds->end = 1;
			else if (!str)
				printf("warning: here-document at line %d delimited by end-of-file (wanted `%s')\n",
				   data->heredoc->nbr_l, word);
			errno = 0;
            break ;
        }
		if (!bool_quotes)
			str = heredoc_expand(*data, str);
		if (str)
			write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		ft_free((void **)&str);
	}
	ft_free((void **)&str);
	if (dup2(dup_fd, 0) == -1)
		exit(42);
	close(dup_fd);
}

char	*create_tmp_file(int *fd, int i, char *name, t_simple_cmds *cmds)
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
		exit(1);
	new_name = ft_strjoin("/tmp/.tmp", name);
	ft_free((void **)&name);
	if (!new_name)
		exit(1);
	*fd = open(new_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*fd == -1)
	{
		ft_free((void **)&new_name);
		cmds_is_finish(cmds);
	}
	return (new_name);
}

int	heredoc_handler(t_arg *snake, t_data *data, t_simple_cmds *cmds)
{
	int		i;
	int		fd;

	i = 0;
	fd = -2;
	while (snake && cmds->end == 0)
	{
		if (snake->is_token == D_LOWER)
		{
			data->heredoc->open_file = create_tmp_file(&fd, i, data->heredoc->open_file, cmds);
			if (!data->heredoc->open_file)
				return (-3);
			ft_handler_signal(1);
			heredoc_open(fd, snake->word, data, cmds);
			ft_handler_signal(0);
			i++;
		}
		snake = snake->next;
	}
	if (fd != -2)
	{
		close(fd);
		fd = open(data->heredoc->open_file, O_RDWR, 0644);
		if (fd == -1)
		{
			cmds->end = 1;
			return (-2);
		}
	}
	return (fd);
}
