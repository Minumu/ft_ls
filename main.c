#include "ft_ls.h"

void	record_stat(t_ls *ls, t_addit *addit, char *data1)
{
	struct stat st;
	t_ls *temp;
	char *temp_d;

	temp = ls;
	while (temp)
	{
		if (data1 != NULL)
			temp_d = ft_strjoin(data1, "/");
		else
			temp_d = ft_strdup("");
		temp->name_d = ft_strjoin(temp_d, temp->name);
		ft_strdel(&temp_d);
		lstat(temp->name_d, &st);
		temp->block = st.st_blocks;
		temp->link = st.st_nlink;
		temp->mode = st.st_mode;
		temp->size = st.st_size;
		temp->uid = st.st_uid;
		temp->gid = st.st_gid;
		record_permission(temp, st.st_mode);
		record_time(temp, st.st_mtime);
		if (S_ISLNK(temp->mode) && addit->l == 1)
			record_link(temp);
		temp = temp->next;
	}
}

void	print_l(t_ls *ls, char *name_dir, t_addit *addit)
{
	t_ls *temp;

	temp = ls;
	if (addit->flag_dir != 0)
		ft_printf("%s:\n", name_dir);
	if (addit->l == 1)
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

t_ls	*begin_ls(DIR *dir, char *name_dir, t_addit *addit)
{
	t_dir *sd;
	t_ls *ls;

	ls = NULL;
	while ((sd = readdir(dir)) != NULL)
	{
		if (sd->d_name[0] != '.')
			ft_list_push_back(&ls, sd->d_name);
	}
	if (addit->t == 1)
		sorting_time(&ls, name_dir);
	else
		sorting(&ls);
	record_stat(ls, addit, name_dir);
	return (ls);
}

void	do_shit(char *av, t_all **all, char *prev_dir, t_addit *addit)
{
	DIR *dir;
	t_all *temp;
	t_ls	*ls_temp;
	char 	*path;
	char *temp_path;

	if (prev_dir != NULL)
	{
		temp_path = ft_strjoin(prev_dir, "/");
		path = ft_strjoin(temp_path, av);
		ft_strdel(&temp_path);
	}
	else
		path = ft_strdup(av);
	dir = opendir(path);
	if (dir == NULL)
	{
		ft_strdel(&path);
		return ;
	}
	else
	{
		if (*all != NULL || addit->flag_file == 1)
			ft_printf("\n");
		ft_dir_push_back(all, prev_dir, av);
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
					do_shit(ls_temp->name, all, temp->name_dir, addit);
				ls_temp = ls_temp->next;
			}
			clean_list(all);
		}
		ft_strdel(&path);
	}
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

void	sort_av(char **av, int i, int  ac)
{
	int j;
	char *temp;

	while (i < ac)
	{
		j = i;
		while (j < ac)
		{
			if (ft_strcmp(av[i], av[j]) > 0)
			{
				temp = av[i];
				av[i] = av[j];
				av[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	printf_noexist(char **av, int i, int ac)
{
	struct stat st;

	while (i < ac)
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
		if (dir == NULL && lstat(av[i], &st) == 0)
			ft_list_push_back(ls, av[i]);
		i++;
		if (dir != NULL)
			closedir(dir);
	}
	if (*ls != NULL)
	{
		record_stat(*ls, addit, NULL);
		start_print(NULL, *ls, addit);
		addit->flag_file = 1;
	}
}

int		main(int ac, char **av)
{
	int		i;
	t_all	*all;
	t_addit	*addit;
	t_ls *ls;

	all = NULL;
	ls = NULL;
	addit = init_addit(ac);
	i = check_flags(ac, av, addit);
	if (check_empty_av(av, i) == 0)
		return (0);
	if (i == 0)
		av[i] = ".";
	sort_av(av, i, ac);
	printf_noexist(av, i, ac);
	record_files(av, i, ac, &ls, addit);
	while (i < ac)
	{
		if (av[i + 1])
			addit->flag_dir = 1;
		do_shit(av[i], &all, NULL, addit);
		i++;
	}
	free(addit);
	while (1);
	return (0);
}