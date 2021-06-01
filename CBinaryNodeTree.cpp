// ============================================================================
// File: CBinaryNodeTree.cpp
// ============================================================================
// Programmer: Ramin Dehghan
// Date: May 22, 2021
// Class: CSCI 133 ("Data Structures Using C++")
// Time: Online
// Instructor: Dr. Rodriguez
// Project: Project CBST
//
// Description:
// Implementation file for the class CBinaryNodeTree.tpp
// ============================================================================

#include "CBinaryNodeTree.h"


// ==== CBinaryNodeTree<ItemType>::CBinaryNodeTree ============================
//
// This is the default constructor for CBinaryNodeTree. It sets the root to
// nullptr.
//
// Input:
//       void
//       
// Output:
//       Nothing
//
// ============================================================================

template <class ItemType>
CBinaryNodeTree<ItemType>::CBinaryNodeTree() :
	m_rootPtr(nullptr)
{} //end of "CTOR"


// ==== CBinaryNodeTree<ItemType>::CBinaryNodeTree ============================
//
// This is the type constructor for CBinaryNodeTree. It allocates a space for a
// CBinaryNode and sets it equal to m_rootPtr. The new node will have it's
// right and left child pointers set to nullptr.
//
// Input:
//       rootItem   [IN] - A const reference ItemType.
//       
// Output:
//       Nothing
//
// ============================================================================

template <class ItemType>
CBinaryNodeTree<ItemType>::CBinaryNodeTree(const ItemType &rootItem) :
	m_rootPtr(std::make_shared<CBinaryNode<ItemType>>
	(rootItem, nullptr, nullptr))
{} //end of "CTOR"


// ==== CBinaryNodeTree<ItemType>::CBinaryNodeTree ============================
//
// This is the type constructor for CBinaryNodeTree. It allocates a space for a
// CBinaryNode and sets it equal to m_rootPtr. The new node will have it's
// right and left child pointers set to rightTreePtr and leftTreePtr,
// respectively.
//
// Input:
//       rootItem     [IN] - A const ItemType reference to initialize the
//                           new node.
//       leftTreePtr  [IN] - A const CBinaryNode<ItemType> pointer that
//                           points to the left child.
//       rightTreePtr [IN] - A const CBinaryNode<ItemType> pointer that
//                           points to the right child.
//       
// Output:
//       Nothing
//
// ============================================================================

template <class ItemType>
CBinaryNodeTree<ItemType>::CBinaryNodeTree(const ItemType &rootItem,
	const std::shared_ptr<CBinaryNodeTree<ItemType>> leftTreePtr,
	const std::shared_ptr<CBinaryNodeTree<ItemType>> rightTreePtr) :
		m_rootPtr(std::make_shared<CBinaryNode<ItemType>>(rootItem,
		CopyTree(leftTreePtr->GetRootPtr()),
		CopyTree(rightTreePtr->GetRootPtr())))
{} //end of "CTOR"


// ==== CBinaryNodeTree<ItemType>::CBinaryNodeTree ============================
//
// This is the copy constructor for CBinaryNodeTree. It creates a deep copy of
// "tree."
//
// Input:
//       tree   [IN] - A const templated CBinaryNodeTree that will be copied.
//       
// Output:
//       Nothing
//
// ============================================================================

template <class ItemType>
CBinaryNodeTree<ItemType>::
	CBinaryNodeTree(const CBinaryNodeTree<ItemType> &tree)
{
	SetRootPtr(CopyTree(tree->GetRootPtr()));
} //end of "CTOR"


// ==== CBinaryNodeTree<ItemType>::~CBinaryNodeTree ===========================
//
// This is the destructor for CBinaryNodeTree. It will release all the nodes
// from the heap.
//
// Input:
//       void
//       
// Output:
//       Nothing
//
// ============================================================================

template <class ItemType>
CBinaryNodeTree<ItemType>::~CBinaryNodeTree()
{
	DestroyTree(m_rootPtr);
} //end of "DTOR"


