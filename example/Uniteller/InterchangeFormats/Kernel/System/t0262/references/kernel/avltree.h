//*************************************************************************************
//	Copyright 2001 by Raymond A. Virzi, Jr.
//	You may freely use and distribute this source code provide the above copyright notice
//	and this statement remains intact within the source module or any modified versions of it.
//	email:	mail@rvirzi.com
//
// The class AVLTree<T> was originally created by Andreas Jager.
// It has been modified a bit but the essential algorithms and
// basic functionality has remained intact. I added logic to keep
// track of the indexes allowing the derived classes to work.
//
// Here is the original copyright notice:
//*************************************************************
// Creator: Andreas Jäger
//          Ortsstr. Nr. 2
//        D-07407 Geitersdorf
//
// Last updated: 15. November 1998
// e-mail: Jaeger-Geitersdorf@t-online.de
//
// 
// Copyright and author: 
// Andreas Jäger: Jaeger-Geitersdorf@t-online.de
// 
// You may handle this code to others only when you do not delete these
// copyright-lines.
// These source files may not be copied except by permission of the author.
// These source files may not be included in source or compiled form as any
// part of a commercial distribution except by permission of the
// author. 
// These files may be used freely for internal corporate use.
// These files may also may be used freely by students for 
// educational purposes.
// No warranty or guarrantee of fitness can be made to these files.
//
// 
// have fun!
//
// Updates:
// 
// * 15.11.1998 - Some fixes in Delete()- and RestructureDelete()-
//                routines which could make the tree inconsistent
//                and result in a GPF (after lots of Insert- and 
//                Delete-operations)
//              - Rename Level() -> GetLevel()
//              - new methods GetDepth() and GetCount() for 
//                AVLTree class
//              - new (debug) function CheckBalances()
//              - Draw() function only in Visual C++ environment
//                (not Borland) for portability
//              - updated sample project
//***************************************************************
//////////////////////////////////////////////////////////////////
// Introduction:
//
// Five STL containers are derived from an AVL tree. These are index_list,
// index_set, index_multiset, index_map, index_multimap, all of which 
// are explained at the beginning of each class definition. The unique
// feature of the classes is that they include a fast indexing operation
// (operator[]) made possible by adding an extra long int for each
// tree node to hold the total number of child nodes below it. The extra
// logic required to update these counters does not add to the complexity
// of any of the tree's original algorithms.
// NOTE: The STL interfaces may not be fully complete.
//--------------------------------------------------------------------
// Change History:
// 03/06/01 - Added this copyright notice and uploaded to Code Project
// 03/08/01 - Copy constructor for Sorted_AVLTree was not working -
//            same for sorted containers.
//          - Sortred_AVLTree::swap() missed a data member.
//			- Constructor for index_list which takes a sequence did not
//            preserve the sequence order.
//          - Added assignment operators to all classes via the base classes.
//          - Added empty virtual destructors to all STL classes.
// 11/27/01	- Fixed bugs in random access iterator functions (operator+=,operator-=)
//			  These were not working all the time for n > 1.
//			- Reworked base classes in iterator_base.h to work better with STL template functions.
// 07/20/02	- Fixed return value error in compilation of index_multiset insert function.
//			- Fixed access errors in compilation of index_multiset do to erroneous non-public derivation.
// 08/04/02	- Count function was not working when limit reached the end of container. This caused 
//			  erroneous results for count() function in all associative classes (sets and maps).

#ifndef __AVLTREE_H
#define __AVLTREE_H

// disable STL warnings
#pragma warning(disable:4786)	// truncated identifier in the browser
#pragma warning(disable:4503)	// truncated decorated name
#pragma warning(disable:4127)

#include <memory>
#include <utility>
#include <functional>
#include <algorithm>
#include <assert.h>

#include "iterator_base.h"

// Forward declarations
template<class T> class AVLNode;
template<class T> class AVLTree;

//--------------------------------------------------------------
// class AVLNode

template<class T>
class AVLNode
{
	friend class AVLTree<T>;

	// standard constructor, constructors, destructor
	AVLNode(const T& data, AVLNode<T>* parent = NULL, AVLNode<T>* left = NULL, AVLNode<T>* right = NULL);
	~AVLNode();
public:
	T Data;		// item data
	AVLNode<T>* Parent;	// parent node
	AVLNode<T>* Left;		// left subtree
	AVLNode<T>* Right;		// right subtree
	unsigned long _count;	// number of nodes in tree, including this.
	int Balance;
		// information about the height of the subtrees
		// -1: left subtree is 1 higher than the right one
		//  0: both subtrees have the same height
		//  1: right subtree is 1 higher than the left one

	// restructuration
	bool LeftRotation();
	bool RightRotation();
	bool DoubleRotationLeft();
	bool DoubleRotationRight();
	bool RestructureInsert();
	bool RestructureDelete();
public:
	// Access to data
	T& GetData() { return Data;}
	const T& GetData() const { return Data;}
	// information about the position in the tree
	bool IsRoot() const;
	bool IsLeftSibling() const;
	bool IsRightSibling() const;
	bool HasLeftSibling() const;
	bool HasRightSibling() const;
	// further information
	int GetDepth() const;
	int GetLevel() const;
	unsigned long GetCount() const { return _count;}
	unsigned long GetIndex() const;
	unsigned long GetPositionInTree() const { return Left ? Left->_count : 0;}
	// retrieving other nodes
	AVLNode<T>* GetRoot();
	AVLNode<T>* GetLeftSibling();
	AVLNode<T>* GetRightSibling();
	AVLNode<T>* GetNodeInTree(unsigned long n);
	AVLNode<T>* GetFirstNodeInTree();
	AVLNode<T>* GetLastNodeInTree();
	AVLNode<T>* GetPrevNodeInOrder(unsigned long n = 1);
	AVLNode<T>* GetNextNodeInOrder(unsigned long n = 1);
	// diagnostics
	bool Validate() const;
};


template<class T>
AVLNode<T>::AVLNode(const T& data, AVLNode<T>* parent, AVLNode<T>* left, AVLNode<T>* right)
	: Data(data), Parent(parent), Left(left), Right(right)
{
	// Calculate balance
	Balance = 0;
	Balance += Right ? Right->GetDepth() : 0;
	Balance -= Left ? Left->GetDepth() : 0;

	// Calculate count
	_count = 1;			// add one for this node
	_count += Left ? Left->GetCount() : 0;
	_count += Right ? Right->GetCount() : 0;
}

template <class T>
AVLNode<T>::~AVLNode()
{
	if(Left)
		delete Left;
	if(Right)
		delete Right;
}

template <class T>
bool AVLNode<T>::RestructureInsert()
{
	AVLNode<T>* item = this;
	while(!item->IsRoot())
	{
		switch(item->Parent->Balance)
		{
		case 0:
			if(item->IsLeftSibling())
			{
				item->Parent->Balance = -1;
				item = item->Parent;
			}
			else
			{
				item->Parent->Balance = 1;
				item = item->Parent;
			}
			continue;
		case 1:
			if(item->IsLeftSibling())
			{
				item->Parent->Balance = 0;
			}
			else
			{
				if (item->Balance == -1)
					item->Parent->DoubleRotationRight();
				else
					item->Parent->LeftRotation();
			}
			return true;
		case -1:
			if(item->IsLeftSibling())
			{
				if (item->Balance == 1)
					item->Parent->DoubleRotationLeft();
				else
					item->Parent->RightRotation();
			}
			else
			{
				item->Parent->Balance = 0;
			}
			return true;
		}
		assert(false);		// should never reach
	}
	return true;
}

