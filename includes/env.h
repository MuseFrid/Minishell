/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 01:43:03 by aabda             #+#    #+#             */
/*   Updated: 2023/04/30 05:35:30 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	int				index;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

void	ft_getenv(t_data *data, char **envp);

#endif