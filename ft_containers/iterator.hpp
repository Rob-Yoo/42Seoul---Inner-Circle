/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 22:01:20 by jinyoo            #+#    #+#             */
/*   Updated: 2023/01/19 23:03:16 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <memory>

namespace ft {
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
struct iterator {
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
};
// iterator_traits => 템플릿은 제네릭 프로그래밍이기 때문에 iterator 같이 타입이 있는 경우 컴파일 타임에서 타입에 따른 분기를 위해 _traits를 만들어준다.
template<typename Iter>
struct iterator_traits {
	typedef typename Iter::iterator_category	iterator_category;
	typedef typename Iter::value_type			value_type;
	typedef typename Iter::difference_type		difference_type;
	typedef typename Iter::pointer				pointer;
	typedef typename Iter::reference			reference;
};

template<typename T>
struct iterator_traits<T*>	// 포인터일 경우를 특수화
{
	typedef random_access_iterator_tag	iterator_category;
	typedef T							value_type;
	typedef std::ptrdiff_t				difference_type; // ptrdiff_t는 두 포인터의 거리를 나타내는 타입
	typedef T*							pointer;
	typedef T&							reference;
};

template <typename T>
struct iterator_traits<const T*>
{
	typedef random_access_iterator_tag	iterator_category;
	typedef T							value_type;
	typedef std::ptrdiff_t				difference_type;
	typedef const T*					pointer;
	typedef const T&					reference;
};

template <class Iterator> 
class reverse_iterator {
public:
	typedef Iterator												iterator_type;
	typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename iterator_traits<Iterator>::value_type			value_type;
	typedef typename iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename iterator_traits<Iterator>::pointer				pointer;
	typedef typename iterator_traits<Iterator>::reference			reference;

private:
	iterator_type _iter;

public:
	// Constructor
	reverse_iterator(): _iter() {}
	explicit reverse_iterator(iterator_type it): _iter(it) {}
	template <class Iter>
	reverse_iterator(const reverse_iterator<Iter>& rev_it): _iter(rev_it.base()) {}

	// methods
	iterator_type base() const {
		return _iter;
	}
	reference operator*() const { // reverse_iteratort의 시작은 _iter.end()이므로 *(--tmp)를 리턴해야함
		iterator_type tmp = _iter;
		return *(--tmp);
	}
	reverse_iterator operator+(difference_type n) const {
		reverse_iterator tmp(*this);
		return tmp += n;
	}
	reverse_iterator& operator++() {
		--_iter; // reverse_iteratort이므로 ++일 땐 --이어야함
		return *this;
	}
	reverse_iterator operator++(int) { // 후위 증가 연산자 int는 dummy parameter -> 전위 연산자와 구분짓기 위해서 사용
		reverse_iterator tmp(*this);
		--_iter;
		return tmp;
	}
	reverse_iterator& operator+=(difference_type n) {
		_iter -= n;
		return *this;
	}
	reverse_iterator operator-(difference_type n) const {
		reverse_iterator tmp(*this);
		return tmp -= n;
	}
	reverse_iterator& operator--() { //전위 감소연산자
		++_iter;
		return *this;
	}
	reverse_iterator operator--(int) { 
		reverse_iterator tmp(*this);
		++_iter;
		return tmp;
	}
	reverse_iterator& operator-=(difference_type n) {
		_iter += n;
		return *this;
	}
	pointer operator->() const {
		return &(operator*());
	}
	reference operator[](difference_type n) const {
		iterator_type tmp = _iter;
		return *(tmp - n - 1);
	}
};

// non-member
template<typename Iterator>
bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
	return lhs.base() == rhs.base();
}
template<typename Iterator>
bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
	return lhs.base() != rhs.base();
}
template<typename Iterator>
bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
	return lhs.base() > rhs.base();
}
template<typename Iterator>
bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
	return lhs.base() >= rhs.base();
}
template<typename Iterator>
bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
	return lhs.base() < rhs.base();
}
template<typename Iterator>
bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
	return lhs.base() <= rhs.base();
}

template <class Iterator>
reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {
	return rev_it + n;
}
template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
	return rhs.base() - lhs.base();
}

}

#endif