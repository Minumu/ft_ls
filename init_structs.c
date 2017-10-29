#include "ft_ls.h"

t_addit		*init_addit(int ac)
{
	t_addit *addit;

	addit = malloc(sizeof(t_addit));
	addit->ac_g = ac;
	addit->l = 0;
	addit->r = 0;
	addit->a = 0;
	addit->cr = 0;
	addit->t = 0;
	addit->flag_dir = 0;
	addit->flag_file = 0;
	addit->total = 0;
	return (addit);
}

void		ft_ls_clear(t_ls **begin_list)
{
	t_ls *current;
	t_ls *next;

	current = *begin_list;
	while (current != NULL)
	{
		ft_strdel(&current->name_d);
		ft_strdel(&current->name);
		next = current->next;
		free(current);
		current = next;
	}
	*begin_list = NULL;
}

void		clean_list(t_all **all)
{
	t_all *temp;
	t_all *temp1;

	temp = *all;
	if (temp->next != NULL)
	{
		while (temp->next->next)
			temp = temp->next;
		temp1 = temp;
		temp = temp->next;
		temp1->next = NULL;
		ft_strdel(&temp->name_dir);
		ft_ls_clear(&temp->ls);
		free(temp);
	}
}

void			free_double_arr(char **arr)
{
	int i;

	i = 0;
	if (arr == NULL)
		return ;
	else
	{
		while (arr[i])
		{
			ft_strdel(&arr[i]);
			i++;
		}
		free(arr);
	}
}
