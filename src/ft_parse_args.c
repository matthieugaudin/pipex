/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:04:15 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/06 12:19:01 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_parse_args(t_pipex *pipex, char **av)
{
	pipex->cmds_args = malloc(sizeof(char **) * 3);
	if (!pipex->cmds_args)
	{
		ft_clean(pipex);
		ft_fail("malloc", 1);
	}
	pipex->cmds_args[2] = NULL;
	pipex->cmds_args[0] = ft_split(av[2], ' ');
	pipex->cmds_args[1] = ft_split(av[3], ' ');
	if (!pipex->cmds_args[0] || !pipex->cmds_args[1])
	{
		ft_clean(pipex);
		ft_fail("malloc", 1);
	}
}
