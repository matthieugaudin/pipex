/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:55:20 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/11 12:29:43 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/pipex_bonus.h"

static void	ft_handle_open_err(t_pipex *pipex, char *file_path, int is_fd_in)
{
	if (is_fd_in != 0)
		close(pipex->fd_out);
	free(pipex);
	if (is_fd_in != 0)
		ft_fail(file_path, 0);
	else
		ft_fail(file_path, 1);
}

int	ft_open_fd(t_pipex *pipex, char *file_path, int is_fd_in)
{
	int	fd;

	if (!file_path)
		ft_handle_open_err(pipex, file_path, is_fd_in);
	if (is_fd_in != 0)
	{
		fd = open(file_path, O_RDONLY);
		if (fd == -1)
			ft_handle_open_err(pipex, file_path, is_fd_in);
	}
	else
	{
		fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd == -1)
			ft_handle_open_err(pipex, file_path, is_fd_in);
	}
	return (fd);
}

void	ft_check_ac(int ac)
{
	if (ac < 5)
	{
		ft_putstr_fd("./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2", 2);
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
