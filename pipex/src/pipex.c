/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:06:34 by eschwart          #+#    #+#             */
/*   Updated: 2025/02/13 11:50:06 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static char	*ft_find_path(char *cmd, char **env)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (ft_strchr(cmd, '/')) // si deja un chemin absolu
		return(ft_strdup(cmd));
	
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
		{
			free_tab(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_tab(paths);
	return (NULL);
}

static void	ft_find_cmd(char *av, char **env, t_pipe pipex)
{
	pipex.cmd = ft_split(av, ' ');
	if (!pipex.cmd || !pipex.cmd[0])
	{
		free_tab(pipex.cmd);
		error_handler(4);
	}
	pipex.path = ft_find_path(pipex.cmd[0], env);
	if (!pipex.path)
	{
		free_tab(pipex.cmd);
		error_handler(5);
	}
	if (execve(pipex.path, pipex.cmd, env) == -1)
		error_handler(6);
}

static void	ft_child_process(char *av, char **env, t_pipe pipex)
{
	pid_t	pid;

	if (pipe(pipex.fd) == -1)
		error_handler(2);
	pid = fork();
	if (pid == -1)
		error_handler(3);
	if (pid > 0)
	{
		close(pipex.fd[1]);
		if (dup2(pipex.fd[0], STDIN_FILENO) == -1)
			error_handler(9);
		close(pipex.fd[0]);
		waitpid(pid, NULL, 0);
	}
	else if (pid == 0)
	{
		close(pipex.fd[0]);
		if (dup2(pipex.fd[1], STDOUT_FILENO) == -1)
			error_handler(8);
		close(pipex.fd[1]);
		ft_find_cmd(av, env, pipex);
		exit(EXIT_FAILURE);
	}
}

static void	ft_here_doc(char *limiter, t_pipe *pipex)
{
	int		fd;
	char	*line;

	fd = open(".here_doc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		error_handler(1);
	while (1)
	{
		write(1, "here_doc> ", 10);
		line = get_next_line(STDIN_FILENO);
		if (!line || ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	pipex->infile = open(".here_doc_tmp", O_RDONLY);
	if (pipex->infile < 0)
		error_handler(1);
}

int	main(int ac, char **av, char **env)
{
	int		i;
	t_pipe	pipex;

	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			ft_here_doc(av[2], &pipex);
			i = 3;
		}
		else
		{
			pipex.infile = ft_open_check(av[1], 1);
			i = 2;
		}
		pipex.outfile = ft_open_check(av[ac - 1], 2);
		if (dup2(pipex.infile, STDIN_FILENO) == -1)
			error_handler(10);
		close(pipex.infile);
		while (i < (ac - 2))
		{
			ft_child_process(av[i], env, pipex);
			i++;
		}
		if (dup2(pipex.outfile, STDOUT_FILENO) == -1)
			error_handler(11);
		close(pipex.outfile);
		ft_find_cmd(av[i], env, pipex);
		ft_waitpid();
	}
	else
		error_handler(13);
	return (0);
}
