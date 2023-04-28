/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 01:49:58 by aabda             #+#    #+#             */
/*   Updated: 2023/04/28 18:20:41 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

typedef struct s_env
{
	int				index;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_data
{
	struct s_env	*env;
}	t_data;

void	ft_init_struct(t_data *data, char **envp);
void	ft_getenv(t_data *data, char **envp);
void	ft_unset(t_data *data, char *value);
void	ft_init_struct(t_data *data, char **envp);

#endif
