/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hena <hena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 22:44:14 by hena              #+#    #+#             */
/*   Updated: 2022/04/29 16:53:01 by hena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

typedef struct s_list
{
 	struct s_list *next;
 	char *key;
 	char *value;
} t_list;

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1 != '\0' && *s2 != '\0')
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

/*
 * headnode 필요할듯 요청
 */

static void	find_and_erase_key(char *str)
{
	t_list	*envp;
	t_list	*prev;

	envp = head->next;// 전역 필요
	prev = head;	//전역 필요
	while (copy)
	{
		if (!ft_strcmp(copy.key, str))
		{
			prev->next = envp->next;
			free(envp->key);
			free(envp->value);
			free(envp);
			break ;
		}
		envp++;
		prev++;
	}
}

void	unset(char **argv)
{
	argv++;
	while (*argv)
	{
		find_and_erase_key(*argv);
		argv++;
	}
	// exit 코드
}
