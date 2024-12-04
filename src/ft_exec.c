/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:04:18 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/04 12:02:34 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	ft_redirect_fds(t_pipex *pipex, int end[2], int index)
{
	if (index == 0)
	{
		dup2(pipex->fd_in, 0);
		dup2(end[1], 1);
	}
	else
	{
		dup2(end[0], 0);
		dup2(pipex->fd_out, 1);
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
		ft_fail("Command not found", 127);
	if (execve(path, args, envp) == -1) // free allocated memory before
		ft_fail("execve", 127);
}

void	ft_exec(t_pipex *pipex, int index, char **envp)
{
	pid_t		pid;
	static int	end[2];
	int			status;

	if (index == 0)
	{
		if (pipe(end) == -1)
			ft_fail("pipe", 1);
	}
	pid = fork();
	if (pid == -1)
		ft_fail("fork", 1);
	else if (pid == 0)
	{
		ft_redirect_fds(pipex, end, index);
		ft_exec_cmd(pipex, envp, index);
	}
	if (index == 1)
	{
		close(end[0]);
		close(end[1]);
	}
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status))
		exit(WEXITSTATUS(status));
}
