/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzabal-m <mzabal-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:34:50 by mzabal-m          #+#    #+#             */
/*   Updated: 2024/12/16 14:43:48 by mzabal-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h> // Para manejar argumentos variádicos
# include <unistd.h> // Para write
# include <stdlib.h> // Para malloc, free, calloc

// Prototipo de ft_printf
int		ft_printf(const char *format, ...);

// Prototipos de los manejadores
int		handle_char(char c);
int		handle_string(char *str);
int		handle_pointer(void *ptr);
int		handle_int(int num);
int		handle_unsigned(unsigned int num);
int		handle_hex_lower(unsigned int num);
int		handle_hex_upper(unsigned int num);

// Prototipo de ft_futoa (para convertir números a cadenas dinámicas)
char	*ft_futoa(unsigned long long num, const char *digits);

// Prototipos de utilidades
int		ft_putstr_printf(char *s);
int		ft_strlen_printf(const char *str);
void	*ft_memcpy_printf(void *dst, const void *src, size_t n);
void	*ft_memset_printf(void *s, int c, size_t n);
void	ft_bzero_printf(void *s, size_t n);
void	*ft_calloc_pf_printf(int count, size_t size);
char	*ft_strdup(const char *s1);

#endif
