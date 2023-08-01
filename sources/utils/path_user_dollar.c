/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_user_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabda <aabda@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:15:00 by aabda             #+#    #+#             */
/*   Updated: 2023/07/30 18:50:51y gdaabda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
static void     ft_create_pwd_str(char *home, char *str, char *res)
{
        int     i;
        int     j;

        i = 0;
        while (str[i] == home[i])
                ++i;
        res[0] = '~';
        j = 0;
        while (++j < (int)ft_strlen(str) - (int)ft_strlen(home) + 1)
        {
                res[j] = str[i];
                ++i;
        }
        res[j] = '\0';
}

static char     *ft_cmp_res(char *res, char *home_str, char *str)
{
        if (!home_str)
                return (res);
        if ((ft_strlen(str) - ft_strlen(home_str) == 0))
        {
                res = malloc(sizeof(char) * 3);
                if (!res)
                        kill_mini("Minishell");
                res[0] = '~';
                res[1] = '/';
                res[2] = '\0';
        }
        else
        {
                res = malloc(sizeof(char) * ft_strlen(str) - ft_strlen(home_str) + 2);
                if (!res)
                        kill_mini("Minishell");
                ft_create_pwd_str(home_str, str, res);
        }
        free(home_str);
        return (res);
}

static char     *ft_catch_home(t_data *data, char *str)
{
        char    *home;
        char    *res;

        res = NULL;
        home = ft_strdup(ft_get_value_env(data, "HOME"));
        if (!home)
        {
                free(str);
                return (NULL);
        }
        res = ft_cmp_res(res, home, str);
        free(str);
        return (res);
}

static char     *ft_catch_pwd_env(t_data *data)
{
        char    *res;
        char    *home;

        home = NULL;
        res = getcwd(NULL, 0);
        if (!res)
                return (NULL);
        home = ft_strdup(ft_get_value_env(data, "HOME"));
        if (!home)
                return (res);
        if (ft_strlen(home) < ft_strlen(res))
                res = ft_catch_home(data, res);
        free(home);
        return (res);
}

char    *ft_path_and_username(t_data *data)
{
        char    *user;
        char    *pwd;
        char    *res;
        char    *final;

        user = ft_strdup(ft_get_value_env(data, "USER"));
        pwd = ft_catch_pwd_env(data);
        if (!user || !pwd)
        {
                free(user);
                free(pwd);
                return (NULL);
        }
        res = malloc(sizeof(char) * ft_strlen(user) + ft_strlen(pwd) + 4);
        if (!res)
                kill_mini("Minishell : promt_name");
        ft_join_pwd_user_dollar(user, pwd, res);
        free(pwd);
        free(user);
        final = ft_strjoin(res, RESET);
        free(res);
        res = ft_strjoin(BOLDYELLOW, final);
        free(final);
        return (res);
}