// ==== CBinaryNodeTree<ItemType>::IsEmpty ====================================
//
// This function checks if the tree is empty or not.
//
// Input:
//       void
//
// Output:
//       Returns true if the tree is empty, otherwise false.
//
// ============================================================================

template <class ItemType>
bool CBinaryNodeTree<ItemType>::IsEmpty() const
{
	return (m_rootPtr == nullptr) ? 1 : 0;
} //end of "IsEmpty"


// ==== CBinaryNodeTree<ItemType>::GetHeight ==================================
//
// This function returns the height of the tree. It calls the protected member
// function GetHeightHelper to get the height from the root of the tree.
//
// Input:
//       void
//
// Output:
//       Returns an integer for the height of the tree.
//
// ============================================================================

template <class ItemType>
int CBinaryNodeTree<ItemType>::GetHeight() const
{
	return GetHeightHelper(m_rootPtr);
} //end of "GetHeight"


// ==== CBinaryNodeTree<ItemType>::GetNumberOfNodes ===========================
//
// This function returns the number of nodes in the tree. It calls the
// protected member function GetNumberOfNodesHelper to get the number of nodes
// from the root of the tree.
//
// Input:
//       void
//
// Output:
//       Returns an integer for the number of nodes in the tree.
//
// ============================================================================

template <class ItemType>
int CBinaryNodeTree<ItemType>::GetNumberOfNodes() const
{
	return GetNumberOfNodesHelper(m_rootPtr);
} //end of "GetNumberOfNodes"


// ==== CBinaryNodeTree<ItemType>::GetRootData ================================
//
// This function returns the data item in the root of the tree.
//
// Throws a PrecondViolatedExcept if the root of the tree is empty (nullptr).
//
// Input:
//       void
//
// Output:
//       Returns an ItemType, which is the item in the root of the tree.
//
// ============================================================================

template <class ItemType>
ItemType CBinaryNodeTree<ItemType>::GetRootData() const
	throw(PrecondViolatedExcept)
{
	if (!IsEmpty())
	{
		return m_rootPtr->GetItem();
	}
	throw PrecondViolatedExcept("Empty Tree");
} //end of "GetRootData"


// ==== CBinaryNodeTree<ItemType>::SetRootData ================================
//
// This function sets the data item in the root of the tree.
//
// Input:
//       newData   [IN] - A const ItemType reference that has the new data
//                        value.
//       
// Output:
//       void
//
// ============================================================================

template <class ItemType>
void CBinaryNodeTree<ItemType>::SetRootData(const ItemType &newData)
{
	m_rootPtr->SetItem(newData);
} //end of "SetRootData"


// ==== CBinaryNodeTree<ItemType>::Clear ======================================
//
// This function removes all nodes from the heap and sets the root pointer to
// nullptr. To make things easier, this function can call the member function
// DestroyTree.
//
// Input:
//       void
//       
// Output:
//       void
//
// ============================================================================

template <class ItemType>
void CBinaryNodeTree<ItemType>::Clear()
{
	DestroyTree(m_rootPtr);
	SetRootPtr(nullptr);
} //end of "Clear"


// ==== CBinaryNodeTree<ItemType>::Contains ===================================
//
// This function checks if a particular entry exists in the tree.
//
// Input:
//       anEntry   [IN] - A const ItemType reference to check of its
//                        existence.
//
// Output:
//       Returns true if the entry is already in the tree, false otherwise.
//
// ============================================================================

template <class ItemType>
bool CBinaryNodeTree<ItemType>::Contains(const ItemType &anEntry) const
{
	bool success;
	FindNode(m_rootPtr, anEntry, success);
	return success;
} //end of "Contains"


// ==== CBinaryNodeTree<ItemType>::PreorderTraverse ===========================
//
// This function traverses in pre-order by calling
// the protected member function Preorder.
//
// Input:
//       void Visit(ItemType &item)   [IN] - The function used to display (or
//                                           process) a node.
//
// Output:
//       void
//
// ============================================================================

template <class ItemType>
void CBinaryNodeTree<ItemType>::PreorderTraverse(
	void Visit(const ItemType &item)) const
{
	Preorder(Visit, m_rootPtr);
} //end of "PreorderTraverse"


