/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:36:40 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/13 13:39:44 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	int		is_heredoc;
	int		**pipes;
	char	**cmds_path;
	char	***cmds_args;
}	t_pipex;

void	ft_check_ac(char **av, int ac);
char	*get_next_line(int fd, int size, int to_clean);
void	ft_to_clean(char **pstash);
void	free_tab(char **tab);
void	ft_fail(char *error_message, int exit_status);
int		ft_open_fd(t_pipex *pipex, char **av, char *file_path, int is_fd_in);
void	ft_init_pipex(t_pipex **pipex, char **av, int ac);
void	ft_parse_args(t_pipex *pipex, char **av, int ac);
void	ft_parse_paths(t_pipex *pipex, char **envp);
void	ft_fail_and_clean(t_pipex *pipex, char *error_message, int exit_status);
void	ft_create_pipes(t_pipex *pipex);
void	ft_exec(t_pipex *pipex, char **envp);
void	ft_clean(t_pipex *pipex);
void	free_tab_size(char **tab, int size);
void	ft_fail_and_clean_pids(t_pipex *pipex, char *err, int exit, pid_t *p);

#endif /* PIPEX_BONUS_H */