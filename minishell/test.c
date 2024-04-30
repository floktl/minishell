//	public libraries
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

size_t	ft_strlen(const char *c)
{
	size_t	counter;

	counter = 0;
	while (*c != '\0')
	{
		counter++;
		c++;
	}
	return (counter);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	counter;
	char	*char_s;

	counter = 0;
	char_s = (char *)s;
	while (counter < n)
	{
		char_s[counter] = '\0';
		counter++;
	}
	s = char_s;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	str = malloc(count * size);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, count * size);
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	char	*temp_sub_s;
	size_t	count;
	size_t	count_sub;
	size_t	size_s;

	size_s = strlen(s);
	if (len > size_s)
		len = size_s;
	sub_s = (char *)calloc(len + 1, sizeof(char));
	if (!sub_s)
		return (NULL);
	count_sub = 0;
	count = 0;
	temp_sub_s = sub_s;
	while (s[count] && count_sub < len)
	{
		if (count >= start)
		{
			*sub_s++ = s[count];
			count_sub++;
		}
		count++;
	}
	return (temp_sub_s);
}

int	search_for_variable_in_env(char *variable, char **envp)
{
	int		i;
	int		j;
	int		temp;
	int		found;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && variable[j + 1] && envp[i][j] == variable[j + 1])
		{
			j++;
		}
		if (envp[i][j] && envp[i][j + 1] && envp[i][j] == '=')
		{
			j++;
			temp = 0;
			while (envp[i][j + temp])
			{
				temp++;
			}
			printf("i: %d, j: %d, len: %d \n", i, j, temp);
			free(variable);
			variable = ft_substr(envp[i], j, temp);
			found = 1;
		}
		printf("%d\n", i);
		i++;
	}
	if (found)
		return (1);
	return (0);
}

int main()
{
    // Allocate memory for the environment variables array
    char **envp = (char **)malloc(7 * sizeof(char *));
    if (envp == NULL)
	{
        perror("Memory allocation failed");
        return 1;
    }

    // Set environment variables
    envp[0] = strdup("HOSTNAME=e3d678c4e42d");
    envp[1] = strdup("PWD=/dorker_workspace/miniiii/minishell");
    envp[2] = strdup("HOME=/root");
    envp[3] = strdup("TERM=xterm");
    envp[4] = strdup("SHLVL=1");
    envp[5] = strdup("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
    envp[6] = strdup("OLDPWD=/dorker_workspace/miniiii");

    // Test the search_for_variable_in_env function
    char *variable = strdup("$TRM");
    if (search_for_variable_in_env(variable, envp))
	{
        printf("Variable found: %s\n", variable);
    }
	else
	{
        printf("Variable not found\n");
    }
    for (int i = 0; i < 7; i++)
	{
        free(envp[i]);
    }
    free(envp);
    free(variable); // Don't forget to free the variable allocated by strdup
    return 0;
}