/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_blt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 10:57:51 by efischer          #+#    #+#             */
/*   Updated: 2019/07/23 13:12:57 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int		ft_check_arg(char *arg)
{
	size_t	i;

	i = 1;
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static void		ft_process_av(char **av, size_t *index, uint8_t *flags)
{
	while (av[*index] != NULL && av[*index][0] == '-')
	{
		if (ft_check_arg(av[*index]) == FALSE)
			return ;
		if (ft_strchr(av[*index], 'n') != NULL)
			*flags |= FLAG_N;
		(*index)++;
	}
}

static void		ft_print_arg(char **av, size_t i)
{
	char	*out;

	out = NULL;
	while (av[i] != NULL)
	{
		out = ft_join_free(out, av[i], 1);
		if (av[i + 1] != NULL)
			out = ft_join_free(out, " ", 1);
		i++;
	}
	if (ft_putstr(out) == FAILURE)
		ft_putendl_fd("minishell: echo: write error: Bad file descriptor", 2);
	ft_strdel(&out);
}

int				echo_blt(char **av, t_list **lst)
{
	uint8_t		flags;
	size_t		i;

	(void)lst;
	av++;
	i = 0;
	flags = 0;
	if (av != NULL)
	{
		ft_process_av(av, &i, &flags);
		ft_print_arg(av, i);
	}
	if ((flags & FLAG_N) == FALSE)
		ft_putchar('\n');
	return (SUCCESS);
}
