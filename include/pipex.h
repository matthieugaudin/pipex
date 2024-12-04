/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:03:00 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/04 11:17:14 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

typedef struct s_pipex
{
    int     fd_in;
    int     fd_out;
    char    **cmds_path;
    char    ***cmds_args;
}   t_pipex;

void	ft_check_ac(int ac);
void    ft_fail(char *error_message, int exit_status);
int		ft_open_fd(char *file_path, int is_fd_in);
void    free_tab(char **tab);
void    ft_init_pipex(t_pipex *pipex, char **av);
void    ft_parse_args(t_pipex *pipex, char **av);
void    ft_parse_paths(t_pipex *pipex, char **envp);
void	ft_exec(t_pipex *pipex, int index, char **envp);
void    ft_clean(t_pipex *pipex);

#endif /* PIPEX_H */