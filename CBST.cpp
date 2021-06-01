// ============================================================================
// File: CBST.cpp
// ============================================================================
// Programmer: Ramin Dehghan
// Date: May 22, 2021
// Class: CSCI 133 ("Data Structures Using C++")
// Time: Online
// Instructor: Dr. Rodriguez
// Project: Project CBST
//
// Description:
// Implementation file for the class CBST
// ============================================================================

#include "CBST.h"


// ==== CBST<ItemType>::CBST ==================================================
//
// This is the default constructor for CBST<ItemType>. It sets the root to
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
CBST<ItemType>::CBST() :
    CBinaryNodeTree<ItemType>()
{} //end of "CTOR"


// ==== CBST<ItemType>::CBST ==================================================
//
// This is the type constructor for CBST<ItemType>. It allocates a space for a
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
CBST<ItemType>::CBST(const ItemType &rootItem) :
    CBinaryNodeTree<ItemType>(rootItem)
{} //end of "CTOR"


// ==== CBST<ItemType>::CBST ==================================================
//
// This is the copy constructor for CBST<ItemType>. It creates a deep copy of
// "tree."
//
// Input:
//       tree   [IN] - A const templated CBST that will be copied.
//       
// Output:
//       Nothing
//
// ============================================================================

template <class ItemType>
CBST<ItemType>::CBST(const CBST<ItemType> &tree) :
    CBinaryNodeTree<ItemType>()
{
    this->SetRootPtr(this->CopyTree(tree.GetRootPtr()));
} //end of "CTOR"


// ==== CBST<ItemType>::~CBST =================================================
//
// This is the destructor for CBST<ItemType>. It will release all the nodes
// from the heap.
//
// Input:
//       void
//       
// Output:
//       Nothing
//
// ============================================================================

/** No need for implementation.
    Default constructor will take care of smart pointers
    by invoking CBinaryNodeTree destructor */


// ==== CBST<ItemType>::Add ===================================================
//
// This function adds an item to a tree.  Calls the PlaceNode function to add
// the node to the tree to make sure it is balanced using AVL.
//
// Input:
//       newEntry   [IN] - A const ItemType reference to the new entry to be
//                         added to the tree.
//       
// Output:
//       Returns true if successful, otherwise false.
//
// ============================================================================

template <class ItemType>
bool CBST<ItemType>::Add(const ItemType &newEntry)
{
    this->SetRootPtr(PlaceNode(this->GetRootPtr(),
        std::make_shared<CBinaryNode<ItemType>>(newEntry)));
    return true;
} //end of "Add"


// ==== CBST<ItemType>::Remove ================================================
//
// This function removes an entry (a node), if it exists, from the tree.
//
// Input:
//       anEntry   [IN] - A const ItemType reference to the new entry to be
//                        added to the tree.
//
// Output:
//       Returns true if successful, otherwise false.
//
// ============================================================================

template <class ItemType>
bool CBST<ItemType>::Remove(const ItemType &anEntry)
{
    bool success;
    this->SetRootPtr(RemoveValue(this->GetRootPtr(), anEntry, success));
    return success;
} //end of "Remove"


// ==== CBST<ItemType>::operator= =============================================
//
// This function assigns the right-hand side CBST to the left-hand side CBST.
// Make sure to protect against assignment to self!
//
// Input:
//       rhs   [IN] - A const templated CBST to copy from.
// Output:
//       A templated CBST reference object (the left-hand side of the tree.
//
// ============================================================================

/** Will not implement.
 * Inherited assignment operator from CBinaryNodeTree is sufficient! */


// ==== CBST<ItemType>::PlaceNode =============================================
//
// This function adds a node in the tree. It makes sure that the same node
//  value is not added twice. Furthermore, as soon as it adds a node,
//  it makes sure the tree is still AVL balanced.
//
// Input:
//      subTreePtr  [IN]    - A templated CBinaryNode pointer to start the
//                              search of where to add the node.
//      newNode     [IN]    - A templated CBinaryNode pointer node that will be
//                              added to the tree.
// Output:
//       A CBinaryNode<ItemType> templated pointer that is the address of
//          the updated parent node pointer (after any shifts caused from AVL
//          balancing, parent node may need updating).
//
// ============================================================================

