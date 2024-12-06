/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:04:12 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/06 12:23:25 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*ft_get_envp_path(char **envp)
{
	char	*envp_path;
	int		i;

	i = 0;
	envp_path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			envp_path = ft_strdup(envp[i] + 5);
			if (!envp_path)
				return (NULL);
			return (envp_path);
		}
		i++;
	}
	return (envp_path);
}

static char	**ft_append_to_each_subtab(char **bin_paths, char *str)
{
	char	*tmp;
	int		i;

	if (!bin_paths || !str)
		return (NULL);
	i = 0;
	while (bin_paths[i] != NULL)
	{
		tmp = bin_paths[i];
		bin_paths[i] = ft_strjoin(tmp, str);
		if (!bin_paths[i])
		{
			free(tmp);
			free_tab(bin_paths);
			return (NULL);
		}
		free(tmp);
		i++;
	}
	return (bin_paths);
}

static char	**get_bin_paths(char *cmd, char **envp)
{
	char	*envp_path;
	char	**bin_paths;

	if (!cmd)
		return (NULL);
	envp_path = ft_get_envp_path(envp);
	if (!envp_path)
		return (NULL);
	if (cmd[0] == '/')
	{
		bin_paths = ft_split(cmd, ' ');
	}
	else
	{
		bin_paths = ft_split(envp_path, ':');
		bin_paths = ft_append_to_each_subtab(bin_paths, "/");
		bin_paths = ft_append_to_each_subtab(bin_paths, cmd);
	}
	free(envp_path);
	if (!bin_paths)
		return (NULL);
	return (bin_paths);
}

static char	*ft_get_access_path(t_pipex *pipex, char **paths)
{
	char	*access_path;
	size_t	i;

	if (!paths)
		return (NULL);
	i = 0;
	access_path = NULL;
	while (paths[i])
	{
		if (access(paths[i], X_OK) == 0)
		{
			access_path = ft_strdup(paths[i]);
			if (!access_path)
				return (NULL);
			return (access_path);
		}
		i++;
	}
	return (access_path);
}

void	ft_parse_paths(t_pipex *pipex, char **envp)
{
	char	**cmd1_paths;
	char	**cmd2_paths;

	pipex->cmds_path = malloc(sizeof(char *) * 3);
	if (!pipex->cmds_path)
	{
		ft_clean(pipex);
		ft_fail("malloc", 1);
	}
	pipex->cmds_path[2] = NULL;
	cmd1_paths = get_bin_paths(pipex->cmds_args[0][0], envp);
	cmd2_paths = get_bin_paths(pipex->cmds_args[1][0], envp);
	pipex->cmds_path[0] = ft_get_access_path(pipex, cmd1_paths);
	pipex->cmds_path[1] = ft_get_access_path(pipex, cmd2_paths);
	free_tab(cmd1_paths);
	free_tab(cmd2_paths);
}
