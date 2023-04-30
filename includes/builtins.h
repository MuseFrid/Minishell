/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:23:01 by aabda             #+#    #+#             */
/*   Updated: 2023/04/30 05:35:40 by aabda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	ft_exit(t_data *data);
int	ft_env(t_data *data);
int	ft_unset(t_data *data);
int	ft_pwd(t_data *data);
int	ft_export(t_data *data);

#endif