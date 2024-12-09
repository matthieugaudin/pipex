/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:00:24 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/09 15:25:40 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/pipex_bonus.h"

void	ft_fail(char *error_message, int exit_status)
{
	perror(error_message);
	exit(exit_status);
}

void	ft_fail_and_clean(t_pipex *pipex, char *error_message, int exit_status)
{
	ft_clean(pipex);
	ft_fail(error_message, exit_status);
}

void	ft_fail_and_clean_pids(t_pipex *pipex, char *err, int exit, pid_t *p)
{
	free(p);
	ft_clean(pipex);
	ft_fail(err, exit);
}
