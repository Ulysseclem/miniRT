#include "minirt.h"
#include "struct.h"

int checktype(char **line, int lineNbr)
{
    int ret;

    ret = 0;
    if (strcmp (line[0],"A") == 0)
        ret = check_A(line, lineNbr);
    else if (strcmp (line[0],"C") == 0)
        ret = check_C(line, lineNbr);
    else if (strcmp (line[0],"L") == 0)
        ret = check_L(line, lineNbr);
    else if (strcmp (line[0],"sp") == 0)
        ret = check_sp(line, lineNbr);
    else if (strcmp (line[0],"pl") == 0)
        ret = check_pl(line, lineNbr);
    else if (strcmp (line[0],"cy") == 0)
        ret = check_cy(line, lineNbr);
    else
        return (printf("%d | Invalid ID\n", lineNbr), 0);
    return (ret);
}

int checker(char *line)
{
    char **s_line;
    static int lineNbr = 0;
    int size;
    
    lineNbr++;
    if (is_empty(line))
        return(1);
    s_line = ft_split(line, ' ');
    if (!s_line)
        return(0);
    size = ft_strlen(s_line[0]);
    if (size > 2 || size < 0)
        return (free_2(s_line), 0);
    if (!checktype(s_line, lineNbr))
        return (free_2(s_line), 0);
    return (free_2(s_line), 1);
}

char **checkfile(int argc, char **argv)
{
    char    **res = NULL;
    char    *line;
    int     fd;

    if (argc != 2)
        exit(1);
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        exit(1);
    line = get_next_line(fd);
    while (line)
    {
        if (!checker(line))
        {
            if (res)
                free_2(res);
            free(line);
            exit(1);
        }
        if (!is_empty(line))
            add_string_to_array(&res, line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (res);
}