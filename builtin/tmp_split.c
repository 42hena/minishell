#include <string.h>

char	**split(char *str, char ch)
{
    char **array;
    int i;
    int size;
	int j = 0;

    size = strlen(str);
    array = (char **)malloc(sizeof(char *) * 2);
    i = 0;
	while (str[i])
	{
        if (str[i] == '=')
            break;
        ++i;
	}
	array[0] = (char *)malloc(sizeof(char) * i + 1);
	array[1] = (char *)malloc(sizeof(char) * (size - i));
	while (j < i)
	{
		array[0][j] = str[j];
		++j;
	}
	array[0][i] = NULL;
	array[1][size - i - 1] = NULL;
	j = i + 1;
	while (j < size)
	{
		array[1][j] = str[j];
		++j;
	}
	return (array);
}
