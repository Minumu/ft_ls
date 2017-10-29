#include "ft_ls.h"

void	do_sorting_time(t_ls **ls)
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

void	sorting_time(t_ls **ls, char *data1)
{
	char *temp_d;
	char *dir;
	t_ls *temp;
	struct stat st;

	temp = *ls;
	while (temp)
	{
		if (data1 != NULL)
			temp_d = ft_strjoin(data1, "/");
		else
			temp_d = ft_strdup("");
		dir = ft_strjoin(temp_d, temp->name);
		ft_strdel(&temp_d);
		lstat(dir, &st);
		temp->m_time = st.st_mtime;
		temp = temp->next;
		ft_strdel(&dir);
	}
	do_sorting_time(ls);
}

void	sorting(t_ls **sort)
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