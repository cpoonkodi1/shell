/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 09:23:58 by pchennia          #+#    #+#             */
/*   Updated: 2024/07/31 11:01:28 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Extract the part before the '$'
char	*find_prefix(t_shell *shell, char *str, char *dollar)
{
	size_t	prefix_len;
	char	*prefix;

	prefix_len = dollar - str;
	prefix = (char *)malloc(prefix_len + 1);
	if (!prefix)
		exit(exit_msg(&shell, MF, 0, EXIT_FAILURE));
	bi_strncpy(prefix, str, prefix_len);
	prefix[prefix_len] = '\0';
	return (prefix);
}

char	*find_var_value(t_shell *shell, char *dollar, char **var_end)
{
	char	*var_start;
	size_t	var_len;
	char	*var_value;
	char	*var_name;

	var_start = dollar + 1;
	var_len = get_var_length(var_start, var_end);
	if (var_len > 0)
	{
		var_name = extract_var_name_and_value(shell, var_start, var_len);
		if (check_first_char1(var_name[0]))
			return (varname_without_firstchar(&var_name, shell), var_name);
		var_value = custom_getenv(shell, var_name);
		free(var_name);
		return (var_value);
	}
	if (**var_end == '?')
	{
		(*var_end)++;
		var_value = ft_itoa(shell->execution_status);
		return (var_value);
	}
	return (NULL);
}

int	find_result_len(char *dollar, char *var_value, char *var_end, char *str)
{
	size_t	prefix_len;
	size_t	result_len;

	prefix_len = dollar - str;
	if (var_value)
	{
		result_len = prefix_len + ft_strlen(var_value) + ft_strlen(var_end) + 1;
	}
	else
	{
		result_len = prefix_len + ft_strlen(var_end) + 1;
	}
	return (result_len);
}

char	*replace_core(t_param *param, char *str, t_shell *shell, char *dollar)
{
	size_t	result_len;
	char	*result;
	char	*prefix;
	char	*var_value;
	char	*var_end;

	var_value = find_var_value(shell, dollar, &var_end);
	result_len = find_result_len(dollar, var_value, var_end, str);
	prefix = find_prefix(shell, str, dollar);
	result = (char *)malloc(result_len);
	if (result == NULL)
		exit(exit_msg(&shell, "Malloc failed.\n", 0, EXIT_FAILURE));
	bi_strcpy(result, prefix);
	if (var_value)
	{
		ft_strcat(result, var_value);
		free(var_value);
		param->new_status = 1;
	}
	else
		param->new_status = 0;
	ft_strcat(result, var_end);
	free(prefix);
	return (result);
}

char	*replace_this(t_param *param, char *str, t_shell *shell)
{
	char	*result;
	char	*dollar;

	if (ft_strcmp(str, "$") == 0)
		return (ft_strdup(str));
	dollar = ft_strchr(str, '$');
	if (!dollar)
		return (ft_strdup(str));
	result = replace_core(param, str, shell, dollar);
	return (result);
}
