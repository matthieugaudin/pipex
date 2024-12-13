/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:55:20 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/13 18:11:08 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_open_fd(char *file_path, int is_fd_in)
{
	int	fd;

	if (is_fd_in != 0)
	{
		fd = open(file_path, O_RDONLY);
		if (fd == -1)
		{
			perror(file_path);
			fd = open("/dev/null", O_RDONLY);
		}
	}
	else
	{
		fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd == -1)
		{
			perror(file_path);
			fd = open("/dev/null", O_RDONLY);
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
	int	i;

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
