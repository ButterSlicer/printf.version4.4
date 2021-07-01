#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int ft_circle_di(int len, char *l)
{
    int i;

    i = 0;
    while (i < len)
    {
        write(1, &l[i], 1);
        i++;
    }
    return (i);
}
int ft_zero_circle(int zero)
{
    int i;
    
    i = 0;
    while(i < zero)
    {
        write(1, "0", 1);
        i++;
    }
    return (i);
}
int ft_space_circle(int space)
{
    int i;

    i = 0;
    while(i < space)
    {
        write(1, " ", 1);
        i++;
    }
    return(i);
}
int ft_zero_rasp(t_fl *flager, int fl, int len)
{
    int zero;
    zero = 0;

    if (flager->width >= flager->precision && flager->precision >= len)
        zero = flager->precision - len;
    else if (flager->precision > 0 && flager->width == 0 && flager->precision >= len && flager->flpr == 0)
        zero = flager->precision - len;
    else if (flager->precision > flager->width && flager->width > 0)
        zero = flager->precision - len;
    else if (flager->zero == 1 && flager->width > 0 && flager->dot == 0 && fl == 0)
        zero = flager->width - len;
    else if (flager->zero == 1 && flager->width > 0 && flager->dot == 0 && fl == 1)
        zero = flager->width - len - 1;
    return (zero);
}

int ft_space_rasp_min(t_fl *flager, int fl, int len, int p)
{
    int space;

    space = 0;
        if (flager->precision >= len && flager->flpr == 0 && fl == 0)
            space = flager->width - flager->precision;
        else if (flager->precision < len && fl == 0 && flager->flpr == 0 && flager->precision >= 0 && p == 0)
            space = flager->width;
        else if (flager->precision < len && fl == 0 && flager->flpr == 0 && flager->precision >= 0 && p != 0)
            space = flager->width - len;
        else if (flager->precision < len && fl == 0 && flager->flpr == 0 && flager->precision == -1 && flager->dot == 0)
            space = flager->width - len;
        else if (flager->precision < len && fl == 0 && flager->flpr == 0 && flager->precision == -1 && flager->dot == 1)
            space = flager->width;
        else if (flager->precision == 0 && fl == 1)
            space  = flager->width - len - 1;
        else if (flager->precision >= len && flager->flpr == 0 && fl == 1)
            space = flager->width - flager->precision - 1;
        else if (flager->precision < len && flager->flpr == 0 && fl == 1)
            space = flager->width - len - 1;
    return (space);
}


