#include "ft_ls.h"

void	help_record_stat(t_ls *temp, t_addit *addit)
{
	struct stat st;

	lstat(temp->name_d, &st);
	temp->block = st.st_blocks;
	temp->link = st.st_nlink;
	temp->mode = st.st_mode;
	temp->size = st.st_size;
	temp->uid = st.st_uid;
	temp->gid = st.st_gid;
	record_permission(temp, st.st_mode);
	choose_time(temp, st.st_mtime, addit);
	if (S_ISLNK(temp->mode) && addit->l == 1)
		record_link(temp);
}

void	record_stat(t_ls *ls, t_addit *addit, char *data1)
{
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
		help_record_stat(temp, addit);
		temp = temp->next;
	}
}

t_ls	*begin_ls(DIR *dir, char *name_dir, t_addit *addit)
{
	t_dir *sd;
	t_ls *ls;

	ls = NULL;
	while ((sd = readdir(dir)) != NULL)
	{
		if (addit->a == 1)
			ft_list_push_back(&ls, sd->d_name);
		else if (sd->d_name[0] != '.')
			ft_list_push_back(&ls, sd->d_name);
	}
	sorting(&ls);
	if (addit->cs == 1)
		sorting_bysize(&ls, name_dir);
	else if (addit->t == 1)
		sorting_bytime(&ls, name_dir);
	if (addit->r == 1)
		ft_list_reverse(&ls);
	record_stat(ls, addit, name_dir);
	return (ls);
}

t_ls	*ft_create_elem(char *data)
{
	t_ls *new_elem;

	new_elem = malloc(sizeof(t_ls));
	if (new_elem)
	{
		new_elem->name = ft_strdup(data);
		new_elem->next = NULL;
	}
	return (new_elem);
}

void	ft_list_push_back(t_ls **begin_list, char *data)
{
	t_ls *new_last_elem;
	t_ls *last;

	last = *begin_list;
	new_last_elem = ft_create_elem(data);
	if (!last)
	{
		*begin_list = new_last_elem;
	}
	else if (new_last_elem)
	{
		while (last->next)
			last = last->next;
		last->next = new_last_elem;
	}
}