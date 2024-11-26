/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:13:22 by mgaudin           #+#    #+#             */
/*   Updated: 2024/11/22 17:13:12 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec_proc(char *cmd, char **envp)
{
	char	**paths;
	char	**cmds;
	int		i;

	i = 0;
	cmds = ft_split(cmd, ' ');
	paths = get_envp_paths(cmd, envp);
	if (!paths)
		exit(EXIT_FAILURE);
	while (paths[i])
	{
		if (access(paths[i], X_OK) == 0)
		{
			if (execve(paths[i], cmds, envp) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
			break;
		}
		i++;
	}
	if (access(paths[i], X_OK) == -1)
	{
		perror("access");
		exit(EXIT_FAILURE);
	}
}

static void	settle_child_proc(int fd_in, int filefd[2], char **av, char **envp)
{
	dup2(fd_in, 0);
	close(filefd[0]);
	dup2(filefd[1], 1);
	close(filefd[1]);
	exec_proc(av[2], envp);
}

static void	settle_parent_proc(int fd_out, int filefd[2], int pid, char **av, char **envp)
{
	int	status;

	waitpid(pid, &status, 0);
	if (!WIFEXITED(status))
		exit(EXIT_FAILURE);
	close(filefd[1]);
	dup2(filefd[0], 0);
	close(filefd[1]);
	dup2(fd_out, 1);
	exec_proc(av[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	int		filefd[2];
	int		fd_in;
	int		fd_out;
	pid_t	child;

	if (ac != 5)
	{
		ft_putstr_fd("./pipex file1 cmd1 cmd2 file2", 2);
		exit(-1);
	}
	fd_in = open_fd(av[1], 1);
	fd_out = open_fd(av[4], 0);
	if (pipe(filefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	child = fork();
	if (child == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child == 0)
		settle_child_proc(fd_in, filefd, av, envp);
	else
		settle_parent_proc(fd_out, filefd, child, av, envp);
	exit(EXIT_SUCCESS);	
}
