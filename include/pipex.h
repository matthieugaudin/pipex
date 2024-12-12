/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:36:40 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/12 19:10:03 by mgaudin          ###   ########.fr       */
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
	int		fd_in;
	int		fd_out;
	int		nb_cmds;
	int		**pipes;
	char	**cmds_path;
	char	***cmds_args;
}	t_pipex;

void	ft_check_ac(int ac);
void	free_tab(char **tab);
void	ft_fail(char *error_message, int exit_status);
int		ft_open_fd(t_pipex *pipex, char *file_path, int is_fd_in);
void	ft_init_pipex(t_pipex **pipex, char **av, int ac);
void	ft_parse_args(t_pipex *pipex, char **av, int ac);
void	ft_parse_paths(t_pipex *pipex, char **envp);
void	ft_fail_and_clean(t_pipex *pipex, char *error_message, int exit_status);
void	ft_create_pipes(t_pipex *pipex);
void	ft_exec(t_pipex *pipex, char **envp);
void	ft_clean(t_pipex *pipex);
void	free_tab_size(char **tab, int size);
void	ft_fail_and_clean_pids(t_pipex *pipex, char *err, int exit, pid_t *p);

#endif /* PIPEX_H */