/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format_ls2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshevchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 11:51:14 by tshevchu          #+#    #+#             */
/*   Updated: 2017/11/01 11:51:28 by tshevchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_intlen(long long int nb)
{
	int i;

	i = 1;
	while (nb >= 10)
	{
		i++;
		nb = nb / 10;
	}
	return (i);
}

void	record_width(t_ls *ls, t_addit *addit)
{
	t_ls *temp;

	temp = ls;
	addit->width[0] = ft_intlen(temp->link);
	addit->width[1] = ft_intlen(temp->size);
	addit->width[2] = (int)ft_strlen(getpwuid(temp->uid)->pw_name);
	addit->width[3] = (int)ft_strlen(getgrgid(temp->gid)->gr_name);
	while (temp->next)
	{
		if (addit->width[0] < ft_intlen(temp->next->link))
			addit->width[0] = ft_intlen(temp->next->link);
		if (addit->width[1] < ft_intlen(temp->next->size))
			addit->width[1] = ft_intlen(temp->next->size);
		if (addit->width[2] < (int)ft_strlen(getpwuid(temp->next->uid)->
				pw_name))
			addit->width[2] = (int)ft_strlen(getpwuid(temp->next->uid)->
					pw_name);
		if (addit->width[3] < (int)ft_strlen(getgrgid(temp->next->gid)->
				gr_name))
			addit->width[3] = (int)ft_strlen(getgrgid(temp->next->gid)->
					gr_name);
		temp = temp->next;
	}
}

int		find_abs(int nb)
{
	if (nb < 0)
		return (nb * -1);
	else
		return (nb);
}

void	record_time(t_ls *ls, char *temp_day, char *temp_mon, char *temp_hour)
{
	char *temp_time;
	t_ls *temp;

	temp = ls;
	temp_time = ft_strjoin(temp_mon, temp_day);
	ft_strdel(&temp_day);
	ft_strdel(&temp_mon);
	temp->time = ft_strjoin(temp_time, temp_hour);
	ft_strdel(&temp_time);
	ft_strdel(&temp_hour);
}

void	choose_time(t_ls *ls, time_t time_m, t_addit *addit)
{
	char *temp_time;
	char *temp_mon;
	char *temp_day;
	char *temp_hour;
	char **split;

	temp_time = ft_strdup(ctime(&time_m));
	split = ft_strsplit(temp_time, ' ');
	temp_mon = ft_strsub(temp_time, 4, 4);
	temp_day = ft_strsub(temp_time, 8, 3);
	if (addit->ct == 1)
		temp_hour = ft_strsub(temp_time, 11, 13);
	else if (find_abs((int)(time(NULL) - time_m)) < HALF)
		temp_hour = ft_strsub(temp_time, 11, 5);
	else
	{
		temp_hour = ft_strdup(split[4]);
		free_double_arr(split);
		split = ft_strsplit(temp_hour, '\n');
		ft_strdel(&temp_hour);
		temp_hour = ft_strjoin(" ", split[0]);
	}
	free_double_arr(split);
	ft_strdel(&temp_time);
	record_time(ls, temp_day, temp_mon, temp_hour);
}
