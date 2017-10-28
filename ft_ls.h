#ifndef FT_LS_FT_LS_H
# define FT_LS_FT_LS_H

# include <dirent.h>
# include "libft/include/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>

# define HALF 15778463

# include <stdio.h> //DELETE /////////

typedef struct	dirent	t_dir;

typedef struct		s_addit
{
	int				ac_g;
	int				l;
	int 			cr;
	int 			r;
	int 			a;
	int 			t;
	int 			flag_dir;
	int 			flag_file;
	blkcnt_t 		total;
}					t_addit;

typedef struct		s_ls
{
	char			*name;
	char			*name_d;
	mode_t			mode;
	off_t			size;
	nlink_t			link;
	blkcnt_t		block;
	uid_t			uid;
	gid_t			gid;
	time_t			m_time;
	char			*perm;
	char			*time;
	struct s_ls		*next;
}					t_ls;

typedef struct		s_all
{
	char			*name_dir;
	struct s_all	*next;
	t_ls			*ls;
}					t_all;




void	ft_ls_clear(t_ls **begin_list);

void	ft_list_push_back(t_ls **begin_list, char *data);
void		sorting(t_ls **sort);
void		sorting_time(t_ls **ls, char *data1);

void	ft_list_reverse(t_ls **begin_list);
int		check_flags(int ac, char **av, t_addit *addit);

void	record_permission(t_ls *ls, mode_t mode);
void	record_time(t_ls *ls, time_t time_m);
void	record_link(t_ls *ls);
void	record_time_year(t_ls *ls);

void	count_total(t_ls *ls, t_addit *addit);

t_all		*ft_create_dir(char *data, char *data2);
void	ft_dir_push_back(t_all **begin_list, char *data, char *data2);


t_addit		*init_addit(int ac);
void	clean_list(t_all **all);



#endif
