// These are interface classes for the STL iterator types.

// Remove warning about truncated identifier names in the browser
#pragma warning(disable:4786)

#ifndef __ITERATOR_BASE_H
#define __ITERATOR_BASE_H

#include <iterator>

// In all classes, 'I' is the iterator implementation.
template<class I> class stl_bidirectional_iterator;
template<class I> class stl_const_bidirectional_iterator;
template<class I> class stl_random_access_iterator;
template<class I> class stl_const_random_access_iterator;

// Required for bidirectional iterator I:
//	types value_type, pointer, const_pointer, reference, const_reference, distance_type
//	I()
//	I(const I& other);
//	I& operator=(const I& other);
//	bool operator==(const I& other) const;
//	I::reference GetData();
//	I::const_reference GetData() const;
//	void MoveNext();
//	void MovePrev();

// Required for random_access_iterator I:
//	types value_type, pointer, const_pointer, reference, const_reference, distance_type
//	I()
//	I(const I& other);
//	I& operator=(const I& other);
//	bool operator==(const I& other) const;
//	I::reference GetData();
//	I::const_reference GetData() const;
//	void MoveNext(unsigned n);
//	void MovePrev(unsigned n);
//	void MoveTo(size_t i);
//	size_t GetIndex() const;

template<class I>
class stl_bidirectional_iterator : public std::iterator<std::bidirectional_iterator_tag, typename I::value_type, typename I::distance_type>
{
	friend class stl_const_bidirectional_iterator<I>;
protected:
	I iter;
public:
	typedef typename I::pointer pointer;
	typedef typename I::reference reference;

	stl_bidirectional_iterator()
		: iter()
	{}
	stl_bidirectional_iterator(const stl_bidirectional_iterator<I>& other)
		: iter(other.iter)
	{}
	stl_bidirectional_iterator(const I& other)
		: iter(other)
	{}
	operator I&() { return iter;}
	operator const I&() const { return iter;}
	stl_bidirectional_iterator<I>& operator=(const I& other)
	{
		iter = other;
		return *this;
	}
	bool operator==(const I& other) const
	{
		return iter == other;
	}
	bool operator!=(const I& other) const
	{
		return iter != other;
	}
	reference operator*()
	{
		return iter.GetData();
	}
	pointer operator->()
	{
		return &iter.GetData();
	}
	stl_bidirectional_iterator<I>& operator++()
	{
		iter.MoveNext();
		return *this;
	}
	stl_bidirectional_iterator<I> operator++(int)
	{
		I tmp(iter);
		iter.MoveNext();
		return tmp;
	}
	stl_bidirectional_iterator<I>& operator--()
	{
		iter.MovePrev();
		return *this;
	}
	stl_bidirectional_iterator<I> operator--(int)
	{
		I tmp(iter);
		iter.MovePrev();
		return tmp;
	}
};

template<class I>
class stl_const_bidirectional_iterator : public std::iterator<std::bidirectional_iterator_tag, typename I::value_type, typename I::distance_type>
{
protected:
	I iter;
public:
	typedef typename I::const_pointer pointer;
	typedef typename I::const_reference reference;

	stl_const_bidirectional_iterator()
		: iter()
	{}
	stl_const_bidirectional_iterator(const stl_const_bidirectional_iterator<I>& other)
		: iter(other.iter)
	{}
	stl_const_bidirectional_iterator(const stl_bidirectional_iterator<I>& other)
		: iter(other.iter)
	{}
	stl_const_bidirectional_iterator(const I& other)
		: iter(other)
	{}
	operator I&() { return iter;}
	operator const I&() const { return iter;}
	stl_const_bidirectional_iterator<I>& operator=(const I& other)
	{
		iter = other;
		return *this;
	}
	bool operator==(const I& other) const
	{
		return iter == other;
	}
	bool operator!=(const I& other) const
	{
		return iter != other;
	}
	reference operator*() const
	{
		return iter.GetData();
	}
	pointer operator->() const
	{
		return &iter.GetData();
	}
	stl_const_bidirectional_iterator<I>& operator++()
	{
		iter.MoveNext();
		return *this;
	}
	stl_const_bidirectional_iterator<I> operator++(int)
	{
		I tmp(iter);
		iter.MoveNext();
		return tmp;
	}
	stl_const_bidirectional_iterator<I>& operator--()
	{
		iter.MovePrev();
		return *this;
	}
	stl_const_bidirectional_iterator<I> operator--(int)
	{
		I tmp(iter);
		iter.MovePrev();
		return tmp;
	}
};


template<class I>
class stl_random_access_iterator : public std::iterator<std::random_access_iterator_tag, typename I::value_type, typename I::distance_type>
{
	friend class stl_const_random_access_iterator<I>;
protected:
	I iter;
public:
	typedef typename I::pointer pointer;
	typedef typename I::reference reference;
	typedef typename I::distance_type distance;

