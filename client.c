/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poscenes <poscenes@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 11:59:18 by poscenes          #+#    #+#             */
/*   Updated: 2022/01/16 14:05:10 by poscenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_message	g_message;

static void	send_bit(int sig, siginfo_t *info, void *context)
{
	int	bit;

	(void)context;
	if (sig == SIGUSR2)
	{
		write(1, "Message was successfully sent, sir!\n", 37);
		exit(0);
	}
	bit = ((g_message.str[g_message.str_pos]) >> (7 - g_message.bit_pos)) & 1;
	usleep(50);
	if (bit == 0)
		kill(info->si_pid, SIGUSR1);
	else
		kill(info->si_pid, SIGUSR2);
	++g_message.bit_pos;
	if (g_message.bit_pos == 8)
	{
		g_message.bit_pos = 0;
		++g_message.str_pos;
	}
}

static void	send_message(int serv_pid)
{
	struct sigaction	handler;
	siginfo_t			info;

	handler.sa_sigaction = send_bit;
	handler.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &handler, NULL);
	sigaction(SIGUSR2, &handler, NULL);
	info.si_pid = serv_pid;
	send_bit(SIGUSR1, &info, NULL);
	while (1)
		pause();
}

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		g_message.str = argv[2];
		send_message(ft_atoi(argv[1]));
	}
	else
		write(1, "Usage: ./client [SERVER_PID] [YOUR_MESSAGE]\n", 45);
}