template <class T>
bool AVLNode<T>::RestructureDelete()
{
	AVLNode<T>* item = this;
	switch(item->Balance)
	{
	case 0:
		if(item->Left == NULL) 
		{
			item->Balance = 1;
			return true;
		}
		if(item->Right == NULL) 
		{
			item->Balance = -1;
			return true;
		}
		break;
	case 1:
		if(item->Right == NULL)
		{
			item->Balance = 0;
		}
		else if(item->Left == NULL)
		{
			if(item->Right->Balance == -1)
			{
				item->DoubleRotationRight();
				item = item->Parent;
			}
			else
			{
				item->LeftRotation();
				item = item->Parent;
			}
			if(item->Balance == -1)
				return true;
		}
		break;
	case -1:
		if(item->Left == NULL)
		{
			item->Balance = 0;
		}
		else if(item->Right == NULL)
		{
			if(item->Left->Balance == 1)
			{
				item->DoubleRotationLeft();
				item = item->Parent;
			}
			else
			{
				item->RightRotation();
				item = item->Parent;
			}
			if(item->Balance == 1)
				return true;
		}
		break;
	}

	while(!item->IsRoot())
	{
		switch(item->Parent->Balance)
		{
		case 0:
			if(item->IsLeftSibling())
			{
				item->Parent->Balance = 1;
			}
			else
			{
				item->Parent->Balance = -1;
			}
			return true;
		case -1:
			if(item->IsLeftSibling())
			{
				item->Parent->Balance = 0;
				item = item->Parent;
			}
			else
			{
				if(item->Parent->Left->Balance == 1)
				{
					item->Parent->DoubleRotationLeft();
					item = item->Parent->Parent;
				}
				else
				{
					item->Parent->RightRotation();
					item = item->Parent->Parent;
				}
				if(item->Balance == 1)
					return true;
			}
			continue;
		case 1:
			if(item->IsRightSibling())
			{
				item->Parent->Balance = 0;
				item = item->Parent;
			}
			else
			{
				if(item->Parent->Right->Balance == -1)
				{
					item->Parent->DoubleRotationRight();
					item = item->Parent->Parent;
				}
				else
				{
					item->Parent->LeftRotation();
					item = item->Parent->Parent;
				}
				if(item->Balance == -1)
					return true;
			}
			continue;
		}
		assert(false);		// should never reach
	}
	return true;
}

template <class T>
bool AVLNode<T>::IsRoot() const
{
	return Parent == NULL;
}

template <class T>
bool AVLNode<T>::IsLeftSibling() const
{
	return !IsRoot() && Parent->Left == this;
}

template <class T>
bool AVLNode<T>::IsRightSibling() const
{
	return !IsRoot() && Parent->Right == this;
}

template <class T>
bool AVLNode<T>::HasLeftSibling() const
{
	return IsRightSibling() && Parent->Left != NULL;
}
	
template <class T>
bool AVLNode<T>::HasRightSibling() const
{
	return IsLeftSibling() && Parent->Right != NULL;
}

template <class T>
int AVLNode<T>::GetDepth() const
{
	int i = 0;
	if (Left != NULL)
	  i = Left->GetDepth();
	if (Right != NULL)
	{
		int j = Right->GetDepth();
		if(j > i)
			i = j;
	}
	return i+1;
}

template <class T>
int AVLNode<T>::GetLevel() const
{
	const AVLNode<T>* item = this;
	int level = 0;
	while (item->Parent != NULL)
	{
		item = item->Parent;
		level++;
	}
	return level;
}

template <class T>
AVLNode<T>* AVLNode<T>::GetRoot()
{
	AVLNode<T>* item = this;
	while (item->Parent != NULL) 
		item = item->Parent;
	return item;
}

template <class T>
AVLNode<T>* AVLNode<T>::GetLeftSibling()
{
	if (IsRoot() || IsLeftSibling()) 
		return NULL;
	return Parent->Left;
}

template <class T>
AVLNode<T>* AVLNode<T>::GetRightSibling()
{
	if (IsRoot() || IsRightSibling()) 
		return NULL;
	return Parent->Right;
}

template <class T>
AVLNode<T>* AVLNode<T>::GetFirstNodeInTree()
{
	AVLNode<T>* item = this;
	while(item->Left != NULL)
	{
		item = item->Left;
	}
	return item;
}

template <class T>
AVLNode<T>* AVLNode<T>::GetLastNodeInTree()
{
	AVLNode<T>* item = this;
	while(item->Right != NULL)
	{
		item = item->Right;
	}
	return item;
}

template <class T>
AVLNode<T>* AVLNode<T>::GetPrevNodeInOrder(unsigned long n)
// Gets the node which is 'n' before this one. Returns NULL if 'n' is out of range.
{
	if(n == 0)
		return this;
	if(Left)
	{
		if(n <= Left->_count)
			return Left->GetNodeInTree(Left->_count-n);
		else
			n -= Left->_count;
	}
	AVLNode<T>* item = this;
	while(item->IsLeftSibling())
	{
		item = item->Parent;
	}
	item = item->Parent;
	if(!item)
		return NULL;
	return item->GetPrevNodeInOrder(n-1);
}

template <class T>
AVLNode<T>* AVLNode<T>::GetNextNodeInOrder(unsigned long n)
// Gets the node which is 'n' after this one. Returns NULL if 'n' is out of range.
{
	if(n == 0)
		return this;
	if(Right)
	{
		if(n <= Right->_count)
			return Right->GetNodeInTree(n-1);
		else
			n -= Right->_count;
	}
	AVLNode<T>* item = this;
	while(item->IsRightSibling())
	{
		item = item->Parent;
	}
	item = item->Parent;
	if(!item)
		return NULL;
	return item->GetNextNodeInOrder(n-1);
}

template<class T>
AVLNode<T>* AVLNode<T>::GetNodeInTree(unsigned long n)
// Returns the 'n'th(0-based) node in the subtree. Returns NULL if 'n' is 
// out of range.
{
unsigned long cnt;

	cnt = Left ? Left->_count : 0;
	if(n == cnt)
		return this;
	if(n < cnt)
	{
		return Left->GetNodeInTree(n);
	}
	n -= (cnt+1);
	cnt = Right ? Right->_count : 0;
	if(n >= cnt)		// out of range
		return NULL;
	return Right->GetNodeInTree(n);
}

template<class T>
unsigned long AVLNode<T>::GetIndex() const
// Returns the 0-based index of this node in the entire tree.
// Not valid for end marker!
{
unsigned long n;

	n = GetPositionInTree();
	const AVLNode<T>* item = this;
	while(item->IsLeftSibling())
	{
		item = item->Parent;
	}
	item = item->Parent;
	if(!item)
		return n;
	n++;		// add one for the parent item itself
	n += item->GetIndex();
	return n;
}

