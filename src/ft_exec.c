/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:04:18 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/06 12:04:38 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	ft_redirect_fds(t_pipex *pipex, int end[2], int index)
{
	if (index == 0)
	{
		if (dup2(pipex->fd_in, 0) == -1 || dup2(end[1], 1) == -1)
			ft_fail_and_cleanfd(pipex, "dup2", 1, end);
	}
	else
	{
		if (dup2(end[0], 0) == -1 || dup2(pipex->fd_out, 1) == -1)
			ft_fail_and_cleanfd(pipex, "dup2", 1, end);
	}
	close(end[0]);
	close(end[1]);
}

static void	ft_exec_cmd(t_pipex *pipex, char **envp, int index)
{
	char	*path;
	char	**args;

	path = pipex->cmds_path[index];
	args = pipex->cmds_args[index];
	if (path == NULL)
		ft_fail_and_clean(pipex, "Command not found", 127);
	if (execve(path, args, envp) == -1)
		ft_fail_and_clean(pipex, "execve", 127);
}

void	ft_exec(t_pipex *pipex, int index, char **envp)
{
	pid_t		pid;
	static int	end[2];
	int			status;

	if (index == 0)
	{
		if (pipe(end) == -1)
			ft_fail_and_cleanfd(pipex, "pipe", 1, end);
	}
	pid = fork();
	if (pid == -1)
		ft_fail_and_cleanfd(pipex, "fork", 1, end);
	else if (pid == 0)
	{
		ft_redirect_fds(pipex, end, index);
		ft_exec_cmd(pipex, envp, index);
	}
	if (index == 0)
		close(end[1]);
	if (index == 1)
		close(end[0]);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status))
		ft_clean_and_exit(pipex, WEXITSTATUS(status), end);
}
