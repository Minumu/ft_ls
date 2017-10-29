#include "ft_ls.h"

void	print_l(t_ls *ls, char *name_dir, t_addit *addit)
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
		if (temp->name[0] != '.')
		{
			if (addit->l == 1)
			{
				ft_printf("%s  ", temp->perm);
				ft_printf("%3d ", temp->link);
				ft_printf("%s ", getpwuid(temp->uid)->pw_name);
				ft_printf("%s ", getgrgid(temp->gid)->gr_name);
				ft_printf("%10lli ", temp->size);
				ft_printf("%s ", temp->time);
				ft_strdel(&temp->time);
				ft_strdel(&temp->perm);
			}
			ft_printf("%s\n", temp->name);
		}
		temp = temp->next;
	}
}

void	start_print(char *name_dir, t_ls *ls, t_addit *addit)
{
	print_l(ls, name_dir, addit);

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
			if (ls_temp->name[0] != '.' && !S_ISLNK(ls_temp->mode))
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

void	printf_noexist(char **av, int i, t_addit *addit)
{
	struct stat st;

	while (i < addit->ac_g)
	{
		if (lstat(av[i], &st) == -1)
			ft_printf("ls: %s: No such file or directory\n", av[i]);
		i++;
	}
}

void	record_files(char **av, int i, int ac, t_ls **ls, t_addit *addit)
{
	struct stat st;
	DIR *dir;

	while (i < ac)
	{
		dir = opendir(av[i]);
		if (dir == NULL && lstat(av[i], &st) == 0 && !(S_ISDIR(st.st_mode)))
			ft_list_push_back(ls, av[i]);
		i++;
		if (dir != NULL)
			closedir(dir);
	}
	if (*ls != NULL)
	{
		if (addit->t == 1)
			sorting_bytime(ls, NULL);
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
		return (0);
	if (check_empty_av(av, i) == 0)
		return (0);
	if (i == 0)
	{
		addit->ac_g = 1;
		av[i] = ".";
	}
	sorting_av(av, i, &avc, addit);
	printf_noexist(av, i, addit);
	record_files(av, i, ac, &ls, addit);
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