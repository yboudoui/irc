/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BiMultiMap.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 17:05:18 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/20 17:44:55 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIMULTIMAP_HPP
# define BIMULTIMAP_HPP

#include <map>
#include <algorithm>

template <class K, class V>
class value_equals {
	private:
		V value;
	public:
		value_equals	(const V& v) : value(v) {}
		bool operator()	(std::pair<const K, V> elem) {
		    return elem.second == value;
		}
};

template <class A, class B>
struct mm {
	typedef	std::multimap<A,B>			type;
	typedef	typename type::iterator		it;
	typedef	std::pair<it, it>			range;
};


template <class A, class B>
class BiMultiMap
{
	private:
		typedef	mm<A,B>	t_1;
		typedef	mm<B,A>	t_2;

		typename t_1::type		_1;
		typename t_2::type		_2;

	public:
		void	remove(A a)
		{
			typename t_1::range		_1r;
			typename t_1::it		_1i;
			typename t_2::range		_2r;
			typename t_2::it		_2i;

			_1r = _1.equal_range(a);
			if (_1r.first == _1.end())
				return ;
			for (_1i = _1r.first; _1i != _1r.second; _1i++)
			{
				_2r = _2.equal_range(_1i->second);
				_2i = std::find_if(_2r.first, _2r.second, value_equals<B,A>(a));
				_2.erase(_2i);
			}
			_1.erase(a);
		}

		void	remove(B b)
		{
			typename t_1::range		_1r;
			typename t_1::it		_1i;
			typename t_2::range		_2r;
			typename t_2::it		_2i;

			_2r = _2.equal_range(b);
			if (_2r.first == _2.end())
				return ;
			for (_2i = _2r.first; _2i != _2r.second; _2i++)
			{
				_1r = _1.equal_range(_2i->second);
				_1i = std::find_if(_1r.first, _1r.second, value_equals<A,B>(b));
				_1.erase(_1i);
			}
			_2.erase(b);
		}

};

#endif
