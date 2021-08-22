/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 17:18:29 by ensebast          #+#    #+#             */
/*   Updated: 2021/08/22 13:36:36 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_last(t_list *node, int a_read)
{
	int	i;

	if (a_read == 0)
		return (1);
	i = 0;
	while (i < a_read)
	{
		if ((node -> buff_c)[i] == '\n' || (node -> buff_c)[i] == 0)
			return (1);
		i += 1;
	}
	return (0);
}

long	read_and_copy(t_list *node, int fd)
{
	int		read_code;

	read_code = read(fd, node -> buff_c, BUFFER_SIZE);
	if (read_code == -1)
		node -> flag = -1;
	else if (read_code == 0 || check_last(node,  read_code))
		node -> flag = 1;
	else
		node -> flag = 0;
	if (read_code != -1)
	{
		(node -> buff_c)[read_code] = 0;
		return (read_code);
	}
	return (-1);
}

//Create nodes
t_list	*create_node(int fd)
{
	t_list		*node;

	if ((node = malloc(sizeof(t_list))) == 0)
		return (0);
	if ((node -> buff_c = malloc(BUFFER_SIZE + 1)) == 0)
	{
		free(node);
		return (0);
	}
	if ((node -> len = read_and_copy(node, fd)) == -1)
	{
		free(node);
		free(node -> buff_c);
		return (0);
	}
	node -> curr_index = 0;
	node -> next = 0;
	node -> fd = fd;
	return (node);
}

//Add nodes to the tail of the list
t_list	*add_nodes(t_list *node, int fd)
{
	t_list	*new_node;

	while (node -> flag != 1
			|| (node -> flag == 1 && node -> curr_index > 0))
	{
		if (node -> flag == -1)
			return (0);
		new_node = create_node(fd);
		if (new_node == 0)
			return (0);
		node -> next = new_node;
		node = node -> next;
	}
	return (node);
}

t_list	*free_node(t_list *node)
{
	t_list	*tmp;

	free(node -> buff_c);
	tmp = node;
	node = node -> next;
	free(tmp);
	return (node);
}
