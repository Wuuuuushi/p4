#ifndef __PROJ_FOUR_CRUMPLE_TREE_HPP
#define __PROJ_FOUR_CRUMPLE_TREE_HPP

#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>

namespace shindler::ics46::project4 {

class ElementNotFoundException : public std::runtime_error {
   public:
    explicit ElementNotFoundException(const std::string &err)
        : std::runtime_error(err) {}
};

template <typename K, typename V>
class CrumpleTree {
   private:

    size_t TreeSize{}; //Store the size of the tree


    struct Node
    {
        Node(K key, V value)
        : key{key}, value{value}, right{nullptr}, left{nullptr}, level{}
        {}
        K key;
        V value;
        Node * right{nullptr};
        Node * left{nullptr};
        unsigned level{};
            
    };

    Node * root{};

    Node * findNode(const K &key);
    Node * findNode(const K &key) const;

    Node * findPreviousNode(const K &key);

    void checkNode(Node * node);

    void deleteTree(Node * root);

    std::vector<K> recInOrder(Node* node, std::vector<K> vec) const;
    std::vector<K> recPreOrder(Node* node, std::vector<K> vec) const;
    std::vector<K> recPostOrder(Node* node, std::vector<K> vec) const;

    bool case5left(Node * node);
    bool case5right(Node * node);

    Node * findleftSwapNode(Node * node);
    Node * findrightSwapNode(Node * node);


   public:
    CrumpleTree();

    // In general, a copy constructor and assignment operator
    // are good things to have.
    // For this quarter, I am not requiring these.
    //	CrumpleTree(const CrumpleTree & st);
    //	CrumpleTree & operator=(const CrumpleTree & st);
    // You do not need to implement these
    CrumpleTree(const CrumpleTree &) = delete;
    CrumpleTree(CrumpleTree &&) = delete;
    CrumpleTree &operator=(const CrumpleTree &) = delete;
    CrumpleTree &operator=(CrumpleTree &&) = delete;

    // The destructor is required.
    ~CrumpleTree();

    // size() returns the number of distinct keys in the tree.
    [[nodiscard]] size_t size() const noexcept;

    // isEmpty() returns true if and only if the tree has no values in it.
    [[nodiscard]] bool empty() const noexcept;

    // contains() returns true if and only if there
    //  is a (key, value) pair in the tree
    //	that has the given key as its key.
    bool contains(const K &key) const noexcept;

    // returns the level on which the node with this key resides.
    // If !contains(k), this will throw an ElementNotFoundException
    unsigned level(const K &key) const;

    // find returns the value associated with the given key
    // If !contains(k), this will throw an ElementNotFoundException
    // There needs to be a version for const and non-const CrumpleTrees.
    V &find(const K &key);
    const V &find(const K &key) const;

    bool validLevel(Node * node); //Finds out if the level is valid for moving up.
    bool sameLevelRight(Node * node); //Finds out if the nodes are on the same level on the right side.
    bool sameLevelLeft(Node * node); //Finds out if the nodes are on the same level on the left side.

    // Inserts the given key-value pair into
    // the tree and performs the balancing operation(s)
    // if needed as described in lecture.
    // If the key already exists in the tree,
    // you may do as you please (no test cases in
    // the grading script will deal with this situation)
    void insert(const K &key, const V &value);

    // Deletes the given key from the tree
    // and performs the balancing operation(s) if needed.
    // If the key does not exist in the tree,
    // do not modify the tree.
    void remove(const K &key);

