/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <claudio.raimondi@pm.me>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:43:46 by craimond          #+#    #+#             */
/*   Updated: 2025/01/17 17:33:03 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_PARSER_H
# define HTTP_PARSER_H

# include <stdint.h>

# include "logger.h"

# define HTTP_GET 0
# define HTTP_POST 1
# define HTTP_PUT 2
# define HTTP_DELETE 3

# define HTTP_1_0 0
# define HTTP_1_1 1

typedef struct
{
  const char *str;
  const uint8_t len;
} str_len_pair_t;

//TODO in caso si scelga di usare allocazione dinamica allora usare array dinamici invece di puntatori (per risparmiare gli 8 byte del puntatore)

typedef struct
{
  const char *key;
  const char *value;

  const uint16_t key_len;
  const uint16_t value_len;
} header_t;

typedef struct
{
  const header_t *headers;
  const char *body;
  const char *path;
  const uint8_t method  : 2;
  const uint8_t version : 1;

  const uint16_t body_len;
  const uint8_t headers_count;
  const uint8_t path_len;
} http_request_t;

typedef struct
{
  const header_t *headers;
  const char *body;
  const uint16_t status_code;
  const uint8_t version : 1;

  const uint16_t body_len;
  const uint8_t headers_count;
} http_response_t;

void __attribute__((hot)) build_http_request(const http_request_t *req, char *buf);
void __attribute__((hot)) parse_http_response(const char *buf, http_request_t *req);

#endif