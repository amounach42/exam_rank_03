#include "get_next_line.h"

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

int ft_strchr(char   *str)
{
    int i = 0;
    if (!str)
        return 0;
    while (str[i])
    {
        if (str[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

char    *ft_strjoin(char *s1, char  *s2)
{
    int     i = 0;
    int     j = 0;
    int     len = 0;
    char    *str;

    if (!s2)
        return (NULL);
    if (!s1)
    {
        s1 = malloc(1);
        s1[0] = '\0';
    }
    len = ft_strlen(s1) + ft_strlen(s2);
    str = (char*)malloc(sizeof(char) * (len + 1));
    if (!str)
        return NULL;
    while (s1[i])
    {
        str[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j])
        str[i++] = s2[j++];
    str[i] = '\0';
    free(s1);
    return (str);
}

char	*readline(char *line, int fd)
{
	int		i;
	char	*buff;

	i = 1;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (i != 0 && ft_strchr(line) == 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[i] = '\0';
		if (i == 0)
			break ;
		line = ft_strjoin(line, buff);
	}
	free(buff);
	return (line);
}

char	*get_line(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	i += (line[i] == '\n');
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	while (j < i)
	{
		str[j] = line[j];
		j++;
	}
	str[j] = '\0';
	if (str[0] == '\0')
		return (NULL);
	return (str);
}

char	*get_rest(char *line)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	i = 0;
	j = 0;
    while (line[i] && line[i] != '\n')
        i++;
    i += (line[i] == '\n');
	len = ft_strlen(line) - i;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (line[i])
		str[j++] = line[i++];
	str[j] = '\0';
	free(line);
	if (str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = readline(save, fd);
	if (!save)
		return  (NULL);
	line = get_line(save);
	save = get_rest(save);
	return (line);
}

int main(void)
{
    char	*line;
	int		fd;

	fd = open("get_next_line.h", O_RDONLY);
	line = get_next_line(fd);
    while (line)
	{
		printf ("line--> %s\n", line);
        line = get_next_line(fd);
        if (!line)
            break;
        free(line);
		system("leaks a.out");
    }
    return (0);
}