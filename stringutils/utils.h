#ifndef UTILS_H
#define UTILS_H
#include <unistd.h>

#include "../minishell.h"
size_t	ft_strlcat(char *dst, char *src, size_t size);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
#endif