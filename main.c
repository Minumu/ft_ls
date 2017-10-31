#include "ft_ls.h"

int 	ft_intlen(long long int nb)
{
	int i;

	i = 1;
	while (nb >= 10)
	{
		i++;
		nb = nb / 10;
	}
	return (i);
}

void	print_ls(t_ls *ls, char *name_dir, t_addit *addit)
{
	t_ls *temp;

	temp = ls;
	if (addit->flag_dir != 0)
		ft_printf("%s:\n", name_dir);
	if (addit->l == 1 && ls != NULL && name_dir != NULL)
	{
		count_total(ls, addit);
		ft_printf("total %lli\n", addit->total);
	}
	while (temp)
	{
		addit->flag_dir = 1;
		if (addit->l == 1)
		{
			ft_printf("%s  ", temp->perm);
			ft_printf("%*d ", addit->width[0], temp->link);
			ft_printf("%*-s  ", addit->width[2], getpwuid(temp->uid)->pw_name);
			ft_printf("%*-s  ", addit->width[3], getgrgid(temp->gid)->gr_name);
			ft_printf("%*lli ", addit->width[1], temp->size);
			ft_printf("%s ", temp->time);
		}
		if (temp->time != NULL)
			ft_strdel(&temp->time);
		if (temp->perm != NULL)
			ft_strdel(&temp->perm);
		ft_printf("%s\n", temp->name);
		temp = temp->next;
	}
}

void	record_width(t_ls *ls, t_addit *addit)
{
	t_ls *temp;

	temp = ls;
	addit->width[0] = ft_intlen(temp->link);
	addit->width[1] = ft_intlen(temp->size);
	addit->width[2] = (int)ft_strlen(getpwuid(temp->uid)->pw_name);
	addit->width[3] = (int)ft_strlen(getgrgid(temp->gid)->gr_name);
	while (temp->next)
	{
		if (addit->width[0] < ft_intlen(temp->next->link))
			addit->width[0] = ft_intlen(temp->next->link);
		if (addit->width[1] < ft_intlen(temp->next->size))
			addit->width[1] = ft_intlen(temp->next->size);
		if (addit->width[2] < ft_strlen(getpwuid(temp->next->uid)->pw_name))
			addit->width[2] = (int)ft_strlen(getpwuid(temp->next->uid)->pw_name);
		if (addit->width[3] < ft_strlen(getgrgid(temp->next->gid)->gr_name))
			addit->width[3] = (int)ft_strlen(getgrgid(temp->next->gid)->gr_name);
		temp = temp->next;
	}
}

void	start_print(char *name_dir, t_ls *ls, t_addit *addit)
{
	if (addit->l == 1 && ls != NULL)
		record_width(ls, addit);
	print_ls(ls, name_dir, addit);

//			if (a)
//				;
//			if (r)
//				;

//	else
//		print_normal(ls);
}

void	do_ls(DIR *dir, char *path, t_all **all, t_addit *addit)
{
	t_all *temp;
	t_ls	*ls_temp;

	temp = *all;
	while (temp->next)
		temp = temp->next;
	temp->ls = begin_ls(dir, path, addit);
	ls_temp = temp->ls;
	closedir(dir);
	start_print(temp->name_dir, temp->ls, addit);
	if (addit->cr == 1)
	{
		while (ls_temp)
		{
			if (addit->a == 1 && ft_strcmp(ls_temp->name, ".") != 0 &&
					ft_strcmp(ls_temp->name, "..") != 0)
				start_check_dir(ls_temp->name, all, temp->name_dir, addit);
			else if (ls_temp->name[0] != '.' && !S_ISLNK(ls_temp->mode))
				start_check_dir(ls_temp->name, all, temp->name_dir, addit);
			ls_temp = ls_temp->next;
		}
		clean_list(all);
	}
	ft_strdel(&path);
}

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
	struct stat st;
	t_ls *temp;

	temp = avc;
	while (temp)
	{
		if (lstat(temp->name, &st) == -1)
			ft_printf("ls: %s: No such file or directory\n", temp->name);
		temp = temp->next;
	}
}

void	record_files(t_ls *avc, int i, t_ls **ls, t_addit *addit)
{
	struct stat st;
	DIR *dir;
	t_ls *temp;

	temp = avc;
	while (temp)
	{
		dir = opendir(temp->name);
		if (dir == NULL && lstat(temp->name, &st) == 0 && !(S_ISDIR(st.st_mode)))
			ft_list_push_back(ls, temp->name);
		i++;
		if (dir != NULL)
			closedir(dir);
		temp = temp->next;
	}
	if (*ls != NULL)
	{
		if (addit->t == 1)
			sorting_bytime(ls, NULL);
		if (addit->r == 1)
			ft_list_reverse(ls);
		record_stat(*ls, addit, NULL, st);
		start_print(NULL, *ls, addit);
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
	if (addit->t == 1)
		sorting_bytime(avc, NULL);
}

int		main(int ac, char **av)
{
	int		i;
	t_all	*all;
	t_addit	*addit;
	t_ls *ls;
	t_ls *avc;
	t_ls *temp;

	all = NULL;
	ls = NULL;
	avc = NULL;
	addit = init_addit(ac);
	if ((i = check_flags(ac, av, addit, 1)) == -1)
		return (1);
	if (check_empty_av(av, i) == 0)
		return (1);
	if (i == 0)
	{
		addit->ac_g = 1;
		av[i] = ".";
	}
	sorting_av(av, i, &avc, addit);
	printf_noexist(avc);
	record_files(avc, i, &ls, addit);
	if (addit->r == 1)
		ft_list_reverse(&avc);
	temp = avc;
	while (temp)
	{
		if (av[i + 1] && i != 0)
			addit->flag_dir = 1;
		start_check_dir(temp->name, &all, NULL, addit);
		temp = temp->next;
	}
	free(addit);
//	while (1);
	return (0);
}