/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:04:12 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/04 11:53:44 by mgaudin          ###   ########.fr       */
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

	if (!bin_paths)
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

	envp_path = ft_get_envp_path(envp);
	if (!envp_path)
		return (NULL);
	bin_paths = ft_split(envp_path, ':');
	free(envp_path);
	if (!bin_paths)
		return (NULL);
	bin_paths = ft_append_to_each_subtab(bin_paths, "/");
	bin_paths = ft_append_to_each_subtab(bin_paths, cmd);
	return (bin_paths);
}

static char	*ft_get_access_path(char **paths)
{
	size_t	i;

	i = 0;
	while (paths[i])
	{
		if (access(paths[i], X_OK) == 0)
		{
			return (ft_strdup(paths[i]));
			// si dup fail il renvoie NULL car dup est portéger
			// trouver une solution pour décoréler le fail de dup et l'acces non-existing
		}
		i++;
	}
	return (NULL);
}

void    ft_parse_paths(t_pipex *pipex, char **envp)
{
    char	**cmd1_paths;
    char	**cmd2_paths;

	if (pipex->cmds_args[0][0][0] == '/')
	{
		pipex->cmds_path[0] = ft_strdup(pipex->cmds_args[0][0]);// to protect
		pipex->cmds_path[1] = ft_strdup(pipex->cmds_args[1][0]);// to protect
	}
	else
	{	
		cmd1_paths = get_bin_paths(pipex->cmds_args[0][0], envp); // to protect
		cmd2_paths = get_bin_paths(pipex->cmds_args[1][0], envp); // to protect
		pipex->cmds_path[0] = ft_get_access_path(cmd1_paths);
		pipex->cmds_path[1] = ft_get_access_path(cmd2_paths); // not to protect it's settle by the function
		free_tab(cmd1_paths);
		free_tab(cmd2_paths);
	}
}
