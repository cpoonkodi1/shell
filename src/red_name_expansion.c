/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_name_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 09:57:01 by olmohame          #+#    #+#             */
/*   Updated: 2024/07/26 15:59:03 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_var_mid_quotes(char *str)
{
	long	i;
	char	out_quo;

	i = -1;
	out_quo = '*';
	while (str[++i])
	{
		if (in(str[i], "\'\""))
		{
			if (out_quo == '*')
				out_quo = str[i];
			else if (str[i] == out_quo)
				out_quo = '*';
		}
		if ((str[i] == '$') && is_expandable(str, i) && (out_quo == '\"'))
			break ;
	}
	return (out_quo == '\"');
}

static void	trim_filename(t_shell **shell, char **file, \
								int will_expand, int the_var_isquoted)
{
	char	*temp;

	if (will_expand)
	{
		if (the_var_isquoted || !ft_strlen(*file))
			temp = ft_strdup(*file);
		else
			temp = ft_strtrim(*file, " \n\t\r\f\v");
		free(*file);
		*file = NULL;
		if (!temp)
			exit(exit_msg(shell, "Malloc failed.\n", 0, EXIT_FAILURE));
		*file = temp;
	}
}

void	expand_filename(t_shell **shell, t_sub	*sub, char **file)
{
	int	will_expand;
	int	the_var_isquoted;

	will_expand = has_expandable_variable(*file);
	the_var_isquoted = is_var_mid_quotes(*file);
	expand_and_clean(file, sub->op != 2, sub, *shell);
	trim_filename(shell, file, will_expand, the_var_isquoted);
	if (!ft_strlen(*file))
	{
		if ((*shell)->delim_quoted)
			sub->invalid_expansion = 0;
		else
			sub->invalid_expansion = 1;
	}
	else
	{
		if ((will_expand && the_var_isquoted))
			sub->invalid_expansion = 0;
		else if (will_expand && !the_var_isquoted && \
							has_mixed_spaces(*file))
			sub->invalid_expansion = 1;
	}
}
