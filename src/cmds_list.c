/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsuguiur <fsuguiur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 00:00:00 by fsuguiur          #+#    #+#             */
/*   Updated: 2025/10/17 17:21:06 by fsuguiur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*cmd_new(char *txt)
{
	t_cmd	*n;

	n = (t_cmd *)malloc(sizeof(*n));
	if (!n)
		return (NULL);
	n->text = txt;
	n->next = NULL;
	return (n);
}

int list_size(t_cmd **head)
{
    t_cmd *ptr;
    ptr = *head;
    int count;

    count = 0;
    if (!*head)
        return (1);
    while (ptr)
    {
        count++;
        ptr = ptr->next;
    }
    return (count);
}

void	cmd_push_back(t_cmd **head, t_cmd *n)
{
	t_cmd	*cur;

	if (!n)
		return ;
	if (!*head)
	{
		*head = n;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = n;
}

void	cmd_list_free(t_cmd **head)
{
	t_cmd	*cur;
	t_cmd	*nx;

	if (!head || !*head)
		return ;
	cur = *head;
	while (cur)
	{
		nx = cur->next;
		free(cur->text);
		free(cur);
		cur = nx;
	}
	*head = NULL;
}


t_cmd	*cmd_build_from_parts(char **parts)
{
	t_cmd	*list;
	size_t	i;
	t_cmd	*n;

	list = NULL;
	i = 0;
	while (parts && parts[i])
	{
		n = cmd_new(parts[i]);
		if (!n)
		{
			cmd_list_free(&list);
			return (NULL);
		}
		cmd_push_back(&list, n);
		parts[i] = NULL;
		i++;
	}
	return (list);
}
