/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:06:34 by eschwart          #+#    #+#             */
/*   Updated: 2025/02/24 13:42:33 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static char	*ft_find_path(char *cmd, char **env)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	while (*env && ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	if (!*env)
		error_handler(7);
	paths = ft_split(*env + 5, ':');
	if (!paths)
		error_handler(7);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin_3(paths[i], "/", cmd);
		if (access(full_path, X_OK) == 0)
			return (ft_free_tab(paths), full_path);
		free(full_path);
		i++;
	}
	ft_free_tab(paths);
	return (NULL);
}

static void	ft_find_cmd(char *av, char **env, t_pipe *pipex)
{
	pipex->cmd = ft_split(av, ' ');
	if (!pipex->cmd || !pipex->cmd[0])
	{
		ft_free_tab(pipex->cmd);
		error_handler(4);
	}
	pipex->path = ft_find_path(pipex->cmd[0], env);
	if (!pipex->path || access(pipex->path, F_OK | X_OK) == -1)
	{
		if (!pipex->path)
			ft_putstr_fd("pipex: command not found\n", 2);
		else if (access(pipex->path, F_OK) == -1)
			perror("Found");
		else
			perror("Execute");
		ft_free_tab(pipex->cmd);
		free(pipex->path);
		exit(127 - (pipex->path && access(pipex->path, F_OK) == 0));
	}
	execve(pipex->path, pipex->cmd, env);
	perror("execve");
	ft_free_tab(pipex->cmd);
	free(pipex->path);
	exit(1);
}

static void	ft_child_process(char *av, char **env, t_pipe *pipex, int cmd_i)
{
	if (pipex->pid[cmd_i] == -1)
		error_handler(3);
	if (pipex->pid[cmd_i] == 0)
	{
		if (cmd_i == 0)
		{
			if (dup2(pipex->infile, STDIN_FILENO) == -1
				|| dup2(pipex->fd[1], STDOUT_FILENO) == -1)
				error_handler(8);
		}
		else if (cmd_i == 1)
		{
			if (dup2(pipex->fd[0], STDIN_FILENO) == -1
				|| dup2(pipex->outfile, STDOUT_FILENO) == -1)
				error_handler(9);
		}
		ft_close_all(pipex);
		ft_find_cmd(av, env, pipex);
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipe	pipex;
	int		exit_code;

	if (ac != 5)
	{
		ft_putstr_fd("Error: too few arguments.\n", 2);
		exit(EXIT_FAILURE);
	}
	init_pipex(&pipex);
	ft_open_check(av[1], 1, &pipex);
	ft_open_check(av[4], 2, &pipex);
	if (pipe(pipex.fd) == -1)
		error_handler(2);
	pipex.pid[0] = fork();
	ft_child_process(av[2], env, &pipex, 0);
	pipex.pid[1] = fork();
	ft_child_process(av[3], env, &pipex, 1);
	ft_close_all(&pipex);
	exit_code = ft_wait_child(&pipex, 2);
	free_pipex(&pipex);
	return (exit_code);
}
