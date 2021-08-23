/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 16:58:01 by ensebast          #+#    #+#             */
/*   Updated: 2021/08/23 18:09:56 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*get_next_line(int fd)
{
	char			*result;
	int				quant;
	char			*res;
	static t_list	*head;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (0);
	if (!(head = read_and_add(head, fd)))
	{
		free_all(head, fd);
		return (0);
	}
	quant = line_size(head, fd);
	result = malloc(quant + 1);
	res = copy_and_free(result, head, &head, fd);
	if (res[0] == '\0')
	{
		free(res);
		return (0);
	}
	return (res);
}

/*
 * Will copy the content of the node and free
 * up the memory
*/
char	*copy_and_free(char *line, t_list *node, t_list **head, int fd)
{
	int		k;
	t_list	*prev;
	t_list	*true_head;

	k = 0;
	prev = 0;
	true_head = 0;
	while (node)
	{
		if (node -> fd == fd)
		{
			line[k] = node -> buff_c;
			k += 1;
			node = free_node(prev, node);
			if (k > 0 && line[k - 1] == '\n')
				break ;
		}
		else
		{
			prev = node;
			node = node -> next;
			if (!(true_head) && prev)
				true_head = prev;
		}
	}
	if (true_head)
		(*head) = true_head;
	else
		(*head) = node;
	line[k] = '\0';
	return (line);
}

t_list	*free_all(t_list *node, int fd)
{
	t_list	*prev;

	prev = 0;
	while (node)
	{
		if (node -> fd == fd)
			node = free_node(prev, node);
		else
		{
			prev = node;
			node = node -> next;
		}
	}
	return (0);
}

int	line_size(t_list *head, int fd)
{
	int	i;

	i = 0;
	while (head)
	{
		if (head -> fd == fd)
			i += 1;
		if (head -> buff_c == '\n')
			break ;
		head = head -> next;
	}
	return (i);
}
