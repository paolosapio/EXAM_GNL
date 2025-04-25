#ifndef TEST_H
# define TEST_H

/* STRUCT */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	int				sticker;
}	t_list;

#endif