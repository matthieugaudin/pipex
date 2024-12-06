/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:02:03 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/06 12:24:24 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_open_fd(t_pipex *pipex, char *file_path, int is_fd_in)
{
	int	fd;

	if (!file_path)
		ft_fail(file_path, 1);
	if (is_fd_in != 0)
	{
		fd = open(file_path, O_RDONLY);
		if (fd == -1)
		{
			close(pipex->fd_out);
			free(pipex);
			ft_fail(file_path, 0);
		}
	}
	else
	{
		fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd == -1)
		{
			free(pipex);
			ft_fail(file_path, 1);
		}
	}
	return (fd);
}

void	ft_check_ac(int ac)
{
	if (ac != 5)
	{
		ft_putstr_fd("./pipex infile cmd1 cmd2 outfile", 2);
		exit(1);
	}
}

void	free_tab(char **tab)
{
	size_t	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_tab_size(char **tab, int size)
{
	size_t	i;

	if (!tab)
		return ;
	i = 0;
	while (i < size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
