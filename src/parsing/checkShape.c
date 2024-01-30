#include "minirt.h"
#include "struct.h"

int    check_sp(char **line, const int n)
{
    if (len_2(line) != 4)
        return (print_error("sp - Wrong number of parameter", n), 0);;
    if (!valid_tuple(line[1], 0, 0))
        return (print_error("sp - Position format not respected", n), 0);;
    if(!valid_float(line[2]))
        return (print_error("sp - Diameter format not respected", n), 0);;
    if (!valid_rgb(line[3]))
        return (print_error("sp - Color format not respected", n), 0);;
    return (1);
}

int    check_pl(char **line, const int n)
{
    if (len_2(line) != 4)
        return (print_error("pl - Wrong number of parameter", n), 0);;
    if (!valid_tuple(line[1], 0, 0))
        return (print_error("pl - Position format not respected", n), 0);;
    if (!valid_tuple(line[2],-1.0, 1.0))
        return (print_error("pl - Vector format not respected", n), 0);;
    if (!valid_rgb(line[3]))
        return (print_error("pl - Color format not respected", n), 0);;
    return (1);
}

int    check_cy(char **line, const int n)
{
    if (len_2(line) != 6)
        return (print_error("cy - Wrong number of parameter", n), 0);;
    if (!valid_tuple(line[1], 0, 0))
        return (print_error("cy - Position format not respected", n), 0);;
    if (!valid_tuple(line[2],-1.0, 1.0))
        return (print_error("cy - Vector format not respected", n), 0);;
    if (!valid_float(line[3]))
        return (print_error("cy - Diameter format not respected", n), 0);;
    if (!valid_float(line[4]))
        return (print_error("cy - Height format not respected", n), 0);;
    if (!valid_rgb(line[5]))
        return (print_error("cy - Color format not respected", n), 0);;
    return (1);
}