template <class T>
bool AVLNode<T>::LeftRotation()
{
	assert(Right);
	
	AVLNode<T>* b = Right;
	if(!IsRoot())
	{
		if(IsLeftSibling())
			Parent->Left = b;
		else
			Parent->Right = b;
		b->Parent = Parent;
	}
	else
	{
		b->Parent = NULL;
	}
	
	// Update counters
	b->_count++;
	b->_count += (Left ? Left->_count : 0);
	_count--;
	assert(b->Right);
	_count -= b->Right->_count;

	// Do the switch
	Right = b->Left;
	b->Left = this;

	// Re-align parents
	Parent = b;
	if(Right)
		Right->Parent = this;

	// Assume Balance == 2 before rotation is called
	// Assume b->Balance != -1 because that calls for double rotation
	if(b->Balance == 0)
	{
		Balance = 1;
		b->Balance = -1;
	}
	else	// b->Balance == 1
	{
		Balance = 0;
		b->Balance = 0;
	}

	return true;
}

template <class T>
bool AVLNode<T>::RightRotation()
{
	assert(Left);
	
	AVLNode<T>* b = Left;
	if(!IsRoot())
	{
		if(IsLeftSibling())
			Parent->Left = b;
		else
			Parent->Right = b;
		b->Parent = Parent;
	}
	else
	{
		b->Parent = NULL;
	}
	
	// Update counters
	b->_count++;
	b->_count += (Right ? Right->_count : 0);
	_count--;
	assert(b->Left);
	_count -= b->Left->_count;

	// Do the switch
	Left = b->Right;
	b->Right = this;

	// Re-align parents
	Parent = b;
	if(Left != NULL) 
		Left->Parent = this;

	// Assume Balance == -2 before rotation is called
	// Assume b->Balance != 1 because that calls for double rotation
	if(b->Balance == 0)
	{
		Balance = -1;
		b->Balance = 1;
	}
	else		// b->Balance == -1
	{
		Balance = 0;
		b->Balance = 0;
	}

	return true;
}

template <class T>
bool AVLNode<T>::DoubleRotationLeft()
{
	assert(Left && Left->Right);

	AVLNode<T>* b = Left;
	AVLNode<T>* c = Left->Right;

	if(!IsRoot())
	{
		if (IsLeftSibling())
			Parent->Left = c;
		else
			Parent->Right = c;
	}

	// Update counters
	c->_count = _count;
	b->_count--;
	b->_count -= (c->Right ? c->Right->_count : 0);
	_count -= 2;
	_count -= (b->Left ? b->Left->_count : 0);
	_count -= (c->Left ? c->Left->_count : 0);

	// Do the switch
	b->Right = c->Left;
	Left = c->Right;
	c->Left = b;
	c->Right = this;

	// Re-align parents
	c->Parent = Parent;
	Parent = c;
	b->Parent = c;
	if(b->Right != NULL) 
		b->Right->Parent = b;
	if(Left != NULL) 
		Left->Parent = this;

	// Assume Balance == -2 before rotation is called
	// Assume b->Balance == 1 because other cases call for single rotation
	switch(c->Balance)
	{
	case -1:
		Balance = 1;
		b->Balance = 0;
		break;
	case 0:
		Balance = 0;
		b->Balance = 0;
		break;
	case 1:
		Balance = 0;
		b->Balance = -1;
		break;
	}
	c->Balance = 0;
	
	return true;
}

template <class T>
bool AVLNode<T>::DoubleRotationRight()
{
	assert(Right && Right->Left);
	
	AVLNode<T>* b = Right;
	AVLNode<T>* c = Right->Left;

	if(!IsRoot())
	{
		if(IsLeftSibling())
			Parent->Left = c;
		else
			Parent->Right = c;
	}

	// Update counters
	c->_count = _count;
	b->_count--;
	b->_count -= (c->Left ? c->Left->_count : 0);
	_count -= 2;
	_count -= (b->Right ? b->Right->_count : 0);
	_count -= (c->Right ? c->Right->_count : 0);

	// Do the switch
	Right = c->Left;
	b->Left = c->Right;
	c->Left = this;
	c->Right = b;

	// Re-align parents
	c->Parent = Parent;
	Parent = c;
	b->Parent = c;
	if(Right) 
		Right->Parent = this;
	if(b->Left)
		b->Left->Parent = b;

	// Assume Balance == 2 before rotation is called
	// Assume b->Balance == -1 because other cases call for single rotation
	switch(c->Balance)
	{
	case -1:
		Balance = 0;
		b->Balance = 1;
		break;
	case 0:
		Balance = 0;
		b->Balance = 0;
		break;
	case 1:
		Balance = -1;
		b->Balance = 0;
		break;
	}
	c->Balance = 0;

	return true;
}

template <class T>
bool AVLNode<T>::Validate() const
// Returns false if tree is out of balance. Also checks the counters.
{
	int bal = 0;
	unsigned long c = 1;
	if(Right)
	{
		if(!Right->Validate()) 
			return false;
		bal += Right->GetDepth();
		c += Right->GetCount();
	}
	if(Left)
	{
		if(!Left->Validate()) 
			return false;
		bal -= Left->GetDepth();
		c += Left->GetCount();
	}

	if(Balance != bal)
		return false;
	if(_count != c)		// also check node count
		return false;

	return true;
}

//------------------------------------------------------------------
// class AVLTree

template<class T>
class AVLTree
{
protected:
	AVLNode<T>* _root;
	AVLNode<T>* _endnode;	// dummy end marker

//	AVLNode<T>* GetRoot() { return _root;}
	void RemoveNode(AVLNode<T>* remove);
	void ReplaceNode(AVLNode<T>* remove, AVLNode<T>* replace);
	AVLNode<T>* _InternalInsertBefore(AVLNode<T>* pos, const T& data);
	AVLNode<T>* _InternalInsertAfter(AVLNode<T>* pos, const T& data);
	virtual AVLNode<T>* GetInsertPosition(const T& data, bool& before) const;
	AVLNode<T>* Insert(const T& item);
	static AVLNode<T>* CopyTree(AVLNode<T>* src, AVLNode<T>* par);
public:
	bool Validate() const
	{
		if(!empty())
			return _root->Validate();
		return true;
	}
	// STL interface-------------------------
	// basic types
	typedef T value_type;
#ifdef __STL_CONFIG_H
	typedef std::__allocator<T,alloc> allocator_type;
#else
	typedef std::allocator<T> allocator_type;
#endif
	typedef typename allocator_type::size_type size_type;
	/*typedef typename _SIZT size_type;*/
	typedef typename allocator_type::difference_type difference_type;
	/*typedef _PDFT difference_type;*/
//	typedef allocator_type::pointer pointer;
//	typedef allocator_type::const_pointer const_pointer;
//	typedef allocator_type::reference reference;
//	typedef allocator_type::const_reference const_reference;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;

	class AVLTree_Iterator;
	friend AVLTree_Iterator;
	class AVLTree_Iterator
	{
		friend class AVLTree<T>;
		AVLNode<T>* _pos;
		const AVLTree<T>* _over;	// identifies the tree we are iterating over

		operator AVLNode<T>*() { return _pos;}
		bool IsEnd() const { return _pos == _over->_endnode;}
	public:
		typedef T value_type;
//		typedef allocator_type::pointer pointer;
//		typedef allocator_type::const_pointer const_pointer;
//		typedef allocator_type::reference reference;
//		typedef allocator_type::const_reference const_reference;
		typedef typename allocator_type::difference_type distance_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		/*typedef _PDFT distance_type;*/

