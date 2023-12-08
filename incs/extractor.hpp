/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:43:12 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/08 13:41:46 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRACTOR_HPP
# define EXTRACTOR_HPP

# include <string>
# include <sstream>
# include <deque>

class Extractor : public std::string
{
	public:
		Extractor();
		Extractor(const std::string& other);
		Extractor(const std::string& str, size_t pos, size_t len = std::string::npos);
		Extractor	*extract_to(std::string delimiter, bool or_end = false);
		Extractor	*extract_from(std::string delimiter, bool or_end = false);

		template <typename T>
		T	to(void)
		{
			T	output;
		
			std::stringstream ss;
			ss << (*this);
			ss >> output;
			return (output);
		};
		bool						is_digits(size_t len = 0);
		std::deque<std::string>		split(std::string delimiter = " ");
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
