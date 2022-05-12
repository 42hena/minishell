#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
// #include <minishell.h>
#define TRUE 1
#define FALSE 0

#ifndef TEST
#define TEST
#include "../includehena/pipe_signal.h"
/*ft_strlen,  ft_strcmp 있어야함 */

void	heredoc_prompt(int fd, char *end)
{
	char	*str;

	while (1)
	{
		str = readline(">");
		if (str == NULL)
		{
			close(fd);
			break ;
		}
		else if (*str == '\0')
			write(fd, "\n", 1);
		else if (!strcmp(str, end)) // ft_strcmp로 고쳐야함
		{
			free(str);
			break ;
		}
		else
		{
			write(fd, str, strlen(str)); // < ft_strlen으로 고치기
			write(fd, "\n", 1);
		}
		free(str);
	}
}

/*
*	heredoc 하나씩 실행할 예정
*	히어독 안에 환경변수 보류하기
*	signal 처리 및 echoctl_off처리 후 heredoc시작
*/

int	run_heredoc()
{
	t_heredoc	*iter;
	int			fd;

	iter = g_minishell.heredoc;// 입력 x(전역) -> void 고치기 or 입력 o 위에 헤드 사용
	// iter = head;
	signal(SIGINT, sig_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
	// echoctl_off(); << -- 주석 풀어야 함
	while (iter->next)
	{
		iter = iter->next;
		fd = open(iter->filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (fd < 0)
		{
			g_minishell.is_ended = 1;
			return (FALSE);
		}
		heredoc_prompt(fd, iter->endstring);
	}
	return (TRUE);
}
//---------------------TEST 용도

// t_heredoc	*init(void)
// {
// 	t_heredoc	*tmp;

// 	tmp = (t_heredoc *)malloc(sizeof(t_heredoc));
// 	tmp->next = NULL;
// 	tmp->endstring = NULL;
// 	tmp->filename = NULL;
// 	return (tmp);
// }


// #ifndef LEN
// # define LEN
// int	ft_strlen(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (*str)
// 	{
// 		str++;
// 		i++;
// 	}
// 	return (i);
// }
// #endif

// void	addString(t_heredoc	*newl, char *addstring)
// {
// 	newl->endstring = malloc(sizeof(char) * ft_strlen(addstring) + 1);
// 	strcpy(newl->endstring, addstring);
// }

// void	addfile(t_heredoc *newl, char *addstring)
// {
// 	newl->filename = malloc(sizeof(char) * ft_strlen(addstring) + 1);
// 	strcpy(newl->filename, addstring);
// }

// #ifndef MAIN
// #define MAIN
// int main()
// {
// 	t_heredoc	*iter;
// 	t_heredoc	*newl;

// 	iter = init();
// 	newl = init();
// 	addString(newl, "a");
// 	addfile(newl, "a");
// 	iter->next = newl;
// 	newl = init();
// 	addString(newl, "b");
// 	addfile(newl, "b");
// 	iter->next->next = newl;
// 	newl = init();
// 	addString(newl, "c");
// 	addfile(newl, "c");
// 	iter->next->next->next = newl;
// 	run_heredoc(iter);
// }
// #endif