		AVLTree_Iterator()
			: _pos(NULL), _over(NULL)
		{}
		AVLTree_Iterator(const AVLTree<T>& over, AVLNode<T>* pos = NULL) 
			: _pos(pos), _over(&over)
		{}
		AVLTree_Iterator(const AVLTree_Iterator& other) 
			: _pos(other._pos), _over(other._over)
		{}
		AVLTree_Iterator& operator=(const AVLTree_Iterator& iter)
		{
			_pos = iter._pos;
			_over = iter._over;
			return *this;
		}
		bool operator==(const AVLTree_Iterator& iter) const
		{
			return (_over == iter._over && _pos == iter._pos);
		}
		bool operator!=(const AVLTree_Iterator& iter) const
		{
			return (_pos != iter._pos || _over != iter._over);
		}
		T& GetData()
		{
			assert(_pos);
			assert(!IsEnd());
			return _pos->GetData();
		}
		const T& GetData() const
		{
			assert(_pos);
			assert(!IsEnd());
			return _pos->GetData();
		}
		void MoveNext(unsigned n = 1)
		{
			//assert(n >= 0);
			if(n == 0)
				return;
			assert(_pos);
			if(IsEnd())
			{
				//_pos = NULL;
				return;
			}
			_pos = _pos->GetNextNodeInOrder(n);
			if(_pos == NULL)
				_pos = _over->_endnode;
		}
		void MovePrev(unsigned n = 1)
		{
			//assert(n >= 0);
			if(n == 0)
				return;
			assert(_pos);
			if(IsEnd())
			{
				assert(_over);
				assert(_over->size() >= n);
				_pos = _over->_root->GetLastNodeInTree();
				n -= 1;
			}
			_pos = _pos->GetPrevNodeInOrder(n);
		}
		void MoveTo(size_t i)
		{
			assert(_over);
			_pos = _over->_root->GetNodeInTree(i);
		}
		size_type GetIndex() const
		{
			assert(_pos);
			if(IsEnd())
			{
				assert(_over);
				return _over->_root->GetCount();
			}
			return _pos->GetIndex();
		}
	};

	typedef typename stl_random_access_iterator<AVLTree_Iterator> iterator;
	typedef typename stl_const_random_access_iterator<AVLTree_Iterator> const_iterator;

	// construction and destruction
	AVLTree()
	{
		_root = NULL;
		_endnode = new AVLNode<T>(T());		// end marker must be unique to each set
	}
	virtual ~AVLTree() 
	{
		assert(_endnode);
		delete _endnode;
		if(_root)
			delete _root;
	}
	AVLTree(const AVLTree& other)	// copy constructor
	{
		_root = CopyTree(other._root, NULL);
		_endnode = new AVLNode<T>(T());		// end marker must be unique to each set
	}
	AVLTree& operator=(const AVLTree& other)
	{
		if(&other != this)
		{
			// copy and swap
			AVLTree tmp(other);
			swap(tmp);
		}
		return *this;
	}

	// Set information
	size_type size() const { return _root ? _root->GetCount() : 0;}
	size_type max_size() const { return (size_t)-1;}
	bool empty() const { return !_root;}
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
	// No operator<() - T does not have to be less-than comparable
	//bool operator<(const AVLTree<T>& other) const;
	bool operator==(const AVLTree<T>& other) const
	{
		return (size() == other.size() && std::equal(begin(), end(), other.begin()));
	}
	// 'at' is supposed to throw an out_of_range exception
	reference at(size_type n)
	{
		assert(_root);
		AVLNode<T>* pos = _root->GetNodeInTree(n);
		assert(pos);
		return pos->GetData();
	}
	const_reference at(size_type n) const
	{
		assert(_root);
		AVLNode<T>* pos = _root->GetNodeInTree(n);
		assert(pos);
		return pos->GetData();
	}
	// operator[] is supposed to be unchecked access
	reference operator[](size_type n) { return at(n);}
	const_reference operator[](size_type n) const { return at(n);}
	reference front();
	const_reference front() const;
	reference back();
	const_reference back() const;

	void push_back(const T& item)
	{
		if(!_root)
			_root = new AVLNode<T>(item);
		else
		{
			AVLNode<T> *last = _root->GetLastNodeInTree();
			_InternalInsertAfter(last, item);
		}
	}
	void push_front(const T& item)
	{
		if(!_root)
			_root = new AVLNode<T>(item);
		else
		{
			AVLNode<T> *first = _root->GetFirstNodeInTree();
			_InternalInsertBefore(first, item);
		}
	}

	iterator erase(iterator pos);
	void clear()
	{
		if(empty())
			return;
		assert(_root);
		delete _root;
		_root = NULL;
	}

	void swap(AVLTree<T>& other)
	{
		AVLNode<T> *tmp;
		tmp = _root;
		_root = other._root;
		other._root = tmp;
		tmp = _endnode;
		_endnode = other._endnode;
		other._endnode = tmp;
	}
};

template<class T>
AVLNode<T>* AVLTree<T>::CopyTree(AVLNode<T>* src, AVLNode<T>* par)
{
	if(!src)
		return NULL;

	AVLNode<T> *copy = new AVLNode<T>(src->GetData(), par);
	if(src->Left)
		copy->Left = CopyTree(src->Left, copy);
	if(src->Right)
		copy->Right = CopyTree(src->Right, copy);
	copy->_count = src->_count;
	copy->Balance = src->Balance;
	return copy;
}

template<class T>
typename AVLTree<T>::iterator AVLTree<T>::begin()
{
	return AVLTree_Iterator(*this, _root ? _root->GetFirstNodeInTree() : _endnode);
}

template<class T>
typename AVLTree<T>::const_iterator AVLTree<T>::begin() const
{
	return AVLTree_Iterator(*this, _root ? _root->GetFirstNodeInTree() : _endnode);
}

template<class T>
typename AVLTree<T>::iterator AVLTree<T>::end()
{
	return AVLTree_Iterator(*this, _endnode);
}

template<class T>
typename AVLTree<T>::const_iterator AVLTree<T>::end() const
{
	return AVLTree_Iterator(*this, _endnode);
}

template<class T>
typename AVLTree<T>::reference AVLTree<T>::front()
{
	assert(!empty());
	return *begin();
}

template<class T>
typename AVLTree<T>::const_reference AVLTree<T>::front() const
{
	assert(!empty());
	return *begin();
}

template<class T>
typename AVLTree<T>::reference AVLTree<T>::back()
{
	assert(!empty());
	return *(end()-1);
}

template<class T>
typename AVLTree<T>::const_reference AVLTree<T>::back() const
{
	assert(!empty());
	return *(end()-1);
}

template<class T>
AVLNode<T>* AVLTree<T>::_InternalInsertBefore(AVLNode<T>* pos, const T& data)
{
AVLNode<T> *newitem;

	assert(pos);
	if(pos == _endnode)
	{
		if(!_root)
			newitem = _root = new AVLNode<T>(data);
		else
			newitem = _InternalInsertAfter(_root->GetLastNodeInTree(), data);
		assert(newitem);
		return newitem;
	}
	if(pos->Left)
	{
		pos = pos->Left->GetLastNodeInTree();
		return _InternalInsertAfter(pos, data);
	}
	// create a new node
	newitem = new AVLNode<T>(data, pos, NULL, NULL);
	assert(newitem);
	// add as left node
	pos->Left = newitem;
	// increment parent counters
	while(pos)
	{
		pos->_count++;
		pos = pos->Parent;
	}
	// restructuration
	newitem->RestructureInsert();
	_root = _root->GetRoot();
	// return the new inserted node
	return newitem;
}

