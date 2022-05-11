/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hena <hena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 02:22:45 by hena              #+#    #+#             */
/*   Updated: 2022/05/12 02:22:46 by hena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

void	sig_cmd_int_handler(int signal)
{
	if (signal != SIGINT)
		return ;
	g_minishell.flag = 1;
	g_minishell.state = 130;
}

void	sig_cmd_quit_handler(int signal)
{
	if (signal != SIGQUIT)
		return ;
	write(2, "Quit: 3\n", 8);
	g_minishell.flag = 1;
	g_minishell.state = 131;
}
