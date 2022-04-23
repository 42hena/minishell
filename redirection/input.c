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

#define READ 0
#define WRITE 1
#define STDIN 0
#define STDOUT 1
#define STDERR 2
#endif

void	redirect_input(char *filename, int heredoc_flag)
{
	int	fd;
	int	ret;

	if (access(filename, F_OK))
	{
		// file 이름 넣어줄 방법 생각하기
		write(2, "bash: file: No such file or directory\n", 38);
		return ;//?? 찾아보기
	}
	if (access(filename, R_OK))
	{
		write(2, "bash: permission denied\n", 24);
		return ;//??
	}
	fd = open(filename, O_RDWR);
	if (fd < 0)
	{
		printf("bash: %s: %s\n", filename, strerror(errno));
		exit(errno);
	}
	if (!heredoc_flag)
		dup2(fd, 0);
	close(fd);
}
