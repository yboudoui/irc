/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:43:12 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/17 15:34:40 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRACTOR_HPP
# define EXTRACTOR_HPP

# include <string>
#include "Colors.hpp"
# include <sstream>
# include <deque>

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

typedef available<std::string>	t_available_string;

class Extractor
{
	public:
		Extractor();
		Extractor(const std::string& other);
		Extractor(const std::string& str, size_t pos, size_t len = std::string::npos);
		t_available_string	extract_to(std::string delimiter, bool or_end = false);
		t_available_string	extract_from(std::string delimiter, bool or_end = false);

		std::string	str(void) const {return (_data);}

		bool						is_digits(size_t len = 0);
		std::deque<std::string>		split(std::string delimiter = " ");
		Extractor& operator+= (const std::string &str);
		char	operator[] (size_t index);
		size_t	size(void) const;
		void	erase(const char *str);
		Extractor& erase (size_t pos = 0, size_t len = std::string::npos);
		std::string operator = (const Extractor &);
		friend std::ostream& operator<< (std::ostream& stream, Extractor& e);
	private:
		std::string	_data;
};

template <class InputIterator, class UnaryPredicate>
bool	all_of(InputIterator first, InputIterator last, UnaryPredicate pred)
{
	while (first!=last)
	{
		if (!pred(*first))
		return false;
	++first;
	}
	return true;
}

#endif
