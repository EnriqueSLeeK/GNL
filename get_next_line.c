/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 16:58:01 by ensebast          #+#    #+#             */
/*   Updated: 2021/08/24 02:34:50 by ensebast         ###   ########.br       */
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
	head = read_and_add(malloc(BUFFER_SIZE + 1), head, fd);
	if (head == 0 )
		return (0);
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

int	get_and_free(t_list **node, t_list *prev, char *line, int *k)
{
	line[*k] = (*node)-> buff_c;
	*k += 1;
	*node = free_node(prev, *node);
	if (*k > 0 && line[*k - 1] == '\n')
		return (1);
	return (0);
}

void	adjust_pointer(t_list **prev, t_list **node, t_list **true_head)
{
	*prev = *node;
	*node = (*node)-> next;
	if (!(*true_head) && *prev)
		*true_head = *prev;
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
			if (get_and_free(&node, prev, line, &k))
				break ;
		}
		else
		{
			adjust_pointer(&prev, &node, &true_head);
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
	t_list	*head;

	prev = 0;
	head = 0;
	while (node)
	{
		if (node -> fd == fd)
			node = free_node(prev, node);
		else
		{
			prev = node;
			node = node -> next;
			if (head == 0)
				head = prev;
		}
	}
	if (head != 0)
		return (head);
	else
		return (0);
}
