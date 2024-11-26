/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:36:52 by mgaudin           #+#    #+#             */
/*   Updated: 2024/11/22 17:11:50 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*truncate_path(char *path)
{
	char	*truncated_path;
	int		path_len;

	path_len = ft_strlen(path);
	truncated_path = ft_substr(path, 5, path_len);
	if (!truncated_path)
		return (NULL);
	return (truncated_path);
}

static char	**format_envp_paths(char *cmd, char **paths)
{
	int	i;
	int	cmd_len;
	int	path_len;

	i = 0;
	cmd_len = ft_strlen(cmd) - (ft_strchr(cmd, ' ') - cmd);
	while (paths[i])
	{
		path_len = ft_strlen(paths[i]);
		ft_strlcat(paths[i], "/", path_len + 2);
		ft_strlcat(paths[i], cmd, path_len + 1 + cmd_len);
		i++;
	}
	return (paths);
}

char **get_envp_paths(char *cmd, char **envp)
{
	char	*envp_path;
	char	**envp_paths;
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			envp_path = truncate_path(envp[i]);
			break;
		}	
		i++;
	}
	if (!envp_path)
		return (NULL);
	envp_paths = ft_split(envp_path, ':');
	if (!envp_paths)
		return (NULL);
	envp_paths = format_envp_paths(cmd, envp_paths);
	return (envp_paths);
}

int	open_fd(char *fd, int is_fd_in)
{
	int	res;

	if (is_fd_in == 0)
		res = open(fd, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		res = open(fd, O_RDONLY);
	if (res == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (res);
}