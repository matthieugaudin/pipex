/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:48:36 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/09 15:19:45 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/pipex_bonus.h"

static void	ft_close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nb_cmds - 1)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		i++;
	}
}

static void	ft_redirect_fds(t_pipex *pipex, int i, pid_t *pids)
{
	if (i == 0)
	{
		if (dup2(pipex->fd_in, 0) == -1 || dup2(pipex->pipes[i][1], 1) == -1)
			ft_fail_and_clean_pids(pipex, "dup2", 1, pids);
	}
	else if (i == pipex->nb_cmds - 1)
	{
		if (dup2(pipex->pipes[i - 1][0], 0) == -1 ||
			dup2(pipex->fd_out, 1) == -1)
			ft_fail_and_clean_pids(pipex, "dup2", 1, pids);
	}
	else
	{
		if (dup2(pipex->pipes[i - 1][0], 0) == -1 ||
			dup2(pipex->pipes[i][1], 1) == -1)
			ft_fail_and_clean_pids(pipex, "dup2", 1, pids);
	}
	ft_close_pipes(pipex);
}

static void	ft_exec_cmd(t_pipex *pipex, char **envp, int i, pid_t *pids)
{
	char	*path;
	char	**args;

	path = pipex->cmds_path[i];
	args = pipex->cmds_args[i];
	if (path == NULL)
		ft_fail_and_clean_pids(pipex, "Command not found", 127, pids);
	if (execve(path, args, envp) == -1)
		ft_fail_and_clean_pids(pipex, "execve", 127, pids);
}

static void	ft_wait_pids(t_pipex *pipex, pid_t *pids)
{
	int	status;
	int	i;

	i = 0;
	while (i < pipex->nb_cmds - 1)
	{
		waitpid(pids[i], &status, 0);
		if (WEXITSTATUS(status))
		{
			free(pids);
			ft_clean(pipex);
			exit(WEXITSTATUS(status));
		}
		i++;
	}
	free(pids);
}

void	ft_exec(t_pipex *pipex, char **envp)
{
	pid_t	*pids;
	int		i;

	pids = malloc(sizeof(pid_t) * pipex->nb_cmds);
	if (!pids)
		ft_fail_and_clean(pipex, "malloc", 1);
	i = 0;
	while (i < pipex->nb_cmds)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			ft_fail_and_clean_pids(pipex, "fork", 1, pids);
		else if (pids[i] == 0)
		{
			ft_redirect_fds(pipex, i, pids);
			ft_exec_cmd(pipex, envp, i, pids);
		}
		if (i != 0)
			close(pipex->pipes[i - 1][0]);
		if (i != pipex->nb_cmds - 1)
			close(pipex->pipes[i][1]);
		i++;
	}
	ft_wait_pids(pipex, pids);
}
