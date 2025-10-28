#include "../headers/bst.h"
#include <iostream>
#include <algorithm>
using namespace std;

template <typename K, typename V>
BST<K, V>::BST() : root(nullptr), nodeCount(0)
{
    comparator = [](const K &a, const K &b)
    { return a < b; };
}

template <typename K, typename V>
BST<K, V>::BST(function<bool(const K &, const K &)> comp)
    : root(nullptr), nodeCount(0), comparator(comp)
{
}

template <typename K, typename V>
bool BST<K, V>::insert(const K &key, const V &value)
{
    this->root = this->insertHelper(this->root, key, value);
    /* this additional part is to confirm whether the node is added or not. */
    shared_ptr<BSTNode> temp = nullptr;
    temp = this->findHelper(this->root, key);
    if(temp)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename K, typename V>
shared_ptr<typename BST<K, V>::BSTNode> BST<K, V>::insertHelper(shared_ptr<BSTNode> node, const K &key, const V &value)
{
    if (node == nullptr)
    {
        return make_shared<BSTNode>(key, value);
    }
    else if (node->key == key)
    {
        return node;
    }
    else if (comparator(key, node->key))
    {
        node->left = insertHelper(node->left, key, value);
        if(node->left)
        {
            node->left->parent = node;
        }
        this->updateHeight(node);
        return node;
    }
    else
    {
        node->right = insertHelper(node->right, key, value);
        if(node->right)
        {
            node->right->parent = node;
        }
        this->updateHeight(node);
        return node;
    }
}

template <typename K, typename V>
bool BST<K, V>::remove(const K &key)
{
    this->root = this->removeHelper(this->root, key);
    /* this additional part is to confirm whether the node is removed or not. */
    shared_ptr<BSTNode> temp = nullptr;
    temp = this->findHelper(this->root, key);
    if(temp)
    {
        return false;
    }
    else
    {
        return true;
    }
}

template <typename K, typename V>
shared_ptr<typename BST<K, V>::BSTNode> BST<K, V>::removeHelper(shared_ptr<BSTNode> node, const K &key)
{
    if (node == nullptr)
    {
        return node;
    }
    else if(node->key == key)
    {
        if (!temp->left && !temp->right)
        {
            temp.reset();
            return nullptr;
        }
        else if (node->left)
        {
            shared_ptr<BSTNode> temp = node->left;
            node.reset();
            return temp;
        }
        else if (node->right)
        {
            shared_ptr<BSTNode> temp = node->right;
            node.reset();
            return temp;
        }
        else
        {
            shared_ptr<BSTNode> succ = this->findMinHelper(node->right); // searching for the smallest immediate successor
            node->key = succ->key;
            node->value = succ->value;
            this->removeHelper(node->right, succ->key);
            return node;
        }
    }
    else if (comparator(key, temp->key))
    {
        node->left = removeHelper(node->left, key);
        if(node->left)
        {
            node->left->parent = node;
        }
        this->updateHeight(node);
        return node;
    }
    else
    {
        node->right = removeHelper(node->right, key);
        if(node->right)
        {
            node->right->parent = node;
        }
        this->updateHeight(node);
        return node;
    }
}
template <typename K, typename V>
V *BST<K, V>::find(const K &key)
{
    shared_ptr<BST> temp = this->findHelper(this->root, key);
    if(temp)
    {
        return temp->value;
    }
    else
    {
        return nullptr;
    }
}

template <typename K, typename V>
const V *BST<K, V>::find(const K &key) const
{
    shared_ptr<BST> temp = this->findHelper(this->root, key);
    if(temp)
    {
        return const_cast<const V*>(temp->value);
    }
    else
    {
        return nullptr;
    }
}

template <typename K, typename V>
shared_ptr<typename BST<K, V>::BSTNode> BST<K, V>::findHelper(shared_ptr<BSTNode> node, const K &key) const
{
    if(node == nullptr || node->key == key)
    {
        return node;
    }
    else if(this->comparator(key, node->key))
    {
        return this->findHelper(node->left);
    }
    else
    {
        return this->findHelper(node->right);
    }
}

template <typename K, typename V>
pair<K, V> BST<K, V>::min() const
{
    shared_ptr<BSTNode> temp = nullptr;
    temp = this->findMinHelper(this->root);
    if(temp)
    {
        std::pair(K, V) p(temp->key, temp->value);
        return p;
    }
    else
    {
        std::pair(K, V) p;
        return p;
    }
}

template <typename K, typename V>
shared_ptr<typename BST<K, V>::BSTNode> BST<K, V>::findMinHelper(shared_ptr<BSTNode> node) const
{
    if(node == nullptr || node->left == nullptr)
    {
        return node;
    }
    else
    {
        return findMinHelper(node->left);
    }
}

template <typename K, typename V>
pair<K, V> BST<K, V>::max() const
{
    shared_ptr<BSTNode> temp = nullptr;
    temp = this->findMaxHelper(this->root);
    if(temp)
    {
        std::pair(K, V) p(temp->key, temp->value);
        return p;
    }
    else
    {
        std::pair(K, V) p;
        return p;
    }
}

template <typename K, typename V>
shared_ptr<typename BST<K, V>::BSTNode> BST<K, V>::findMaxHelper(shared_ptr<BSTNode> node) const
{
    if(node == nullptr || node->right == nullptr)
    {
        return node;
    }
    else
    {
        return findMaxHelper(node->right);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
template <typename K, typename V>
vector<pair<K, V>> BST<K, V>::findRange(const K &minKey, const K &maxKey) const
{
}

template <typename K, typename V>
void BST<K, V>::rangeHelper(shared_ptr<BSTNode> node, const K &minKey, const K &maxKey, vector<pair<K, V>> &result) const
{
}

template <typename K, typename V>
vector<pair<K, V>> BST<K, V>::inOrderTraversal() const
{
}

template <typename K, typename V>
void BST<K, V>::inOrderHelper(shared_ptr<BSTNode> node, vector<pair<K, V>> &result) const
{
    if(node == nullptr)
    {
        return;
    }
    inOrderHelper(node->left, result);
    std::pair<K, V> p(node->key, node->value);
    result.push_back(node->)
}

template <typename K, typename V>
void BST<K, V>::displayTree() const
{
}

template <typename K, typename V>
void BST<K, V>::displayHelper(shared_ptr<BSTNode> node, int depth) const
{
}

template <typename K, typename V>
bool BST<K, V>::isValidBST() const
{
}

template <typename K, typename V>
bool BST<K, V>::isValidBSTHelper(shared_ptr<BSTNode> node, const K *minVal, const K *maxVal) const
{
}

template <typename K, typename V>
void BST<K, V>::updateHeight(shared_ptr<BSTNode> node)
{
}

template <typename K, typename V>
int BST<K, V>::getHeight(shared_ptr<BSTNode> node) const
{
}

template class BST<int, string>;
template class BST<string, string>;
template class BST<int, int>;
template class BST<string, void *>;