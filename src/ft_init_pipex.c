/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:04:21 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/06 12:18:15 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_init_pipex(t_pipex **pipex, char **av)
{
	*pipex = malloc(sizeof(t_pipex));
	if (!*pipex)
		ft_fail("malloc", 1);
	(*pipex)->fd_out = ft_open_fd(*pipex, av[4], 0);
	(*pipex)->fd_in = ft_open_fd(*pipex, av[1], 1);
	(*pipex)->cmds_args = NULL;
	(*pipex)->cmds_path = NULL;
}
