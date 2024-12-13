/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:00:24 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/13 17:58:30 by mgaudin          ###   ########.fr       */
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

void	ft_to_clean(char **pstash)
{
	free(*pstash);
	*pstash = NULL;
}

void	ft_check_ac(char **av, int ac)
{
	if (ac < 5)
	{
		ft_putstr_fd("./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2", 2);
		exit(1);
	}
	if (ac != 6 && ft_strcmp(av[1], "here_doc") == 0)
	{
		ft_putstr_fd("./pipex here_doc LIMITER cmd cmd1 file", 2);
		exit(1);
	}
}