int ft_proc_di(va_list as, t_fl *flager)
{
    int p;
    int i;
    int len;
    char *l;
    int fl;
    int count;
    int space;
    int zero;

    i = 0;
    count = 0;
    fl = 0;
    zero = 0;
    space = 0;
    p = va_arg(as, int);
    if (p < 0)
    {
        l = ft_itoa(-p);
        fl += 1;
    }
    else
        l = ft_itoa(p);
    len = (int)ft_strlen(l);
    zero = ft_zero_rasp(flager,fl, len);
    space = ft_space_rasp_min(flager, fl, len, p);
    if (flager->minus > 0)
    {   
        if (fl == 1)
        {
            write(1, "-", 1);
            count++;
        }
        if (flager->flpr == 0 && flager->minus == 0)
        {
            count += ft_zero_circle(zero);
        }
        else if (flager->flpr == 0 && flager->precision > 0)
        {
            count += ft_zero_circle(zero);
        }
        count += ft_circle_di(len, l);
        count += ft_space_circle(space);
    }
    else if (flager->zero > 0)
    {
        if (flager->flpr == 0 && flager->precision > 0)
            count += ft_space_circle(space);
        else if (flager->dot == 1 && flager->width > 0 && flager->precision == 0)
            count += ft_space_circle(space);
        if (fl == 1)
        {
            write(1, "-", 1);
            count++;
        }
        count += ft_zero_circle(zero);
        if (flager->dot == 0 )
            count += ft_circle_di(len, l);
        if (flager->precision > 0)
            count += ft_circle_di(len, l);
        else if (flager->precision == 0 && flager->dot == 1 && p != 0)
            count += ft_circle_di(len, l);
    }
    else if (flager->minus == 0 && flager->zero == 0)
    {
        count += ft_space_circle(space);
        if (fl == 1)
        {
            write(1, "-", 1);
            count++;
        }
        if (flager->flpr == 0)
            count += ft_zero_circle(zero);
        if (flager->precision > 0)
            count += ft_circle_di(len, l);
        else if (flager->dot == 0)
            count += ft_circle_di(len, l);
        else if (flager->dot == 1 && p != 0)
            count += ft_circle_di(len, l);
    }
    free (l);
    return (count);
}
int ft_circle_s(int len,  char *p, t_fl *flager)
{
    int i;

    i = 0;
    if (flager->precision >= len && flager->minus == 1)
    {
        while(i < len)
        {
            write(1, &p[i], 1);
            i++;
        }
    }
    else if (flager->precision < len && flager->precision > 0)
    {
        while(i < flager->precision)
        {
            write(1, &p[i], 1);
            i++;
        }
    }
    else if (flager->precision >= len && flager->minus == 0)
    {
        while(i < len)
        {
            write(1, &p[i], 1);
            i++;
        }
    }
    else if (flager->precision == 0 && flager->width == 0 && flager->dot == 0)
    {
        while (i < len)
        {
            write(1, &p[i], 1);
            i++;
        }
    }
    
    else if (flager->width > 0 && flager->precision == 0 && flager->dot == 0)
    {
        while (i < len)
        {
            write(1, &p[i], 1);
            i++;
        }
    }
    return (i);
}
int ft_space_s(t_fl *flager, int len)
{
    int space;

    space = 0;
    if (flager->width >= flager->precision && flager->flpr == 0 && flager->precision < len
     && flager->precision > 0)
        space = flager->width - flager->precision;
    else if (flager->width >= flager->precision && flager->flpr == 0 && flager->precision >= len)
        space = flager->width - len;
    else if (flager->width >= flager->precision && flager->flpr == 1)
        space = flager->width - len;
    else if (flager->width < flager->precision && flager->flpr == 0)
        space = flager->width - len;
    else if (flager->width < flager->precision && flager->flpr == 1)
        space = flager->width - len;
    else if (flager->width > 0 && flager->precision == 0 && flager->dot == 1)
        space = flager->width;
    else if (flager->width > 0 && flager->precision == 0 && flager->dot == 0)
        space = flager->width - len;
    return (space);
}
int ft_space_c(t_fl *flager)
{
    int i;

    i = 0;
    while(i < flager->width - 1)
    {
        write(1, " ", 1);
        i++;
    }
    return (i);
}
int ft_proc_c(va_list as, t_fl *flager, char what)
{
    char p;
    int count;

    count = 0;
    if (what == '%')
        p = what;
    else
       p = va_arg(as, int);
    if (flager->minus == 1)
    {
        count += write(1,&p,1);
        count += ft_space_c(flager);
    }
    else if (flager->minus == 0)
    {
        count += ft_space_c(flager);
        count += write(1,&p,1);
    }
    return (count);
}
int ft_circle_s_space_reverse(int len, char *p, t_fl *flager, int space)
{
    int i;
    int count;

    count = 0;
    i = 0;
    count += ft_space_circle(space);
    count += ft_circle_s(len, p, flager);
    return (count);
}
int ft_circle_s_space(int len, char *p, t_fl *flager, int space)
{
    int i;
    int count;

    count = 0;
    i = 0;
    count += ft_circle_s(len, p, flager);
    count += ft_space_circle(space);
    return (count);
}
int ft_proc2_s(int len, char *p, t_fl *flager, int space)
{
    int count;

    count = 0;
    if (flager->flpr == 0 && flager->width >= flager->precision)
        count += ft_circle_s_space(len, p, flager, space);
    else if (flager->flpr == 1 && flager->width >= flager->precision)
        count += ft_circle_s_space(len, p, flager, space);
    else if (flager->flpr == 0 && flager->precision > flager->width)
        count += ft_circle_s_space(len, p, flager, space);
    else if (flager->flpr == 1 && flager->precision > flager->width)
        count += ft_circle_s_space(len, p, flager, space);
    return (count);
}
int ft_proc_s(va_list as, t_fl *flager)
{
    char *p;
    int len;
    int i;
    int count;
    int space;

    count = 0;
    p = va_arg(as, char *);
    if (flager->precision == -1)
        flager->precision = 0;
    if (!p)
    {
        p = "(null)";
        if (flager->dot && flager->precision < 0)
            flager->precision = 6;
    }
    i = 0;
    len = (int)ft_strlen(p);
    space = ft_space_s(flager, len);
    if (flager->minus > 0)
        count += ft_proc2_s(len, p, flager, space);
    else if (flager->minus == 0 && flager->zero == 0 && flager->dot == 1 && flager->precision > 0)
        count += ft_circle_s_space_reverse(len, p, flager, space);
    else if (flager->width == 0 && flager->precision == 0 && flager->dot == 0)
        count += ft_circle_s(len, p, flager);
    else if (flager->width > 0 && flager->dot == 0)
        count += ft_circle_s_space_reverse(len, p, flager, space);
    else if (flager->width > 0 && flager->dot == 1 && flager->precision == 0)
        count += ft_space_circle(space);
    return (count);
}

