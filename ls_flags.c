#include "ft_ls.h"

void	record_link(t_ls *ls)
{
	t_ls *temp;
	char *temp_link;
	char *temp_name;
	ssize_t r;

	temp = ls;
	temp_link = (char*)malloc(sizeof(char) * (size_t)(ls->size + 1));
	r = readlink(temp->name_d, temp_link, (size_t)(ls->size + 1));
	if (r == -1 || r > (size_t)(ls->size + 1))
		return ;
	temp_link[r] = '\0';
	temp_name = ft_strjoin(temp->name, " -> ");
	ft_strdel(&temp->name);
	temp->name = ft_strjoin(temp_name, temp_link);
	ft_strdel(&temp_name);
	ft_strdel(&temp_link);
}

void	count_total(t_ls *ls, t_addit *addit)
{
	t_ls *temp;

	temp = ls;
	addit->total = 0;
	while (temp)
	{
		if (temp->name[0] != '.')
			addit->total += temp->block;
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

void	record_time(t_ls *ls, time_t time_m)
{
	t_ls *temp;
	char *temp_time;
	char *temp_mon;
	char *temp_day;
	char *temp_hour;

	temp = ls;
	temp_time = ft_strdup(ctime(&time_m));
	if (find_abs((int)(time(NULL) - time_m)) < HALF)
	{
		temp_mon = ft_strsub(temp_time, 4, 4);
		temp_day = ft_strsub(temp_time, 8, 3);
		temp_hour = ft_strsub(temp_time, 11, 5);
	}
	else
	{
		temp_mon = ft_strsub(temp_time, 4, 4);
		temp_day = ft_strsub(temp_time, 8, 3);
		temp_hour = ft_strsub(temp_time, 19, 5);
	}
		ft_strdel(&temp_time);
		temp_time = ft_strjoin(temp_day, temp_mon);
		ft_strdel(&temp_day);
		ft_strdel(&temp_mon);
		temp->time = ft_strjoin(temp_time, temp_hour);
		ft_strdel(&temp_time);
		ft_strdel(&temp_hour);
}

char	check_isuid(mode_t mode)
{
	if (S_IXUSR & mode)
		return ((char)(mode & S_ISUID ? 's' : 'x'));
	else
		return ((char)(mode & S_ISUID ? 'S' : '-'));
}

char	check_isgid(mode_t mode)
{
	if (S_IXGRP & mode)
		return ((char)(mode & S_ISGID ? 's' : 'x'));
	else
		return ((char)(mode & S_ISGID ? 'S' : '-'));
}

char	check_isvtx(mode_t mode)
{
	if (S_IXOTH & mode)
		return ((char)(mode & S_ISVTX ? 't' : 'x'));
	else
		return ((char)(mode & S_ISVTX ? 'T' : '-'));
}

void	record_permission(t_ls *ls, mode_t mode)
{
	t_ls *temp;

	temp = ls;
	temp->perm = (char*)malloc(sizeof(char) * 11);
	temp->perm[0] = (char)(S_ISDIR(mode) ? 'd' : temp->perm[0]);
	temp->perm[0] = (char)(S_ISREG(mode) ? '-' : temp->perm[0]);
	temp->perm[0] = (char)(S_ISLNK(mode) ? 'l' : temp->perm[0]);
	temp->perm[0] = (char)(S_ISCHR(mode) ? 'c' : temp->perm[0]);
	temp->perm[0] = (char)(S_ISBLK(mode) ? 'b' : temp->perm[0]);
	temp->perm[0] = (char)(S_ISFIFO(mode) ? 'p' : temp->perm[0]);
	temp->perm[0] = (char)(S_ISSOCK(mode) ? 's' : temp->perm[0]);
	temp->perm[1] = (char)(mode & S_IRUSR ? 'r' : '-');
	temp->perm[2] = (char)(mode & S_IWUSR ? 'w' : '-');
	temp->perm[3] = check_isuid(mode);
	temp->perm[4] = (char)(mode & S_IRGRP ? 'r' : '-');
	temp->perm[5] = (char)(mode & S_IWGRP ? 'w' : '-');
	temp->perm[6] = check_isgid(mode);
	temp->perm[7] = (char)(mode & S_IROTH ? 'r' : '-');
	temp->perm[8] = (char)(mode & S_IWOTH ? 'w' : '-');
	temp->perm[9] = check_isvtx(mode);
	temp->perm[10] = '\0';
}

int		check_flags(int ac, char **av, t_addit *addit)
{
	int i;
	int j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		if (av[i][j] == '-' && av[i][j + 1] != '-')
		{
			j++;
			while (av[i][j])
			{
				if (av[i][j] == 'l')
					addit->l = 1;
				else if (av[i][j] == 'R')
					addit->cr = 1;
				else if (av[i][j] == 'a')
					addit->a = 1;
				else if (av[i][j] == 'r')
					addit->r = 1;
				else if (av[i][j] == 't')
					addit->t = 1;
				else
				{
					ft_printf("error\n");
					return (0);
				}
				j++;
			}
			i++;
		}
		else
			return (i);
	}
	return (0);
}