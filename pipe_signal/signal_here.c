/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_here.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hena <hena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 02:25:15 by hena              #+#    #+#             */
/*   Updated: 2022/05/12 02:25:15 by hena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include "../includehena/test.h"

extern t_minishell g_minishell;

void	sig_heredoc_handler(int signal)
{
	if (signal != SIGINT)
		return ;
	printf(">");
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
	g_minishell.is_ended = 1;
	g_minishell.state = 1;
}
