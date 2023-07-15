/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduchesn <gduchesn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:50:42 by gduchesn          #+#    #+#             */
/*   Updated: 2023/07/15 19:18:15 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmp_delimiter(char c)
{
	static char delimiter[] = END_VAR_ENV;
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
		if (!ft_strncmp((str + i + 1), data.env->key, (j - i - 1)))
		{
			printf("j - i = %d / str + i + 1 = %s\n", j - i, str + i + 1);
			printf("seems to work\n");
			return (data.env->value);
		}
		data.env = data.env->next;
	}
	return (ft_strdup(""));
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*heredoc_expand(t_data data, char *str)
{
	int	i;
	int	j;
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
		while ((str[j] && !cmp_delimiter(str[j])) && !(j - 1 == i && ft_isdigit(str[j])))
			j++;
		if (!(j - 1 == i && ft_isdigit(str[j])))
			env_value = find_env_variable(str, i, j, data);
		else if (++j)
			env_value = ft_strdup("");
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

void	redesign_word(char **word, int *i, char type, int *bool_quotes)
{
	char	*tmp;
	char	*redesign;
	char	*tmp2;
	int		j;

	if (*bool_quotes == 0)
		*bool_quotes = 1;
	tmp = ft_strndup((*word), *i);
	dprintf(2, "ha\n");
	dprintf(2, "tmp : %s\n", tmp);
	if (!tmp)
		exit(18);
	j = *i + 1;
	while ((*word)[j] && (*word)[j] != type)
		j++;
	redesign = ft_strndup(((*word) + *i + 1), (j - *i - 1));
	if (!redesign)
		exit(18);
	tmp2 = ft_strjoin(tmp, redesign);
	free(tmp);
	free(redesign);
	if (!tmp2)
		exit(18);
	*i = ft_strlen(tmp2);
	dprintf(2, "value i : %d\n", *i);
	tmp = ft_strjoin(tmp2, ((*word) + j + 1));
	free(tmp2);
	ft_free((void **)&(*word));
	if (!tmp)
		exit(18);
	*word = tmp;
	printf("word = %s\n", *word);
}

int	fix_word(char **word)
{
	int	bool_quotes;
	int	i;

	i = 0;
	bool_quotes = 0;
	while ((*word) && (*word)[i])
	{
		if ((*word)[i] == '\'')
			redesign_word(word, &i, '\'', &bool_quotes);
		if ((*word)[i] == '"')
			redesign_word(word, &i, '"', &bool_quotes);
		else
			++i;
	}
	return (bool_quotes);
}

void	heredoc_open(int fd, char *word, t_data *data)
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
			if (close(0) != -1 && !str)
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
	if (str)
		close(0);
	ft_free((void **)&str);
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
	int		i;
	int		fd;

	i = 0;
	fd = -2;
	while (snake)
	{
		if (snake->is_token == D_LOWER)
		{
			data->heredoc->open_file = create_tmp_file(&fd, i, data->heredoc->open_file);
			if (!data->heredoc->open_file)
				return (-3);
			ft_handler_signal(1);
			heredoc_open(fd, snake->word, data);
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
			exit (1);
	}
	return (fd);
}
