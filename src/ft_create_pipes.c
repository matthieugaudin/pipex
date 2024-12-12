/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:36:13 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/12 19:09:10 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_create_pipes(t_pipex *pipex)
{
	int	i;
	int	nb_pipes;

	nb_pipes = pipex->nb_cmds - 1;
	pipex->pipes = malloc(sizeof(int *) * (nb_pipes + 1));
	if (!pipex->pipes)
		ft_fail_and_clean(pipex, "malloc", 1);
	pipex->pipes[nb_pipes] = NULL;
	i = 0;
	while (i < nb_pipes)
	{
		pipex->pipes[i] = malloc(sizeof(int) * 2);
		if (!pipex->pipes[i])
			ft_fail_and_clean(pipex, "malloc", 1);
		if (pipe(pipex->pipes[i]) == -1)
			ft_fail_and_clean(pipex, "pipe", 1);
		i++;
	}
}
