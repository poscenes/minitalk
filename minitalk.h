/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poscenes <poscenes@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 12:53:16 by poscenes          #+#    #+#             */
/*   Updated: 2022/01/15 17:03:23 by poscenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

# define BUFF 1024

struct	s_message
{
	int		str_pos;
	int		bit_pos;
	char	*str;
	int		transaction_on_go;
};

typedef struct s_message	t_message;

size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
void	ft_putnbr_fd(int n, int fd);

#endif
