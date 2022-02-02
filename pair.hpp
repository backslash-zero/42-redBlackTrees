#pragma once

#include <iostream>
#include <string>

namespace ft {

	// Re-Defining std::pair structure
	template <class T1, class T2>
	struct pair
	{
		T1 first;
		T2 second;

		// Constructors
		pair(void) : first(), second() {};
		template <class T, class U>
		pair(const pair<T, U> & src) : first(src.first), second(src.second) {};
		pair(const T1 &a, const T2 &b) : first(a), second(b) {};

		// Operator overload
		pair &operator=(const pair &rhs)
		{
			if (this != &rhs)
			{
				this->first = rhs.first;
				this->second = rhs.second;
			}
			return(*this);
		}
	};

	// Redifing non-menber functions: 

	template<class T1, class T2>
	ft::pair<T1,T2> make_pair( T1 t, T2 u )
	{
		ft::pair<T1, T2> new_pair(t, u);
		return (new_pair);
	};

	// re-defining comparation operators for ft::pairs:

	template <class T1, class T2>
	bool operator==(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) 
	{
		if (lhs.first == rhs.first && lhs.second == rhs.second)
			return (true);
		return (false);
	}

	template <class T1, class T2>
	bool operator!=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) 
	{
		if (lhs == rhs)
			return (false);
		return (true);
	}

	template <class T1, class T2>
	bool operator< (const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) 
	{
		if (lhs.first < rhs.first)
			return (true);
		if (lhs.first == rhs.first && lhs.second < rhs.second)
			return (true);
		return (false);
		// return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template <class T1, class T2>
	bool operator<=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) 
	{
		if (rhs < lhs)
			return (false);
		return (true);
	}

	template <class T1, class T2>
	bool operator> (const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) 
	{
		if (rhs < lhs)
			return (true);
		return (false);
	}

	template <class T1, class T2>
	bool operator>=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs) 
	{
		if (lhs < rhs)
			return (false);
		return (true);
	}

	// << overload
	template< class T1, class T2 >
    std::ostream & operator<<( std::ostream & flux, ft::pair<T1, T2> const & rhs)
    {
        flux << rhs.second << std::endl;
        return flux;
    }

}