template <class T>
AVLNode<T>* AVLTree<T>::_InternalInsertAfter(AVLNode<T>* pos, const T& data)
{
	assert(pos);
	assert(pos != _endnode);
	if(pos->Right)
	{
		pos = pos->Right->GetFirstNodeInTree();
		return _InternalInsertBefore(pos, data);
	}
	// create a new node
	AVLNode<T>* newitem = new AVLNode<T>(data, pos, NULL, NULL);
	// add as right node
	pos->Right = newitem;
	// increment parent counters
	while(pos)
	{
		pos->_count++;
		pos = pos->Parent;
	}
	// restructuration
	newitem->RestructureInsert();
	_root = _root->GetRoot();
	// return the new inserted node
	return newitem;
}

template<class T>
void AVLTree<T>::RemoveNode(AVLNode<T>* remove)
// Internal use only. Removes a node 'remove' from the tree and detaches
// it from its parent. The node must have no more than one child. The tree 
// is re-balanced after removal.
{
	assert(remove);
	assert(remove != _endnode);
	assert(!remove->Left || !remove->Right);

	// Get the only child of the remove node if any
	AVLNode<T>* save_child = (remove->Left ? remove->Left : remove->Right);
	if(save_child)
	{
		assert(!save_child->Left && !save_child->Right);	// should not happen
		save_child->Parent = remove->Parent;
		save_child->Balance = remove->Balance;
		save_child->_count = remove->_count;
	}

	if(remove == _root)		// removing root
	{
		_root = save_child;
	}
	else
	{
		assert(remove->Parent);
		if(remove->IsLeftSibling())
			remove->Parent->Left = save_child;
		else
			remove->Parent->Right = save_child;
	}

	// Save parent of deleted node
	AVLNode<T>* save_parent = (save_child ? save_child : remove->Parent);

	// Remove tree structure data from removed node
	remove->Parent = NULL;
	remove->Left = NULL;
	remove->Right = NULL;

	// Decrement parent counters
	AVLNode<T>* item = save_parent;
	while(item)
	{
		item->_count--;
		item = item->Parent;
	}
	// Restructure the tree
	if(save_parent)
	{
		save_parent->RestructureDelete();
		_root = _root->GetRoot();
	}
}

template<class T>
void AVLTree<T>::ReplaceNode(AVLNode<T>* remove, AVLNode<T>* replace)
// Internal use only. Removes a node 'remove' from the tree and detaches
// it from its parent and children. If 'replace' is not NULL, it is put
// into the old position. Replace must have no more than one child. If 
// 'replace' is NULL, 'remove' must have no children. The tree is 
// restructured properly in the case of a deletion.
{
	assert(remove);
	if(!replace)
	{
		RemoveNode(remove);
		return;
	}

	if(remove == replace)		// no-op
		return;

	assert(!replace->Left || !replace->Right);
	assert(replace->Parent);
	// Get the only child of the replace node if any
	AVLNode<T>* save_child = (replace->Left ? replace->Left : replace->Right);
	if(save_child)
	{
		assert(!save_child->Left && !save_child->Right);	// should not happen
		assert(save_child != remove);		// should not happen
		save_child->Parent = replace->Parent;
		save_child->Balance = replace->Balance;
		save_child->_count = replace->_count;
	}

	// Remove the replace node without restructuring.
	if(replace->IsLeftSibling())
		replace->Parent->Left = save_child;
	else
		replace->Parent->Right = save_child;

	if(remove == _root)		// removing root
		_root = replace;
	else
	{
		if(remove->IsLeftSibling())
			remove->Parent->Left = replace;
		else
			remove->Parent->Right = replace;
	}
	if(remove->Left)
		remove->Left->Parent = replace;
	if(remove->Right)
		remove->Right->Parent = replace;

	// Save parent of deleted node
	AVLNode<T>* save_parent = (save_child ? save_child : replace->Parent);
	if(save_parent == remove)
		save_parent = replace;

	// copy the old nodes tree structure data
	replace->Parent = remove->Parent;
	replace->Left = remove->Left;
	replace->Right = remove->Right;
	replace->Balance = remove->Balance;
	replace->_count = remove->_count;
	// remove tree structure data from removed node
	remove->Parent = NULL;
	remove->Left = NULL;
	remove->Right = NULL;
	remove->Balance = 0;
	remove->_count = 1;

	// Decrement parent counters
	AVLNode<T>* item = save_parent;
	while(item)
	{
		item->_count--;
		item = item->Parent;
	}
	// Restructure the tree if necessary
	if(save_parent)
	{
		save_parent->RestructureDelete();
		_root = _root->GetRoot();
	}
}

template<class T>
typename AVLTree<T>::iterator AVLTree<T>::erase(iterator pos)
// Removes item pointed to by 'pos' from tree and deletes it. Returns a
// pointer to the item following. Does not invalidate any iterators pointing
// to other elements in the tree.
{
	iterator nextpos = pos + 1;
	AVLNode<T>* item = (AVLNode<T>*)(AVLTree_Iterator)pos;
	assert(item);
	assert(item != _endnode);	// cannot delete end marker

	AVLNode<T> *replace = NULL;
	if(item->Left && item->Right)
	{
		replace = item->Left->GetLastNodeInTree();
		// replace->Right is NULL by definition of last node
	}
	ReplaceNode(item, replace);
	delete item;
	return nextpos;
}

template<class T>
AVLNode<T>* AVLTree<T>::GetInsertPosition(const T& /*item*/, bool& before) const
// Returns the AVL node under which the next item should be inserted. If 'before'
// returns as true, the item should be inserted before the node (left child),
// otherwise it should be inserted after the node (right child). The insert
// position is chosen so as to minimize rotation operations.
{
	assert(_root);
	AVLNode<T> *at = _root;
	while(at)
	{
		if(!at->Left)
		{
			before = true;
			return at;
		}
		if(!at->Right)
		{
			before = false;
			return at;
		}

		switch(at->Balance)
		{
		case 1:
		case 0:
			at = at->Left;
			break;
		case -1:
			at = at->Right;
			break;
		default:
			assert(false);	// should not occur
		}
	}
	assert(at);
	return at;
};

template<class T>
AVLNode<T>* AVLTree<T>::Insert(const T& item)
// Inserts an item into the tree and returns the position of the newly inserted
// item or NULL if the item could not be inserted because it is a duplicate
// and _unique is true.
{
	// Check if first item
	if(!_root)
		return _InternalInsertBefore(_endnode, item);
	
	// detect insert position
	bool before;
	AVLNode<T>* pos = GetInsertPosition(item, before);
	if(pos)
	{
		if(before)
			pos = _InternalInsertBefore(pos, item);
		else
			pos = _InternalInsertAfter(pos, item);
	}

	return pos;
};

//-----------------------------------------------------------------
// This class is same as AVLTree<T> except that a sort order is maintained
// on a binary predicate function Cmp.
template<class T, class Cmp = std::less<T> >
class Sorted_AVLTree : public AVLTree<T>
{
protected:
	Cmp _cmp;		// compare object
	bool _unique;	// true if cannot contain duplicates

	AVLNode<T>* GetInsertPosition(const T& item, bool& before) const
	{
		if(_unique)
			return GetUniqueInsertPosition(item, before);
		else
			return GetLowerInsertPosition(item, before);
	}
	AVLNode<T>* GetUniqueInsertPosition(const T& item, bool& before) const;
	AVLNode<T>* GetLowerInsertPosition(const T& item, bool& before) const;
	AVLNode<T>* GetUpperInsertPosition(const T& item, bool& before) const;
public:
	typedef typename AVLTree<T> base_type;
	typedef typename base_type::iterator iterator;
	typedef typename base_type::const_iterator const_iterator;
	typedef typename base_type::value_type value_type;
	typedef typename base_type::size_type size_type;

