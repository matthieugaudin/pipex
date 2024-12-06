/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:03:21 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/06 12:25:46 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_clean(t_pipex *pipex)
{
	close(pipex->fd_in);
	close(pipex->fd_out);
	if (pipex->cmds_args)
	{
		free_tab(pipex->cmds_args[0]);
		free_tab(pipex->cmds_args[1]);
		free(pipex->cmds_args);
	}
	if (pipex->cmds_path)
		free_tab_size(pipex->cmds_path, 2);
	free(pipex);
}
