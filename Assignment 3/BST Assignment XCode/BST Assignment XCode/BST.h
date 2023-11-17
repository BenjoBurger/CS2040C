#pragma once
#include <iostream>
using namespace std;

template <class T>
class BinarySearchTree;

template <class T>
class TreeNode {
private:
    T _item;
    TreeNode<T>* _left;
    TreeNode<T>* _right;
    int _height;
public:
    TreeNode(T x) { _left = _right = NULL; _item = x; _height = 0; };

    friend BinarySearchTree<T>;
};

template <class T>
class BinarySearchTree {
protected:
    int _size;
    TreeNode<T>* _root;
    void _printTree(int indent, TreeNode<T>*, bool withHeight);

    // The following functions are optional for you to implement.
    TreeNode<T>* _insert(TreeNode<T>* current, T x);
    void _inOrderPrint(TreeNode<T>*);
    void _postOrderPrint(TreeNode<T>*);
    void _preOrderPrint(TreeNode<T>*);
    TreeNode<T>* _rightRotation(TreeNode<T>*);
    TreeNode<T>* _leftRotation(TreeNode<T>*);
    TreeNode<T>* _searchMax(TreeNode<T>*);
    TreeNode<T>* _searchMin(TreeNode<T>*);
    TreeNode<T>* _search(TreeNode<T>*, T);
    void _destroySubTree(TreeNode<T>*);
    int _calHeight(TreeNode<T>*);
    TreeNode<T>* _successor(TreeNode<T>*, T);
    TreeNode<T>* _checkBalanced(TreeNode<T>* node);
    int _difference(TreeNode<T>* node);

public:
    BinarySearchTree() { _root = NULL; _size = 0; }
    ~BinarySearchTree();
    int size() { return _size; };
    void insert(T);
    void printTree(bool withHeight = 1);
    void inOrderPrint();
    void postOrderPrint();
    void preOrderPrint();
    T searchMax();
    T searchMin();
    bool exist(T x);
    T search(T x);
    T successor(T);
    void calHeight(TreeNode<T>*);
    void checkBalanced(TreeNode<T>*);
};

template <class T>
void BinarySearchTree<T>::insert(T x)
{
    _root = _root ? _insert(_root, x) : new TreeNode<T>(x);
    if (_size == 0) _size++;
}

template <class T>
void BinarySearchTree<T>::_printTree(int indent, TreeNode<T>* node, bool withHeight) {

    if (!node)
        return;
    if (node->_right)
        _printTree(indent + 2, node->_right, withHeight);
    for (int i = 0; i < indent; i++)
        cout << "  ";
    cout << node->_item;
    if (withHeight)
        cout << "(h=" << node->_height << ")";
    cout << endl;
    if (node->_left)
        _printTree(indent + 2, node->_left, withHeight);


};

template <class T>
void BinarySearchTree<T>::printTree(bool withHeight) {
    _printTree(0, _root, withHeight);
}


template <class T>
void BinarySearchTree<T>::preOrderPrint() {
    _preOrderPrint(_root);
    cout << endl;
}


template <class T>
void BinarySearchTree<T>::_preOrderPrint(TreeNode<T>* node) {
    if (!node) return;
    cout << node->_item << " ";
    _preOrderPrint(node->_left);
    _preOrderPrint(node->_right);
}


template <class T>
void BinarySearchTree<T> ::_destroySubTree(TreeNode<T>* node)
{
    if (node->_left)
        _destroySubTree(node->_left);
    if (node->_right)
        _destroySubTree(node->_right);
    delete node;
}

template <class T>
BinarySearchTree<T> :: ~BinarySearchTree()
{
    if (_root)
        _destroySubTree(_root);
}



template <class T>
void BinarySearchTree<T>::inOrderPrint() {
    _inOrderPrint(_root);
    cout << endl;
}


template <class T>
void BinarySearchTree<T>::_inOrderPrint(TreeNode<T>* node) {
    if (!node) return;
    _inOrderPrint(node->_left);
    cout << node->_item << " ";
    _inOrderPrint(node->_right);
    return;
}

template <class T>
void BinarySearchTree<T>::postOrderPrint() {
    _postOrderPrint(_root);
    cout << endl;
}

