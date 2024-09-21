/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:01:03 by hhadhadi          #+#    #+#             */
/*   Updated: 2024/08/30 19:47:02 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_here_doc(t_data *data, char *str)
{
	free(str);
	free(data->name);
	free_list(data->tokens);
	ft_lstclear(&data->lst_cmd, free);
	ft_free_env(&data->envp);
	ft_lstclear(&data->here_doc_name, free);
}
	/*ft_free2d(data->env_tab);*/

void	free_data(t_data *data, t_exec *exec)
{
	if (data->cmd)
	{
		ft_cmd_clear(&data->cmd);
		exec->cmd = NULL;
	}
	if (data->lst_cmd)
		ft_lstclear(&data->lst_cmd, free);
	if (data->lst_err)
		ft_lstclear(&data->lst_err, free);
	if (data->tokens)
		free_list(data->tokens);
	if (data->here_doc_name)
		ft_lstclear(&data->here_doc_name, free);
	if (data->expend)
		free(data->expend);
}
	/*if (data->envp)
	{
		ft_free_env(&data->envp);
		exec->env = NULL;
	}*/

void	cleanup(t_data *data, t_exec *exec)
{
	if (exec->n_env)
		ft_free2d(exec->n_env);
	if (exec->env)
		ft_free_env(&exec->env);
	if (exec->tube)
	{
		free(exec->tube);
		exec->tube = NULL;
	}
	free_data(data, exec);
}
