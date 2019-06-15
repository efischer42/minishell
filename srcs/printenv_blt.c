/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printenv_blt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:13:22 by efischer          #+#    #+#             */
/*   Updated: 2019/06/15 16:20:53 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printenv_blt(char **av, t_list *lst)
{
	t_list	*tmp;

	if (*av == NULL)
		lstprint(lst);
	else
	{
		while (*av != NULL)
		{
			tmp = find_env(*av++, lst);
			ft_putendl(((t_env*)(tmp->content))->all);
		}
	}
}