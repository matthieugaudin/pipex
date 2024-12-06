/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:21:42 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/06 12:21:10 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_clean_and_exit(t_pipex *pipex, int exit_code, int end[2])
{
	if (end[0] >= 0)
		close(end[0]);
	if (end[1] >= 0)
		close(end[1]);
	ft_clean(pipex);
	exit(exit_code);
}

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

void	ft_fail_and_cleanfd(t_pipex *pipex, char *error, int exit, int end[2])
{
	if (end[0] >= 0)
		close(end[0]);
	if (end[1] >= 0)
		close(end[1]);
	ft_clean(pipex);
	ft_fail(error, exit);
}
