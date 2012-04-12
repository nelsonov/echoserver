/*
Copyright (C) 2012 Pellegrino E.

This file is part of libcrafter

This is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifndef IPV4PARSE_H_
#define IPV4PARSE_H_

typedef struct ipv4_parse_ctx
{
	unsigned char m_state[4] [256];
	unsigned short m_index[4];

} ipv4_parse_ctx;

/*
 * ipv4_parse_ctx_init()
 *
 *
 */

int ipv4_parse_ctx_init (ipv4_parse_ctx *ctx, char *range);

/*
 * ipv4_parse_next_addr()
 *
 *
 */

int ipv4_parse_next (ipv4_parse_ctx *ctx, unsigned int *addr);

std::vector<std::string>* ParseIP(const std::string& str_argv);

#endif /* IPV4PARSE_H_ */
