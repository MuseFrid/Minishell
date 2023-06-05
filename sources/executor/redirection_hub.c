#include "minishell.h"

void	create_outfile(t_data *data, int fd[2], int pick, char *file_to_open)
{
	if (fd[OUT] != -2)
		close(fd[OUT]);
	if (pick == D_GREATER)
		fd[OUT] = open(file_to_open, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd[OUT] = open(file_to_open, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd[OUT] == -1)
		data->err_return_val = 1;
}

void	open_infile(t_data *data, int *which, int pick, char *file_to_open)
{
	if (*which != -2 && *which != 3)
		close(*which);
	if (pick == D_LOWER)
		*which = -3;
	if (pick == LOWER)
		*which = open(file_to_open, O_RDONLY);
	if (*which == -1)
		data->err_return_val = 1;
}

int	printf_redirection(t_arg *redirection)
{
	if (!redirection)
		return (printf("No redirection\n"));
	while (redirection)
	{
		printf("%s\n", redirection->word);
		redirection = redirection->next;
	}
	return (0);
}

void	redirection_hub(t_arg *redirection, t_data *data, int fd[2])
{
	int	which;

	printf("ah\n");
	printf_redirection(redirection);
	fd[IN] = heredoc_handler(redirection, data);
	printf("%d\n", fd[IN]);
	fd[OUT] = -2;
	which = -2;
	while (redirection && data->err_return_val == 0)
	{
		if (redirection->is_token == D_GREATER || redirection->is_token == GREATER)
			create_outfile(data, fd, redirection->is_token, redirection->word);
		else
			open_infile(data, &which, redirection->is_token, redirection->word);
		redirection = redirection->next;
	}
	if (which != -3)
	{
		if (fd[IN] != -2)
			close (fd[IN]);
		fd[IN] = which;
	}
}