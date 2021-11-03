/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 20:32:23 by vserra            #+#    #+#             */
/*   Updated: 2021/11/03 14:27:19 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_H
# define MESSAGE_H

static char g_str_msg[TOTAL][256] =
{
	[EATING] = " is eating\n",
	[SLEEPING] = " is sleeping\n",
	[THINKING] = " is thinking\n",
	[FORK] = " took a fork\n",
	[DIED] = " died\n",
	[ALL] = "All the philosophers had eat enough.\n"
};

#endif