#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char *itoa_basex(unsigned int n)
{
	char *ctr;
	unsigned int num;
	int len;
	char *p;

	p = "0123456789abcdef";
	num = n;
    len = 0;
    if (n == 0)
        len++;
	while (n > 0)
	{
		n = n / 16;
		len++;
	}
	ctr = (char *)malloc(sizeof(char) * len + 1);
    if (!ctr)
        return (NULL);
	ctr[len] = '\0';
    while (len > 0)
    {
        ctr[len - 1] = p[num % 16];
        len--;
        num /= 16;
    }
	return (ctr);
}
char *itoa_basep(unsigned long n)
{
	char *ctr;
	unsigned long num;
	int len;
	char *p;

	p = "0123456789abcdef";
	num = n;
    len = 0;
    if (n == 0)
        len++;
	while (n > 0)
	{
		n = n / 16;
		len++;
	}
	ctr = (char *)malloc(sizeof(char) * len + 1);
    if (!ctr)
        return (NULL);
	ctr[len] = '\0';
    while (len > 0)
    {
        ctr[len - 1] = p[num % 16];
        len--;
        num /= 16;
    }
	return (ctr);
}
char *itoa_baseux(unsigned int n)
{
    char *pu;
    unsigned int num;
    char *ctr;
    int len;

    len = 0;
    pu = "0123456789ABCDEF";
    num = n;
    len = 0;
    if (n == 0)
        len++;
	while (n > 0)
	{
		n = n / 16;
		len++;
	}
	ctr = (char *)malloc(sizeof(char) * len + 1);
    if (!ctr)
        return (NULL);
	ctr[len] = '\0';
    while (len > 0)
    {
        ctr[len - 1] = pu[num % 16];
        len--;
        num /= 16;
    }
    return (ctr);
}
size_t	ft_strlen(const char *s)
{
	size_t	i;
	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	p = (char *)malloc(sizeof(char) * len + 1);
	if (!p)
		return (NULL);
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	ft_rep(int len, long long n)
{
	if (n == 0)
	{
        //printf("CUM");
		len++;
		return (len);
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_mal(int i, int len, long long num, int min)
{
	char	*p;

    if (num == 0)
    {
        p = (char *)malloc(sizeof(char) * 2);
        p[0] = '0';
        p[1] = '\0';
        return (p);
    }
	p = (char *)malloc(sizeof(char) * (len) + 1 + min);
	if (!p)
		return (NULL);
	p[i + 1] = '\0';
	while (i >= 0)
	{
		p[i] = num % 10 + '0';
		num = num / 10;
		i--;
	}
	// if (min == 1)
	// 	p[0] = '-';
	return (p);
}

char	*ft_itoa(long long n)
{
	int		        len;
	int		        i;
	unsigned long long		num;
	int		        min;
	char	        *ptr;

	min = 0;
	i = 0;
	len = 0;
	if (n < 0)
	{
		//min++;
		n *= -1;
	}
    //printf("CUM");
	num = n;
	if (n >= 0)
	{
		len = ft_rep(len, n);
		i = len - 1 + min;
	}
	ptr = ft_mal(i, len, num, min);
	return (ptr);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				min;
	unsigned int	res;
	char			*p;
	p = (char *) str;
	i = 0;
	min = 1;
	res = 0;
	while ((p[i] >= 0x09 && p[i] <= 0x0D) || (p[i] == ' '))
		i++;
	if (p[i] == '-')
		min *= -1;
	if (p[i] == '-' || p[i] == '+')
		i++;
	while (p[i] >= '0' && p[i] <= '9')
	{
		res = (res * 10) + (p[i] - '0');
		i++;
	}
	if (res > 2147483648 && min == -1)
		return (0);
	if (res > 2147383647 && min == 1)
		return (-1);
	return (min * res);
}

int ft_space_u(t_fl *flager, int len)
{
    int space;

    space = 0;
    if (flager->precision < len && flager->minus > 0 && flager->flpr == 0)
    {
        space = flager->width - len;
        // printf("!");
    }
    else if (flager->width >= flager->precision && flager->flpr == 0 && flager->minus > 0)
        space = flager->width - flager->precision;
    else if (flager->width >= flager->precision && flager->flpr == 1)
        space = flager->width - len;
    else if (flager->width >= flager->precision && flager->flpr == 0 && flager->zero > 0 && flager->precision >= len)
        space = flager->width - flager->precision;
    else if (flager->width >= flager->precision && flager->flpr == 0 && flager->zero > 0 && flager->precision < len
    && flager->precision > 0) 
        space = flager->width - len;
    else if (flager->precision > flager->width && flager->flpr == 1)
        space = flager->width - len;
    else if (flager->zero == 0 && flager->minus == 0 && flager->flpr == 0 && flager->precision >= len)
        space = flager->width - flager->precision;
    else if (flager->zero == 0 && flager->minus == 0 && flager->flpr == 0 && flager->precision < len)
        space = flager->width - len;
    else if (flager->precision == 0 && flager->width> 0)
        space = flager->width - len;
    return (space);
}
int ft_zero_u(t_fl *flager, int len)
{
    int zero;

    zero = 0;
    if (flager->width >= flager->precision && flager->flpr == 0 && flager->precision > 0)
        zero = flager->precision - len;
    else if (flager->width >= flager->precision && flager->flpr == 0 && flager->dot == 0)
        zero = flager->width - len;
    else if (flager->precision >= flager->width && flager->flpr == 0)
        zero = flager->precision - len;
    else if (flager->width >= flager->precision && flager->flpr == 1 && flager->zero > 0)
        zero = flager->width - len;
    else if (flager->precision >= flager->width && flager->flpr == 1)
        zero = flager->width - len;
    else if (flager->zero == 0 && flager->minus == 0 && flager->flpr == 0)
        zero = flager->precision - len;
    return (zero);
}
// int ft_circle_u(int len, char *l)
// {
//     int i;

//     i = 0;
//     while (i)
// }
int ft_proc_u(va_list as, t_fl *flager)
{
    unsigned int p;
    char *l;
    int len;
    int i;
    int count;
    int zero;
    int space;
    count = 0;

    zero = 0;
    space = 0;
    i = 0;
    p = va_arg(as, unsigned int);
    l = ft_itoa(p);
    len = (unsigned int)ft_strlen(l);
    space = ft_space_u(flager, len);
    zero = ft_zero_u(flager, len);
    if (flager->minus > 0)
    {
        if (flager->width >= flager->precision)
        {
            if (flager->flpr == 0)
            {
                count += ft_zero_circle(zero);
                count += ft_circle_di(len, l);
                count += ft_space_circle(space);
            }
            else if (flager->flpr == 1)
            {
                count += ft_circle_di(len, l);
                count += ft_space_circle(space);
            }
        }
        else if (flager->precision > flager->width && flager->flpr == 0)
        {
            count += ft_zero_circle(zero);
            count += ft_circle_di(len, l);
        }
        else if (flager->precision > flager->width && flager->flpr == 1)
        {
            count += ft_circle_di(len, l);
            count += ft_space_circle(space);
        }
    }
    else if (flager->zero > 0)
    {
        if (flager->width >= flager->precision)
        {
            if (flager->flpr == 0)
            {
                if (flager->dot == 1)
                {
                    count += ft_space_circle(space);
                }
                count += ft_zero_circle(zero);
                count += ft_circle_di(len, l);
            }
            else if (flager->flpr == 1)
            {
                count += ft_zero_circle(zero);
                count += ft_circle_di(len, l);
            }
        }
        else if (flager->precision > flager->width)
        {
            if (flager->flpr == 1)
            {
                count += ft_zero_circle(zero);
                count += ft_circle_di(len, l);
            }
            else if (flager->flpr == 0)
            {
                count += ft_zero_circle(zero);
                count += ft_circle_di(len, l);
            }
        }
    }
    else if (flager->minus == 0 && flager->zero == 0)
    {
        if (flager->precision >= len)
        {
            count += ft_space_circle(space);
            count += ft_zero_circle(zero);
            count += ft_circle_di(len, l);
        }
        else if (len > flager->precision)
        {
            count += ft_space_circle(space);
            if (flager->width > 0 || flager->precision > 0)
            {
                count += ft_circle_di(len, l);
            }
            else if (flager->width == 0 && flager->precision == 0 && flager->dot == 0)
            {
                count += ft_circle_di(len, l);
            }
            else if (flager->dot == 1 && flager->precision == 0 && flager->width == 0)
                count += ft_circle_di(len, l);
            else if (flager->width == 0 && flager->precision == -1 && flager->dot == 0)
                count += ft_circle_di(len, l);
            
        }
    }
    free(l);
    return (count);
}