template <class ItemType>
std::shared_ptr<CBinaryNode<ItemType>> CBST<ItemType>::
    PlaceNode(std::shared_ptr<CBinaryNode<ItemType>> subTreePtr,
        std::shared_ptr<CBinaryNode<ItemType>> newNode)
{
    //BalanceFactor lambda
    auto balanceFactor = [&](std::shared_ptr<CBinaryNode<ItemType>> node)
    {
        return (this->GetHeightHelper(node->GetLeftChildPtr()) -
            this->GetHeightHelper(node->GetRightChildPtr()));
    }; //end of "balanceFactor"

    //balance Lambda
    auto balance = [&](std::shared_ptr<CBinaryNode<ItemType>> node)
    {
        int bf = balanceFactor(node);
        if (bf > 1)
        {
            if (balanceFactor(node->GetLeftChildPtr()) > 0)
            {
                node = RightRotate(node);
            }
            else
            {
                node = LeftRightRotate(node);
            }
        }
        else if (bf < -1)
        {
            if (balanceFactor(node->GetRightChildPtr()) > 0)
            {
                node = RightLeftRotate(node);
            }
            else
            {
                node = LeftRotate(node);
            }
        }
        return node;
    }; //end of "balance"

    bool containsSuccess;
    FindNode(this->GetRootPtr(), newNode->GetItem(), containsSuccess);
    if (containsSuccess)
    {
        return subTreePtr;
    }
    if (subTreePtr == nullptr)
    {
        return newNode;
    }
    else if (subTreePtr->GetItem() > newNode->GetItem())
    {
        subTreePtr->SetLeftChildPtr(PlaceNode(
            subTreePtr->GetLeftChildPtr(), newNode));

        //Rebalance Tree
        subTreePtr = balance(subTreePtr);
    }
    else
    {
        subTreePtr->SetRightChildPtr(PlaceNode(
            subTreePtr->GetRightChildPtr(), newNode));

        //Rebalance Tree
        subTreePtr = balance(subTreePtr);
    }
    return subTreePtr;
} //end of "PlaceNode"


// ==== CBST<ItemType>::LeftRotate ============================================
//
// This function rotates the nodes to the left.
//
// Input:
//      subTreePtr   [IN] - A templated CBinaryNode pointer to start the
//                          rotation.
// Output:
//       An updated CBinaryNode<ItemType> templated pointer that is the new
//       "subTreePtr" after the rotation.
//
// ============================================================================

template <class ItemType>
std::shared_ptr<CBinaryNode<ItemType>>CBST<ItemType>::
    LeftRotate(std::shared_ptr<CBinaryNode<ItemType>> subTreePtr)
{
    std::shared_ptr<CBinaryNode<ItemType>> st1 =
        subTreePtr->GetRightChildPtr();
    std::shared_ptr<CBinaryNode<ItemType>> st2 = st1->GetLeftChildPtr();
    st1->SetLeftChildPtr(subTreePtr);
    subTreePtr->SetRightChildPtr(st2);
    return st1;
} //end of "LeftRotate"


// ==== CBST<ItemType>::RightRotate ===========================================
//
// This function rotates the nodes to the right.
//
// Input:
//      subTreePtr   [IN] - A templated CBinaryNode pointer to start the
//                          rotation.
// Output:
//       An updated CBinaryNode<ItemType> templated pointer that is the new
//       "subTreePtr" after the rotation.
//
// ============================================================================

template <class ItemType>
std::shared_ptr<CBinaryNode<ItemType>> CBST<ItemType>::
    RightRotate(std::shared_ptr<CBinaryNode<ItemType>> subTreePtr)
{
    std::shared_ptr<CBinaryNode<ItemType>> st1 = subTreePtr->GetLeftChildPtr();
    std::shared_ptr<CBinaryNode<ItemType>> st2 = st1->GetRightChildPtr();
    st1->SetRightChildPtr(subTreePtr);
    subTreePtr->SetLeftChildPtr(st2);
    return st1;
} //end of "RightRotate"


// ==== CBST<ItemType>::LeftRightRotate =======================================
//
// This function rotates the nodes to the left and then right. In other words,
// it rotates the left child of subTreePtr to the left and then rotates
// subTreePtr to the right.
//
// Input:
//      subTreePtr   [IN] - A templated CBinaryNode pointer to start the
//                          rotation.
// Output:
//       An updated CBinaryNode<ItemType> templated pointer that is the new
//       "subTreePtr" after the rotation.
//
// ============================================================================

template <class ItemType>
std::shared_ptr<CBinaryNode<ItemType>> CBST<ItemType>::
    LeftRightRotate(std::shared_ptr<CBinaryNode<ItemType>> subTreePtr)
{
    std::shared_ptr<CBinaryNode<ItemType>> st1 = subTreePtr->GetLeftChildPtr();
    st1 = LeftRotate(st1);
    subTreePtr->SetLeftChildPtr(st1);
    subTreePtr = RightRotate(subTreePtr);
    return subTreePtr;
} //end of "LeftRightRotate"


// ==== CBST<ItemType>::RightLeftRotate =======================================
//
// This function rotates the nodes to the right and then left. In other words,
// it rotates the right child of subTreePtr to the right and then rotates
// subTreePtr to the left.
//
// Input:
//      subTreePtr   [IN] - A templated CBinaryNode pointer to start the
//                          rotation.
// Output:
//       An updated CBinaryNode<ItemType> templated pointer that is the new
//       "subTreePtr" after the rotation.
//
// ============================================================================

template <class ItemType>
std::shared_ptr<CBinaryNode<ItemType>> CBST<ItemType>::
    RightLeftRotate(std::shared_ptr<CBinaryNode<ItemType>> subTreePtr)
{
    std::shared_ptr<CBinaryNode<ItemType>> st1 =
        subTreePtr->GetRightChildPtr();
    st1 = RightRotate(st1);
    subTreePtr->SetRightChildPtr(st1);
    subTreePtr = LeftRotate(subTreePtr);
    return subTreePtr;
} //end of "RightLeftRotate"


