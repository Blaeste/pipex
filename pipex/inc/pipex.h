/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:44:50 by eschwart          #+#    #+#             */
/*   Updated: 2025/02/13 11:26:06 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// INCLUDES
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

//	STRUCT
typedef struct s_pipe
{
	int		infile;
	int		outfile;
	int		fd[2];
	char	*path;
	char	**cmd;
}	t_pipe;

// PROTOTYPES
// Utils
void	free_tab(char **tab);
char	*ft_strjoin_3(char *s1, char *s2, char *s3);
void	error_handler(int i);
int		ft_open_check(char *av, int i);
void	ft_waitpid(void);

#endif // PIPEX_H