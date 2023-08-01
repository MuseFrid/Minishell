/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 01:49:58 by aabda             #+#    #+#             */
/*   Updated: 2023/08/01 05:40:59 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

typedef struct s_data
{
	int						nbr_l;
	struct s_env			*env;
	struct s_hidden_env		*hidden_env;
	struct s_simple_cmds	*cmds;
}	t_data;
int		g_ret_val;
char	*ft_prompt(t_data *data);
void	ft_handler_signal(int pick);

#endif
