/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:05:49 by eschwart          #+#    #+#             */
/*   Updated: 2025/02/24 13:41:09 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	init_pipex(t_pipe *pipex)
{
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->fd[0] = -1;
	pipex->fd[1] = -1;
	pipex->path = NULL;
	pipex->cmd = NULL;
	pipex->open_error = 0;
	pipex->pid[0] = -1;
	pipex->pid[1] = -1;
}

void	free_pipex(t_pipe *pipex)
{
	if (pipex->cmd)
		ft_free_tab(pipex->cmd);
	if (pipex->path)
		free(pipex->path);
}

int	ft_wait_child(t_pipe *pipex, int cmd_i)
{
	int	i;
	int	status;
	int	exit_code;

	i = 0;
	exit_code = 0;
	while (i < cmd_i)
	{
		waitpid(pipex->pid[i], &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		i++;
	}
	if (pipex->open_error)
		exit_code = 1;
	return (exit_code);
}
