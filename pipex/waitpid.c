/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschwart <eschwart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:08:23 by eschwart          #+#    #+#             */
/*   Updated: 2024/12/03 13:47:28 by eschwart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int argc, char **argv)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == -1)
	{
		printf("Error creating process");
		return (1);
	}
	if (pid1 == 0)
	{
		sleep(4);
		printf("Finished execution (%d)\n", getpid());
		return (0);
	}

	pid2 = fork();
	if (pid2 == -1)
	{
		printf("Error creating process");
		return (2);
	}
	if (pid2 == 0)
	{
		sleep(1);
		printf("Finished execution (%d)\n", getpid());
		return (0);
	}

	printf("Waited for %d\n", waitpid(pid1, NULL, 0));
	printf("Waited for %d\n", waitpid(pid2, NULL, 0));

	return (0);
}
