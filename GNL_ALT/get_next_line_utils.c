/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 17:18:29 by ensebast          #+#    #+#             */
/*   Updated: 2021/08/23 12:29:36 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*find_last(t_list *node)
{
	while (node -> next)
		node = node -> next;
	return (node);
}
t_list	*copy(t_list *node, int fd, char *buff_t, int flag_code[])
{
	t_list	*root;
	t_list	*tmp;

	root = node;
	while (buff_t[flag_code[2]] && flag_code[2] < flag_code[1])
	{
		flag_code[2] += 1;
		tmp = create_node(buff_t[flag_code[2] - 1], fd);
		if (tmp == 0)
		{
			free_all(node, fd);
			return (0);
		}
		node = find_last(node);
		node -> next = tmp;
	}
	node = root;
	return (root);
}

/*
 * flag_code [0] = flag
 * flag_code [1] = read_code
 * flag_code [2] = index
 */
t_list	*read_and_add(t_list *node, int fd)
{
	char	*tmp;
	int		flag_code[3];

	tmp = malloc(BUFFER_SIZE + 1);
	if (tmp == 0)
		 return (0);
	flag_code[0] = 1;
	while (flag_code[0])
	{
		flag_code[2] = 0;
		flag_code[1] = read(fd, tmp, BUFFER_SIZE);
		if (flag_code[1] == -1 || flag_code[1] == 0)
		{
			free(tmp);
			return (node);
		}
		if (node == 0)
			node = create_node(tmp[flag_code[2]++], fd);
		copy(node, fd, tmp, flag_code);
		if (flag_code[1] != BUFFER_SIZE)
			flag_code[0] = 0;
	}
	free(tmp);
	return (node);
}

//Create nodes
t_list	*create_node(char c, int fd)
{
	t_list		*node;

	if ((node = malloc(sizeof(t_list))) == 0)
		return (0);
	node -> buff_c = c;
	node -> next = 0;
	node -> fd = fd;
	return (node);
}

t_list	*free_node(t_list *prev, t_list *node)
{
	t_list	*tmp;

	tmp = node;
	if (!(prev))
	{
		node = node -> next;
		free(tmp);
		return (node);
	}
	else if (prev)
	{
		if (node -> next == 0)
		{
			prev -> next = 0;
			free(tmp);
			return (0);
		}
		prev -> next = node -> next;
		free(tmp);
		return (prev -> next);
	}
	return (0);
}
