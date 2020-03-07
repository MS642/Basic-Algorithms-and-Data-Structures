/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file. IMPORTANT: read avltree.h to understand
 * what to do in this lab.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    /** 
     * TODO: your code here. Make sure the following cases are included:
     * Case 1: subtree is NULL
     * Case 2: (key, value) pair should be inserted into left subtree
     * Case 3: (key, value) pair should be inserted into right subtree
     */
    if (subtree == NULL) {
        subtree = new Node(key, value);
        return;

    }
    else {
        if (key < subtree->key) {
            insert(subtree->left, key, value);
        } else {
            insert(subtree->right, key, value);
        }
    }
    //*_out << key << " insert under " << subtree->key << endl;
    //updateHeight(subtree);
    // Rebalance tree after insertion (don't remove this)
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::updateHeight(Node* node)
{
    updateHeight(node, 0);

        
}

template <class K, class V>
int AVLTree<K, V>::updateHeight(Node* node, int count) {
    if (!node) {
        return 0;
    }
    else
    {
        //count += max(updateHeight(node->left, count + 1), updateHeight(node->right, count + 1));
        //node->height = count;
        if (node->left != nullptr && node->right != nullptr) {
            node->height = max(height(node->left), height(node->right)) + 1;
        }
        else if (node->left != nullptr) {
            node->height = height(node->left) + 1;

        }
        else if (node->right != nullptr) {
            node->height = height(node->right) + 1;

        }
        else {
            node->height = 0;
        }
        //*_out << node->key << " " << " height " << node->height << endl;
        return node->height;
    }
}


template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)

    //*_out << "rotate left" << "\n";
    Node* newSubRoot = t->right;
    t->right = newSubRoot->left;
    newSubRoot->left = t;
    t = newSubRoot;
    updateHeight(t->left);
    updateHeight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)

    // TODO: your code here
    Node* temp = t->left;
    t->left = temp->right;
    temp->right = t;
    t = temp;
    updateHeight(t->right);
    updateHeight(t);

}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)

    // TODO: your code here
    // HINT: you should make use of the other functions defined in this file,
    // instead of manually changing the pointers again
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)

    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    /** 
      * TODO: your code here. Make sure the following cases are included:
      * Cases 1-4: the four cases of tree imbalance as discussed in lecture
      * Case 5: the tree is already balanced. You MUST still correctly update
      * subtree's height 
      */
    int balance = 0;

    if (!subtree) {
        return;
    }

    //if (subtree->left != nullptr && subtree->right != nullptr) {

    //    balance = height(subtree->right) - height(subtree->left);
    //    int leftB = updateHeight(subtree->left->right,0) - updateHeight(subtree->left->left,0);
    //    int rightB = updateHeight(subtree->right->right,0) - updateHeight(subtree->right->left,0);
    //    if (balance == -2) {
    //        // *_out << subtree->key << " " << "parent to " << subtree->left->key << " and " << subtree->right->key << endl;
    //        if (leftB == -1) {
    //            rotateRight(subtree);
    //        }
    //        else {
    //            rotateLeftRight(subtree);
    //        }
    //    }
    //    else if (balance == 2) {
    //        // *_out << subtree->key << " " << "parent to " << subtree->left->key << " and " << subtree->right->key << endl;
    //        if (rightB == 1) {
    //            rotateLeft(subtree);
    //        }
    //        else {
    //            rotateRightLeft(subtree);
    //        }
    //    }
    //}
    //else if (subtree->left != nullptr) {
    //    balance = subtree->height;
    //    if (balance >1) {
    //        // *_out << subtree->key << " " << "parent to " << subtree->left->key << endl;
    //        if (subtree->left->right) {
    //            rotateLeftRight(subtree);
    //        }
    //        else {
    //            rotateRight(subtree);
    //        }
    //    }

    //}
    //else if (subtree->right != nullptr) {
    //    balance = subtree->height;
    //    if (balance > 1) {
    //        // *_out << subtree->key << " " << "parent to " << subtree->right->key << endl;
    //        if (subtree->right->left)
    //        {
    //            rotateRightLeft(subtree);
    //        }
    //        else {
    //            rotateLeft(subtree);
    //        }
    //    }
    //}
    //updateHeight(subtree);


    // LL
    balance = height(subtree->right) - height(subtree->left);

    //*_out << subtree -> key << " right height " << height(subtree->right)<< " left height " << height(subtree->left) << " balance = " << balance << endl;
    if (balance == 2) {
        //*_out << subtree->key << endl;
        int Rbalance = height(subtree->right->right) - height(subtree->right->left);
        if (Rbalance > 0) {
            rotateLeft(subtree);
        }
        else {
            rotateRightLeft(subtree);
        }
    } 
    else if (balance == -2) {
        //*_out << subtree->key  << endl;
        int Lbalance = height(subtree->left->right) - height(subtree->left->left);
        if (Lbalance > 0) {
            rotateLeftRight(subtree);
        }
        else {
            rotateRight(subtree);
        }
    }
    else {
        updateHeight(subtree);

    }
    

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{

    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        /* Reached the node that we need to delete */
        if (subtree->left == NULL && subtree->right == NULL) {
            /* Case 1: Node to remove has no children */
            delete subtree;
            subtree = NULL;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /**
             * Case 2: Node to remove has two children
             * TODO: your code here. For testing purposes, you
             * should use the PREDECESSOR.
             */
            Node*& predecessor = maxN(subtree->left);
            predecessor->right = subtree->right;
            Node* temp = subtree;

            if (predecessor->left == nullptr) {
                predecessor->left = subtree->left;
                subtree = predecessor;
            }
            else
            {
                subtree = predecessor;
                Node* left = predecessor->left;
                predecessor = predecessor->left;

            }
            predecessor = nullptr;
            delete temp;
            rebalance(subtree);
            return;

        } else {
            /* Case 3: Node to remove has one child */
            Node* curr = subtree;
            subtree = max(subtree->left, subtree->right);
            delete curr;
        }
        rebalance(subtree);
    }
}


template <class K, class V>
typename AVLTree<K, V>::Node*& AVLTree<K, V>::AVLTree<K, V>::maxN(Node*& node) {
    if (!node) {
        return node;
    }
    if (node->right) {
        return maxN(node->right);
    }
    return node;
}
