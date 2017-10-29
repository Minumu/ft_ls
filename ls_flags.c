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

int		record_flags(char **av, int i, int j, t_addit *addit)
{
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
			ft_printf("ls: illegal option -- %c\n"
			"usage: ls [-Ralrt] [file ...]\n", av[i][j]);
			return (-1);
		}
		j++;
	}
	return (1);
}

int		check_flags(int ac, char **av, t_addit *addit, int i)
{
	int j;

	while (++i < ac)
	{
		j = 0;
		if (av[i][j] == '-')
		{
			j++;
			if (av[i][j] == '\0')
				return (i);
			if (av[i][j] == '-' && av[i][j + 1] == '\0')
			{
				if (av[i + 1] == NULL)
					return (0);
				else
					return (i + 1);
			}
			if (record_flags(av, i, j, addit) == -1)
				return (-1);
		}
		else
			return (i);
	}
	return (0);
}