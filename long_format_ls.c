#include "ft_ls.h"

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