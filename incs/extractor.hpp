/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:43:12 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/11 18:24:43 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRACTOR_HPP
# define EXTRACTOR_HPP

# include <string>
# include <sstream>
# include <deque>

template <typename Type>
class available
{
	public:
	available()
		: ok(false)
	{}
	operator bool() const {
		return ok;
	}

	available& operator = (available other) {
		value = other.value;
		ok = other.ok;
		return (*this);
	}

	void operator ()(Type v) {
		value = v;
		ok = true;
	}

	std::ostream& operator<< (std::ostream& stream) const {
		if (ok)
			stream << value;
		return (stream);
	}
	bool	ok;
	Type	value;
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

		operator std::string() const { return _data; }

		template <typename T>
		T	to(void)
		{
			T	output;
		
			std::stringstream ss;
			ss << _data;
			ss >> output;
			return (output);
		};
		
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
