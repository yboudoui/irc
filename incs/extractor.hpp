/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sethomas <sethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:43:12 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/11 15:52:08 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRACTOR_HPP
# define EXTRACTOR_HPP

# include <string>
# include <sstream>
# include <deque>

class Extractor
{
	public:
		Extractor();
		Extractor(const std::string& other);
		Extractor(const std::string& str, size_t pos, size_t len = std::string::npos);
		std::string	*extract_to(std::string delimiter, bool or_end = false);
		std::string	*extract_from(std::string delimiter, bool or_end = false);

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
//		Extractor& operator+= (const char *str);
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
