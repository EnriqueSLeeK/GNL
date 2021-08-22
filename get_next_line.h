/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 14:40:30 by ensebast          #+#    #+#             */
/*   Updated: 2021/08/22 12:20:58 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

//########## flag codes ###########
//0 = it's not the last node
//1 = last node
//-1 = error, abort operation
typedef struct s_link_lst
{
	int					flag;
	int					fd;
	int					len;
	int					curr_index;
	char				*buff_c;
	struct s_link_lst	*next;
}	t_list;

//Data utils
int		line_size(t_list *head, int fd);

//String contruction utils
char	*build(int fd);
char	*get_next_line(int fd);
char	*copy_and_free(char *line, t_list **head);

//Node utils
t_list	*create_node(int fd);
t_list	*add_nodes(t_list *node, int fd);

//Free mem utils
t_list	*free_all(t_list *head, int fd);
t_list	*free_node(t_list *node);

#endif
