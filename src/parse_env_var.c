/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 06:07:35 by olmohame          #+#    #+#             */
/*   Updated: 2024/08/01 05:11:22 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strcpy(char *dest, char *src)
{
	if (!dest || !src)
		return ;
	while (*src)
		*dest++ = *src++;
}

void	ft_strncpy(char *dest, char *src, size_t n)
{
	size_t	i;

	if (!dest || !src)
		return ;
	i = 0;
	while (*src && i++ < n)
		*dest++ = *src++;
}

static size_t	extend_str(char **str, size_t start, t_shell *shell, \
											char *extension)
{
	ssize_t	len;
	ssize_t	ret;
	char	*res;

	res = NULL;
	if (!extension)
		exit(exit_msg(&shell, "Malloc failed.\n", 0, EXIT_FAILURE));
	len = ft_strlen(*str) + 1 - shell->extra_rem + ft_strlen(extension);
	res = (char *)malloc(len * sizeof(char));
	if (!res)
	{
		free(extension);
		extension = NULL;
		exit(exit_msg(&shell, "Malloc failed.\n", 0, EXIT_FAILURE));
	}
	ft_memset(res, '*', len);
	res[len - 1] = 0;
	ft_strncpy(res, *str, start);
	ft_strcpy(res + start, extension);
	ret = ft_strlen(extension) + start - 1;
	free(*str);
	*str = res;
	free(extension);
	extension = NULL;
	return (ret);
}

static size_t	sh_chunklen(char *str, char *cond)
{
	size_t	str_len;

	str_len = 1;
	while (str[str_len] && !ft_isspace(str[str_len]) && !in(str[str_len], cond))
		str_len++;
	return (str_len);
}

int	expand_var(char **str, t_param *param, char **new_token, t_shell *shell)
{
	char	*replace;
	char	*new_val;

	replace = ft_substr((*str), param->i, \
					sh_chunklen((*str) + param->i, "$\"\'"));
	if (!replace)
		exit(exit_msg(&shell, "Malloc failed.\n", 0, EXIT_FAILURE));
	param->i += ft_strlen(replace) - 1;
	shell->extra_rem = ft_strlen(replace);
	new_val = replace_this(param, replace, shell);
	free(replace);
	replace = NULL;
	if (!new_val)
		exit(exit_msg(&shell, "Malloc failed.\n", 0, EXIT_FAILURE));
	param->start_index = extend_str(new_token, ++(param->start_index), \
					shell, new_val);
	if (param->status == -1 || param->new_status)
		param->status = param->new_status;
	return (0);
}