// ==== CBinaryNodeTree<ItemType>::InorderTraverse ============================
//
// This function traverses in in-order by callingt
// he protected member function Inorder.
//
// Input:
//       void Visit(ItemType &item)   [IN] - The function used to display (or
//                                           process) a node.
// Output:
//       void
//
// ============================================================================

template <class ItemType>
void CBinaryNodeTree<ItemType>::InorderTraverse(
	void Visit(const ItemType &item)) const
{
	Inorder(Visit, m_rootPtr);
} //end of "InorderTraverse"


// ==== CBinaryNodeTree<ItemType>::PostorderTraverse ==========================
//
// This function traverses in post-order by calling the protected member
// function Postorder.
//
// Input:
//       void Visit(ItemType &item)   [IN] - The function used to display (or
//                                           process) a node.
// Output:
//       void
//
// ============================================================================

template <class ItemType>
void CBinaryNodeTree<ItemType>::PostorderTraverse(
	void Visit(const ItemType &item)) const
{
	Postorder(Visit, m_rootPtr);
} //end of "PostorderTraverse"


// ==== CBinaryNodeTree<ItemType>::LevelorderTraverse =========================
//
// This function traverses in level-order by calling the protected member
// function Levelorder for each level to process.
//
// Input:
//       void Visit(ItemType &item)   [IN] - The function used to display (or
//                                           process) a node.
// Output:
//       void
//
// ============================================================================

template <class ItemType>
void CBinaryNodeTree<ItemType>::LevelorderTraverse(
	void Visit(const ItemType &item)) const
{
	for (int i = 1; i <= GetHeight(); i++)
	{
		std::cout << "Level " << i - 1 << ": " << std::endl << std::endl;
		Levelorder(Visit, m_rootPtr, i);
		std::cout << std::endl;
	}
} //end of "LevelorderTraverse"



// ==== CBinaryNodeTree<ItemType>::operator= ==================================
//
// This function assigns the right-hand side CBinaryNodeTree to the left-hand
// side CBinaryNodeTree.  Make sure to protect against assignment to self!
//
// Input:
//       rhs   [IN] - A const templated CBinaryNodeTree to copy from.
//
// Output:
//       A templated CBinaryNodeTree reference object
// (the left-hand side of the tree.
//
// ============================================================================

template <class ItemType>
CBinaryNodeTree<ItemType>& CBinaryNodeTree<ItemType>::operator=(
	const CBinaryNodeTree<ItemType> &rhs)
{
	if (this != &rhs)
	{
		this->Clear();
		this->SetRootPtr(this->CopyTree(rhs.GetRootPtr()));
	}
	return *this;
} //end of "operator="


// ==== CBinaryNodeTree<ItemType>::GetRootPtr =================================
//
// This function returns m_rootPtr
//
// Input:
//       Nothing
//
// Output:
//       A CBinaryNode<ItemType> templated pointer that is the address of the
//          root pointer.
//
// ============================================================================

template <class ItemType>
std::shared_ptr<CBinaryNode<ItemType>>
	CBinaryNodeTree<ItemType>::GetRootPtr() const
{
	return m_rootPtr;
} //end of "GetRootPtr"


// ==== CBinaryNodeTree<ItemType>::SetRootPtr =================================
//
// This function sets m_rootPtr
//
// Input:
//       rootPtr    [IN]    - A CBinaryNode<ItemType> pointer.
// Output:
//       Nothing
//
// ============================================================================

template <class ItemType>
void CBinaryNodeTree<ItemType>::
	SetRootPtr(std::shared_ptr<CBinaryNode<ItemType>> rootPtr)
{
	m_rootPtr = rootPtr;
} //end of "SetRootPtr"


// ==== CBinaryNodeTree<ItemType>::GetParentNode ==============================
//
// This function searches for the parent node of any node in the tree.
//
// Input:
//      subTreePtr [IN] - A templated CBinaryNode pointer to start the
//                        search of the parent node.
//      nodePtr    [IN] - A templated CBinaryNode pointer to find the parent
//                        of.
//
// Output:
//       A CBinaryNode<ItemType> templated pointer that is the address of the
//       parent node pointer.
//
// ============================================================================

