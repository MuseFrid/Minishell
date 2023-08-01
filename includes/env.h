/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 01:43:03 by aabda             #+#    #+#             */
/*   Updated: 2023/08/01 05:40:55 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	int				index;
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_hidden_env
{
	char	*pwd;
	char	*oldpwd;
}	t_hidden_env;

void	ft_getenv(t_data *data, char **envp);
void	ft_run_without_env(t_data *data);
void	ft_env_underscore(t_data *data, t_simple_cmds *cmds);

#endif
