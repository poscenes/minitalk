/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poscenes <poscenes@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 11:59:18 by poscenes          #+#    #+#             */
/*   Updated: 2022/01/16 14:05:25 by poscenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_message	g_message;

static void	init_message(t_message *message)
{
	int	cnt;

	cnt = 0;
	message->transaction_on_go = 1;
	message->bit_pos = 0;
	message->str_pos = 0;
	while (cnt < BUFF)
	{
		message->str[cnt] = 0;
		cnt++;
	}
}

static void	print_message(void)
{
	int	cnt;

	write(1, g_message.str, g_message.str_pos);
	cnt = 0;
	while (cnt < g_message.str_pos)
	{
		g_message.str[cnt] = 0;
		cnt++;
	}
	g_message.str_pos = 0;
}

static void	acc_bit(int sig, siginfo_t *info, void *context)
{
	int	bit;

	(void)context;
	if (sig == SIGUSR1)
		bit = 0;
	else
		bit = 1;
	g_message.str[g_message.str_pos] |= (bit << (7 - g_message.bit_pos));
	if (++g_message.bit_pos == 8)
	{
		if (g_message.str[g_message.str_pos] == '\0')
		{
			g_message.transaction_on_go = 0;
			print_message();
			kill(info->si_pid, SIGUSR2);
			write(1, "\n", 1);
			return ;
		}
		g_message.bit_pos = 0;
		g_message.str_pos++;
		if (g_message.str_pos == BUFF)
			print_message();
	}
	usleep(50);
	kill(info->si_pid, SIGUSR1);
}

static void	decoder_func(void)
{
	struct sigaction	handler;

	handler.sa_sigaction = acc_bit;
	handler.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &handler, NULL) < 0)
	{
		write(1, "Sigaction Error!\n", 18);
		exit(0);
	}
	if (sigaction(SIGUSR2, &handler, NULL) < 0)
	{
		write(1, "Sigaction Error!\n", 18);
		exit(0);
	}
	while (g_message.transaction_on_go)
		pause();
}

int	main(void)
{
	int		pid;
	char	message[BUFF];

	g_message.str = message;
	pid = getpid();
	write(1, "Hey you, hello! My PID: ", 24);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	while (1)
	{
		init_message(&g_message);
		decoder_func();
	}
}
