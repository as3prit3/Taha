/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:12:57 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/30 10:20:02 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_path(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PATH") == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static char	*command_not_found(t_exec *exec, char *path)
{
	char	**str;
	char	*tmp;
	int		i;

	i = -1;
	str = ft_split(path, ':');
	while (str[++i])
	{
		tmp = ft_strjoin(str[i], "/");
		exec->command = ft_strjoin(tmp, exec->cmd->args[exec->i]);
		free(tmp);
		if (access(exec->command, X_OK) == 0)
			return (ft_free2d(str), exec->command);
		free(exec->command);
	}
	if (!str[i] || exec->cmd->args[exec->i][0] == '\0')
	{
		ft_putstr_fd(exec->cmd->args[exec->i], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (ft_free2d(str), NULL);
	}
	return (NULL);
}

static void	join_env_vars(t_exec *exec, int j)
{
	char	**new_str;
	int		i;

	i = -1;
	if (exec->cmd->args[exec->i + 1])
	{
		new_str = malloc(sizeof(char *) * (j + 2));
		while (++i < j)
			new_str[i] = ft_strdup(exec->str[i]);
		new_str[j] = ft_strdup(exec->cmd->args[exec->i + 1]);
		new_str[j + 1] = NULL;
		free(exec->str);
		exec->str = new_str;
	}
}

char	*get_command(t_exec *exec, char *path)
{
	int	j;

	if (exec->token && exec->token->type == ENV)
	{
		exec->str = ft_split(exec->cmd->args[exec->i], ' ');
		j = 0;
		while (exec->str[j])
			j++;
		join_env_vars(exec, j);
		exec->cmd->args[exec->i] = exec->str[0];
	}
	if (access(exec->cmd->args[exec->i], F_OK & X_OK) == 0)
		return (exec->cmd->args[exec->i]);
	if (!path)
	{
		ft_putstr_fd(exec->cmd->args[exec->i], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (NULL);
	}
	return (command_not_found(exec, path));
}

void	check_access(t_data *data, t_exec *exec)
{
	check_if_dir(exec, data);
	if (access(exec->cmd->args[exec->i], F_OK) == -1 \
		&& exec->cmd->args[exec->i][ft_strlen(exec->cmd->args[exec->i]) - 1] \
		!= '/')
	{
		exec_error(exec->cmd->args[exec->i]);
		cleanup(data, exec);
		exit(127);
	}
	if (access(exec->cmd->args[exec->i], F_OK) == -1 \
		&& exec->cmd->args[exec->i][ft_strlen(exec->cmd->args[exec->i]) - 1] \
		== '/')
	{
		ft_putstr_fd(exec->cmd->args[exec->i], 2);
		ft_putendl_fd(": Not a directory", 2);
		cleanup(data, exec);
		exit(126);
	}
	if (access(exec->cmd->args[exec->i], X_OK) == -1)
	{
		ft_putstr_fd(exec->cmd->args[exec->i], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		cleanup(data, exec);
		exit(126);
	}
}
