/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 21:52:34 by jinyoo            #+#    #+#             */
/*   Updated: 2022/05/28 17:28:00 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <string>
# include <iostream>
# include <cstdio>
# include <limits>
# include <iomanip>

class Contact {
private:
	std::string	m_fname;
	std::string	m_lname;
	std::string	m_nickname;
	std::string	m_pnum;
	std::string	m_dsecret;
public:
	Contact(void) {};

	std::string	getFname() { return m_fname; };
	std::string	getLname() { return m_lname; };
	std::string	getNickname() { return m_nickname; };
	std::string	getPnum() { return m_pnum; };
	std::string	getDsecret() { return m_dsecret; };

	void	setFname(std::string fname) { m_fname = fname; };
	void	setLname(std::string lname) { m_lname = lname; };
	void	setNickname(std::string nickname) { m_nickname = nickname; };
	void	setPnum(std::string pnum) { m_pnum = pnum; };
	void	setDsecret(std::string dsecret) { m_dsecret = dsecret; };

	bool	make_new_contact(void);
};

#endif