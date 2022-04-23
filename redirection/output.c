/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hena <hena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:52:50 by hena              #+#    #+#             */
/*   Updated: 2022/04/23 19:58:17 by hena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#ifndef FD_OPTION
#define FD_OPTION
#define READ 0
#define WRITE 1
#define STDIN 0
#define STDOUT 1
#define STDERR 2
#endif

/*
 * 찾아봐야 할 점 WROnly처리 일까 RDWR처리 일까
 */

/*
 * redirect > 
 */

void	output(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd < 0)
	{
		printf("bash: %s: %s\n", filename, strerrpr(errno));
		exit(errno);
	}
	dup2(fd, STDOUT);
	close(fd);
}

/*
 * redirect >>
 */

void	output_append(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_APPEND | O_RDWR, 0644);
	if (fd < 0)
	{
		printf("bash: %s: %s\n", filename, strerrpr(errno));
		exit(errno);
	}
	dup2(fd, STDOUT);
	close(fd);
}
