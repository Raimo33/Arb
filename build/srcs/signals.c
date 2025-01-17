/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <claudio.raimondi@pm.me>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:15:10 by craimond          #+#    #+#             */
/*   Updated: 2025/01/19 09:37:18 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/signals.h"

void init_signals(void)
{
  sigset_t mask;

  sigemptyset(&mask);
  sigaddset(&mask, SIGINT);
  sigaddset(&mask, SIGTERM);
  sigprocmask(SIG_BLOCK, &mask, NULL);

  const uint16_t fd = signalfd(-1, &mask, SFD_NONBLOCK);
  dup2(fd, SIG_FILENO);
  close(fd);
}

inline void check_signals(const char fd_state)
{
  switch (fd_state)
  {
    case '\0':
      break;
    case 'r':
      panic(STR_LEN_PAIR("Signal received"));
    case 'e':
      panic(STR_LEN_PAIR("Error on signal fd"));
    default:
      UNREACHABLE;
  }
}

void free_signals(void)
{
  close(SIG_FILENO);
}