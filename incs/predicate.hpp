/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predicate.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:55:49 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/27 16:03:57 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREDICATE_HPP
# define PREDICATE_HPP

template <typename Data>
class predicate {
	public:
		virtual bool operator () (Data) = 0;
};

#endif
