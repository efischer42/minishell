/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 09:45:13 by efischer          #+#    #+#             */
/*   Updated: 2019/07/23 15:50:06 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int		ft_check_arg(char *arg, uint8_t *flags)
{
	size_t	i;

	i = 1;
	while (arg[i] != '\0')
	{
		*flags = 0;
		if (arg[i] == 'P')
			*flags |= FLAG_P;
		else if (arg[i] == 'L')
			*flags |= FLAG_L;
		else
		{
			ft_putstr_fd("minishell: cd: -", 2);
			ft_putchar_fd(arg[i], 2);
			ft_putendl_fd(": Invalid option", 2);
			ft_putendl_fd("usage: cd [-L|-P] [directory]", 2);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

static int	get_flags(char ***av, uint8_t *flags)
{
	while (**av != NULL && ***av == '-')
	{
		if ((**av)[1] == '\0')
			return (SUCCESS);
		if (ft_strequ(**av, "--") == TRUE)
		{
			(*av)++;
			return (SUCCESS);
		}
		else if (ft_check_arg(**av, flags) == FALSE)
			return (FAILURE);
		(*av)++;
	}
	return (SUCCESS);
}

static void	set_pwd_oldpwd(char *curpath, char *buf, t_list **lst, uint8_t flags)
{
	char	*pwd[3];
	char	*oldpwd[3];

	if ((flags & FLAG_P) == FLAG_P)
		getcwd(curpath, PATH_MAX);
	put_name_val_in_tab("PWD", curpath, pwd);
	put_name_val_in_tab("OLDPWD", buf, oldpwd);
	setenv_blt(oldpwd, lst);
	setenv_blt(pwd, lst);
}

static void	init_pwd(t_list **lst)
{
	char	buf[PATH_MAX];
	char	*env_var[3];

	if (ft_getenv("PWD", *lst) == NULL)
	{
		getcwd(buf, PATH_MAX);
		put_name_val_in_tab("PWD", buf, env_var);
		setenv_blt(env_var, lst);
	}
}

int			cd_blt(char **av, t_list **lst)
{
	char	*curpath;
	char	*pwd;
	uint8_t	flags;

	av++;
	init_pwd(lst);
	pwd = ft_getenv("PWD", *lst);
	if (get_flags(&av, &flags) == FAILURE)
		return (FAILURE);
	if (ft_tablen(av) > 1)
	{
		ft_putendl_fd("minishell: cd: Too many arguments", 2);
		return (FAILURE);
	}
	curpath = get_path(*av, *lst);
	get_clean_path(&curpath);
	if (curpath == NULL)
		return (FAILURE);
	if (change_dir(curpath, *av, lst) == FAILURE)
	{
		ft_strdel(&curpath);
		return (FAILURE);
	}
	set_pwd_oldpwd(curpath, pwd, lst, flags);
	if (ft_strequ(*av, "-") == TRUE)
		ft_putendl(curpath);
	ft_strdel(&curpath);
	return (SUCCESS);
}
