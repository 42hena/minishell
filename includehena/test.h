#ifndef TEST_H
# define TEST_H

typedef enum e_node_type
{
	TYPE_IN_OVERWRITE,
	TYPE_OUT_OVERWRITE,
	TYPE_HEREDOC,
	TYPE_OUT_APPEND,
	TYPE_CMD,
	TYPE_ETC
}	t_node_type;

typedef struct s_node
{
	t_node_type		type;
	char			*file_name;
	int				heredoc_idx;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_list
{
	struct s_list	*next;
	void			*data;
}	t_list;

typedef struct s_ll {
	int     pid;          // 0
	int    fd;           // 0
	char   *cmd;         // "echo"
	char    *cmd_address; // "/bin/ls"
	char    **argv;       // {"echo", ("option"), ("arg"), ("arg"), NULL}
	int    heredoc;      // heredoc이 있는지
	int    pipe_exist;   // 뒤에 파이프가 있는지
	t_node  *root;
} t_exec;

t_node	*create_node(char *data);
t_list	*get_last_list(t_list *list);
void	add_list_back(t_list **list, t_list *new);
t_list	*create_list(void *data);
void	print_list(t_list *head);
t_exec	*create_s_ll(char *data, char *path);

typedef struct s_heredoc {
	struct s_heredoc *next;
	char             *end_string;
	char             *file_name;
} t_heredoc;

typedef struct s_minishell {
	t_list		*envp;
	t_list		*exec;
	t_list		*heredoc;
	int			is_ended;
	unsigned short	state;
	char		*oldpwd;
} t_minishell;

typedef struct s_envp
{
	char *key;
	char *value;
}              t_envp;

// #include <unistd.h>
#include <termios.h>
void	echoctl_off(void);

void	echoctl_on(void);

#endif
