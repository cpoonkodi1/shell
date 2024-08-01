/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 12:56:43 by olmohame          #+#    #+#             */
/*   Updated: 2024/07/24 16:29:45 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_expandable_variable(char *str)
{
	ssize_t	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && is_expandable(str, i))
			return (1);
	}
	return (0);
}

void	init_expansion_param(t_param *param)
{
	param->i = -1;
	param->start_index = -1;
	param->out_quo = '*';
	param->status = -1;
	param->new_status = 1;
}

void	expand_and_clean(char **str, int expand, t_sub *sub, t_shell *shell)
{
	expand_token(str, expand, sub, shell);
	clean_token(str, shell);
}

int	has_mixed_spaces(char *str)
{
	ssize_t	i;
	ssize_t	end;

	i = 0;
	if (!str)
		return (0);
	if (ft_strlen(str) == 0)
		return (1);
	end = ft_strlen(str);
	while (ft_isspace(str[i]))
		i++;
	while (ft_isspace(str[end - 1]) && (end - 1) > i)
		end--;
	while (str[i] && (i < end - 1))
	{
		if (ft_isspace(str[i]))
			return (1);
		i++;
	}
	if (!str[i])
		return (1);
	return (0);
}
