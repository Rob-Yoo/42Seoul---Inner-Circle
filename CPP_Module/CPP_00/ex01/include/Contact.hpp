/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 21:52:34 by jinyoo            #+#    #+#             */
/*   Updated: 2022/05/28 22:29:06 by jinyoo           ###   ########.fr       */
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
	Contact(void);

	std::string	getFname(void);
	std::string	getLname(void);
	std::string	getNickname(void);
	std::string	getPnum(void);
	std::string	getDsecret(void);

	void	setFname(std::string fname);
	void	setLname(std::string lname);
	void	setNickname(std::string nickname);
	void	setPnum(std::string pnum);
	void	setDsecret(std::string dsecret);

	bool	make_new_contact(void);
};

#endif
