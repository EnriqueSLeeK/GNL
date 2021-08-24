/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 14:40:30 by ensebast          #+#    #+#             */
/*   Updated: 2021/08/24 02:35:50 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_link_lst
{
	int					fd;
	char				buff_c;
	struct s_link_lst	*next;
}	t_list;

char	*get_next_line(int fd);
t_list	*create_node(char c, int fd);
t_list	*read_and_add(char *tmp, t_list *node, int fd);
char	*copy_and_free(char *line, t_list *node, t_list **head, int fd);

//line utils
int		line_size(t_list *head, int fd);
t_list	*copy(t_list *node, int fd, char *buff_t, int flag[]);

//free utils
t_list	*free_node(t_list *prev, t_list *node);
t_list	*free_all(t_list *node, int fd);
t_list	*free_case(t_list *prev, t_list *node);
#endif
