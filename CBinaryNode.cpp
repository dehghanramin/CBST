// ============================================================================
// File: CBinaryNode.cpp
// ============================================================================
// Programmer: Ramin Dehghan
// Date: May 22, 2021
// Class: CSCI 133 ("Data Structures Using C++")
// Time: Online
// Instructor: Dr. Rodriguez
// Project: Project CBST
//
// Description:
// Implementation file for the class CBinaryNode
// ============================================================================

#include "CBinaryNode.h"


// ==== CBinaryNode<ItemType>::CBinaryNode ====================================
//
// This is the default constructor for CBinaryNode<ItemType>. It initializes
// the left and right child pointer to nullptr and leave m_item as garbage.
//
// Input:
//       void
//       
// Output:
//       Nothing
//
// ============================================================================

template <class ItemType>
CBinaryNode<ItemType>::CBinaryNode() :
	m_leftChildPtr(nullptr),
	m_rightChildPtr(nullptr)
{} //end of "CTOR"


// ==== CBinaryNode<ItemType>::CBinaryNode ====================================
//
// This is the type constructor for CBinaryNode<ItemType>. It initializes
// m_item and sets the left and right child pointer to nullptr.
//
// Input:
//       item   [IN] - A const ItemType reference to initialize the new node.
//       
// Output:
//       Nothing
//
// ============================================================================

template <class ItemType>
CBinaryNode<ItemType>::CBinaryNode(const ItemType &item) :
	m_item(item),
	m_leftChildPtr(nullptr),
	m_rightChildPtr(nullptr)
{} //end of "CTOR"


// ==== CBinaryNode<ItemType>::CBinaryNode ====================================
//
// This is the type constructor for CBinaryNode<ItemType>.  It initializes all
// the private data members with the supplied arguments.
//
// Input:
//       item          [IN]  - A const ItemType reference to initialize the
//                                  new node.
//       leftChildPtr  [IN]  - A CBinaryNode<ItemType> pointer that points to
//                                  the left child.
//       rightChildPtr [IN]  - A CBinaryNode<ItemType> pointer that points to
//                                  the right child.
//       
// Output:
//       Nothing
//
// ============================================================================

template <class ItemType>
CBinaryNode<ItemType>::CBinaryNode(const ItemType &item,
	std::shared_ptr<CBinaryNode<ItemType>> leftChildPtr,
	std::shared_ptr<CBinaryNode<ItemType>> rightChildPtr) :
		m_item(item),
		m_leftChildPtr(leftChildPtr),
		m_rightChildPtr(rightChildPtr)
{} //end of "CTOR"


// ==== CBinaryNode<ItemType>::SetItem ========================================
//
// This function assigns a value to m_item.
//
// Input:
//       item   [IN] - A const ItemType reference.
//       
// Output:
//       void
//
// ============================================================================

template <class ItemType>
void CBinaryNode<ItemType>::SetItem(const ItemType &item)
{
	m_item = item;
} //end of "SetItem"


// ==== CBinaryNode<ItemType>::GetItem ========================================
//
// This function returns the value of m_item.
//
// Input:
//       void
//
// Output:
//       An ItemType.
//
// ============================================================================

template <class ItemType>
ItemType CBinaryNode<ItemType>::GetItem() const
{
	return m_item;
} //end of "GetItem"


// ==== CBinaryNode<ItemType>::IsLeaf =========================================
//
// This function checks if the node is a leaf.
//
// Input:
//       void
//
// Output:
//       Returns true if the node is a leaf, false otherwise.
//
// ============================================================================

template <class ItemType>
bool CBinaryNode<ItemType>::IsLeaf() const
{
	return (m_leftChildPtr == nullptr && m_rightChildPtr == nullptr) ?
		1 : 0;
} //end of "IsLeaf"


// ==== CBinaryNode<ItemType>::GetLeftChildPtr ================================
//
// This function returns the pointer to the left node.
//
// Input:
//       void
//
// Output:
//       Returns a CBinaryNode<ItemType> pointer.
//
// ============================================================================

template <class ItemType>
std::shared_ptr<CBinaryNode<ItemType>>
	CBinaryNode<ItemType>::GetLeftChildPtr() const
{
	return m_leftChildPtr;
} //end of "GetLeftChildPtr"


// ==== CBinaryNode<ItemType>::GetRightChildPtr ===============================
//
// This function returns the pointer to the right node.
//
// Input:
//       void
//
// Output:
//       Returns a CBinaryNode<ItemType> pointer.
//
// ============================================================================

template <class ItemType>
std::shared_ptr<CBinaryNode<ItemType>>
	CBinaryNode<ItemType>::GetRightChildPtr() const
{
	return m_rightChildPtr;
} //end of "GetRightChildPtr"


// ==== CBinaryNode<ItemType>::SetLeftChildPtr ================================
//
// This function assigns the poitner to the left node.
//
// Input:
//       leftChildPtr   [IN] - A CBinaryNode<ItemType> pointer to the left
//                             node.
//       
// Output:
//       void
//
// ============================================================================

template <class ItemType>
void CBinaryNode<ItemType>::SetLeftChildPtr(
	std::shared_ptr<CBinaryNode<ItemType>> leftChildPtr)
{
	m_leftChildPtr = leftChildPtr;
} //end of "SetLeftChildPtr"


// ==== CBinaryNode<ItemType>::SetRightChildPtr ===============================
//
// This function assigns the poitner to the right node.
//
// Input:
//       rightChildPtr   [IN] - A CBinaryNode<ItemType> pointer to the left
//                              node.
//       
// Output:
//       void
//
// ============================================================================

template <class ItemType>
void CBinaryNode<ItemType>::SetRightChildPtr(
	std::shared_ptr<CBinaryNode<ItemType>> rightChildPtr)
{
	m_rightChildPtr = rightChildPtr;
} //end of "SetRightChildPtr"
