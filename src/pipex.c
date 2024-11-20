/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:13:22 by mgaudin           #+#    #+#             */
/*   Updated: 2024/11/20 16:55:46 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

static void settle_child_one(int filefd[2], char **av, char **envp)
{
        dup2(filefd[1], STDOUT_FILENO);
        close(filefd[0]);
        execve(av[1], ft_split(av[2], ' '), envp);
}

static void settle_child_two(int filefd[2], char **av, char **envp)
{
        dup2(filefd[0], STDIN_FILENO);
        close(filefd[1]);
        execve(av[2], ft_split(av[3], ' '), envp);
}

static int pipex(int fd1, int fd2, char **av, char **envp)
{
    int     filefd[2];
    int     status;
    pid_t   child1;
    pid_t   child2;

    if (pipe(filefd) == -1)
        return (-1);
    child1 = fork();
    if (child1 == -1)
        return (-1);
    else if (child1 == 0)
        settle_child_one(filefd, av, envp);
    child2 = fork();
    if (child2 == -1)
        return (-1);
    else if (child2 == 0)
        settle_child_two(filefd, av, envp);
    close(filefd[0]);
    close(filefd[1]);
    waitpid(child1, &status, 0);
    waitpid(child2, &status, 0);
    return (0);
}

int main(int ac, char **av, char **envp)
{
    int     fd1;
    int     fd2;

    if (ac != 5)
    {
        ft_putstr_fd("Error : please verify your number of args", 2);
        return (-1);
    }
    fd1 = open(av[1], O_RDONLY);
    fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
    // rediriger les fds vers les fds de la pipes
    if (fd1 < 0 | fd2 < 0)
        return (-1);
    if (pipex(fd1, fd2, av, envp) == -1)
        return (-1);
    close(fd1);
    close(fd2);
    return (0);
}