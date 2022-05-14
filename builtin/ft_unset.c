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

#include "../includehena/check_string_util.h"
#include "../includehena/test.h"
#include <string.h> //TODO:: 삭제해야 함
#ifndef BOOL
# define BOOL

# define TRUE 1
# define FALSE 0

#endif

/*
 * headnode 필요할듯 요청
 */

extern t_minishell g_minishell;

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
			free(envpl);//TODO:: leak 체크 해야할듯
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

static void	unset_error_print(char *argv)
{
	write(2, "unset: `", 8);
	write(2, *argv, strlen(*argv)); //TODO:: strlen ->ft_strlen
	write(2, "': not a valid identifier\n", 26);
}

void	ft_unset(t_exec	*data, int pipe_flag)
{
	int		err_flag;
	char	**argv;

	err_flag = 0;
	argv++;
	while (*argv)
	{
		if (!is_valid_idenfier(*argv))
		{
			unset_error_print(*argv);
			err_flag = 1;
		}
		else
			find_and_erase_key(*argv);
		argv++;
	}
	g_minishell.state = 0;
	if (pipe_flag)
		exit(0);
}
