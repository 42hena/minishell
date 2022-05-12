/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hena <hena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 02:42:51 by hena              #+#    #+#             */
/*   Updated: 2022/05/12 02:42:53 by hena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define TRUE 1
#define FALSE 0
#include "../test.h"

void	pipe_logic(t_list *parse)
{
	t_exec	*execl;

	execl = (t_exec)parse->data;
	// 명령어가 한개일때 
	if (!parse->next)
		
	else ()	//파이프가 있을 때
		fork_pipe(parse);
}

int	main_logic(t_list *parse)
{
	dup2(0, 255);//언제 넣을지 생각하기
	if (run_heredoc())
		return (FALSE);
	// 헤더 있는지 확인해야할듯
	pipe_logic(parse);
	return (TRUE);
}
