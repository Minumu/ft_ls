/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshevchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 11:54:39 by tshevchu          #+#    #+#             */
/*   Updated: 2017/11/01 19:25:15 by tshevchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_l(t_ls *temp, t_addit *addit)
{
	ft_printf("%s  ", temp->perm);
	ft_printf("%*d ", addit->width[0], temp->link);
	ft_printf("%*-s  ", addit->width[2], getpwuid(temp->uid)->pw_name);
	ft_printf("%*-s  ", addit->width[3], getgrgid(temp->gid)->gr_name);
	ft_printf("%*lli ", addit->width[1], temp->size);
	ft_printf("%s ", temp->time);
}

void	print_ls(t_ls *ls, char *name_dir, t_addit *addit)
{
	t_ls *temp;

	temp = ls;
	if (addit->l == 1 && ls != NULL)
		record_width(ls, addit);
	if (addit->flag_dir != 0)
		print_root(name_dir);
	if (addit->l == 1 && ls != NULL && name_dir != NULL)
	{
		count_total(ls, addit);
		ft_printf("total %lli\n", addit->total);
	}
	while (temp)
	{
		addit->flag_dir = 1;
		if (addit->l == 1)
			print_l(temp, addit);
		if (temp->time != NULL)
			ft_strdel(&temp->time);
		if (temp->perm != NULL)
			ft_strdel(&temp->perm);
		ft_printf("%s\n", temp->name);
		temp = temp->next;
	}
}

void	flag_cr(t_ls *ls_temp, t_addit *addit, t_all **all, t_all *temp)
{
	if (addit->a == 1 && ft_strcmp(ls_temp->name, ".") != 0 &&
		ft_strcmp(ls_temp->name, "..") != 0 && !S_ISLNK(ls_temp->mode))
		start_check_dir(ls_temp->name, all, temp->name_dir, addit);
	else if (ls_temp->name[0] != '.' && !S_ISLNK(ls_temp->mode))
		start_check_dir(ls_temp->name, all, temp->name_dir, addit);
}

void	do_ls(DIR *dir, char *path, t_all **all, t_addit *addit)
{
	t_all	*temp;
	t_ls	*ls_temp;

	temp = *all;
	while (temp->next)
		temp = temp->next;
	temp->ls = begin_ls(dir, path, addit);
	ls_temp = temp->ls;
	closedir(dir);
	if (addit->err == 1)
		permission_denied(ls_temp->name_d, all, addit);
	else
	{
		print_ls(temp->ls, temp->name_dir, addit);
		if (addit->cr == 1)
		{
			while (ls_temp)
			{
				flag_cr(ls_temp, addit, all, temp);
				ls_temp = ls_temp->next;
			}
			clean_list(all);
		}
	}
	ft_strdel(&path);
}

int		main(int ac, char **av)
{
	int		i;
	t_all	*all;
	t_addit	*addit;
	t_ls	*avc;
	t_ls	*temp;

	avc = NULL;
	all = NULL;
	addit = init_addit(ac);
	if ((i = check_arguments(addit, av, &avc)) == -1)
		return (1);
	temp = avc;
	while (temp)
	{
		if (av[i + 1] && i != 0)
			addit->flag_dir = 1;
		start_check_dir(temp->name, &all, NULL, addit);
		temp = temp->next;
	}
	free(addit);
	return (0);
}
