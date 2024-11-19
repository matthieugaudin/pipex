/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:13:22 by mgaudin           #+#    #+#             */
/*   Updated: 2024/11/19 19:16:51 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

static void settle_child_one(void)
{
    
}

static void pipex(int fd1, int fd2, char **av, char **envp)
{
    int     filefd[2];
    int     status;
    pid_t   child1;
    pid_t   child2;

    if (pipe(filefd) == -1)
        return (-1);
    child1 = fork();
    if (child1 == -1)
    {
        // settle errno
        return (-1);
    }
    else if (child1 == 0)
    {
        // first function
        if (dup2(filefd[1], STDOUT_FILENO) == -1)
            return (-1);
        close(filefd[0]);
        execve(av[1], ft_split(av[2], ' '), envp);
    }
    else 
    {
        // second function
        if (dup2(filefd[0], STDIN_FILENO) == -1)
            return (-1);
        close(filefd[1]);
        execve(av[2], ft_split(av[3], ' '), envp);
    }
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
    if (fd1 < 0 | fd2 < 0)
        return (-1);
    pipex(fd1, fd2, av, envp);
    return (0);
}