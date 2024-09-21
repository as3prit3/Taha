/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:54:52 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/30 19:47:35 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	change_env(char *name, char *value, t_exec *exec)
{
	char	**tmp;
	char	*tmp2;
	int		i;

	i = 0;
	tmp = exec->n_env;
	while (tmp[i])
	{
		if (ft_strncmp(tmp[i], name, ft_strlen(name)) == 0)
		{
			tmp2 = ft_strjoin(name, "=");
			free(tmp[i]);
			tmp[i] = ft_strjoin(tmp2, value);
			free(tmp2);
		}
		i++;
	}
}

void	set_env(char *name, char *value, t_exec *exec)
{
	t_env	*tmp;

	tmp = exec->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
		}
		tmp = tmp->next;
	}
	change_env(name, value, exec);
}

void	ft_cd_error(char *path, char *name, t_exec *exec)
{
	if (exec->cmd->args[exec->i + 1])
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	else if (!path)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(" not set\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	g_exit_status = 1;
}

char	*change_path(t_exec *exec, char *path, char *name)
{
	t_env	*tmp;

	tmp = exec->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	if (!path)
		ft_cd_error(path, name, exec);
	return (NULL);
}

int	cd(char *path, t_exec *exec)
{
	char	*old_path;
	char	cwd[1024];

	if (exec->cmd->args[exec->i] && exec->cmd->args[exec->i + 1] \
		&& ft_strlen2d(exec->cmd->args) > 2)
		return (ft_cd_error(path, NULL, exec), 3);
	old_path = getcwd(cwd, sizeof(cwd));
	if (!path || ft_strcmp(path, "~") == 0 || ft_strcmp(path, "--") == 0)
		path = change_path(exec, path, "HOME");
	if (ft_strcmp(path, "-") == 0)
	{
		path = change_path(exec, path, "OLDPWD");
		ft_putendl_fd(path, exec->cmd->out_file);
	}
	if (chdir(path) == 0)
	{
		set_env("OLDPWD", old_path, exec);
		getcwd(cwd, sizeof(cwd));
		set_env("PWD", cwd, exec);
	}
	else
		return (ft_cd_error(path, NULL, exec), 3);
	return (1);
}
