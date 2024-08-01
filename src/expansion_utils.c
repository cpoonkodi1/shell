/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 04:19:34 by olmohame          #+#    #+#             */
/*   Updated: 2024/07/26 13:01:09 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**build_new_cmd(t_shell *shell, ssize_t *num_tokens, \
								char **elements_toinsert)
{
	char	**new_cmd;

	if (!elements_toinsert)
		exit(exit_msg(&shell, "Malloc failed.\n", 0, EXIT_FAILURE));
	new_cmd = malloc((*num_tokens + count_elements(elements_toinsert)) * \
									sizeof(char *));
	if (!new_cmd)
	{
		sh_del(elements_toinsert, count_elements(elements_toinsert));
		exit(exit_msg(&shell, "Malloc failed.\n", 0, EXIT_FAILURE));
	}
	new_cmd[(*num_tokens + count_elements(elements_toinsert)) - 1] = NULL;
	return (new_cmd);
}

void	rebuild_cmd(t_shell *shell, t_sub **sub, \
						ssize_t *num_tokens, ssize_t *i)
{
	char	**elements_toinsert;
	char	**new_cmd;
	ssize_t	new_ind;
	ssize_t	j;

	elements_toinsert = sh_split((*sub)->cmd_arr[*i]);
	new_cmd = build_new_cmd(shell, num_tokens, elements_toinsert);
	new_ind = -1;
	while (++new_ind < *i)
		new_cmd[new_ind] = (*sub)->cmd_arr[new_ind];
	j = -1;
	free((*sub)->cmd_arr[*i]);
	while (elements_toinsert[++j])
		new_cmd[new_ind++] = elements_toinsert[j];
	*num_tokens += count_elements(elements_toinsert) - 1;
	while (new_ind < *num_tokens)
	{
		new_cmd[new_ind] = (*sub)->cmd_arr[new_ind - j + 1];
		new_ind++;
	}
	*i = *i + count_elements(elements_toinsert) - 1;
	free(elements_toinsert);
	free((*sub)->cmd_arr);
	(*sub)->cmd_arr = new_cmd;
}

void	order_list(t_sub **sub, ssize_t	num_tokens)
{
	ssize_t	i;
	ssize_t	new_i;

	i = -1;
	new_i = -1;
	while (++i < num_tokens)
	{
		if ((*sub)->cmd_arr[i] != NULL)
			(*sub)->cmd_arr[++new_i] = (*sub)->cmd_arr[i];
	}
	(*sub)->cmd_arr[++new_i] = NULL;
}

void	clean_sequence(t_shell *shell, t_sub **sub, \
						ssize_t old_i, ssize_t i)
{
	while (old_i < i + 1)
	{
		if ((*sub)->cmd_arr[old_i])
			clean_token((*sub)->cmd_arr + old_i, shell);
		old_i++;
	}
}
