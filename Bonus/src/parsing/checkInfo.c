#include "minirt.h"
#include "struct.h"

int    check_A(char **line, const int n)
{
    static  int A = 0;

    if (A == 1)
        return (print_error("A - More than one ambient light", n), 0);;
    if (len_2(line) != 3)
        return (print_error("A - Wrong number of parameter", n), 0);;
    if (!valid_range(line[1], 0.0, 1.0))
        return (print_error("A - Ratio not respected", n), 0);;
    if (!valid_rgb(line[2]))
        return (print_error("A - Color format not respected", n), 0);;
    A++;
    return (1);
}

int    check_C(char **line, const int n)
{
    static int C = 0;

    if (C == 1)
        return (print_error("C - More than one camera", n), 0);;
    if (len_2(line) != 4)
        return (print_error("C - Wrong number of parameter", n), 0);;
    if (!valid_tuple(line[1], 0, 0))
        return (print_error("C - Position format not respected", n), 0);;
    if (!valid_tuple(line[2], -1.0, 1.0))
        return (print_error("C - Vector format not respected", n), 0);;    
    if (!valid_range(line[3], 0.0, 180.0))
        return (print_error("C - FOV format not respected", n), 0);;
    C++;
    return (1);
}

int    check_L(char **line, const int n)
{
    static int L = 0;

    if (L == 1)
        return (print_error("L - More than one spot light", n), 0);;
    if (len_2(line) != 4)
        return (print_error("L - Wrong number of parameter", n), 0);;
    if (!valid_tuple(line[1], 0, 0))
        return (print_error("L - Position format not respected", n), 0);;
    if (!valid_range(line[2], 0.0, 1.0))
        return (print_error("L - Ratio not respected", n), 0);;
    L++;
    return (1);
}
