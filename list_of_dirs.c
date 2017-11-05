/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_of_dirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshevchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 11:49:51 by tshevchu          #+#    #+#             */
/*   Updated: 2017/11/01 19:25:44 by tshevchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <CoreAudio/CoreAudio.h>
#include "ft_ls.h"

void		permission_denied(char *path, t_all **all, t_addit *addit)
{
	char		**split;
	struct stat	st;
	int			i;

	split = NULL;
	i = 0;
	lstat(path, &st);
	if (S_ISDIR(st.st_mode) || addit->err == 1)
	{
		split = ft_strsplit(path, '/');
		while (split[i + 1])
			i++;
		if ((*all != NULL || addit->flag_file == 1))
			ft_printf("\n");
		print_root_perm(path, addit);
		ft_printf("ls: %s: Permission denied\n", split[i]);
		free_double_arr(split);
		if (*all == NULL)
			addit->err = 1;
		else
			addit->err = 0;
	}
}

void		start_check_dir(char *av, t_all **all, char *prev_dir,
t_addit *addit)
{
	DIR		*dir;
	char	*path;
	char	*temp_path;

	if (prev_dir != NULL)
	{
		temp_path = ft_strjoin(prev_dir, "/");
		path = ft_strjoin(temp_path, av);
		ft_strdel(&temp_path);
	}
	else
		path = ft_strdup(av);
	if ((dir = opendir(path)) == NULL)
	{
		permission_denied(path, all, addit);
		ft_strdel(&path);
	}
	else
	{
		if (*all != NULL || addit->flag_file == 1)
			ft_printf("\n");
		ft_dir_push_back(all, prev_dir, av);
		do_ls(dir, path, all, addit);
	}
}

t_all		*ft_create_dir(char *data, char *data2)
{
	t_all	*new_elem;
	char	*temp;

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

void		ft_dir_push_back(t_all **begin_list, char *data, char *data2)
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