	Sorted_AVLTree(Cmp cmp = Cmp(), bool unique = false)
		: AVLTree<T>(), _cmp(cmp), _unique(unique)
	{}
	Sorted_AVLTree(const Sorted_AVLTree<T,Cmp>& other)
		: AVLTree<T>(other), _cmp(other._cmp), _unique(other._unique)
	{}
	virtual ~Sorted_AVLTree() {}
	Sorted_AVLTree<T,Cmp>& operator=(const Sorted_AVLTree<T,Cmp>& other)
	{
		if(&other != this)
		{
			AVLTree<T>::operator=(other);
			_cmp = other._cmp;
			_unique = other._unique;
		}
		return *this;
	}
	virtual bool operator<(const Sorted_AVLTree<T,Cmp>& other) const
	{
		return std::lexicographical_compare(begin(), end(), other.begin(), other.end(), _cmp);
	}
	AVLNode<T>* Find(const T& item) const;
	AVLNode<T>* LowerBound(const T& item) const;
	AVLNode<T>* UpperBound(const T& item) const;
	std::pair<AVLNode<T>*,AVLNode<T>*> EqualRange(const T& item) const;
	size_type Count(const T& item) const
	{
		size_type low, high;
		std::pair<AVLNode<T>*,AVLNode<T>*> range;

		range = EqualRange(item);
		low = (range.first == _endnode ? size() : range.first->GetIndex());
		high = (range.second == _endnode ? size() : range.second->GetIndex());

		return (high - low);
	}

	void swap(Sorted_AVLTree<T,Cmp>& other)
	{
		AVLTree<T>::swap(other);
		Cmp tmp = _cmp;
		_cmp = other._cmp;
		other._cmp = tmp;
		bool btmp = _unique;
		_unique = other._unique;
		other._unique = btmp;
	}
};

template<class T,class Cmp>
AVLNode<T>* Sorted_AVLTree<T,Cmp>::GetUniqueInsertPosition(const T& item, bool& before) const
// Returns the AVL node under which 'data' should be inserted. If 'before'
// returns as true, the item should be inserted before the node (left child),
// otherwise it should be inserted after the node (right child). Returns
// NULL if the item is already in the set.
{
	assert(_unique);
	assert(_root);
	AVLNode<T> *at = _root;
__pragma(warning(push))
__pragma(warning(disable:4127))
	while(1)
__pragma(warning(pop))
	{
		if(_cmp(item, at->GetData()))
		{
			if(!at->Left)
			{
				before = true;
				break;
			}
			at = at->Left;
		}
		else if(_cmp(at->GetData(), item))
		{
			if(!at->Right)
			{
				before = false;
				break;
			}
			at = at->Right;
		}
		else			// item already in set
			return NULL;
	}
	return at;
};

template<class T,class Cmp>
AVLNode<T>* Sorted_AVLTree<T,Cmp>::GetLowerInsertPosition(const T& item, bool& before) const
// Returns the AVL node under which 'data' should be inserted. If 'before'
// returns as true, the item should be inserted before the node (left child),
// otherwise it should be inserted after the node (right child). The position
// is chosen to come before any duplicates already in the set.
{
	assert(_root);
	AVLNode<T> *at = _root;
__pragma(warning(push))
__pragma(warning(disable:4127))
	while(1)
__pragma(warning(pop))
	{
		if(!_cmp(at->GetData(), item))
		{
			if(!at->Left)
			{
				before = true;
				break;
			}
			else
				at = at->Left;
		}
		else
		{
			if(!at->Right)
			{
				before = false;
				break;
			}
			else
				at = at->Right;
		}
	}
	return at;
};

template<class T,class Cmp>
AVLNode<T>* Sorted_AVLTree<T,Cmp>::GetUpperInsertPosition(const T& item, bool& before) const
// Returns the AVL node under which 'data' should be inserted. If 'before'
// returns as true, the item should be inserted before the node (left child),
// otherwise it should be inserted after the node (right child). The position
// is chosen to come after any duplicates already in the set.
{
	assert(_root);
	AVLNode<T> *at = _root;
	while(1)
	{
		if(_cmp(item, at->GetData()))
		{
			if(!at->Left)
			{
				before = true;
				break;
			}
			else
				at = at->Left;
		}
		else
		{
			if(!at->Right)
			{
				before = false;
				break;
			}
			else
				at = at->Right;
		}
	}
	return at;
};

template<class T,class Cmp>
AVLNode<T>* Sorted_AVLTree<T,Cmp>::Find(const T& item) const
// Returns the position of the first item in the tree that matches 'data'
// or NULL if no match is found.
{
	AVLNode<T> *at = _root;
	while(at)
	{
		if(_cmp(item, at->GetData()))
		{
			at = at->Left;
		}
		else
		{
			if(!_cmp(at->GetData(), item))		// match found
				return at;
			at = at->Right;
		}
	}
	return NULL;		// no match found
}

template<class T,class Cmp>
AVLNode<T>* Sorted_AVLTree<T,Cmp>::LowerBound(const T& item) const
// Returns a pointer to the first node in the tree which is greater than or
// equal to 'item'. If 'item' is greater than all the nodes, returns _endnode.
{
	AVLNode<T> *lower = _endnode;
	AVLNode<T> *at = _root;
	while(at)
	{
		if(!_cmp(at->GetData(), item))
		{
			lower = at;
			at = at->Left;
		}
		else
		{
			at = at->Right;
		}
	}
	return lower;
};

template<class T,class Cmp>
AVLNode<T>* Sorted_AVLTree<T,Cmp>::UpperBound(const T& item) const
// Returns a pointer to the first node in the tree which is greater than 'item'.
// If 'item' is greater than or equal to all the nodes, returns _endnode.
{
	AVLNode<T> *upper = _endnode;
	AVLNode<T> *at = _root;
	while(at)
	{
		if(_cmp(item, at->GetData()))
		{
			upper = at;
			at = at->Left;
		}
		else
		{
			at = at->Right;
		}
	}
	return upper;
};

template<class T,class Cmp>
std::pair<AVLNode<T>*,AVLNode<T>*> Sorted_AVLTree<T,Cmp>::EqualRange(const T& item) const
// Returns the lower and upper bounds of 'item'. See LowerBound and UpperBound functions.
{
	AVLNode<T> *lower = _endnode, *upper = _endnode, *backtrack = NULL;
	AVLNode<T> *at = _root;
	while(at)
	{
		if(_cmp(item, at->GetData()))
		{
			lower = at;
			upper = at;
			at = at->Left;
		}
		else if(!_cmp(at->GetData(), item))	// match found
		{
			lower = at;
			if(!backtrack)
				backtrack = at->Right;		// save this for upper search
			at = at->Left;
		}
		else
		{
			at = at->Right;
		}
	}

	// Now go back and find the upper node
	at = backtrack;
	while(at)
	{
		if(_cmp(item, at->GetData()))
		{
			upper = at;
			at = at->Left;
		}
		else
		{
			at = at->Right;
		}
	}
	return std::make_pair(lower, upper);
};

//------------------------------------------------------------------
// STL containers

