/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_identical.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshevchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:05:37 by tshevchu          #+#    #+#             */
/*   Updated: 2017/11/01 19:25:30 by tshevchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sorting_identical_time(t_ls *curr, t_ls *next)
{
	time_t	temp_t;
	char	*temp_name;

	if (curr->m_time == next->m_time)
	{
		if (ft_strcmp(curr->name, next->name) > 0)
		{
			temp_name = curr->name;
			curr->name = next->name;
			next->name = temp_name;
		}
	}
	else
	{
		if (curr->m_time < next->m_time)
		{
			temp_t = curr->m_time;
			curr->m_time = next->m_time;
			next->m_time = temp_t;
			temp_name = curr->name;
			curr->name = next->name;
			next->name = temp_name;
		}
	}
}

void	sorting_identical_size(t_ls *curr, t_ls *next)
{
	off_t	siz;
	char	*temp_name;

	if (curr->size == next->size)
	{
		if (ft_strcmp(curr->name, next->name) > 0)
		{
			temp_name = curr->name;
			curr->name = next->name;
			next->name = temp_name;
		}
	}
	else
	{
		if (curr->size < next->size)
		{
			siz = curr->size;
			curr->size = next->size;
			next->size = siz;
			temp_name = curr->name;
			curr->name = next->name;
			next->name = temp_name;
		}
	}
}

void	print_root_perm(char *path, t_addit *addit)
{
	int j;

	j = 0;
	if (path[0] == '/' && path[1] == '/' && path[2] != '/')
	{
		while (path[++j])
			ft_printf("%c", path[j]);
		ft_printf(":\n");
	}
	else if (addit->flag_file == 1 || addit->flag_dir == 1)
		ft_printf("%s:\n", path);
}

void	print_root(char *name_dir)
{
	int i;

	i = 0;
	if (name_dir[0] == '/' && name_dir[1] == '/' && name_dir[2] != '/')
	{
		while (name_dir[++i])
			ft_printf("%c", name_dir[i]);
		ft_printf(":\n");
	}
	else
		ft_printf("%s:\n", name_dir);
}
