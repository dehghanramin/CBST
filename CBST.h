// ============================================================================
// File: CBST.h
// ============================================================================
// Programmer: Ramin Dehghan
// Date: May 22, 2021
// Class: CSCI 133 ("Data Structures Using C++")
// Time: Online
// Instructor: Dr. Rodriguez
// Project: Project CBST
//
// Description:
// Header file for the class CBST (Binary Search Tree)
// ============================================================================

#ifndef CBST_HEADER
#define CBST_HEADER

#include "CBinaryTreeInterface.h"
#include "CBinaryNode.h"
#include "CBinaryNodeTree.h"
#include <memory>


template<class ItemType>
class CBST : public CBinaryNodeTree<ItemType>
{
public:
    // ========================================================================
    //      Constructors and Destructor
    // ========================================================================

    /** Sets m_rootPtr to nullptr*/
    CBST();

    /** Allocates space for a CBinaryNode and sets it equal to m_rootPtr. The
        allocated node initializes the item and sets nullptr to its left and
        right childs. */
    CBST(const ItemType &rootItem);

    /** Copy constructor. It copies the tree that was given as an argument.
        Uses a deep copy by calling the inherited method CopyTree. */
    CBST(const CBST<ItemType> &tree);

    /** Destructor. Releases the memory of the tree appropriately. */
    virtual ~CBST() = default;
   
    // ========================================================================
    //      Member Functions
    // ========================================================================

    /** Adds a new node to the tree. Allocate the new node first and then call
        the function PlaceNode to add the new node to the tree.
    @param newEntry: An ItemType that will be used to initialzed the new node.
    @return True if add was successful, or false if it is not. */
    virtual bool Add(const ItemType &newEntry);

    /** Removes a node from the tree. This function calls the function 
        RemoveValue.
    @param target: An ItemType that will be used to find the node to delete.
    @return True if remove was successful, or false if it is not. */
    virtual bool Remove(const ItemType &anEntry);

    /** Overloaded assignment operator. Used to assign a CBST.
    @param rhs: A const CBST reference object.
    @return CBST reference object. 
    @note Will not implement. CBinaryNodeTree
        assingment operator is sufficient
    CBST<ItemType>& operator=(const CBST<ItemType> &rhs); */

 
protected:
    // ========================================================================
    //      Protected Member Functions
    // ========================================================================

    /** Rotates the nodes to the left.
    @param subTreePtr: A pointer of CBinaryNodeTree type for where the rotation
        will begin (grandparent node)
    @return CBinaryNode: Returns the updated subTreePtr node after peforming a
        left rotation. */
    std::shared_ptr<CBinaryNode<ItemType>>
        LeftRotate(std::shared_ptr<CBinaryNode<ItemType>> subTreePtr);
    
    /** Rotates the nodes to the right.
    @param subTreePtr: A pointer of CBinaryNodeTree type for where the rotation
        will begin (grandparent node)
    @return CBinaryNode: Returns the updated subTreePtr node after peforming a
        right rotation. */
    std::shared_ptr<CBinaryNode<ItemType>>
        RightRotate(std::shared_ptr<CBinaryNode<ItemType>> subTreePtr);
    
    /** Rotates the nodes to left-right.
    @param subTreePtr: A pointer of CBinaryNodeTree type for where the rotation
        will begin (grandparent node)
    @return CBinaryNode: Returns the updated subTreePtr node after peforming a
        left-right rotation. */
    std::shared_ptr<CBinaryNode<ItemType>>
        LeftRightRotate(std::shared_ptr<CBinaryNode<ItemType>> subTreePtr);
    
    /** Rotates the nodes to right-left.
    @param subTreePtr: A pointer of CBinaryNodeTree type for where the rotation
        will begin (grandparent node)
    @return CBinaryNode: Returns the updated subTreePtr node after peforming a
        right-left rotation. */
    std::shared_ptr<CBinaryNode<ItemType>>
        RightLeftRotate(std::shared_ptr<CBinaryNode<ItemType>> subTreePtr);
                                      
    /** Removes the target value from the tree and keeps the tree as AVL
        balanced. This is done using recursion.
    @param subTreePtr: A pointer of CBinaryNodeTree type for the root of the
        tree.
    @param target: A const ItemType reference to remove.
    @param success: A bool reference to report success or failture of the
        removal.
    @return CBinaryNode: Returns the updated subTreePtr after removing the
        node. */
    virtual std::shared_ptr<CBinaryNode<ItemType>>
        RemoveValue(std::shared_ptr<CBinaryNode<ItemType>> subTreePtr,
            const ItemType &target, bool &success);                                             

    /** This function recursively finds where the given node should be placed
        and inserts it. Then it makes sure the tree is AVL balanced.
    @param subTreePtr: A pointer of CBinaryNode type for the root of the tree.
    @param newNode: A pointer of CBinaryNode type for
        the new node to add/place.
    @return CBinaryNode: Returns the updated subTreePtr after adding the node */
    std::shared_ptr<CBinaryNode<ItemType>>
        PlaceNode(std::shared_ptr<CBinaryNode<ItemType>> subTreePtr,
            std::shared_ptr<CBinaryNode<ItemType>> newNode);
   
    /** Recursively searches for target value in the tree by using a
        preorder traversal.
    @param treePtr: A pointer of CBinaryNodeTree type for the root of the
        tree.
    @param target: A const ItemType reference to find.
    @param success: A bool reference to report success or failture of the
        search.
    @return CBinaryNode: Returns target node pointer. */
    virtual std::shared_ptr<CBinaryNode<ItemType>>
        FindNode(std::shared_ptr<CBinaryNode<ItemType>> treePtr,
            const ItemType &target, bool &success) const;
}; //end of "CBST"

#include "CBST.cpp"
#endif //CBST_HEADER
