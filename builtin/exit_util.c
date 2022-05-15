/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hena <hena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:00:56 by hena              #+#    #+#             */
/*   Updated: 2022/04/27 17:43:48 by hena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#ifndef BOOL
#define BOOL

#define TRUE 1
#define FALSE 0

#endif

#ifndef EXITKIND
#define EXITKIND

#define NUMBER 0
#define NUMBERSIZE 27
#define MANYARGU 1
#define MANYARGUSIZE 25

#endif

/*
 * ex) 256 -> 0, -1 -> 255
 */

unsigned char	calculate_exit_number(int exit_num)
{
	return exit_num;
}

int	ft_strlen(char *str)
{
	int i;

	while (*str)
		++i;
	return (i);
}

void	print_exit_error(char *str, int type)
{
	write(1, "exit\n", 5); // 확인해봐야할듯 pipe 유무에 따라
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	if (type == NUMBER)
		write(2, "numeric argument required\n", NUMBERSIZE);
	else if (type == MANYARGU)
		write(2, "too many arguments exit\n", MANYARGUSIZE);
}

int	check_all_integer(char *str)
{
	if (*str == '+' || *str == '-')
		++str;
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (FALSE);
		++str;
	}
	return (TRUE);
}

int	ft_atoi(char *str)
{
	int	flag;
	int	sum;

	sum = 0;
	flag = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			flag = -1;
		str++;
	}
	while (*str)
	{
		sum = sum * 10 + *str - '0';
		str++;
	}
	return (sum);
}
