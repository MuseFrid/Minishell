/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 01:49:58 by aabda             #+#    #+#             */
/*   Updated: 2023/07/15 18:40:22 by gduchesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

typedef struct s_data
{
	int						err_return_val;
	struct s_env			*env;
	struct s_simple_cmds	*cmds;
	struct s_heredoc		*heredoc;
}	t_data;
int	ret_val;
char	*ft_prompt(t_data *data);
void	ft_handler_signal(int is_heredoc);

#endif
