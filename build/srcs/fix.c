/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <claudio.raimondi@pm.me>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:02:36 by craimond          #+#    #+#             */
/*   Updated: 2025/01/13 19:43:38 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/fix.h"

//TODO pool di connessioni
void init_fix(fix_client_t *const fix, ssl_data_t *ssl_data)
{
  fix->addr = (struct sockaddr_in){
    .sin_family = AF_INET,
    .sin_port = htons(FIX_PORT),
    .sin_addr = {
      .s_addr = inet_addr(FIX_HOST) //TODO getaddrinfo e dns resolve
    }
  };

  const uint16_t fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
  setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &(bool){1}, sizeof(bool));
  init_ssl_socket(fd, &fix->ssl_sock);

  connect(fd, (const struct sockaddr *)&fix->addr, sizeof(fix->addr));
  wolfSSL_connect(fix->ssl_sock.ssl);

  dup2(fd, FIX_FILENO);
  close(fd);
}

void free_fix(fix_client_t *const fix)
{
  free_ssl_socket(&fix->ssl_sock);
  close(FIX_FILENO);
}