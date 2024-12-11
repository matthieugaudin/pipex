/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:20:55 by mgaudin           #+#    #+#             */
/*   Updated: 2024/12/11 12:26:53 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	*pipex;

	ft_check_ac(ac);
	ft_init_pipex(&pipex, av);
	ft_parse_args(pipex, av);
	ft_parse_paths(pipex, envp);
	ft_exec(pipex, 0, envp);
	ft_exec(pipex, 1, envp);
	ft_clean(pipex);
	return (0);
}
