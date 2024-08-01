/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_manipulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 04:42:43 by olmohame          #+#    #+#             */
/*   Updated: 2024/08/01 05:08:13 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_sub	*new_node(char *str)
{
	t_sub	*node;

	node = (t_sub *)malloc(sizeof(t_sub));
	if (!node)
		return (NULL);
	node->str = str;
	node->cmd_arr = NULL;
	node->op_in = -1;
	node->op_out = -1;
	node->op = -1;
	node->fd_in = -1;
	node->fd_out = -1;
	node->fname_in = NULL;
	node->fname_out = NULL;
	node->invalid_expansion = 0;
	node->prev = node;
	node->next = node;
	return (node);
}

void	lstadd_back(t_sub **lst, t_sub *newnode)
{
	if (lst && !*lst && newnode)
		*lst = newnode;
	else if (lst && newnode)
	{
		(*lst)->prev->next = newnode;
		newnode->prev = (*lst)->prev;
		newnode->next = *lst;
		(*lst)->prev = newnode;
	}
}

int	add_sub(t_sub **head, char *str, long start, long end)
{
	long	len;
	char	*sub;
	t_sub	*node;

	while (ft_isspace(str[start]))
		start++;
	while (ft_isspace(str[end - 1]) && end > start)
		end--;
	len = end - start;
	if (!len)
		return (0);
	sub = ft_substr(str, start, len);
	if (!sub)
		return (exit_msg(NULL, "Malloc failed.\n", 0, EXIT_FAILURE));
	node = new_node(sub);
	if (!node)
		return (exit_msg(NULL, "Malloc failed.\n", 0, EXIT_FAILURE));
	lstadd_back(head, node);
	return (0);
}

static void	free_sub_content(t_sub	*sub)
{
	if (sub)
	{
		if (sub->str)
		{
			free(sub->str);
			sub->str = NULL;
		}
		if (sub->fname_in)
		{
			free(sub->fname_in);
			sub->fname_in = NULL;
		}
		if (sub->fname_out)
		{
			free(sub->fname_out);
			sub->fname_out = NULL;
		}
		del_tokens(sub);
	}
}

void	lstclear(t_sub **lst)
{
	t_sub	*temp;

	if (lst && *lst)
	{
		(*lst)->prev->next = NULL;
		while (*lst)
		{
			temp = *lst;
			(*lst) = (*lst)->next;
			free_sub_content(temp);
			free(temp);
			temp = NULL;
		}
	}
}
