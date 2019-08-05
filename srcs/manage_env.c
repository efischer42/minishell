/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:53:47 by efischer          #+#    #+#             */
/*   Updated: 2019/08/05 11:13:16 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_list *lst, char *utility)
{
	if (ft_lstprint(lst, get_content_to_print) == FAILURE)
	{
		ft_dprintf(2, "minishell: %s: write error: Bad file descriptor\n",
		utility);
	}
}

void	print_env_one(t_list *lst, char *utility, char *env_var)
{
	t_list	*tmp;

	tmp = find_env(env_var, lst);
	if (tmp != NULL && ft_strequ(((t_env*)(tmp->content))->name, "RET")
		== FALSE)
	{
		if (ft_putendl(((t_env*)(tmp->content))->value) == FAILURE)
		{
			ft_dprintf(2, "minishell: %s: write error: Bad file descriptor\n",
			utility);
		}
	}
}

void	put_name_val_in_tab(char *name, char *value, char **env_var)
{
	env_var[0] = name;
	env_var[1] = value;
	env_var[2] = NULL;
}

char	*ft_getenv(char *env_name, t_list *lst)
{
	if (env_name == NULL || lst == NULL)
		return (NULL);
	while (lst != NULL)
	{
		if (ft_strequ(((t_env*)(lst->content))->name, env_name) == TRUE)
			return (((t_env*)(lst->content))->value);
		lst = lst->next;
	}
	return (NULL);
}

void	get_env_lst(char **envp, t_list **lst)
{
	t_env	env;
	char	**tab;
	size_t	i_env;
	size_t	i_tab;

	i_env = 0;
	while (envp[i_env] != NULL)
	{
		i_tab = 0;
		ft_bzero(&env, sizeof(env));
		tab = ft_strsplit(envp[i_env], '=');
		env.name = ft_strdup(tab[i_tab++]);
		while (tab[i_tab] != NULL)
		{
			env.value = ft_join_free(env.value, tab[i_tab], 1);
			i_tab++;
			if (tab[i_tab] != NULL)
				env.value = ft_join_free(env.value, "=", 1);
		}
		ft_free_tab(tab);
		ft_lstaddend(lst, ft_lstnew(&env, sizeof(env)));
		i_env++;
	}
}

t_list	*find_env(const char *arg, t_list *lst)
{
	while (lst != NULL)
	{
		if (ft_strequ(((t_env*)(lst->content))->name, arg) == TRUE)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
