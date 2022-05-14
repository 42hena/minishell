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
#include <unistd.h>
#include <stdlib.h>

void	input(char *filename, int dup_fd)
{
	int	fd;
	int	ret;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(2, "bash: permission denied\n", 24);
		exit(1);
	}
	dup2(fd, dup_fd);
	close(fd);
}
