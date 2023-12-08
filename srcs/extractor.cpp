/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:44:25 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/08 13:32:49 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extractor.hpp"

Extractor::Extractor() : std::string() { }

Extractor::Extractor(const std::string& other) : std::string(other) { }

Extractor::Extractor(const std::string& str, size_t pos, size_t len): std::string(str, pos, len) {}

Extractor	*Extractor::extract_to(std::string delimiter, bool or_end)
{
	Extractor	*output;
	std::size_t	has_delimiter = this->find(delimiter);
	if (has_delimiter == std::string::npos)
	{
		if (!or_end)
			return (NULL);
		output = new Extractor(*this);
		this->erase();
	}
	else
	{
		output = new Extractor(*this, 0, has_delimiter);
		this->erase(0, has_delimiter + delimiter.size());
	}
	return (output);
}

Extractor	*Extractor::extract_from(std::string delimiter, bool or_end)
{
	Extractor	*output;
	std::size_t	has_delimiter = this->find(delimiter);
	if (has_delimiter == std::string::npos)
	{
		if (!or_end)
			return (NULL);
		output = new Extractor(*this);
		this->erase();

	}
	else
	{
		output = new Extractor(*this, has_delimiter);
		this->erase(has_delimiter);
	}
	return (output);
}

bool	Extractor::is_digits(size_t len)
{
	std::string::iterator	end;
	if (len >= this->size())
		return (false);
	end = this->end();
	if (len != 0)
		end = this->begin() + len;
	return (all_of(this->begin(), end, ::isdigit));
}

std::deque<std::string>	Extractor::split(std::string delimiter)
{
	std::deque<std::string>	output;
	size_t		pos;
	std::string	token;

	pos = this->find(delimiter);
	while (pos != std::string::npos)
	{
		token = this->substr(0, pos);
		output.push_back(token);
		this->erase(0, pos + delimiter.length());
		pos = this->find(delimiter);
	}
	return (output);
}
