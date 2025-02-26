/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_stack_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:05:49 by eschwart          #+#    #+#             */
/*   Updated: 2025/02/24 13:41:31 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	ft_init(int ac, char **av, t_pipe *pipex)
{
	if (ac < 5)
	{
		ft_putstr_fd("Error: too few arguments.\n", 2);
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		pipex->here_doc = 1;
		pipex->cmd_start = 3;
	}
	else
	{
		pipex->here_doc = 0;
		pipex->cmd_start = 2;
	}
}

void	init_pipex(t_pipe *pipex, int cmd_count)
{
	int	i;

	pipex->pid = NULL;
	pipex->pipes = NULL;
	pipex->cmd = NULL;
	pipex->path = NULL;
	pipex->cmd_count = cmd_count;
	pipex->open_error = 0;
	pipex->flags = O_WRONLY | O_CREAT | O_TRUNC;
	pipex->pid = malloc(sizeof(pid_t) * cmd_count);
	pipex->pipes = malloc(sizeof(int *) * (cmd_count - 1));
	if (!pipex->pid || !pipex->pipes)
		error_handler(1, pipex);
	i = 0;
	while (i < cmd_count - 1)
	{
		pipex->pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipex->pipes[i]) == -1)
			error_handler(2, pipex);
		i++;
	}
}

void	free_pipex(t_pipe *pipex)
{
	int	i;

	if (pipex->cmd)
		ft_free_tab(pipex->cmd);
	if (pipex->path)
		free(pipex->path);
	if (pipex->pipes)
	{
		i = 0;
		while (i < pipex->cmd_count - 1)
		{
			if (pipex->pipes[i])
				free(pipex->pipes[i]);
			i++;
		}
		free(pipex->pipes);
	}
	if (pipex->pid)
		free(pipex->pid);
}

int	ft_wait_child(t_pipe *pipex)
{
	int	i;
	int	status;
	int	exit_code;

	i = 0;
	exit_code = 0;
	while (i < pipex->cmd_count)
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
