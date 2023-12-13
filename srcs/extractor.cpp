/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:44:25 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/13 15:54:06 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extractor.hpp"

Extractor::Extractor()
{}

Extractor::Extractor(const std::string& other)
	: _data(other)
{}

Extractor::Extractor(const std::string& str, size_t pos, size_t len)
	: _data(str, pos, len)
{}

t_available_string	Extractor::extract_to(std::string delimiter, bool or_end)
{
	t_available_string	output;
	std::size_t			has_delimiter;

	has_delimiter = _data.find(delimiter);
	if (has_delimiter == std::string::npos)
	{
		if (!or_end)
			return (output);
		output(_data);
		_data.erase();
	}
	else
	{
		output(std::string(_data, 0, has_delimiter));
		_data.erase(0, has_delimiter + delimiter.size());
	}
	return (output);
}

t_available_string	Extractor::extract_from(std::string delimiter, bool or_end)
{
	t_available_string	output;
	std::size_t			has_delimiter;

	has_delimiter = _data.find(delimiter);
	if (has_delimiter == std::string::npos)
	{
		if (!or_end)
			return (output);
		output(_data);
		_data.erase();
	}
	else
	{
		output(std::string(_data, has_delimiter));
		_data.erase(has_delimiter);
	}
	return (output);
}

bool	Extractor::is_digits(size_t len)
{
	std::string::iterator	end;
	if (len >= _data.size())
		return (false);
	end = _data.end();
	if (len != 0)
		end = _data.begin() + len;
	return (all_of(_data.begin(), end, ::isdigit));
}

std::deque<std::string>	Extractor::split(std::string delimiter)
{
	std::deque<std::string>	output;
	size_t		pos;
	std::string	token;

	pos = _data.find(delimiter);
	while (pos != std::string::npos)
	{
		token = _data.substr(0, pos);
		output.push_back(token);
		_data.erase(0, pos + delimiter.length());
		pos = _data.find(delimiter);
	}
	return (output);
}

size_t	Extractor::size(void) const
{
	return (_data.size());
}

void	Extractor::erase(const char *str)
{
	size_t	pos = _data.find(str);
	_data.erase(pos);
}

Extractor& Extractor::erase(size_t pos, size_t len)
{
	_data.erase(pos, len);
	return (*this);
}

char Extractor::operator[] (size_t index)
{
	return (_data[index]);
}

Extractor& Extractor::operator+= (const std::string &str)
{
	_data += str;
	return (*this);
}

std::string Extractor::operator = (const Extractor &)
{
	return (_data);
}

std::ostream& operator<< (std::ostream& stream, Extractor& e)
{
	stream << e._data;
	return (stream);
}

