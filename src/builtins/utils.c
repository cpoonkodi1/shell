/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:15:59 by pchennia          #+#    #+#             */
/*   Updated: 2024/07/31 11:51:00 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_msg(char *pre, char *str, char *cmd, t_shell *mshell)
{
	size_t	len;
	char	*error_message;

	len = ft_strlen(pre) + ft_strlen(cmd) + ft_strlen(str) + 1;
	error_message = (char *)malloc(len);
	if (error_message == NULL)
		exit(exit_msg(&mshell, MF, 0, EXIT_FAILURE));
	bi_strcpy(error_message, pre);
	ft_strcat(error_message, cmd);
	ft_strcat(error_message, str);
	ft_putstr_fd(error_message, STDERR_FILENO);
	free(error_message);
}

int	count_env_vars(char **env)
{
	int	count;

	count = 0;
	while (env[count])
		count++;
	return (count);
}

int	check_some_conditions(t_shell *mshell, char *str)
{
	int	i;

	i = 0;
	if (!ft_strlen(str) || check_first_char(str[0]))
		return (print_err("minishell: export: ", str, \
		": not a valid identifier\n"), 1);
	if (!(ft_strchr(str, '=')))
	{
		while (str[i] != 0)
		{
			if (check_brace(str[i]))
				return (1);
			else if (check_special_char(str[i]))
			{
				return (print_err("minishell: export: ", str, \
		": not a valid identifier\n"), 1);
			}
			i++;
		}
	}
	if (check_identifier(mshell, str))
		return (1);
	return (0);
}

int	find_index(char **env, char *var_with_equal)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var_with_equal, env[i], ft_strlen(var_with_equal)) == 0)
			break ;
		i++;
	}
	return (i);
}