template <class ItemType>
std::shared_ptr<CBinaryNode<ItemType>> CBinaryNodeTree<ItemType>::
	GetParentNode(std::shared_ptr<CBinaryNode<ItemType>> subTreePtr,
    std::shared_ptr<CBinaryNode<ItemType>> nodePtr) const
{
    if (subTreePtr == nullptr)
    {
        return nullptr;
    }
    if (subTreePtr->GetLeftChildPtr() == nodePtr
        || subTreePtr->GetLeftChildPtr() == nodePtr)
    {
        return subTreePtr;
    }
    else
    {
		if (subTreePtr->GetItem() < nodePtr->GetItem())
		{
			GetParentNode(subTreePtr->GetRightChildPtr(), nodePtr);
		}
		else
		{
        	GetParentNode(subTreePtr->GetLeftChildPtr(), nodePtr);
		}
    }

} //end of "GetParentNode"


// ==== CBinaryNodeTree<ItemType>::GetHeightHelper ============================
//
// This function finds the height starting at subTreePtr (this could be root or
// any other node within the tree).
//
// Input:
//      subTreePtr   [IN] - A templated CBinaryNode pointer to find the height
//                          from.
//
// Output:
//       An int that is the height from subTreePtr.
//
// ============================================================================

template <class ItemType>
int CBinaryNodeTree<ItemType>::GetHeightHelper
	(std::shared_ptr<CBinaryNode<ItemType>> subTreePtr) const
{
	if (subTreePtr == nullptr)
	{
		return 0;
	}
	else
	{
		return 1 + std::max(GetHeightHelper(subTreePtr->GetLeftChildPtr()),
			GetHeightHelper(subTreePtr->GetRightChildPtr()));
	}
} //end of "GetHeightHelper"


// ==== CBinaryNodeTree<ItemType>::GetNumberOfNodesHelper =====================
//
// This function finds the number of nodes starting at subTreePtr
// (this could be root or any other node within the tree).
//
// Input:
//      subTreePtr   [IN] - A templated CBinaryNode pointer to find the number
//                          of nodes from.
//
// Output:
//       An int that represents the number of nodes from subTreePtr.
//
// ============================================================================

template <class ItemType>
int CBinaryNodeTree<ItemType>::GetNumberOfNodesHelper
	(std::shared_ptr<CBinaryNode<ItemType>> subTreePtr) const
{
	if (subTreePtr == nullptr)
	{
		return 0;
	}
	int numNodes = 1;
	numNodes += GetNumberOfNodesHelper(subTreePtr->GetLeftChildPtr());
	numNodes += GetNumberOfNodesHelper(subTreePtr->GetRightChildPtr());
	return numNodes;
} //end of "GetNumberOfNodesHeler"


// ==== CBinaryNodeTree<ItemType>::FindMinNode ================================
//
// This function finds the minimum ItemType Node in the tree starting from
// subTreePtr. If there is no minimum ItemType Node found, the function returns
// nullptr.
//
// Input:
//      subTreePtr   [IN] - A templated CBinaryNode pointer to find the
//                          minimum node from.
//
// Output:
//       A templated CBinaryNode<ItemType> pointer that points to the minimum
//          node.
//
// ============================================================================

template <class ItemType>
std::shared_ptr<CBinaryNode<ItemType>> CBinaryNodeTree<ItemType>::
	FindMinNode(std::shared_ptr<CBinaryNode<ItemType>> subTreePtr)
{
	bool success;
	std::shared_ptr<CBinaryNode<ItemType>> minItem;
	minItem = FindNode(m_rootPtr, FindMinValue(subTreePtr), success);
	if (success)
	{
		return minItem;
	}
	return nullptr;
} //end of "FindMinNode"


// ==== CBinaryNodeTree<ItemType>::FindMinValue ===============================
//
// This function finds the minimum key value in the tree starting from
// subTreePtr.
//
// Input:
//      subTreePtr   [IN] - A templated CBinaryNode pointer to find the
//                          minimum node from.
//
// Output:
//       An ItemType
//
// ============================================================================

