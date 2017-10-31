#include "ft_ls.h"

void	record_stat(t_ls *ls, t_addit *addit, char *data1, struct stat st)
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
		lstat(temp->name_d, &st);
		temp->block = st.st_blocks;
		temp->link = st.st_nlink;
		temp->mode = st.st_mode;
		temp->size = st.st_size;
		temp->uid = st.st_uid;
		temp->gid = st.st_gid;
		record_permission(temp, st.st_mode);
		choose_time(temp, st.st_mtime);
		if (S_ISLNK(temp->mode) && addit->l == 1)
			record_link(temp);
		temp = temp->next;
	}
}

t_ls	*begin_ls(DIR *dir, char *name_dir, t_addit *addit)
{
	t_dir *sd;
	t_ls *ls;
	struct stat st;

	ls = NULL;
	while ((sd = readdir(dir)) != NULL)
	{
		if (addit->a == 1)
			ft_list_push_back(&ls, sd->d_name);
		else if (sd->d_name[0] != '.')
			ft_list_push_back(&ls, sd->d_name);
	}
	sorting(&ls);
	if (addit->t == 1)
		sorting_bytime(&ls, name_dir);
	if (addit->r == 1)
		ft_list_reverse(&ls);
	record_stat(ls, addit, name_dir, st);
	return (ls);
}


t_ls		*ft_create_elem(char *data)
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

void		ft_list_push_back(t_ls **begin_list, char *data)
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

void		ft_list_reverse(t_ls **begin_list)
{
	t_ls *current;
	t_ls *previous;
	t_ls *next;

	current = *begin_list;
	previous = 0;
	while (current)
	{
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}
	*begin_list = previous;
}