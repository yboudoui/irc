/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Colors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:54:16 by yboudoui          #+#    #+#             */
/*   Updated: 2023/12/06 16:27:08 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_HPP
# define COLORS_HPP

# define RESET		"\033[0m"
# define BLACK		"\033[30m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define BLUE		"\033[34m"
# define YELLOW		"\033[33m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"
# define BOLD		"\033[1m"

# ifdef DEBUG

# define PRINT_DEBUG_MESSAGE(color, message)\
	std::cout << color << message << RESET << std::endl;

# define PRINT_DEBUG_CALL(color, class_name)\
	PRINT_DEBUG_MESSAGE(color, #class_name << "::" << __FUNCTION__)

# else
# define PRINT_DEBUG_MESSAGE(color, message)
# define PRINT_DEBUG_CALL(color, class_name)
# endif

#endif