    // The following three functions all return
    // the set of keys in the tree as a standard vector.
    // Each returns them in a different order.
    [[nodiscard]] std::vector<K> inOrder() const;
    [[nodiscard]] std::vector<K> preOrder() const;
    [[nodiscard]] std::vector<K> postOrder() const;
};

template <typename K, typename V>
CrumpleTree<K, V>::CrumpleTree() {
    TreeSize = 0;
}

template <typename K, typename V>
CrumpleTree<K, V>::~CrumpleTree() {
    deleteTree(root);
}

template <typename K, typename V>
typename CrumpleTree<K, V>::Node* CrumpleTree<K, V>::findNode(const K& key){
    
    Node * tmp{root};
    while(tmp != nullptr) //This statement continues to check downward until it reaches the end or the key. If key return the value. If no key is found throw error.
    {
        if (tmp -> key == key)
        {
            return tmp;
        }
        if (tmp -> key < key)
        {
            tmp = tmp -> right;
        }
        else
        {
            tmp = tmp -> left;
        }
    }
    throw ElementNotFoundException("Key Not Found");
}

template <typename K, typename V>
typename CrumpleTree<K, V>::Node* CrumpleTree<K, V>::findNode(const K& key) const{
    
    Node * tmp{root};
    while(tmp != nullptr) //This statement continues to check downward until it reaches the end or the key. If key return the value. If no key is found throw error.
    {
        if (tmp -> key == key)
        {
            return tmp;
        }
        if (tmp -> key < key)
        {
            tmp = tmp -> right;
        }
        else
        {
            tmp = tmp -> left;
        }
    }
    throw ElementNotFoundException("Key Not Found");
}

template <typename K, typename V>
size_t CrumpleTree<K, V>::size() const noexcept {
    // TODO: Implement this
    return TreeSize;
}

template <typename K, typename V>
bool CrumpleTree<K, V>::empty() const noexcept {
    // TODO: Implement this
    return (TreeSize == 0);
}

template <typename K, typename V>
bool CrumpleTree<K, V>::contains(const K &key) const noexcept {
    try
    {
        findNode(key);
        return true;
    }
    catch (ElementNotFoundException)
    {
        return false;
    }
}

template <typename K, typename V>
unsigned CrumpleTree<K, V>::level(const K &key) const {
    return findNode(key) -> level;
}

template <typename K, typename V>
V &CrumpleTree<K, V>::find(const K &key) {
    
    return findNode(key) -> value;
}

template <typename K, typename V>
const V &CrumpleTree<K, V>::find(const K &key) const {
    return findNode(key) -> value;

}

template <typename K, typename V>
typename CrumpleTree<K, V>::Node* CrumpleTree<K, V>::findPreviousNode(const K& key){
    Node * tmp{root};
    while (tmp != nullptr)
    {
        if (tmp -> key < key)
        {
            if (tmp -> right -> key == key)
            {
                return tmp;
            }
            tmp = tmp -> right;
        }
        else
        {
            if (tmp -> left -> key == key)
            {
                return tmp;
            }
            tmp = tmp -> left;
        }
    }
    return tmp;
}

template <typename K, typename V>
bool CrumpleTree<K, V>::validLevel(Node * node)
{
    if (node -> right == nullptr)
    {
        if (2 < node -> level + 1)
        {
            return false;
        }
    }
    else if (node -> left == nullptr)
    {
        if (2 < node -> level + 1)
        {
            return false;
        }
    }
    else
    {
        if ((node -> level - node -> right -> level + 1 > 2) or (node -> level - node -> left -> level + 1 > 2))
        {
            return false;
        }
    }
    return true;
}

template <typename K, typename V>
bool CrumpleTree<K,V>::sameLevelRight(Node * node)
{
    if (node -> right == nullptr)
    {
    }
    else
    {
        if (node -> level == node -> right -> level)
        {
            return true;
        }
    }
    return false;
}

template <typename K, typename V>
bool CrumpleTree<K,V>::sameLevelLeft(Node * node)
{
    if (node -> left == nullptr)
    {
    }
    else
    {
        if (node -> level == node -> left -> level)
        {
            return true;
        }
    }
    return false;
}

template <typename K, typename V>
bool CrumpleTree<K,V>::case5left(Node * node)
{
    if ( node -> left -> right == nullptr)
    {
        return false;
    }
    if (node -> left -> left == nullptr)
    {
        if ((node -> left -> level - node -> left -> right -> level == 1) and (node -> left -> level - 0 == 2))
        {
            return true;
        }
    }
    if ((node -> left -> level - node -> left -> right -> level == 1 ) and (node -> left -> level - node -> left -> left -> level == 2))
    {
        return true;
    }
    return false;
}

template <typename K, typename V>
bool CrumpleTree<K,V>::case5right(Node * node)
{
    if (node -> right -> left == nullptr)
    {
        return false;
    }
    if ( node -> right -> right == nullptr)
    {
        if((node -> right -> level - node -> right -> left -> level == 1) and (node -> right -> level - 0 ==2))
        {
            return true;
        }
    }
    if ( (node -> right -> level - node -> right -> left -> level == 1) and (node -> right -> level - node -> right -> right -> level == 2))
    {
        return true;
    }
    return false;
}

template <typename K, typename V>
void CrumpleTree<K,V>::deleteTree(Node * root) {
        if (root == nullptr)
            return;

        deleteTree(root->left);
        deleteTree(root->right);

        delete root;
}

template <typename K, typename V>
void CrumpleTree<K, V>::checkNode(Node * node)
{
    if(node -> left == nullptr and node -> right == nullptr)
    {
        if (node -> level > 1)
        {
            node -> level--;
        }
    }
    if (sameLevelLeft(node)) //Child node is on the left side of the parent node
    {
        if (validLevel(node)) //Case 2 Right side where edges collide/ are on the same level and do not go over the level limit when added with 1
        {
            node -> level++;
            if (node != root)
            {
                checkNode(findPreviousNode(node -> key));
            }
        }
        else // Case 3,4,5 Right side where edges are too far up so that it cannot be added with 1
        {
            if (node == root)
            {
                if (case5left(node)) //Case 5 left side
                {
                    
                    root = node -> left -> right; //Set the root equal to the node right of the child of the node
                    root -> level += 1; //Move it up by 2
                    node -> left -> right = root -> left;
                    root -> left = node -> left;
                    node -> left = root -> right;
                    root -> right = node;
                    root -> left -> level--;
                    root -> right -> level--;
                }
                else //Case 4
                {
                    
                    root = node -> left;
                    node -> level--;
                    node -> left = root -> right;
                    root -> right = node;
                    checkNode(node);
                }
            }
            else //Case 3
            {

                Node * tmp{findPreviousNode(node -> key)}; //Store parent node of this node
                if (tmp -> left == node) //If node is on the left
                {
                    if  (case5left(node))
                    {

                        tmp -> left = node -> left -> right;
                        tmp -> left -> level++;
                        node -> left -> right = tmp -> left -> left;
                        tmp -> left -> left = node -> left;
                        node -> left = tmp -> left -> right;
                        tmp -> left -> right = node;
                        tmp -> left -> right -> level--;
                        tmp -> left -> left -> level--;

                        
                    }
                    else
                    {
                    tmp -> left = node -> left; //Set parent of parent node to child of parent node
                    node -> left = tmp -> left -> right;
                    tmp -> left -> right = node; //Set the node function equal to the old parent
                    tmp -> left -> right -> level--;
                    }
                }
                else
                {
                    if  (case5left(node))
                    {
                        tmp -> right = node -> left -> right;
                        tmp -> right -> level++;
                        node -> left -> right = tmp -> right -> left;
                        tmp -> right -> left = node -> left;
                        node -> left = tmp -> right -> right;
                        tmp -> right -> right = node;
                        tmp -> right -> right -> level--;
                        tmp -> right -> left -> level--;
                        
                    }
                    else
                    {
                    tmp -> right = node -> left;
    
                    node -> left = tmp -> right -> right;
                    
                    tmp -> right -> right = node;
                    tmp -> right -> right -> level--;
                    }
                }

                checkNode(node);
            }
        }
        
    }
    else if (sameLevelRight(node)) //Child node is on the right side of the parent node
    {
        if (validLevel(node)) //Case 2 Right side where edges collide/ are on the same level and do not go over the level limit when added with 1
        {
            node -> level++;
            if (node != root)
            {
                checkNode(findPreviousNode(node -> key));
            }
        }
        else // Case 3,4,5 Right side where edges are too far up so that it cannot be added with 1
        {
            if (node == root)
            {
                if (case5right(node)) //Case 5 right side
                {

                    root = node -> right -> left;
                    root -> level += 1;
                    node -> right -> left = root -> right;
                    root -> right = node -> right;
                    node -> right = root -> left;
                    root -> left = node;
                    root -> left -> level --;
                    root -> right -> level--;
                }
                else //Case 4
                {
                    root = node -> right;
                    node -> level--;
                    node -> right = root -> left;
                    root -> left = node;
                    checkNode(node);
                }
            }
            else //Case 3
            {
                Node * tmp{findPreviousNode(node -> key)}; //Store parent node of this node
                if (tmp -> left == node) //If node is on the left
                {
                    if (case5right(node))
                    {
                        tmp -> left = node -> right -> left;
                        tmp -> left -> level++;
                        node -> right -> left = tmp -> left -> right;
                        tmp -> left -> right = node -> right;
                        node -> right = tmp -> left -> left;
                        tmp -> left  -> left = node;
                        tmp -> left -> left -> level--;
                        tmp -> left -> right -> level--;
                    }
                    else
                    {
                    tmp -> left = node -> left; //Set parent of parent node to child of parent node
                    node -> left = tmp -> left -> right;
                    tmp -> left -> right = node; //Set the node function equal to the old parent
                    tmp -> left -> right -> level--;
                    }
                }
                else
                {
                    if (case5right(node))
                    {
                        tmp -> right = node -> right -> left;
                        tmp -> right -> level++;
                        node -> right -> left = tmp -> right -> right;
                        tmp -> right -> right = node -> right;
                        node -> right = tmp -> right -> left;
                        tmp -> right  -> left = node;
                        tmp -> right -> left -> level--;
                        tmp -> right -> right -> level--;
                    }
                    else
                    {
                    tmp -> right = node -> right;
                    node -> right = tmp -> right -> left;
                    tmp -> right -> left = node;
                    tmp -> right -> left -> level--;
                    }
                }
                checkNode(node);
            }
        }
    }
}

template <typename K, typename V>
void CrumpleTree<K, V>::insert(const K &key, const V &value) {
    if (TreeSize == 0) //The first insert will set a root node
    {
        root = new Node(key, value);
        root -> level = 1;
        TreeSize++;
    }
    else
    {
        Node * tmp{root};
        while(tmp != nullptr) //Finds node to place at
        {
            if (tmp -> key < key)
            {
                if (tmp -> right == nullptr)
                {
                    
                    Node * newNode = new Node(key,value); //Make a new leaf node that will be on the right of the temporary node who represents the node that is its parent
                    newNode -> level = 1; //New leaf node so level will be 1
                    tmp -> right = newNode; //Set the right of the parent to be this leaf node.
                    //This will be the recursive call to check if parent is valid after creation of this node
                    checkNode(tmp);
                    TreeSize++;
                    break;
                }
                tmp = tmp -> right;
            }
            else
            {
                if (tmp -> left == nullptr)
                {

                    Node * newNode = new Node(key,value); //Make a new leaf node that will be on the right of the temporary node who represents the node that is its parent
                    newNode -> level = 1; //New leaf node so level will be 1
                    tmp -> left = newNode; //Set the right of the parent to be this leaf node.
                     //This will be the recursive call to check if parent is valid after creation of this node
                    checkNode(tmp);
                    TreeSize++;
                    break;
                }
                tmp = tmp -> left;
            }
        }
    }
}

template <typename K, typename V>
typename CrumpleTree<K, V>::Node* CrumpleTree<K, V>::findrightSwapNode(Node* node){
    if(node -> left == nullptr and node -> right ==nullptr)
    {
        return node;
    }
    if(node -> left != nullptr)
    {
        return findrightSwapNode(node -> left);
    }
    else
    {
        return findrightSwapNode(node -> right);
    }
}

template <typename K, typename V>
typename CrumpleTree<K, V>::Node* CrumpleTree<K, V>::findleftSwapNode(Node* node){
    if(node -> left == nullptr and node -> right ==nullptr)
    {
        return node;
    }
    if(node -> right != nullptr)
    {
        return findleftSwapNode(node -> right);
    }
    else
    {
        return findleftSwapNode(node -> left);
    }
}

template <typename K, typename V>
void CrumpleTree<K, V>::remove(const K &key) {
    Node * deleteNode{findNode(key)};
    if(deleteNode != root)
    {
        Node * previousNode{findPreviousNode(key)};
        if( deleteNode -> right == nullptr and deleteNode -> left == nullptr) //When the node is a leaf node
        {
            if (previousNode -> left == deleteNode)
            {
                previousNode -> left = nullptr;
            }
            else if (previousNode -> right == deleteNode)
            {
                previousNode -> right = nullptr;
            }
            delete deleteNode;
            TreeSize--;
            if(!validLevel(previousNode))
            {
                previousNode -> level--;
                checkNode(previousNode);
            }

        }
        else if (deleteNode -> right != nullptr)
        {

            Node * swapNode{findrightSwapNode(deleteNode -> right)};
            Node * tmp{findPreviousNode(swapNode -> key)};
            deleteNode -> key = swapNode -> key;
            deleteNode -> value = swapNode -> value;
            if( tmp -> right == swapNode)
            {
                tmp -> right = nullptr;
            }
            else
            {
                tmp -> left = nullptr;
            }
            TreeSize--;
            delete swapNode;
            if (!validLevel(tmp))
            {
                tmp -> level--;
            }
            checkNode(tmp);
            
        }
        else if (deleteNode -> left != nullptr)
        {
            Node * swapNode{findleftSwapNode(deleteNode -> left)};
            Node * tmp{findPreviousNode(swapNode -> key)};
            deleteNode -> key = swapNode -> key;
            deleteNode -> value = swapNode -> value;
            if (tmp -> right == swapNode)
            {
                tmp -> right = nullptr;
            }
            else
            {
                tmp -> left = nullptr;
            }
            TreeSize--;
            delete swapNode;
            if (!validLevel(tmp))
            {
                tmp -> level--;
            }
            checkNode(tmp); 

        }
        
    }
    else
    {
        if( deleteNode -> right == nullptr and deleteNode -> left == nullptr) //When the node is a leaf node
        {
            delete deleteNode;
            TreeSize = 0;
        }
        else if (deleteNode -> right != nullptr)
        {
            Node * swapNode{findrightSwapNode(deleteNode -> right)};
            Node * tmp{findPreviousNode(swapNode -> key)};
            deleteNode -> key = swapNode -> key;
            deleteNode -> value = swapNode -> value;
            if( tmp -> right == swapNode)
            {
                tmp -> right = nullptr;
            }
            else
            {
                tmp -> left = nullptr;
            }
            delete swapNode;
            TreeSize--;
            if (!validLevel(tmp))
            {
                tmp -> level--;
            }
            checkNode(tmp);
            
        }
        else if (deleteNode -> left != nullptr)
        {
            Node * swapNode{findleftSwapNode(deleteNode -> left)};
            Node * tmp{findPreviousNode(swapNode -> key)};
            deleteNode -> key = swapNode -> key;
            deleteNode -> value = swapNode -> value;
            if (tmp -> right == swapNode)
            {
                tmp -> right = nullptr;
            }
            else
            {
                tmp -> left = nullptr;
            }
            TreeSize--;
            delete swapNode;
            if (!validLevel(tmp))
            {
                tmp -> level--;
            }
            checkNode(tmp); 

        }
    }

}

template <typename K, typename V>
std::vector<K> CrumpleTree<K,V>::recInOrder(Node * node, std::vector<K> vec) const{
    if (node == nullptr)
    {
        return vec;
    }
    vec = recInOrder(node -> left, vec);
    vec.push_back(node -> key);
    vec = recInOrder(node -> right, vec);
    return vec;
}

template <typename K, typename V>
std::vector<K> CrumpleTree<K,V>::recPreOrder(Node * node, std::vector<K> vec) const{
    if (node == nullptr)
    {
        return vec;
    }
    vec.push_back(node -> key);
    vec = recPreOrder(node -> left, vec);
    vec = recPreOrder(node -> right, vec);
    return vec;
}

template <typename K, typename V>
std::vector<K> CrumpleTree<K,V>::recPostOrder(Node * node, std::vector<K> vec) const{
    if (node == nullptr)
    {
        return vec;
    }
    
    vec = recPostOrder(node -> left, vec);
    vec = recPostOrder(node -> right, vec);
    vec.push_back(node -> key);
    return vec;
}

template <typename K, typename V>
std::vector<K> CrumpleTree<K, V>::inOrder() const {
    std::vector<K> returnVec{};
    return recInOrder(root, returnVec);
}

template <typename K, typename V>
std::vector<K> CrumpleTree<K, V>::preOrder() const {
    std::vector<K> returnVec{};
    return recPreOrder(root, returnVec);
}

template <typename K, typename V>
std::vector<K> CrumpleTree<K, V>::postOrder() const {
    std::vector<K> returnVec{};
    return recPostOrder(root, returnVec);
}

}  // namespace shindler::ics46::project4

#endif
