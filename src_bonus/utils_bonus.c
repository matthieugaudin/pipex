/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:55:20 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/13 18:00:14 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/pipex_bonus.h"

static void	ft_fill_here_doc(char *del, int fd)
{
	char	*str;
	char	*read;

	while (1)
	{
		ft_putstr_fd("> ", 0);
		read = get_next_line(0, 5, 0);
		str = ft_substr(read, 0, ft_strlen(read) - 1);
		if (ft_strcmp(str, del) == 0)
			break ;
		write(fd, read, ft_strlen(read));
		free(read);
		free(str);
	}
	get_next_line(0, 5, 1);
	free(read);
	free(str);
	close(fd);
}

static int	ft_handle_fd(char *file_path)
{
	int	fd;

	perror(file_path);
	fd = open("/dev/null", O_RDONLY);
	return (fd);
}

int	ft_open_fd(t_pipex *pipex, char **av, char *file_path, int is_fd_in)
{
	int	fd;

	if (is_fd_in != 0)
	{
		if (pipex->is_heredoc)
		{
			fd = open("/tmp/heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
			ft_fill_here_doc(av[2], fd);
			fd = open("/tmp/heredoc.tmp", O_RDONLY);
		}
		else
			fd = open(file_path, O_RDONLY);
		if (fd == -1)
			fd = ft_handle_fd(file_path);
	}
	else
	{
		if (pipex->is_heredoc)
			fd = open(file_path, O_RDWR | O_CREAT | O_APPEND, 0777);
		else
			fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd == -1)
			fd = ft_handle_fd(file_path);
	}
	return (fd);
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
