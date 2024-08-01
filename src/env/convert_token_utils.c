/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_token_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:54:42 by pchennia          #+#    #+#             */
/*   Updated: 2024/07/31 11:01:45 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	get_var_length(char *var_start, char **var_end)
{
	size_t	var_len;

	*var_end = var_start;
	while (**var_end && (**var_end == '_' || ft_isalnum(**var_end)))
		(*var_end)++;
	var_len = *var_end - var_start;
	return (var_len);
}

void	bi_strncpy(char *dest, char *src, size_t n)
{
	size_t	i;

	if (!dest || !src)
		return ;
	i = 0;
	while (*src && i++ < n)
		*dest++ = *src++;
	*dest = 0;
}

char	*custom_getenv(t_shell *shell, const char *name)
{
	size_t	len;
	size_t	i;
	char	**env;

	len = 0;
	while (name[len] != '\0')
		len++;
	env = shell->curr_envp;
	while (*env != NULL)
	{
		i = 0;
		while (i < len && (*env)[i] == name[i])
			i++;
		if (i == len && (*env)[i] == '=')
		{
			return (ft_strdup(*env + len + 1));
		}
		env++;
	}
	return (NULL);
}

char	*extract_var_name_and_value(t_shell *shell, char *var_start, \
size_t var_len)
{
	char	*var_name;

	var_name = (char *)malloc(var_len + 1);
	if (var_name == NULL)
		exit(exit_msg(&shell, MF, 0, EXIT_FAILURE));
	bi_strncpy(var_name, var_start, var_len);
	var_name[var_len] = '\0';
	return (var_name);
}

void	varname_without_firstchar(char **var_name, t_shell *shell)
{
	char	*temp;
	char	*temp_ptr;
	char	*original;

	temp = (char *)malloc(ft_strlen(*var_name));
	if (!temp)
		exit(exit_msg(&shell, "Malloc failed.\n", 0, EXIT_FAILURE));
	original = *var_name + 1;
	temp_ptr = temp;
	while (*original)
	{
		*temp_ptr++ = *original++;
	}
	*temp_ptr = '\0';
	bi_strcpy(*var_name, temp);
	free(temp);
}
