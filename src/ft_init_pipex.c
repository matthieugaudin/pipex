/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:54:35 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/13 18:11:52 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_init_pipex(t_pipex **pipex, char **av, int ac)
{
	*pipex = malloc(sizeof(t_pipex));
	if (!*pipex)
		ft_fail("malloc", 1);
	(*pipex)->fd_out = ft_open_fd(av[ac - 1], 0);
	(*pipex)->fd_in = ft_open_fd(av[1], 1);
	(*pipex)->nb_cmds = 0;
	(*pipex)->pipes = NULL;
	(*pipex)->cmds_args = NULL;
	(*pipex)->cmds_path = NULL;
}