template <class ItemType>
ItemType CBinaryNodeTree<ItemType>::
	FindMinValue(std::shared_ptr<CBinaryNode<ItemType>> subTreePtr)
{
	ItemType minValue = subTreePtr->GetItem();
	if (subTreePtr->GetLeftChildPtr() != nullptr)
	{
		minValue = std::min(minValue, 
			FindMinValue(subTreePtr->GetLeftChildPtr()));
	}
	if (subTreePtr->GetRightChildPtr() != nullptr)
	{
		minValue = std::min(minValue,
			FindMinValue(subTreePtr->GetRightChildPtr()));
	}
	return minValue;
} //end of "FindMinValue"


// ==== CBinaryNodeTree<ItemType>::FindMaxNode ================================
//
// This function finds the maximum ItemType Node in the tree starting from
// subTreePtr. If there is no maximum ItemType Node found, the function returns
// nullptr.
//
// Input:
//      subTreePtr   [IN] - A templated CBinaryNode pointer to find the
//                          maximum node from.
//
// Output:
//       A templated CBinaryNode<ItemType> pointer that points to the maximum
//       node.
//
// ============================================================================

template <class ItemType>
std::shared_ptr<CBinaryNode<ItemType>> CBinaryNodeTree<ItemType>::
	FindMaxNode(std::shared_ptr<CBinaryNode<ItemType>> subTreePtr)
{
	bool success;
	std::shared_ptr<CBinaryNode<ItemType>> maxItem;
	maxItem = FindNode(m_rootPtr, FindMaxValue(subTreePtr), success);
	if (success)
	{
		return maxItem;
	}
	return nullptr;
} //end of "FindMaxNode"


// ==== CBinaryNodeTree<ItemType>::FindMaxValue ===============================
//
// This function finds the maximum key value in the tree starting from
// subTreePtr.
//
// Input:
//      subTreePtr   [IN] - A templated CBinaryNode pointer to find the
//                          maximum node from.
//
// Output:
//       An ItemType
//
// ============================================================================

template <class ItemType>
ItemType CBinaryNodeTree<ItemType>::
	FindMaxValue(std::shared_ptr<CBinaryNode<ItemType>> subTreePtr)
{
	ItemType maxValue = subTreePtr->GetItem();
	if (subTreePtr->GetLeftChildPtr() != nullptr)
	{
		maxValue = std::max(maxValue, 
			FindMaxValue(subTreePtr->GetLeftChildPtr()));
	}
	if (subTreePtr->GetRightChildPtr() != nullptr)
	{
		maxValue = std::max(maxValue,
			FindMaxValue(subTreePtr->GetRightChildPtr()));
	}
	return maxValue;
} //end of "FindMaxValue"

// ==== CBinaryNodeTree<ItemType>::CopyTree ===================================
//
// This function copies a tree using a deep copy.
//
// Input:
//      oldTreeRootPtr   [IN] - A templated CBinaryNode pointer to copy from.
//
// Output:
//       A templated CBinaryNode<ItemType> pointer that points to the new root.
//
// ============================================================================

template <class ItemType>
std::shared_ptr<CBinaryNode<ItemType>> CBinaryNodeTree<ItemType>::
	CopyTree(const std::shared_ptr<CBinaryNode<ItemType>> oldTreeRootPtr) const
{
	std::shared_ptr<CBinaryNode<ItemType>> newTreePtr;
	if (oldTreeRootPtr != nullptr)
	{
		newTreePtr = std::make_shared<CBinaryNode<ItemType>>
			(oldTreeRootPtr->GetItem(), nullptr, nullptr);
		newTreePtr->SetLeftChildPtr
			(CopyTree(oldTreeRootPtr->GetLeftChildPtr()));
		newTreePtr->SetRightChildPtr
			(CopyTree(oldTreeRootPtr->GetRightChildPtr()));
	}
	return newTreePtr;
} //end of "CopyTree"


// ==== CBinaryNodeTree<ItemType>::DestroyTree ================================
//
// This function destroys a tree. In other words, it releases the memory from
// the heap.
//
// Input:
//       CBinaryNode pointer subTreePtr [IN/OUT] - The tree to destroy.
//       
// Output:
//       void
//
// ============================================================================

