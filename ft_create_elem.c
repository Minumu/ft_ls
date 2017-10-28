#include "ft_ls.h"

void		do_sorting_time(t_ls **ls)
{
	t_ls	*curr;
	t_ls	*next;
	char	*temp;
	time_t	temp_t;

	curr = *ls;
	while (curr)
	{
		next = curr->next;
		while (next)
		{
			if (curr->m_time < next->m_time)
			{
				temp_t = curr->m_time;
				curr->m_time = next->m_time;
				next->m_time = temp_t;
				temp = curr->name;
				curr->name = next->name;
				next->name = temp;
			}
			next = next->next;
		}
		curr = curr->next;
	}
}

void		sorting_time(t_ls **ls, char *data1)
{
	char *temp_d;
	char *dir;
	t_ls *temp;
	struct stat st;

	temp = *ls;
	while (temp)
	{
		temp_d = ft_strjoin(data1, "/");
		dir = ft_strjoin(temp_d, temp->name);
		ft_strdel(&temp_d);
		lstat(dir, &st);
		temp->m_time = st.st_mtime;
		temp = temp->next;
		ft_strdel(&dir);
	}
	do_sorting_time(ls);
}

void		sorting(t_ls **sort)
{
	t_ls	*curr;
	t_ls	*next;
	char	*temp;

	curr = *sort;
	while (curr)
	{
		next = curr->next;
		while (next)
		{
			if (ft_strcmp(curr->name, next->name) > 0)
			{
				temp = curr->name;
				curr->name = next->name;
				next->name = temp;
			}
			next = next->next;
		}
		curr = curr->next;
	}
}

t_ls		*ft_create_elem(char *data)
{
	t_ls *new_elem;
	char *temp;

	new_elem = malloc(sizeof(t_ls));
	if (new_elem)
	{
		new_elem->name = ft_strdup(data);
//		new_elem->block = 0; //st.st_blocks;
//		new_elem->link = 0; //st.st_nlink;
//		new_elem->mode = 0;//st.st_mode;
//		new_elem->size = 0;//st.st_size;
//		new_elem->uid = 0;//st.st_uid;
//		new_elem->gid = 0;//st.st_gid;
//		record_permission(new_elem, st.st_mode);
//		record_time(new_elem, st.st_mtime);
//		if (S_ISLNK(new_elem->mode) && addit->l == 1)
//			record_link(new_elem);
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

void	ft_list_reverse(t_ls **begin_list)
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