int ft_circle_x(char *l, int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        write(1, &l[i], 1);
        i++;
    }
    return (i);
}

int ft_space_x(t_fl *flager, int len, int fl)
{
    int space;
    
    space = 0;
    fl = 0;
    if (flager->width >= flager->precision && flager->precision <= len)
        space = flager->width - len;
    else if (flager->width >= flager->precision && flager->precision > len && flager->flpr == 0)
        space = flager->width - flager->precision;
    else if (flager->width >= flager->precision && flager->precision > len && flager->flpr == 1)
        space = flager->width - len;
    else if (flager->precision > flager->width && flager->flpr == 1)
        space = flager->width - len;
    return (space);
}
int ft_zero_x(t_fl *flager, int len)
{
    int zero;

    zero = 0;
    if (flager->width >= flager->precision && flager->precision > len && flager->flpr == 0)
        zero = flager->precision - len;
    else if (flager->precision > flager->width)
        zero = flager->precision - len;
    else if (flager->width > 0 && flager->dot == 0 && flager->zero == 1)
        zero = flager->width - len;
    return (zero);
}
int ft_proc_x(va_list as, t_fl *flager, char type)
{
    int p;
    int i;
    int len;
    char *l;
    int fl;
    int count;
    int space;
    int zero;

    zero = 0;
    fl = 0;
    count = 0;
    i = 0;
    len = 0;
    p = va_arg(as, unsigned int);
    if (p < 0)
    {
        fl += 1;
    }
    if (type == 'x')
    {
        l = itoa_basex(p);
    }
    else
        l = itoa_baseux(p);
    len = (int)ft_strlen(l);
    space = ft_space_x(flager, len , fl);
    zero = ft_zero_x(flager, len);
    if (flager->minus > 0)
    {
        if (flager->flpr == 0)
        {
            count += ft_zero_circle(zero);
        }
        count += ft_circle_x(l, len);
        count += ft_space_circle(space);
    }
    else if (flager->minus == 0)
    {
        if (flager->width >= flager->precision && flager->precision > 0)
        {
            count += ft_space_circle(space);
            if (flager->flpr == 0)
            {
                count += ft_zero_circle(zero);
            }
        }
        else if (flager->precision > flager->width)
        {
            if (flager->flpr == 0)
                count += ft_zero_circle(zero);
            else if (flager->flpr == 1)
                count += ft_space_circle(space);
        }
        else if (flager->width > 0 && flager->precision == 0)
        {
            count += ft_space_circle(space);
            count += ft_circle_x(l, len);
        }
        if (flager->width > 0 && flager->precision > 0)
            count += ft_circle_x(l, len);
        else if (flager->dot == 0 && p == 0)
            count += ft_circle_x(l, len);
    }
    free (l);
    return (count);
}

