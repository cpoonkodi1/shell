/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:28:58 by pchennia          #+#    #+#             */
/*   Updated: 2024/07/15 13:15:47 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	found_shlvl_in_env(char *var, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], ft_strlen(var)) == 0)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

void	update_shlvl(char **env)
{
	int		index;
	int		num;
	char	*value;
	char	*var_with_val;

	index = found_shlvl_in_env("SHLVL=", env);
	if (index == -1)
		return ;
	num = ft_atoi(&env[index][6]);
	num++;
	value = ft_itoa(num);
	if (!value)
		return ;
	var_with_val = ft_strjoin("SHLVL=", value);
	free(value);
	free(env[index]);
	env[index] = var_with_val;
}
