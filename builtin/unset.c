/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hena <hena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 22:44:14 by hena              #+#    #+#             */
/*   Updated: 2022/05/06 03:35:08 by hena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includehena/check_string.util.h"

#ifndef UNISTD
# define UNISTD
#include <unistd.h>
#endif

#ifndef BOOL
# define BOOL

# define TRUE 1
# define FALSE 0
#endif

// static int	ft_strcmp(const char *s1, const char *s2)
// {
// 	while (*s1 == *s2 && *s1 != '\0' && *s2 != '\0')
// 	{
// 		s1++;
// 		s2++;
// 	}
// 	return ((unsigned char)*s1 - (unsigned char)*s2);
// }

/*
 * headnode 필요할듯 요청
 */

static void	find_and_erase_key(char *str)
{
	t_list	*envpl;
	t_list	*prev;
	t_envp	*envp;

	envpl = g_minishell.envp->next;	// 전역 필요
	prev = g_minishell.envp;		//전역 필요
	while (envpl)
	{
		envp = (t_envp *)envpl->data;
		if (!ft_strcmp(envp->key, str))
		{
			prev->next = envpl->next;
			free(envp->key);
			free(envp->value);
			free(envp);
			free(envpl);//? leak 체크 해야할듯
			break ;
		}
		envpl = envpl->next;
		prev = prev->next;
	}
}

static int	is_valid_idenfier(char *str)
{
	if (!((is_small_alpha(*str) || is_big_alpha(*str) || *str == '_')))
		return (FALSE);
	while (*str)
	{
		if (!((is_small_alpha(*str) || is_big_alpha(*str) || \
		is_integer(*str) || *str == '_')))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

void	unset(t_exec	*data)
{
	int	err_flag;

	err_flag = 0;
	argv++;
	while (*argv)
	{
		if (!is_valid_idenfier(*argv))
		{
			write(2, "unset: `", 8);
			write(2, *argv, ft_strlen(*argv));
			write(2, "': not a valid identifier\n", 26);
			err_flag = 1;
		}
		else
			find_and_erase_key(*argv);
		argv++;
	}
	if (err_flag)
		g_minishell.status = 1;
	else
		g_minishell.status = 0;
}

#ifndef MAIN
#define MAIN

int main(int argc, char **argv, char **envp)
{
	unset(argv);
}

#endif