	stl_random_access_iterator()
		: iter()
	{}
	stl_random_access_iterator(const stl_random_access_iterator<I>& other)
		: iter(other.iter)
	{}
	stl_random_access_iterator(const I& other)
		: iter(other)
	{}
	operator I&() { return iter;}
	operator const I&() const { return iter;}
	stl_random_access_iterator<I>& operator=(const I& other)
	{
		iter = other;
		return *this;
	}
	bool operator<(const I& other) const
	{
		typename I::distance_type d = other.GetIndex() - iter.GetIndex();
		return d > 0;
	}
	bool operator==(const I& other) const
	{
		return iter == other;
	}
	bool operator!=(const I& other) const
	{
		return iter != other;
	}
	reference operator*()
	{
		return iter.GetData();
	}
	pointer operator->()
	{
		return &iter.GetData();
	}
	stl_random_access_iterator<I>& operator++()
	{
		iter.MoveNext();
		return *this;
	}
	stl_random_access_iterator<I> operator++(int)
	{
		I tmp(iter);
		iter.MoveNext();
		return tmp;
	}
	stl_random_access_iterator<I>& operator--()
	{
		iter.MovePrev();
		return *this;
	}
	stl_random_access_iterator<I> operator--(int)
	{
		I tmp(iter);
		iter.MovePrev();
		return tmp;
	}
	distance operator-(const I& other) const
	{
		typename I::distance_type d = iter.GetIndex() - other.GetIndex();
		return d;
	}
	reference operator[](size_t i)
	{
		I tmp(iter);
		tmp.MoveTo(i);
		return tmp.GetData();
	}
	stl_random_access_iterator<I>& operator+=(int n)
	{
		if(n > 0)
			iter.MoveNext(n);
		else if(n < 0)
			iter.MovePrev(-n);
		return *this;
	}
	stl_random_access_iterator<I>& operator-=(int n)
	{
		if(n > 0)
			iter.MovePrev(n);
		else if(n < 0)
			iter.MoveNext(-n);
		return *this;
	}
	stl_random_access_iterator<I> operator+(int n)
	{
		stl_random_access_iterator<I> tmp(iter);
		tmp += n;
		return tmp;
	}
	stl_random_access_iterator<I> operator-(int n)
	{
		stl_random_access_iterator<I> tmp(iter);
		tmp -= n;
		return tmp;
	}
};

template<class I>
stl_random_access_iterator<I> operator+(int n, const stl_random_access_iterator<I>& iter)
{
	return iter+n;
}

template<class I>
class stl_const_random_access_iterator : public std::iterator<std::random_access_iterator_tag, typename I::value_type, typename I::distance_type>
{
protected:
	I iter;
public:
	typedef typename I::const_pointer const_pointer;
	typedef typename I::const_reference const_reference;
	typedef typename I::distance_type distance_type;

	stl_const_random_access_iterator()
		: iter()
	{}
	stl_const_random_access_iterator(const stl_const_random_access_iterator<I>& other)
		: iter(other.iter)
	{}
	stl_const_random_access_iterator(const stl_random_access_iterator<I>& other)
		: iter(other.iter)
	{}
	stl_const_random_access_iterator(const I& other)
		: iter(other)
	{}
	operator I&() { return iter;}
	operator const I&() const { return iter;}
	stl_const_random_access_iterator<I>& operator=(const I& other)
	{
		iter = other;
		return *this;
	}
	bool operator==(const I& other) const
	{
		return iter == other;
	}
	bool operator!=(const I& other) const
	{
		return iter != other;
	}
	const_reference operator*() const
	{
		return iter.GetData();
	}
	const_pointer operator->() const
	{
		return &iter.GetData();
	}
	stl_const_random_access_iterator<I>& operator++()
	{
		iter.MoveNext();
		return *this;
	}
	stl_const_random_access_iterator<I> operator++(int)
	{
		I tmp(iter);
		iter.MoveNext();
		return tmp;
	}
	stl_const_random_access_iterator<I>& operator--()
	{
		iter.MovePrev();
		return *this;
	}
	stl_const_random_access_iterator<I> operator--(int)
	{
		I tmp(iter);
		iter.MovePrev();
		return tmp;
	}
	bool operator<(const I& other) const
	{
		typename I::distance_type d = other.GetIndex() - iter.GetIndex();
		return d > 0;
	}
	distance_type operator-(const I& other) const
	{
		typename I::distance_type d = iter.GetIndex() - other.GetIndex();
		return d;
	}
	const_reference operator[](size_t i) const
	{
		I tmp(iter);
		tmp.MoveTo(i);
		return tmp.GetData();
	}
	stl_const_random_access_iterator<I>& operator+=(int n)
	{
		if(n > 0)
			iter.MoveNext(n);
		else if(n < 0)
			iter.MovePrev(-n);
		return *this;
	}
	stl_const_random_access_iterator<I>& operator-=(int n)
	{
		if(n > 0)
			iter.MovePrev(n);
		else if(n < 0)
			iter.MoveNext(-n);
		return *this;
	}
	stl_const_random_access_iterator<I> operator+(int n)
	{
		stl_const_random_access_iterator<I> tmp(iter);
		tmp += n;
		return tmp;
	}
	stl_const_random_access_iterator<I> operator-(int n)
	{
		stl_const_random_access_iterator<I> tmp(iter);
		tmp -= n;
		return tmp;
	}
};

template<class I>
stl_const_random_access_iterator<I> operator+(int n, const stl_const_random_access_iterator<I>& iter)
{
	return iter+n;
}


#endif
