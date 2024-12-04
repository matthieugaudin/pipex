/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:02:03 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/04 11:18:35 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_open_fd(char *file_path, int is_fd_in)
{
	int	fd;

	if (!file_path)
		ft_fail(file_path, 1);
	if (is_fd_in != 0)
	{
		fd = open(file_path, O_RDONLY);
		if (fd == -1)
			ft_fail(file_path, 0);
	}
	else
	{
		fd = open(file_path, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd == -1)
			ft_fail(file_path, 1);
	}
	return (fd);
}

void    ft_fail(char *error_message, int exit_status)
{
    perror(error_message);
    exit(exit_status);
}

void	ft_check_ac(int ac)
{
	if (ac != 5)
	{
		ft_putstr_fd("./pipex infile cmd1 cmd2 outfile", 2);
		exit(1);
	}
}

void    free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i] != NULL)
	{
			free(tab[i]);
			i++;
	}
	free(tab);
}