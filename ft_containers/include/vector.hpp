/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:04:58 by jinyoo            #+#    #+#             */
/*   Updated: 2022/07/18 20:45:00 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTAINTERS_VECTOR_HPP
# define FT_CONTAINTERS_VECTOR_HPP

# include <iostream>
# include <algorithm>
# include <limits>

template <class T, class Alloc = std::allocator<T> >
class vector {
public:
	typedef T					value_type;
	typedef Alloc				allocator_type;
	typedef value_type&			reference;
	typedef const value_type&	const_reference;
	
	typedef typename std::size_t size_type;

explicit vector (const allocator_type& alloc = allocator_type());
explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
template <class InputIterator>
         vector (InputIterator first, InputIterator last,
                 const allocator_type& alloc = allocator_type());
vector (const vector& x);
};

#endif