void init_struct(t_fl *flager)
{
	flager->width = 0;
	flager->dot = 0;
	flager->minus = 0;
	flager->zero = 0;
	flager->precision = -1;
    flager->rzero = 0;
    flager->rspace = 0;
    flager->flpr = 0;
    flager->type = 0;
    flager->star = 0;
}
int ft_circle_0x(void)
{
    write(1, "0", 1);
    write(1, "x", 1);
    return (2);
}
int ft_circle_p(int len, char *l)
{
    int i;

    i = 0;
    while(i < len)
    {
        write(1, &l[i], 1);
        i++;
    }
    return (i);
}
int ft_space_p(t_fl *flager, int len)
{
    int space;

    space = 0;
    space = flager->width - len - 2;
    return (space);
}
int ft_proc_p(va_list as, t_fl *flager)
{
    unsigned long p;
    int i;
    int len;
    char *l;
    int fl;
    int count;
    int space;


    fl = 0;
    space = 0;
    count = 0;
    i = 0;
    len = 0;
    p = va_arg(as, unsigned long);
    l = itoa_basep(p);
    len = (int)ft_strlen(l);
    space = ft_space_p(flager, len);
    if (flager->minus > 0)
    {
        count += ft_circle_0x();
        count += ft_circle_p(len, l);
        count += ft_space_circle(space);
    }
    else if (flager->minus == 0)
    {
        count += ft_space_circle(space);
        count += ft_circle_0x();
        count += ft_circle_p(len, l);
    }
    free (l);
    return (count);

}
int ft_flags(const char *s, va_list as, t_fl *flager)
{
    int ram;

    ram = 0;
    if (*s == 's')
    {
        ram += ft_proc_s(as, flager);
        s++;
    }
    else if (*s == 'd' || *s == 'i')
    {
        ram = ft_proc_di(as, flager);
        s++;
    }
    else if (*s == 'u')
    {
        ram = ft_proc_u(as, flager);
        s++;
    }
    else if (*s == 'c')
    {
        ram = ft_proc_c(as, flager, 0);
        s++;
    }
    else if (*s == 'x')
    {
        ram = ft_proc_x(as, flager,'x');
        s++;
    }
    else if (*s == 'X')
    {
        ram = ft_proc_x(as, flager,'X');
        s++;
    }
    else if (*s == '%')
    {
        ram = ft_proc_c(as, flager, '%');
        s++;
    }
    else if (*s == 'p')
    {
        ram = ft_proc_p(as, flager);
        s++;
    }
    return (ram);
}

int ft_printf(const char *s, ...)
{
    va_list as;

    int count;
    t_fl flager;
    int prov;
    int i;

    i = 0;
    prov = 0;
    va_start(as, s);
    count = 0;
    while (*s)
    {
        if (*s == '%')
        {
            init_struct(&flager);
            s++;
            while (*s == '-' || *s == '0')
            {
                if (*s == '0' && flager.minus != 1 && flager.zero != 1)
                    flager.zero = 1;
                else if (*s == '-' && flager.minus != 1)
                {
                    flager.minus = 1;
                    flager.zero = 0;
                }
                s++;
            }
            if (*s >= '0' && *s <= '9')
            {
                flager.width = ft_atoi(s);
                while (*s >= '0' && *s <= '9')
                    s++;
            }
            if (*s == '*')
            {
                prov = va_arg(as,int);
                if (prov < 0)
                {
                    prov *= -1;
                    flager.minus = 1;
                }
                //printf("%d\n",flager.minus);
                flager.width = prov;
                s++;
            }
            if (*s == '.')
            {
                flager.dot +=1;
                s++;
                if (*s >= '0' && *s <= '9')
                {
                    flager.precision = ft_atoi(s);
                    flager.star = 1;
					while (*s >= '0' && *s <= '9')
						s++;
                }
                if (*s == '*')
                {
                    prov = va_arg(as, int);
                    if (prov < 0)
                        flager.flpr += 1;
                    flager.precision = prov;
                    s++;
                }
            }
            count += ft_flags(s, as, &flager);
            s++;
        }
        else
            count += write(1, s++, 1);
    }
    va_end(as);
    return (count);
}
// int main()
// {
   
