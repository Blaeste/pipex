/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:44:50 by eschwart          #+#    #+#             */
/*   Updated: 2025/02/24 13:46:15 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

// INCLUDES
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>

//	STRUCT
typedef struct s_pipe
{
	int				cmd_start;
	int				infile;
	int				outfile;
	int				flags;
	int				**pipes;
	char			*path;
	char			**cmd;
	pid_t			*pid;
	int				cmd_count;
	int				here_doc;
	int				open_error;
}	t_pipe;

// PROTOTYPES
void	ft_init(int ac, char **av, t_pipe *pipex);
void	init_pipex(t_pipe *pipex, int cmd_count);
void	free_pipex(t_pipe *pipex);
char	*ft_strjoin_3(char *s1, char *s2, char *s3);
void	error_handler(int i, t_pipe *pipex);
void	ft_open_check(char *av, int i, t_pipe *pipex);
void	ft_close_all(t_pipe *pipex);
int		ft_wait_child(t_pipe *pipex);

#endif // PIPEX_BONUS_H