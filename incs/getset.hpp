/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:33:58 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/26 16:04:45 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETSET_HPP
# define GETSET_HPP

template <typename T>
class	getter
{
	public:
		virtual const T&	get(void) = 0;
};

template <typename T>
class	setter
{
	public:
		virtual void	set(T&) = 0;
};

template <typename T>
class	get_set : public getter<T>, public setter<T>
{
	private:
		T	_value;

	public:
		void	set(T& value)
		{
			_value = value;
		}

		const T&	get(void)
		{
			return (_value);
		}

};

#endif