// // //     // ft_printf("%u", 0000042);
// // //     // printf("\n");
// // //     // printf("%u", 0000042);
// // //    // printf("%0*.*d",14,4,14312);
// // //     // ft_printf("%*.*x\n",-11,-15,1423121);
// // //     // printf("%*.*x\n",-11,-15,1423121);
// // //     // ft_printf("m%05.u\n",43);
// // //     // printf("o%05.u\n",43); 
// //     // printf("o %.*s \n", -2, NULL);
    
// //     // ft_printf("m %.*s \n", -2, NULL);
// //     //printf("\n");
// //     // ft_printf(" 0*%-0*.10d*0 \n", 21,1021);
// //     // printf(" 0*%-*.10d*0 \n", 21, 1021);
// //     //ft_printf(" %d ", 0);
// //     //printf(" %d ", 0);
// //     // ft_printf(" %.0d \n", 0);


//         unsigned long		l;
// 	    l = 2222212;
// //     /////testdi////
// //     // ft_printf("m --0*%0*.0d*0 0*%0*.10d*0-- \n", -2, 0, 21, 1);
// //     // printf("o --0*%0*.0d*0 0*%0*.10d*0-- \n", -2, 0, 21, 1);
// //     // ft_printf("m --0*%-0*.10d*0 0*%-0*.0d*0 \n", 21, 1021, 21, -1011);
// //     // printf("o --0*%-*.10d*0 0*%-*.0d*0 \n", 21, 1021, 21, -1011);
// //     // ft_printf("m --0*%0*.0d*0 0*%0*.10d*0-- \n", -2, 0, 21, 1);
// //     // printf("o --0*%0*.0d*0 0*%0*.10d*0-- \n", -2, 0, 21, 1);
// //     // printf("o %*.*d \n",  -22, -20,-22);
// //     // ft_printf("m %*.*d \n",-22,-20,-22);
// //     // ft_printf("m *%-*.*d* *%*.*d* \n", 6, 2, 102, 10, 21, -101);
// //     // printf("o *%-*.*d* *%*.*d* \n", 6, 2, 102, 10, 21, -101);
// //     // // printf(" *%-*.*d*\n", 6, 2, -102);
// //     // printf("o --0*%0*.0d*0 0*%0*.10d*0-- \n", -21, 2147483647, 21, -2147483647);
// //     // ft_printf("m --0*%0*.0d*0 0*%0*.10d*0-- \n", -21, 2147483647, 21, -2147483647);
// //     // printf("%1.d\n", 0);
// //     // ft_printf("%1.d\n", 0);
// //     // ft_printf("m%3d\n", 1011);
// //     // printf("o%3d\n", 1011);
//         // printf("o%011.0d\n", 2147483647);
//         // ft_printf("m%011.0d\n", 2147483648);
//     //    printf("o%-43.12u\n", 0);
//     //    ft_printf("m%-43.12u\n", 0);
//     // int k;
//     // ft_printf("m --0*%0*.0d*0 \n", -2, 0);
//     // printf("o --0*%0*.0d*0 \n", -2, 0);

//     // k = 1243124;
//     // printf("o %0*.0d*0 \n", -2, 0);
//     // ft_printf("m %0*.0d*0 \n", -2, 0);
//     ft_printf("%9.0x", 429496729);
//     printf("%9.0x", 429496729);
// }
