/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshevchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 11:55:31 by tshevchu          #+#    #+#             */
/*   Updated: 2017/11/01 11:57:04 by tshevchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	do_sorting_bysize(t_ls **ls)
{
	t_ls	*curr;
	t_ls	*next;

	curr = *ls;
	while (curr)
	{
		next = curr->next;
		while (next)
		{
			sorting_identical_size(curr, next);
			next = next->next;
		}
		curr = curr->next;
	}
}

void	sorting_bysize(t_ls **ls, char *data1)
{
	char		*temp_d;
	char		*dir;
	t_ls		*temp;
	struct stat	st;

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
		temp->size = st.st_size;
		temp = temp->next;
		ft_strdel(&dir);
	}
	do_sorting_bysize(ls);
}

void	do_sorting_bytime(t_ls **ls)
{
	t_ls	*curr;
	t_ls	*next;

	curr = *ls;
	while (curr)
	{
		next = curr->next;
		while (next)
		{
			sorting_identical_time(curr, next);
			next = next->next;
		}
		curr = curr->next;
	}
}

void	sorting_bytime(t_ls **ls, char *data1)
{
	char		*temp_d;
	char		*dir;
	t_ls		*temp;
	struct stat	st;

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
		temp->m_time = st.st_mtimespec.tv_sec;
		temp = temp->next;
		ft_strdel(&dir);
	}
	do_sorting_bytime(ls);
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
