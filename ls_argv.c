/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_argv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshevchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 11:51:39 by tshevchu          #+#    #+#             */
/*   Updated: 2017/11/01 11:53:41 by tshevchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		check_empty_av(char **av, int i)
{
	int iter;

	iter = i;
	while (av[iter])
	{
		if (av[iter][0] == '\0')
		{
			ft_printf("ls: fts_open: No such file or directory\n");
			return (0);
		}
		iter++;
	}
	return (1);
}

void	printf_noexist(t_ls *avc)
{
	struct stat	st;
	t_ls		*temp;

	temp = avc;
	while (temp)
	{
		if (lstat(temp->name, &st) == -1)
			ft_printf("ls: %s: No such file or directory\n", temp->name);
		temp = temp->next;
	}
}

void	record_files(t_ls *avc, t_ls **ls, t_addit *addit)
{
	struct stat	st;
	DIR			*dir;
	t_ls		*temp;

	temp = avc;
	while (temp)
	{
		dir = opendir(temp->name);
		if (dir == NULL && lstat(temp->name, &st) == 0 &&
			!(S_ISDIR(st.st_mode)))
			ft_list_push_back(ls, temp->name);
		if (dir != NULL)
			closedir(dir);
		temp = temp->next;
	}
	if (*ls != NULL)
	{
		record_stat(*ls, addit, NULL);
		print_ls(*ls, NULL, addit);
		addit->flag_file = 1;
	}
}

void	sorting_av(char **av, int i, t_ls **avc, t_addit *addit)
{
	while (i < addit->ac_g)
	{
		ft_list_push_back(avc, av[i]);
		i++;
	}
	sorting(avc);
	printf_noexist(*avc);
	if (addit->cs)
		sorting_bysize(avc, NULL);
	else if (addit->t == 1)
		sorting_bytime(avc, NULL);
	if (addit->r == 1)
		ft_list_reverse(avc);
}

int		check_arguments(t_addit *addit, char **av, t_ls **avc)
{
	int			i;
	t_ls		*ls;

	ls = NULL;
	if ((i = check_flags(addit->ac_g, av, addit, 1)) == -1)
		return (-1);
	if (check_empty_av(av, i) == 0)
		return (-1);
	if (i == 0)
	{
		addit->ac_g = 1;
		av[i] = ".";
	}
	sorting_av(av, i, avc, addit);
	record_files(*avc, &ls, addit);
	return (i);
}