template <class ItemType>
void CBinaryNodeTree<ItemType>::DestroyTree
	(std::shared_ptr<CBinaryNode<ItemType>> subTreePtr)
{
	if (subTreePtr != nullptr)
	{
		DestroyTree(subTreePtr->GetLeftChildPtr());
		DestroyTree(subTreePtr->GetRightChildPtr());
		subTreePtr.reset();
	}
} //end of "DestroyTree"


// ==== CBinaryNodeTree<ItemType>::Preorder ===================================
//
// This function traverses the tree in pre-order.
//
// Input:
//      void Visit(ItemType &item) [IN] - The function used to display (or
//                                        process) a node.
//      treePtr                    [IN] - The tree to process.
//
// Output:
//       void
//
// ============================================================================

template <class ItemType>
void CBinaryNodeTree<ItemType>::Preorder
	(void Visit(const ItemType &item),
	std::shared_ptr<CBinaryNode<ItemType>> treePtr) const
{
	if (treePtr != nullptr)
	{
		ItemType currentItem = treePtr->GetItem();
		Visit(currentItem);
		Preorder(Visit, treePtr->GetLeftChildPtr());
		Preorder(Visit, treePtr->GetRightChildPtr());
	}
} //end of "Preorder"


// ==== CBinaryNodeTree<ItemType>::Inorder ====================================
//
// This function traverses the tree in in-order.
//
// Input:
//      void Visit(ItemType &item) [IN] - The function used to display (or
//                                        process) a node.
//      treePtr                    [IN] - The tree to process.
//
// Output:
//       void
//
// ============================================================================

template <class ItemType>
void CBinaryNodeTree<ItemType>::Inorder
	(void Visit(const ItemType &item),
	std::shared_ptr<CBinaryNode<ItemType>> treePtr) const
{
	if (treePtr != nullptr)
	{
		Inorder(Visit, treePtr->GetLeftChildPtr());
		ItemType currentItem = treePtr->GetItem();
		Visit(currentItem);
		Inorder(Visit, treePtr->GetRightChildPtr());
	}
} //end of "Inorder"


// ==== CBinaryNodeTree<ItemType>::Postorder ==================================
//
// This function traverses the tree in post-order.
//
// Input:
//      void Visit(ItemType &item) [IN] - The function used to display (or
//                                        process) a node.
//      treePtr                    [IN] - The tree to process.
//
// Output:
//       void
//
// ============================================================================

template <class ItemType>
void CBinaryNodeTree<ItemType>::Postorder
	(void Visit(const ItemType &item),
	std::shared_ptr<CBinaryNode<ItemType>> treePtr) const
{
	if (treePtr != nullptr)
	{
		Postorder(Visit, treePtr->GetLeftChildPtr());
		Postorder(Visit, treePtr->GetRightChildPtr());
		ItemType currentItem = treePtr->GetItem();
		Visit(currentItem);
	}
} //end of "Postorder"


// ==== CBinaryNodeTree<ItemType>::Levelorder =================================
//
// This function traverses the tree in level-order.
//
// Input:
//      void Visit(ItemType &item) [IN] - The function used to display (or
//                                        process) a node.
//      treePtr                    [IN] - The tree to process.
//		level                      [IN] - The height of the tree (total
//                                        levels to process).
//
// Output:
//       void
//
// ============================================================================

template <class ItemType>
void CBinaryNodeTree<ItemType>::Levelorder
	(void Visit(const ItemType& item),
	std::shared_ptr<CBinaryNode<ItemType>> treePtr,
	int level) const
{
    if (treePtr == nullptr)
    {
        return;
    }
    if (level == 1)
    {
        ItemType currentItem = treePtr->GetItem();
		Visit(currentItem);
    }
    else if (level > 1)
    {
        Levelorder(Visit, treePtr->GetLeftChildPtr(), level - 1);
        Levelorder(Visit, treePtr->GetRightChildPtr(), level - 1);
    }
} //end of "Levelorder"