// An index_list is a sequence which combines the interfaces of array, deque,
// and list. Here are the comparisons:
//					array	deque	list	index_list
// indexed access:	1		1		(N)		lgN
// insert/delete:	N		N		1		1+
// front insertion:	(N)		1+		1		1+
// back insertion	1+		1+		1		1+
// It tends to work best for large sets (N >> 1).
// It also has the extra function insert(const T&), usually used for sets,
// which chooses an insert position which keeps the tree balance with a
// minimal number of rotation operations.

template<class T>
class index_list : public AVLTree<T>
{
public:
	index_list()
		: AVLTree<T>()
	{}
	index_list(const index_list& other)
		: AVLTree<T>(other)
	{}
	index_list(size_t n, const T& item = T())
	{
		for(size_t i = 0; i < n; i++)
			Insert(item);
	}
	index_list(const_iterator first, const_iterator last)
	{
		for(const_iterator at = first; at != last; ++at)
			_InternalInsertBefore(_endnode, *at);	// preserve order
	}
	virtual ~index_list() {}

	iterator insert(iterator at, const T& item)
	{
		AVLNode<T> *pos = (AVLNode<T>*)(AVLTree_Iterator)at;
		assert(pos);
		pos = _InternalInsertBefore(pos, data);
		return AVLTree_Iterator(*this, pos);
	}
	iterator insert(const T& item)
	{
		AVLNode<T> *pos = Insert(item);
		assert(pos);
		return AVLTree_Iterator(*this, pos);
	};
};


//----------------------------------------------------------------
// An index_set implements the STL interface for set with the addition
// of indexed access (operator[n], at(n)).
// Here are the comparisons with other sorted structures.
//					array	list	set		index_set
// indexed access:	1		(N)		(N+)	lgN
// insert/delete:	N		1		1+		1+
// search:			lgN		N		lgN		lgN

// 'T' is the element type and 'Cmp' is the ordering function, which is a
// binary predicate functor.
template<class T, class Cmp = std::less<T> >
class index_set : public Sorted_AVLTree<T,Cmp>
{
public:
	typedef T key_type;
	typedef T value_type;
	typedef Cmp key_compare;
	typedef Cmp value_compare;
	key_compare key_comp() { return _cmp;}
	value_compare value_comp() { return _cmp;}

	explicit index_set(const Cmp& pred = Cmp()) 
		: Sorted_AVLTree<T,Cmp>(pred, true)
	{}
	explicit index_set(const index_set& other)
		: Sorted_AVLTree<T,Cmp>(other)
	{}
	index_set(const_iterator first, const_iterator last, const Cmp& pred = Cmp())
		: Sorted_AVLTree<T,Cmp>(pred, true)
	{
		for(const_iterator at = first; at != last; ++at)
			Insert(*at);
	}
	virtual ~index_set() {}

	std::pair<iterator,bool> insert(const value_type& item)
	{
		AVLNode<T> *pos = Insert(item);
		bool found = (pos ? true : false);
		return std::make_pair(AVLTree_Iterator(*this, pos), found);
	}

	const_iterator find(const T& item) const
	{
		AVLNode<T> *pos = Find(item);
		if(!pos)
			pos = _endnode;
		return AVLTree_Iterator(*this, pos);
	}
	const_iterator lower_bound(const T& item) const
	{
		AVLNode<T> *pos = LowerBound(item);
		return AVLTree_Iterator(*this, pos);
	}
	const_iterator upper_bound(const T& item) const
	{
		AVLNode<T> *pos = UpperBound(item);
		return AVLTree_Iterator(*this, pos);
	}
	std::pair<const_iterator,const_iterator> equal_range(const T& item) const
	{
		std::pair<AVLNode<T>*,AVLNode<T>*> range = EqualRange(item);
		return std::make_pair(const_iterator(AVLTree_Iterator(*this, range.first)), 
			const_iterator(AVLTree_Iterator(*this, range.second)));
	}
	size_type count(const T& item) const
	{
		return Count(item);
	}
};

//template<class T,class Cmp>
//std::pair<typename index_set<T, Cmp>::iterator, bool> index_set<T, Cmp>::insert(const value_type& item)
//// Inserts an item into the set. Returns end of sequence and false if the item is
//// already in the set, otherwise returns a pointer to the item inserted and true.
//{
//	AVLNode<T> *pos = Insert(item);
//	bool found = (pos ? true: false);
//	return std::make_pair(AVLTree_Iterator(*this, pos), found);
//}

//----------------------------------------------------------------
// An index_multiset implements the STL interface for multiset with the
// addition of indexed access (operator[n], at(n)). Performance characteristics
// are the same as with index_set.

template<class T, class Cmp = std::less<T> >
class index_multiset : public Sorted_AVLTree<T,Cmp>
{
public:
	typedef T key_type;
	typedef T value_type;
	typedef Cmp key_compare;
	typedef Cmp value_compare;
	key_compare key_comp() { return _cmp;}
	value_compare value_comp() { return _cmp;}

	index_multiset(const Cmp& pred = Cmp()) 
		: Sorted_AVLTree<T,Cmp>(pred, false)
	{}
	index_multiset(const index_multiset& other)
		: Sorted_AVLTree<T,Cmp>(other)
	{}
	index_multiset(size_t n, const T& item = T(), const Cmp& pred = Cmp())
		: Sorted_AVLTree<T,Cmp>(pred, false)
	{
		for(size_t i = 0; i < n; i++)
			Insert(item);
	}
	index_multiset(const_iterator first, const_iterator last, const Cmp& pred = Cmp())
		: Sorted_AVLTree<T,Cmp>(pred, false)
	{
		for(const_iterator at = first; at != last; ++at)
			Insert(*at);
	}
	virtual ~index_multiset() {}

	iterator insert(const value_type& item);
	const_iterator find(const T& item) const
	{
		AVLNode<T> *pos = Find(item);
		if(!pos)
			pos = _endnode;
		return AVLTree_Iterator(*this, pos);
	}
	const_iterator lower_bound(const T& item) const
	{
		AVLNode<T> *pos = LowerBound(item);
		return AVLTree_Iterator(*this, pos);
	}
	const_iterator upper_bound(const T& item) const
	{
		AVLNode<T> *pos = UpperBound(item);
		return AVLTree_Iterator(*this, pos);
	}
	std::pair<const_iterator,const_iterator> equal_range(const T& item) const
	{
		std::pair<AVLNode<T>*,AVLNode<T>*> range = EqualRange(item);
		return std::make_pair(const_iterator(AVLTree_Iterator(*this, range.first)), 
			const_iterator(AVLTree_Iterator(*this, range.second)));
	}
	size_type count(const T& item) const
	{
		return Count(item);
	}
};

template<class T,class Cmp>
typename index_multiset<T, Cmp>::iterator index_multiset<T, Cmp>::insert(const value_type& item)
// Inserts an item into the set. Returns a pointer to the item inserted.
// The item is inserted before any duplicates already in the set.
{
	AVLNode<T> *at = Insert(item);
	assert(at);
	return AVLTree_Iterator(*this, at);
};


//-----------------------------------------------------------------
// An index_map implements the STL interface for map, with the addition
// of indexed access (operator[n], at(n)). Performance characteristics
// are the same as with index_set.

