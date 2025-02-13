/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:43:59 by eschwart          #+#    #+#             */
/*   Updated: 2025/02/13 11:26:53 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	ft_open_check(char *filename, int mode)
{
	int	fd;

	fd = 0;
	if (mode == 1)
		fd = open(filename, O_RDONLY);
	else if (mode == 2)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		return (-1);
	if (fd < 0)
	{
		error_handler(1);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	error_handler(int i)
{
	if (i == 1)
		perror("Error: ft_open_check | pipex_utils.c\n");
	else if (i == 2)
		perror("Error: ft_child_process on pipe() | pipex.c\n");
	else if (i == 3)
		perror("Error: ft_child_process on fork() pid neg | pipex.c\n");
	else if (i == 4)
		perror("Error: ft_find_cmd on split | pipex.c\n");
	else if (i == 5)
		perror("Error: ft_find_cmd invalid path | pipex.c\n");
	else if (i == 6)
		perror("Error: ft_find_cmd execution failed | pipex.c\n");
	else if (i == 7)
		perror("Error: ft_find_path on split | pipex.c\n");
	else if (i == 8)
		perror("Error: ft_child_process on dup2 (STDOUT) | pipex.c\n");
	else if (i == 9)
		perror("Error: ft_child_process on dup2 (STDIN) | pipex.c\n");
	else if (i == 10)
		perror("Error: main() dup2 infile failed | pipex.c\n");
	else if (i == 11)
		perror("Error: main() dup2 outfile failed | pipex.c\n");
	exit(EXIT_FAILURE);
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
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

void	ft_waitpid(void)
{
	int	status;

	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			printf("Processus terminé avec code %d\n", WEXITSTATUS(status));
	}
}
