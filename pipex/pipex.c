/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:44:35 by eschwart          #+#    #+#             */
/*   Updated: 2024/12/05 12:50:13 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

void	error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

char	*find_path(char *cmd, char **envp)
{
	char	*path;
	char	**paths;
	char	*full_path;
	int		i;
	int		j;

	i = 0;
	printf("Testing\n");
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!envp[i])
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		if (!path)
			break ;
		path = ft_strjoin(path, cmd);
		if (!path)
			break ;
		if (access(path, X_OK) == 0)
		{
			j = 0;
			while (paths[j])
				free(paths[j++]);
			free(paths);
			return (path);
		}
		free(path);
		i++;
	}
	j = 0;
	while (paths[j])
		free(paths[j++]);
	free(paths);
	return (NULL);
}

void	execute_cmd(char *cmd, char **envp)
{
	char	**args;
	char	*path;
	int		i;

	args = ft_split(cmd, ' ');
	if (!args)
		error("Echec de la fonction ft_split");
	if (ft_strchr(args[0], '/'))
		path = args[0];
	else
		path = find_path(args[0], envp);
	if (!path || access(path, X_OK) != 0)
	{
		fprintf(stderr, "Commande introuvable : %s\n", args[0]);
		i = 0;
		while (args[i])
			free(args[i++]);
		free(args);
		exit(EXIT_FAILURE);
	}
	printf("Executing: %s\n", path); // Debug
	if (execve(path, args, envp) == -1)
		error("Echec de la fonction execve");
}

void	child_process(int *pipes, char *cmd, char **envp)
{
	close(pipes[0]);
	if (dup2(pipes[1], STDOUT_FILENO) == -1)
		error("Echec de la fonction dup2 child");
	close(pipes[1]);
	execute_cmd(cmd, envp);
}

void	parent_process(int *pipes)
{
	close(pipes[1]);
	if (dup2(pipes[0], STDIN_FILENO) == -1)
		error("Echec de la fonction dup2 parent");
	close(pipes[0]);
}

void	pipex(char **argv, int argc, char **envp)
{
	int		fd_in;
	int		fd_out;
	int		pipes[2];
	pid_t	pid;
	int		i;

	printf("Opening file1: %s\n", argv[1]); //debug
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0)
		error("Echec ouverture fichier : file 1");
	printf("Opening file2: %s\n", argv[argc - 1]); //debug
	fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
		error("Echec ouverture fichier : file 2");
	if (dup2(fd_in, STDIN_FILENO) == -1)
		error("Echec de la fonction dup2 n1");
	close(fd_in);
	printf("Redirection de STDIN_FILENO réussie\n"); //debug
	i = 2;
	while (i < argc - 1)
	{
		printf("Executing command: %s\n", argv[i]); //debug
		if (pipe(pipes) == -1)
			error("Echec de la fonction pipe");
		pid = fork();
		if (pid == -1)
			error("Echec de la fonction fork");
		if (pid == 0)
			child_process(pipes, argv[i], envp);
		else
			parent_process(pipes);
		i++;
		waitpid(pid, NULL, 0);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		error("Echec de la fonction dup2 n2");
	close(fd_out);
	printf("Redirection de STDOUT_FILENO réussie\n"); //debug
	waitpid(pid, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}

	if (argc < 5)
	{
		write(2, "wrong cmd\n", 10);
		return (EXIT_FAILURE);
	}
	pipex(argv, argc, envp);
	return (EXIT_SUCCESS);
}
