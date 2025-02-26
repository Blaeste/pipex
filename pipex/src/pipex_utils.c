/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:43:59 by eschwart          #+#    #+#             */
/*   Updated: 2025/02/24 13:53:55 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	ft_open_check(char *filename, int mode, t_pipe *pipex)
{
	if (mode == 1)
	{
		pipex->infile = open(filename, O_RDONLY);
		if (pipex->infile < 0)
		{
			perror("Error: ft_open_check infile | pipex_utils.c\n");
			pipex->infile = open("/dev/null", O_RDONLY);
			if (pipex->infile < 0)
				error_handler(1);
		}
	}
	else if (mode == 2)
	{
		pipex->outfile = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->outfile < 0)
		{
			pipex->outfile = open("/dev/null", O_WRONLY);
			pipex->open_error = errno;
			if (pipex->outfile < 0)
				error_handler(12);
		}
	}
}

void	error_handler(int i)
{
	if (i == 1)
		perror("Error 1: ft_open_check infile | pipex_utils.c\n");
	else if (i == 2)
		perror("Error 2: main on pipe() | pipex.c\n");
	else if (i == 3)
		perror("Error 3: ft_child_process on fork() pid neg | pipex.c\n");
	else if (i == 4)
		perror("Error 4: ft_find_cmd on split | pipex.c\n");
	else if (i == 5)
		perror("Error 5: error not use | pipex.c\n");
	else if (i == 6)
		perror("Error 6: error not use | pipex.c\n");
	else if (i == 7)
		perror("Error 7: ft_find_path on split | pipex.c\n");
	else if (i == 8)
		perror("Error 8: ft_child_process on dup2 (child 1) | pipex.c\n");
	else if (i == 9)
		perror("Error 9: ft_child_process on dup2 (child 2) | pipex.c\n");
	else if (i == 10)
		perror("Error 10: error not use | pipex.c\n");
	else if (i == 11)
		perror("Error 11: main() dup2 outfile failed | pipex.c\n");
	else if (i == 12)
		perror("Error 12: ft_open_check outfile | pipex_utils.c\n");
	exit(EXIT_FAILURE);
}

char	*ft_strjoin_3(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, s3);
	if (!result)
		return (NULL);
	free(temp);
	return (result);
}

void	ft_close_all(t_pipe *pipex)
{
	if (pipex->fd[0] != -1)
		close(pipex->fd[0]);
	if (pipex->fd[1] != -1)
		close(pipex->fd[1]);
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
}