template <class T>
void BinarySearchTree<T>::_postOrderPrint(TreeNode<T>* node) {
    if (!node) return;
    _postOrderPrint(node->_left);
    _postOrderPrint(node->_right);
    cout << node->_item << " ";
    return;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_insert(TreeNode<T>* current, T x) {
    if (current->_item > x)
    {
        if (current->_left) {
            current->_left = _insert(current->_left, x);
            calHeight(current);
            current = _checkBalanced(current);
            calHeight(current);
        }
        else
        {
            current->_left = new TreeNode<T>(x);
            _size++;
            calHeight(current);
        }
    }
    else if (x > current->_item) {
        if (current->_right) {
            current->_right = _insert(current->_right, x);
            calHeight(current);
            current = _checkBalanced(current);
            calHeight(current);
        }
        else
        {
            current->_right = new TreeNode<T>(x);
            _size++;
            calHeight(current);
        }
    }

    else
        return current; // When the node already existed in the tree

    calHeight(current);

    return _checkBalanced(current);

}

template <class T>
T BinarySearchTree<T>::searchMax() {
    TreeNode<T>* maxNode = _searchMax(_root);
    return maxNode->_item;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_searchMax(TreeNode<T>* current) {
    while (current->_right != NULL) {
        current = current->_right;
    }
    return current;
}

template <class T>
T BinarySearchTree<T>::searchMin() {
    TreeNode<T>* minNode = _searchMin(_root);
    return minNode->_item;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_searchMin(TreeNode<T>* current) {
    while (current->_left != NULL) {
        current = current->_left;
    }
    return current;
}

template <class T>
bool BinarySearchTree<T>::exist(T x) {
    TreeNode<T>* node = _search(_root, x);
    return node;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_search(TreeNode<T>* current, T x) {
    if (current == NULL) {
        return NULL;
    }
    //cout << current->_item << endl;
    if (current->_item == x) {
        //cout << "corr: " << current->_item << endl;
        return current;
    }
    else if (current->_item < x) {
        //cout << "right: " << current->_item << endl;
        return _search(current->_right, x);
    }
    //cout << "left: " << current->_item << endl;
    return _search(current->_left, x);
}


template <class T>
T BinarySearchTree<T>::successor(T x)
{
    if (searchMax() <= x) {
        return INT32_MIN;
    }
    TreeNode<T>* successorNode = _successor(_root, x);
    return successorNode->_item;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_successor(TreeNode<T>* current, T x) {
    if (current == NULL) {
        return NULL;
    }
    TreeNode<T>* succNode = current;
    if (x < current->_item) {
        succNode = _successor(current->_left, x);
        if (succNode && succNode->_item > x) {
            return succNode;
        }
    }
    if (x >= current->_item) {
        succNode = _successor(current->_right, x);
        if (succNode && succNode->_item > x) {
            return succNode;
        }
    }
    return current;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_leftRotation(TreeNode<T>* node)
{
    TreeNode<T>* ptr = node->_right;
    node->_right = ptr->_left;
    ptr->_left = node;
    calHeight(ptr);
    return ptr;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_rightRotation(TreeNode<T>* node)
{
    TreeNode<T>* ptr = node->_left;
    node->_left = ptr->_right;
    ptr->_right = node;
    calHeight(ptr);
    return ptr;
}

template <class T>
void BinarySearchTree<T>::calHeight(TreeNode<T>* node)
{
    if (node == NULL) {
        return;
    }
    if (node->_left) {
        calHeight(node->_left);
    }
    if (node->_right) {
        calHeight(node->_right);
    }
    node->_height = _calHeight(node);
}

template <class T>
int BinarySearchTree<T>::_calHeight(TreeNode<T>* node)
{
    int leftHeight = -1;
    int rightHeight = -1;
    if (node->_left) {
        leftHeight = node->_left->_height;
    }
    if (node->_right) {
        rightHeight = node->_right->_height;
    }
    return max(leftHeight, rightHeight) + 1;
}

template <class T>
TreeNode<T>* BinarySearchTree<T>::_checkBalanced(TreeNode<T>* node) {
    //cout << node->_item << endl;
    int diff = _difference(node);
    //cout << "node: " << node->_item << endl;
    //cout << "Diff: " << diff << endl;
    if (diff > 1) { // left heavy
        //cout << "Left" << endl;
        if (_difference(node->_left) < 0) { // right heavy
            node->_left = _leftRotation(node->_left);
        }
        node = _rightRotation(node);
    }
    if (diff < -1) {
        //cout << "right: " << endl;
        if (_difference(node->_right) > 0) { // left heavy
            node->_right = _rightRotation(node->_right);
        }
        node = _leftRotation(node);
    }
    return node;
}

template <class T>
int BinarySearchTree<T>::_difference(TreeNode<T>* node) {
    int leftHeight = -1;
    int rightHeight = -1;
    if (!node) {
        return -1;
    }
    if (node->_left) {
        leftHeight = node->_left->_height;
    }
    if (node->_right) {
        rightHeight = node->_right->_height;
    }
    return leftHeight - rightHeight;
}
