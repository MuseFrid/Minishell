#ifndef EXECUTOR_H
# define EXECUTOR_H

# define IN 0
# define OUT 1
void 	redirection_hub(t_arg *redirection, t_data *data, int fd[2]);
int	heredoc_handler(t_arg *snake, t_data *data);

#endif
