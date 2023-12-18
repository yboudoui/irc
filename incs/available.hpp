/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   available.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:43:02 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/18 16:43:48 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVAILABLE_HPP
# define AVAILABLE_HPP

template <typename Type>
class available
{
	public:
	available()
		: _ok(false)
	{}

	available(Type& value)
		: _ok(true)
		, _value(value)
	{}

	operator bool() const {
		return _ok;
	}

	available& operator = (available other) {
		_value = other._value;
		_ok = other._ok;
		return (*this);
	}

	void operator ()(Type v) {
		_value = v;
		_ok = true;
	}

	Type& operator ()(void)  {
		return (_value);
	}

	Type operator ()(void) const {
		return (_value);
	}

	std::ostream& operator<< (std::ostream& stream) const {
		if (_ok)
			stream << _value;
		return (stream);
	}

	private:
		bool	_ok;
		Type	_value;
};

#endif
