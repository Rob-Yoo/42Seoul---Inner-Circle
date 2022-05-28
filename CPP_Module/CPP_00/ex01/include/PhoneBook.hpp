/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:55:56 by jinyoo            #+#    #+#             */
/*   Updated: 2022/05/28 22:29:25 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONE_BOOK_HPP
# define PHONE_BOOK_HPP

#include "Contact.hpp"

class PhoneBook {
private:
	Contact	m_contacts[8];
	bool	m_is_empty;
	int		m_contact_idx;
	int		m_contact_num;

	void	show_saved_contact(int i, bool is_last);
	void	show_contact_list(void);
	void	show_search_interface(void);
	void	show_searched_contact(int idx);
public:
	PhoneBook(void);

	int		get_m_contact_num(void);
	
	void	add_new_contact(void);
	void	search_saved_contacts(void);
};

#endif
