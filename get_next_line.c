/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ensebast <ensebast@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 16:58:01 by ensebast          #+#    #+#             */
/*   Updated: 2021/08/22 12:51:16 by ensebast         ###   ########.br       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*result;
	static t_list	*head;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (0);
	if (head == 0)
		head = create_node(fd);
	if (head == 0)
		return (0);
	if (!(add_nodes(head, fd)))
	{
		free_all(head, fd);
		return (0);
	}
	result = malloc(line_size(head, fd) + 1);
	return (copy_and_free(result, &head));
}

/*
 * Will copy the content of the node and free
 * up the memory
*/
char	*copy_and_free(char *line, t_list **head)
{
	int	k;

	k = 0;
	if (((*head) -> buff_c)[0] == 0)
	{
		free_all((*head), (*head) -> fd);
		free(line);
		(*head) = 0;
		return (0);
	}
	while ((*head))
	{
		while ((*head) -> curr_index < (*head) -> len)
		{
			line[k] = ((*head) -> buff_c)[(*head) -> curr_index];
			(*head) -> curr_index += 1;
			k += 1;
			if (line[k - 1] == '\n')
				break ;
		}
		if ((*head) -> len == (*head) -> curr_index)
			(*head) = free_node((*head));
		else
		{
			(*head) -> flag = 0;
			break ;
		}
	}
	line[k] = '\0';
	return (line);
}

t_list	*free_all(t_list *head, int fd)
{
	while (head)
	{
		if (head -> fd == fd)
			head = free_node(head);
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
			i += head -> len - head -> curr_index;
		head = head -> next;
	}
	return (i);
}
