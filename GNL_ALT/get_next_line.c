/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 16:58:01 by ensebast          #+#    #+#             */
/*   Updated: 2021/08/23 12:28:43 by ensebast         ###   ########.br       */
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
	res = copy_and_free(result, &head, fd);
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
char	*copy_and_free(char *line, t_list **head, int fd)
{
	int		k;
	t_list	*prev;

	k = 0;
	prev = 0;
	while ((*head))
	{
		if ((*head) -> fd == fd)
		{
			line[k] = (*head) -> buff_c;
			k += 1;
			*head = free_node(prev, *head);
			if (k > 0 && line[k - 1] == '\n')
				break ;
		}
		else if ((*head) -> next != 0)
		{
			prev = (*head);
			(*head) = (*head) -> next;
		}
	}
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
