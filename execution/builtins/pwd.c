/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhadhadi <marvin@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:47:04 by mel-hiak          #+#    #+#             */
/*   Updated: 2024/08/22 17:39:26 by hhadhadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd(t_exec *exec)
{
	char	*cmd;
	char	path[2048];

	cmd = getcwd(path, 2048);
	if (cmd != NULL)
		ft_putendl_fd(cmd, exec->cmd->out_file);
	else
		perror("error in getcwd");
}