// ==== CBST<ItemType>::RemoveValue ===========================================
//
// This function removes a value from the tree. It also keeps the tree AVL
// balanced after each removal.
//
// Input:
//      subTreePtr   [IN]  - A templated CBinaryNode pointer to start the
//                             search of the node to remove.
//      target       [IN]  - A const ItemType value that we want to remove from
//                             the tree.
//      success      [OUT] - A bool value that is marked true if sucessful,
//                             false otherwise.
//
// Output:
//       An updated CBinaryNode<ItemType> templated pointer that is the new
//       "subTreePtr" after the removal.
//
// ============================================================================

template <class ItemType>
std::shared_ptr<CBinaryNode<ItemType>> CBST<ItemType>::
    RemoveValue(std::shared_ptr<CBinaryNode<ItemType>> subTreePtr,
        const ItemType &target, bool &success)
{
    //BalanceFactor lambda
    auto balanceFactor = [&](std::shared_ptr<CBinaryNode<ItemType>> node)
    {
        return (this->GetHeightHelper(node->GetLeftChildPtr()) -
            this->GetHeightHelper(node->GetRightChildPtr()));
    }; //end of "balanceFactor"

    //balance Lambda
    auto balance = [&](std::shared_ptr<CBinaryNode<ItemType>> node)
    {
        int bf = balanceFactor(node);
        if (bf > 1)
        {
            if (balanceFactor(node->GetLeftChildPtr()) > 0)
            {
                node = RightRotate(node);
            }
            else
            {
                node = LeftRightRotate(node);
            }
        }
        else if (bf < -1)
        {
            if (balanceFactor(node->GetRightChildPtr()) > 0)
            {
                node = RightLeftRotate(node);
            }
            else
            {
                node = LeftRotate(node);
            }
        }
        return node;
    }; //end of "balance"

    if (subTreePtr == nullptr)
    {
        success = false;
        return subTreePtr;
    }
    bool containsSuccess;
    FindNode(this->GetRootPtr(), target, containsSuccess);
    if (!containsSuccess)
    {
        success = false;
        return subTreePtr;
    }
    if (subTreePtr->GetItem() > target)
    {
        subTreePtr->SetLeftChildPtr(RemoveValue(
            subTreePtr->GetLeftChildPtr(), target, success));
        
        //Rebalance Tree
        subTreePtr = balance(subTreePtr);
    }
    else if (subTreePtr->GetItem() < target)
    {
        subTreePtr->SetRightChildPtr(RemoveValue(
            subTreePtr->GetRightChildPtr(), target, success));
        
        //Rebalance Tree
        subTreePtr = balance(subTreePtr);
    }
    else
    {
        if (subTreePtr->GetLeftChildPtr() == nullptr
            || subTreePtr->GetRightChildPtr() == nullptr)
        {
            std::shared_ptr<CBinaryNode<ItemType>> tempNode =
                (subTreePtr->GetLeftChildPtr() != nullptr) ?
                (subTreePtr->GetLeftChildPtr()) :
                (subTreePtr->GetRightChildPtr());
        
            if (tempNode == nullptr)
            {
                tempNode = subTreePtr;
                subTreePtr = nullptr;

            }
            else
            {
                *subTreePtr = *tempNode;
            }
            tempNode->SetLeftChildPtr(nullptr);
            tempNode->SetRightChildPtr(nullptr);
            tempNode.reset();
        }
        else
        {
            std::shared_ptr<CBinaryNode<ItemType>> tempNode =
                this->FindMinNode(subTreePtr->GetRightChildPtr());
            subTreePtr->SetItem(tempNode->GetItem());
            subTreePtr->SetRightChildPtr(RemoveValue(
                subTreePtr->GetRightChildPtr(), tempNode->GetItem(), success));
        }   
    }
    success = true;
    return subTreePtr;
}


// ==== CBinaryNodeTree<ItemType>::FindNode ===================================
//
// This function finds a target node if it exists.
//
// Input:
//      treePtr  [IN]  - A templated CBinaryNode pointer to start the
//                       search of the node to find
//      target   [IN]  - A const ItemType value that we want to find from
//                       the tree.
//      success  [OUT] - A bool value that is marked true if sucessful,
//                       false otherwise.
//
// Output:
//       An CBinaryNode<ItemType> templated pointer of the node found.  If not
//       found, a nullptr is returned.
//
// ============================================================================

template <class ItemType>
std::shared_ptr<CBinaryNode<ItemType>> CBST<ItemType>::
    FindNode(std::shared_ptr<CBinaryNode<ItemType>> treePtr,
        const ItemType &target, bool &success) const
{
    if (treePtr == nullptr)
    {
        success = false;
        return nullptr;
    }
    else if (treePtr->GetItem() == target)
    {
        success = true;
        return treePtr;
    }
    else if (treePtr->GetItem() > target)
    {
        return FindNode(treePtr->GetLeftChildPtr(), target, success);
    }
    else if (treePtr->GetItem() < target)
    {
        return FindNode(treePtr->GetRightChildPtr(), target, success);
    }
    return nullptr;
} //end of "FindNode"