// This provides a value compare class given the key compare type 'Cmp'.
template<class Key, class T, class Cmp>
class ValueCompare : public std::binary_function<std::pair<const Key,T>,std::pair<const Key,T>,bool>
{
	Cmp _cmp;
public:
	ValueCompare(const Cmp cmp = Cmp())
		: _cmp(cmp) {}
	bool operator()(const std::pair<const Key,T>& v1, const std::pair<const Key,T>& v2) const
	{
		return _cmp(v1.first, v2.first);
	}
};

template<class Key, class T, class Cmp = std::less<Key> >
class index_map : public Sorted_AVLTree<std::pair<const Key,T>,ValueCompare<Key,T,Cmp> >
{
	Cmp _keycmp;
public:
	typedef Key key_type;
	typedef T mapped_type;

	typedef Cmp key_compare;
	typedef ValueCompare<Key,T,Cmp> value_compare;
	key_compare key_comp() { return _keycmp;}
	value_compare value_comp() { return _cmp;}

	typedef typename Sorted_AVLTree<std::pair<const Key, T>, ValueCompare<Key, T, Cmp> > base_type;
	typedef typename base_type::iterator iterator;
	typedef typename base_type::const_iterator const_iterator;
	typedef typename base_type::value_type value_type;
	typedef typename base_type::size_type size_type;

	index_map(const Cmp& pred = Cmp())
		: _keycmp(pred), Sorted_AVLTree<value_type,value_compare>(value_compare(pred), true)
	{}
	index_map(const index_map& other)
		: _keycmp(other._keycmp), Sorted_AVLTree<value_type,value_compare>(other)
	{}
	index_map(const_iterator first, const_iterator last, const Cmp& pred = Cmp())
		: _keycmp(pred), Sorted_AVLTree<value_type,value_compare>(value_compare(pred), true)
	{
		for(const_iterator at = first; at != last; ++at)
			Insert(*at);
	}
	virtual ~index_map() {}

	std::pair<iterator,bool> insert(const value_type& item);
	const_iterator find(const Key& key) const
	{
		AVLNode<std::pair<const Key,T> > *pos = Find(std::pair<const Key,T>(key,T()));
		if(!pos)
			pos = _endnode;
		return AVLTree_Iterator(*this, pos);
	}
	const_iterator lower_bound(const Key& key) const
	{
		AVLNode<std::pair<const Key,T> > *pos = LowerBound(std::pair<const Key,T>(key,T()));
		return AVLTree_Iterator(*this, pos);
	}
	const_iterator upper_bound(const Key& key) const
	{
		AVLNode<std::pair<const Key,T> > *pos = UpperBound(std::pair<const Key,T>(key,T()));
		return AVLTree_Iterator(*this, pos);
	}
	std::pair<const_iterator,const_iterator> equal_range(const Key& key) const
	{
		std::pair<AVLNode<std::pair<const Key,T> >*,AVLNode<std::pair<const Key,T> >*> range = EqualRange(std::pair<const Key,T>(key,T()));
		return std::make_pair(const_iterator(AVLTree_Iterator(*this, range.first)), 
			const_iterator(AVLTree_Iterator(*this, range.second)));
	}
	size_type count(const Key& key) const
	{
		return Count(std::pair<const Key,T>(key,T()));
	}

	void swap(index_map& other)
	{
		Sorted_AVLTree<value_type,value_compare>::swap(other);
		Cmp tmp = _keycmp;
		_keycmp = other._keycmp;
		other._keycmp = tmp;
	}
};

template<class Key,class T,class Cmp>
std::pair<typename index_map<Key, T, Cmp>::iterator, bool> index_map<Key, T, Cmp>::insert(const value_type& item)
// Inserts an item into the set. Returns end of sequence and false if the item is
// already in the set, otherwise returns a pointer to the item inserted and true.
{
	AVLNode<std::pair<const Key,T> > *pos = Insert(item);
	bool found = (pos ? true : false);
	return std::make_pair(index_map<Key,T,Cmp>::iterator(AVLTree_Iterator(*this, pos)), found);
}


//-----------------------------------------------------------------
// An index_multimap implements the STL interface for multimap, with the
// addition of indexed access (operator[n], at(n)). Performance characteristics
// are the same as with index_set.

template<class Key, class T, class Cmp = std::less<Key> >
class index_multimap : public Sorted_AVLTree<std::pair<const Key,T>,ValueCompare<Key,T,Cmp> >
{
	Cmp _keycmp;
public:
	typedef T mapped_type;
	typedef Key key_type;

	typedef Cmp key_compare;
	typedef ValueCompare<Key,T,Cmp> value_compare;
	key_compare key_comp() { return _keycmp;}
	value_compare value_comp() { return _cmp;}

	typedef typename Sorted_AVLTree<std::pair<const Key, T>, ValueCompare<Key, T, Cmp> > base_type;
	typedef typename base_type::iterator iterator;
	typedef typename base_type::const_iterator const_iterator;
	typedef typename base_type::value_type value_type;
	typedef typename base_type::size_type size_type;

	index_multimap(const Cmp& pred = Cmp())
		: _keycmp(pred), Sorted_AVLTree<value_type,value_compare>(value_compare(pred), false)
	{}
	index_multimap(const index_multimap& other)
		: _keycmp(other._keycmp), Sorted_AVLTree<value_type,value_compare>(other)
	{}
	index_multimap(const_iterator first, const_iterator last, const Cmp& pred = Cmp())
		: _keycmp(pred), Sorted_AVLTree<value_type,value_compare>(value_compare(pred), false)
	{
		for(const_iterator at = first; at != last; ++at)
			Insert(*at);
	}
	virtual ~index_multimap() {}

	iterator insert(const value_type& item);
	const_iterator find(const Key& key) const
	{
		AVLNode<std::pair<const Key,T> > *pos = Find(std::pair<const Key,T>(key,T()));
		if(!pos)
			pos = _endnode;
		return AVLTree_Iterator(*this, pos);
	}
	const_iterator lower_bound(const Key& key) const
	{
		AVLNode<std::pair<const Key,T> > *pos = LowerBound(std::pair<const Key,T>(key,T()));
		return AVLTree_Iterator(*this, pos);
	}
	const_iterator upper_bound(const Key& key) const
	{
		AVLNode<std::pair<const Key,T> > *pos = UpperBound(std::pair<const Key,T>(key,T()));
		return AVLTree_Iterator(*this, pos);
	}
	std::pair<const_iterator,const_iterator> equal_range(const Key& key) const
	{
		std::pair<AVLNode<std::pair<const Key,T> >*,AVLNode<std::pair<const Key,T> >*> range = EqualRange(std::pair<const Key,T>(key,T()));
		return std::make_pair(const_iterator(AVLTree_Iterator(*this, range.first)), 
			const_iterator(AVLTree_Iterator(*this, range.second)));
	}
	size_type count(const Key& key) const
	{
		return Count(std::pair<const Key,T>(key,T()));
	}

	void swap(index_multimap& other)
	{
		Sorted_AVLTree<value_type,value_compare>::swap(other);
		Cmp tmp = _keycmp;
		_keycmp = other._keycmp;
		other._keycmp = tmp;
	}
};

template<class Key,class T,class Cmp>
typename index_multimap<Key, T, Cmp>::iterator index_multimap<Key, T, Cmp>::insert(const value_type& item)
// Inserts an item into the set. Returns a pointer to the item inserted.
// The item is inserted before any duplicates already in the set.
{
	AVLNode<std::pair<const Key,T> > *pos = Insert(item);
	assert(pos);
	return AVLTree_Iterator(*this, pos);
};

#endif
