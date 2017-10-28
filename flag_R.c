#include "ft_ls.h"

t_all		*ft_create_dir(char *data, char *data2)
{
	t_all *new_elem;
	char *temp;

	temp = NULL;
	new_elem = malloc(sizeof(t_all));
	if (new_elem)
	{
		if (data != NULL)
		{
			temp = ft_strjoin(data, "/");
			new_elem->name_dir = ft_strjoin(temp, data2);
			ft_strdel(&temp);
		}
		else
			new_elem->name_dir = ft_strdup(data2);
		new_elem->next = NULL;
		new_elem->ls = NULL;
	}
	return (new_elem);
}

void	ft_dir_push_back(t_all **begin_list, char *data, char *data2)
{
	t_all *new_last_elem;
	t_all *last;

	last = *begin_list;
	new_last_elem = ft_create_dir(data, data2);
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