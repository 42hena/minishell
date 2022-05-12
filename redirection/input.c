/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hena <hena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:50:38 by hena              #+#    #+#             */
/*   Updated: 2022/04/23 19:58:44 by hena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>

void	redirect_input(char *filename, int dup_fd, int count)
{
	int	fd;
	int	ret;

	

	if (count == 1)
		//	gnl(1)대입
		;
	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(2, "bash: permission denied\n", 24);
		
	}
	// write(2, "bash: file: No such file or directory\n", 38);
	dup2(fd, dup_fd);
	close(fd);
}
