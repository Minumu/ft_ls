#include "ft_ls.h"

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
	temp_time = ft_strjoin(temp_day, temp_mon);
	ft_strdel(&temp_day);
	ft_strdel(&temp_mon);
	temp->time = ft_strjoin(temp_time, temp_hour);
	ft_strdel(&temp_time);
	ft_strdel(&temp_hour);
}

void	choose_time(t_ls *ls, time_t time_m)
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
	if (find_abs((int)(time(NULL) - time_m)) < HALF)
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
