/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:04:21 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/04 11:22:14 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void    ft_init_pipex(t_pipex *pipex, char **av)
{
    pipex->fd_out = ft_open_fd(av[4], 0);
    pipex->fd_in = ft_open_fd(av[1], 1);
    pipex->cmds_path = malloc(sizeof(char *) * 3); // to protect 
    pipex->cmds_args = malloc(sizeof(char **) * 3); //to protect 
    pipex->cmds_path[2] = NULL;
    pipex->cmds_args[2] = NULL;
    
}