/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:15:35 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/13 17:59:03 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/pipex_bonus.h"

static void	ft_free_cmds_args(t_pipex *pipex)
{
	int	i;

	if (pipex->cmds_args)
	{
		i = 0;
		while (pipex->cmds_args[i])
		{
			free_tab(pipex->cmds_args[i]);
			i++;
		}
		free(pipex->cmds_args);
	}
}

static void	ft_free_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nb_cmds - 1)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < pipex->nb_cmds - 1)
	{
		free(pipex->pipes[i]);
		i++;
	}
	free(pipex->pipes);
}

void	ft_clean(t_pipex *pipex)
{
	close(pipex->fd_in);
	close(pipex->fd_out);
	if (pipex->is_heredoc)
		unlink("/tmp/heredoc.tmp");
	ft_free_cmds_args(pipex);
	if (pipex->cmds_path)
		free_tab_size(pipex->cmds_path, pipex->nb_cmds);
	ft_free_pipes(pipex);
	free(pipex);
}
