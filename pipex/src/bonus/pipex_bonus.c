/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:06:34 by eschwart          #+#    #+#             */
/*   Updated: 2025/02/24 14:33:53 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	ft_here_doc(t_pipe *pipex, char *limiter)
{
	int		fd;
	char	*line;

	fd = open(".here_doc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		error_handler(1, pipex);
	while (1)
	{
		write(1, "here_doc> ", 10);
		line = get_next_line(STDIN_FILENO);
		if (!line || (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
				&& line[ft_strlen(limiter)] == '\n'))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	pipex->infile = open(".here_doc_tmp", O_RDONLY);
	if (pipex->infile < 0)
		error_handler(1, pipex);
}

static char	*ft_find_path(char *cmd, char **env, t_pipe *pipex)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	while (*env && ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	if (!*env)
		error_handler(7, pipex);
	paths = ft_split(*env + 5, ':');
	if (!paths)
		error_handler(7, pipex);
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
		error_handler(4, pipex);
	pipex->path = ft_find_path(pipex->cmd[0], env, pipex);
	if (!pipex->path || access(pipex->path, F_OK | X_OK) == -1)
	{
		if (!pipex->path)
			ft_putstr_fd("pipex: command not found\n", 2);
		else if (access(pipex->path, F_OK) == -1)
			perror("Found");
		else
			perror("Execute");
		free_pipex(pipex);
		exit(127 - (pipex->path && access(pipex->path, F_OK) == 0));
	}
	execve(pipex->path, pipex->cmd, env);
	perror("execve");
	free_pipex(pipex);
	exit(1);
}

static void	ft_child_process(t_pipe *pipex, char *cmd, char **env, int cmd_i)
{
	if (pipex->pid[cmd_i] == -1)
		error_handler(3, pipex);
	if (pipex->pid[cmd_i] == 0)
	{
		if (cmd_i == 0)
		{
			if (dup2(pipex->infile, STDIN_FILENO) == -1
				|| dup2(pipex->pipes[cmd_i][1], STDOUT_FILENO) == -1)
				error_handler(8, pipex);
		}
		else if (cmd_i == pipex->cmd_count - 1)
		{
			if (dup2(pipex->pipes[cmd_i - 1][0], STDIN_FILENO) == -1
				|| dup2(pipex->outfile, STDOUT_FILENO) == -1)
				error_handler(9, pipex);
		}
		else
		{
			if (dup2(pipex->pipes[cmd_i - 1][0], STDIN_FILENO) == -1
				|| dup2(pipex->pipes[cmd_i][1], STDOUT_FILENO) == -1)
				error_handler(9, pipex);
		}
		ft_close_all(pipex);
		ft_find_cmd(cmd, env, pipex);
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipe	pipex;
	int		i;
	int		exit_code;

	ft_init(ac, av, &pipex);
	init_pipex(&pipex, ac - pipex.cmd_start - 1);
	if (pipex.here_doc)
		ft_here_doc(&pipex, av[2]);
	else
		ft_open_check(av[1], 1, &pipex);
	ft_open_check(av[ac - 1], 2, &pipex);
	i = 0;
	while (i < pipex.cmd_count)
	{
		pipex.pid[i] = fork();
		if (pipex.pid[i] == 0)
			ft_child_process(&pipex, av[i + pipex.cmd_start], env, i);
		i++;
	}
	ft_close_all(&pipex);
	exit_code = ft_wait_child(&pipex);
	free_pipex(&pipex);
	return (exit_code);
}
