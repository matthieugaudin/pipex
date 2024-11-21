/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:13:22 by mgaudin           #+#    #+#             */
/*   Updated: 2024/11/20 22:23:37 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

static void settle_child_one(int fd1, int filefd[2], char **av, char **envp)
{
    char    *bin_path;
    char    *cmd;
    char    **cmd_args;

    cmd = ft_strtrim(av[2], " ");
    cmd_args = ft_split(av[2], ' ');
    bin_path = ft_strjoin("/usr/bin/", cmd);
    free(cmd);
    free(cmd_args);
    dup2(fd1, STDIN_FILENO);
    dup2(filefd[1], STDOUT_FILENO);
    close(filefd[0]);
    execve(bin_path, cmd_args, envp);
    free(bin_path);
}

static void settle_child_two(int fd2, int filefd[2], char **av, char **envp)
{}

static void pipex(int fd1, int fd2, char **av, char **envp)
{
    int filefd[2];
    int status;
    pid_t child1;
    pid_t child2;

    if (pipe(filefd) == -1)
        return (-1);
    child1 = fork();
    if (child1 == -1)
        return (perror("Fork : "));
    else if (child1 == 0)
        settle_child_one(fd1, filefd, av, envp);
    child2 = fork();
    if (child2 == -1)
        return (perror("Fork :"));
    else if (child2 == 0)
        settle_child_two(fd2, filefd, av, envp);
    waitpid(child1, &status, 0);
    waitpid(child2, &status, 0);
}

int main(int ac, char **av, char **envp)
{
    int     fd1;
    int     fd2;

    if (ac != 5)
        return (-1);
    fd1 = open(av[1], O_RDONLY);
    fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd1 < 0 | fd2 < 0)
        return (-1);
    if (pipex(fd1, fd2, av, envp) == -1)
        return (-1);
    return (0);
}