#include "BST.h"
#include <iostream>
#include <limits>

BinarySearchTree::Node::Node(Key key, Value value, bool color, Node* parent, Node* left, Node* right) 
    : keyValuePair(key, value), color(color), parent(parent), left(left), right(right) {}

BinarySearchTree::Node::Node(const Node& other) : keyValuePair(other.keyValuePair) {}


void BinarySearchTree::Node::to_left()
{
    Node* left_root = this->right;

    left_root->parent = this->parent;
    if (this->parent)
    {
        if (this->parent->left == this)
        {
            this->parent->left = left_root;
        }
        else
        {
            this->parent->right = left_root;
        }
    }

    this->right = left_root->left;
    if (left_root->left) left_root->left->parent = this;

    this->parent = left_root;
    left_root->left = this;
}

void BinarySearchTree::Node::to_right()
{
    Node* right_node = this->left;
    right_node->parent = this->parent;
    if (this->parent)
    {
        if (this->parent->left == this)
        {
            this->parent->left = right_node;
        }
        else
        {
            this->parent->right = right_node;
        }
    }

    this->left = right_node->right;
    if (right_node->right) right_node->right->parent = this;
    this->parent = right_node;
    right_node->right = this;
}

int BinarySearchTree::Node::max_height() const
{
    if (this->keyValuePair.first == std::numeric_limits<Key>::max()) return 0;
    int lh = 0, rh = 0;
    if (left) lh = left->max_height();
    if (right) rh = right->max_height();
    return 1 + std::max(lh, rh);
}


bool BinarySearchTree::Node::operator==(const Node& other) const 
{
    return this->keyValuePair == other.keyValuePair;
}

void BinarySearchTree::Node::output_node_tree(int level) const
{
    if (left) left->output_node_tree(level+1);
    
    if (this->keyValuePair.first == std::numeric_limits<Key>::max()) return;
    std::cout << "(" << this->keyValuePair.first << "," << this->keyValuePair.second << ")" << std::endl;
    
    if (right) right->output_node_tree(level+1);
}

void BinarySearchTree::Node::insert(const Key& key, const Value& value, Node** root)
{
    if (!root) return;
    if (key <= keyValuePair.first)
    {
        if (left) 
	{
            left->insert(key, value, root);
            return;
        }
        left = new Node(key, value, true, this);
        left->insert_balance(root);
    } 
    else 
    {
        if (right)
       	{
            right->insert(key, value, root);
            return;
        }
        right = new Node(key, value, true, this);
        right->insert_balance(root);
    }
}

void BinarySearchTree::Node::insert_balance(Node** root)
{
    if (!parent) {
        color = 0;
        *root = this;
        return;
    }

    if (parent->color == false) return;
    Node* uncle = parent->parent->left == parent ? parent->parent->right : parent->parent->left;
    if (uncle && uncle->color)
    {
        parent->color = false;
        uncle->color = false;
        parent->parent->color = true;
        parent->parent->insert_balance(root);
        return;
    }
    Node* n = this;
    if (n == parent->right && parent == parent->parent->left)
    {
        parent->to_left();
        n = left;
    }
    else if (n == parent->left && parent == parent->parent->right)
    {
        parent->to_right();
        n = right;
    }

    n->parent->color = false;
    n->parent->parent->color = true;
    if ((n == n->parent->left) && (n->parent == n->parent->parent->left))
    {
        if (n->parent->parent == *root) *root = n->parent->parent->left;
        n->parent->parent->to_right();
    }
    else
    {
        if (n->parent->parent == *root) *root = n->parent->parent->right;
        n->parent->parent->to_left();
    }
}

void BinarySearchTree::Node::erase(const Key& key, Node** root) 
{
    if (!root) return;
    if (key != keyValuePair.first)
    {
        if (left && key <= keyValuePair.first) left->erase(key, root);
        else if (right) right->erase(key, root);
        return;
    }
    
    if (left && right)
    {
        Node* current = right;
        while (current->left) current = current->left;
        
        this->keyValuePair = current->keyValuePair;

        current->erase(current->keyValuePair.first, root);
        
        return;
    }

    if (color)
    {
        if (parent->left == this) parent->left = nullptr;
        else parent->right = nullptr;
        delete this;
        return;
    }

    Node* ptr = nullptr;
    if (left) ptr = left;
    else ptr = right;
    
    if (!ptr) 
    {
        this->color = 0;
        this->erase_balance(root);
        if (parent)
       	{
            if (parent->left == this) parent->left = ptr;
            else parent->right = ptr;
        }
        if (this == *root) *root = ptr;
        delete this;
        return;
    }

    if (parent)
    {
        if (parent->left == this) parent->left = ptr;
        else parent->right = ptr;
    }
    ptr->parent = parent;

    if (ptr->color) 
    {
        ptr->color = false;
    } 
    else ptr->erase_balance(root);
    
    if (this == *root) *root = ptr;
    delete this;
    return;
}


void BinarySearchTree::Node::erase_balance(Node** root) 
{
    if (!parent) return;

    Node* sibling;
    if (parent->left == this) sibling = parent->right;
    else sibling = parent->left;
    
    if (sibling->color) 
    {
        parent->color = 1;
        sibling->color = 0;
        if (parent->left == this)
       	{
            if (parent == *root) *root = parent->right;
            parent->to_left();
        }
       	else
       	{
            if (parent == *root) *root = parent->left;
            parent->to_right();
        }
    }

    if (!parent->color && !sibling->color && (!sibling->left || !sibling->left->color) && (!sibling->right || !sibling->right->color)) 
    {
        sibling->color = 1;
        parent->erase_balance(root);
        return;
    }
    
    if (parent->color && !sibling->color 
            && (!sibling->left || !sibling->left->color)
            && (!sibling->right || !sibling->right->color))
    {
        sibling->color = 1;
        parent->color = 0;
        return;
    }

    if (!sibling->color) 
    {
        if (this == parent->left 
                && (!sibling->right || !sibling->right->color) 
                && (sibling->left && sibling->left->color)) 
	{
            sibling->color = 1;
            sibling->left->color = 0;
            sibling->to_right();
        }
       	else if (this == parent->right && (sibling->right && sibling->right->color) && (!sibling->left || !sibling->left->color)) 
	{
            sibling->color = 1;
            sibling->right->color = 0;
            sibling->to_left();
        }
        return;
    }

    sibling->color = parent->color;
    parent->color = 0;

    if (this == parent->left) 
    {
        if (sibling->right) sibling->right->color = 0;
        if (parent == *root) *root = parent->right;
        parent->to_left();
    }
    else
    {
        if (sibling->left) sibling->left->color = 0;
        if (parent == *root) *root = parent->left;
        parent->to_right();
    }
}

BinarySearchTree::Node* BinarySearchTree::copySubtree(const Node* other)
{
    if (other == nullptr) return nullptr;
    Node* n = new Node(*other);
    n->left = copySubtree(other->left);
    n->right = copySubtree(other->right);
    return n;
}

void BinarySearchTree::freeSubtree(Node* node) 
{
    if (!node) return;
    freeSubtree(node->left);
    freeSubtree(node->right);
    delete node;
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree &other) : _root(copySubtree(other._root)), _size(other._size) {}

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree &other)
{
    if (this == &other) return *this;
    freeSubtree(_root);
    _root = copySubtree(other._root);
    _size = other._size;
    return *this;
}

BinarySearchTree::BinarySearchTree(BinarySearchTree &&other) noexcept : _root(other._root), _size(other._size)
{
    other._root = nullptr;
    other._size = 0;
}

BinarySearchTree& BinarySearchTree::operator=(BinarySearchTree &&other) noexcept
{
    if (this == &other) return *this;
    std::swap(this->_root, other._root);
    std::swap(this->_size, other._size);
    return *this;
}

BinarySearchTree::~BinarySearchTree() 
{
    freeSubtree(_root);
}

BinarySearchTree::Iterator::Iterator(Node *node) : _node(node) {}

std::pair<Key, Value>& BinarySearchTree::Iterator::operator*()
{
    if (!_node) throw std::runtime_error("Null iterator");
    return _node->keyValuePair;
}

const std::pair<Key, Value>& BinarySearchTree::Iterator::operator*() const
{
    if (!_node) throw std::runtime_error("Null iterator");
    return _node->keyValuePair;
}

std::pair<Key, Value>* BinarySearchTree::Iterator::operator->()
{
    if (!_node) throw std::runtime_error("Null iterator");
    return &_node->keyValuePair;
}

const std::pair<Key, Value>* BinarySearchTree::Iterator::operator->() const 
{
    if (!_node) throw std::runtime_error("Null iterator");
    return &_node->keyValuePair;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++() 
{
    if (!_node) throw std::runtime_error("Null iterator");
    if (_node->right)
    {
        _node = _node->right;
        while (_node->left) _node = _node->left;
        return *this;
    }

    while (_node->parent)
    {
        if (_node == _node->parent->left)
       	{
            _node = _node->parent;
            return *this;
        }
        _node = _node->parent;
    }

    throw std::runtime_error("end");
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++(int)
{
    if (!_node) throw std::runtime_error("Null");
    Iterator it = *this;

    if (_node->right)
    {
        _node = _node->right;
        while (_node->left) _node = _node->left;
        return it;
    }

    while (_node->parent)
    {
        if (_node == _node->parent->left) 
	{
            _node = _node->parent;
            return it;
        }
        _node = _node->parent;
    }
    
    throw std::runtime_error("end");

}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--() 
{
    if (!_node) throw std::runtime_error("Null");
    if (_node->left) 
    {
        _node = _node->left;
        while (_node->right) _node = _node->right;
        return *this;
    }

    while (_node->parent)
    {
        if (_node == _node->parent->right)
       	{
            _node = _node->parent;
            return *this;
        }
        _node = _node->parent;
    }

    throw std::runtime_error("begin");
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--(int) 
{
    if (!_node) throw std::runtime_error("Null");

    Iterator it = *this;
    if (_node->left)
    {
        _node = _node->left;
        while (_node->right) _node = _node->right;
        return it;
    }

    while (_node->parent) 
    {
        if (_node == _node->parent->right)
       	{
            _node = _node->parent;
            return it;
        }
        _node = _node->parent;
    }

    throw std::runtime_error("begin");
}

bool BinarySearchTree::Iterator::operator==(const Iterator &other) const
{
    return _node->keyValuePair.first == other._node->keyValuePair.first;
}

bool BinarySearchTree::Iterator::operator!=(const Iterator &other) const
{
    return _node->keyValuePair.first != other._node->keyValuePair.first;
}

BinarySearchTree::ConstIterator::ConstIterator(const Node *node) : _node(node) {}

const std::pair<Key, Value>& BinarySearchTree::ConstIterator::operator*() const
{
    if (!_node) throw std::runtime_error("Null");
    return _node->keyValuePair;
}

const std::pair<Key, Value>* BinarySearchTree::ConstIterator::operator->() const
{
    if (!_node) throw std::runtime_error("Null");
    return &_node->keyValuePair;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++()
{
    if (!_node) throw std::runtime_error("Null");
    if (_node->right) 
    {
        _node = _node->right;
        while (_node->left) _node = _node->left;
        return *this;
    }

    while (_node->parent)
    {
        if (_node == _node->parent->left)
       	{
            _node = _node->parent;
            return *this;
        }
        _node = _node->parent;
    }

    throw std::runtime_error("end");
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++(int) 
{
    if (!_node) throw std::runtime_error("Null");
    ConstIterator it = *this;

    if (_node->right)
    {
        _node = _node->right;
        while (_node->left) _node = _node->left;
        return it;
    }

    while (_node->parent)
    {
        if (_node == _node->parent->left) 
	{
            _node = _node->parent;
            return it;
        }
        _node = _node->parent;
    }
    
    throw std::runtime_error("end");

}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--() 
{
    if (!_node) throw std::runtime_error("Null");
    if (_node->left)
    {
        _node = _node->left;
        while (_node->right) _node = _node->right;
        return *this;
    }

    while (_node->parent)
    {
        if (_node == _node->parent->right)
       	{
            _node = _node->parent;
            return *this;
        }
        _node = _node->parent;
    }

    throw std::runtime_error("begin");
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--(int)
{
    if (!_node) throw std::runtime_error("Null");

    ConstIterator it = *this;
    if (_node->left)
    {
        _node = _node->left;
        while (_node->right) _node = _node->right;
        return it;
    }

    while (_node->parent) 
    {
        if (_node == _node->parent->right) 
	{
            _node = _node->parent;
            return it;
        }
        _node = _node->parent;
    }

    throw std::runtime_error("begin");
}

bool BinarySearchTree::ConstIterator::operator==(const ConstIterator &other) const
{
    return _node->keyValuePair.first == other._node->keyValuePair.first;
}

bool BinarySearchTree::ConstIterator::operator!=(const ConstIterator &other) const
{
    return _node->keyValuePair.first != other._node->keyValuePair.first;
}

void BinarySearchTree::insert(const Key &key, const Value &value)
{
    if (!_root) 
    {
        _root = new Node(key, value);
        _root->right = new Node(std::numeric_limits<Key>::max(), value, false, _root);
        ++_size;
        return;
    }
    Node* _end = end()._node;
    if (_end->parent) _end->parent->right = nullptr;

    _root->insert(key, value, &_root);
    ++_size;

    Node* current = _root;
    while (current->right) current = current->right;
    current->right = _end;
    _end->parent = current;
}

void BinarySearchTree::erase(const Key &key)
{
    if (!_root) return;
    Iterator i(_root);
    while ((i = find(key)) != end()) 
    {
        Node* _end = end()._node;
        _end->parent->right = nullptr;
        
        i._node->erase(key, &_root);
        --_size;
        if (!_root)
       	{
            delete _end;
            return;
        }

        Node* current = _root;
        while (current->right) current = current->right;
        current->right = _end;
        _end->parent = current;
    }
}

BinarySearchTree::ConstIterator BinarySearchTree::find(const Key &key) const
{
    const Node* current = _root;
    while (current) 
    {
        if (current->keyValuePair.first < key)
       	{
            current = current->right;
        } 
	else if (current->keyValuePair.first > key) 
	{
            current = current->left;
        }
       	else 
	{
            return ConstIterator(current);
        }
    }
    return cend();
}

BinarySearchTree::Iterator BinarySearchTree::find(const Key &key) 
{
    Node* current = _root;
    while (current) 
    {
        if (current->keyValuePair.first < key) 
	{
            current = current->right;
        } 
	else if (current->keyValuePair.first > key)
       	{
            current = current->left;
        } 
	else
       	{
            return Iterator(current);
        }
    }
    return end();
}

std::pair<BinarySearchTree::Iterator, BinarySearchTree::Iterator> BinarySearchTree::equalRange(const Key &key) 
{
    Iterator it = end();
    Iterator current = begin();
    while (current != it && current->first != key) ++current;

    Iterator first = current;
    while (current != it && current->first == key) ++current;
    return {first, current};
}

std::pair<BinarySearchTree::ConstIterator, BinarySearchTree::ConstIterator> BinarySearchTree::equalRange(const Key &key) const 
{
    ConstIterator it = cend();
    ConstIterator current = cbegin();
    while (current != it && current->first != key) ++current;

    ConstIterator first = current;
    while (current != it && current->first == key) ++current;
    return {first, current};
}

BinarySearchTree::ConstIterator BinarySearchTree::min() const
{
    return cbegin();
}

BinarySearchTree::ConstIterator BinarySearchTree::max() const 
{
    return --cend();
}

BinarySearchTree::ConstIterator BinarySearchTree::min(const Key &key) const 
{
    std::pair<ConstIterator, ConstIterator> range = equalRange(key);
    ConstIterator current = range.first;
    ConstIterator it = current;
    
    for (; current != range.second; ++current) 
    {
        if (current->second < it->second) it = current;
    }

    return it;
}

BinarySearchTree::ConstIterator BinarySearchTree::max(const Key &key) const
{
    std::pair<ConstIterator, ConstIterator> range = equalRange(key);
    ConstIterator current = range.first;
    ConstIterator it = current;
    
    for (; current != range.second; ++current)
    {
        if (current->second > it->second) it = current;
    }

    return it;
}

BinarySearchTree::Iterator BinarySearchTree::begin() 
{
    Node* current = _root;
    while (current->left) current = current->left;
    return Iterator(current);
}

BinarySearchTree::Iterator BinarySearchTree::end()
{
    Node* current = _root;
    while (current->right) current = current->right;
    return Iterator(current);
}

BinarySearchTree::ConstIterator BinarySearchTree::cbegin() const 
{
    Node* current = _root;
    while (current->left) current = current->left;
    return ConstIterator(current);
}

BinarySearchTree::ConstIterator BinarySearchTree::cend() const
{
    Node* current = _root;
    while (current->right) current = current->right;
    return ConstIterator(current);
}

size_t BinarySearchTree::size() const 
{
    return _size;
}

void BinarySearchTree::output_tree() const
{
    if (!_root) return;
    _root->output_node_tree();
}

int BinarySearchTree::max_height() const
{
    return _root->max_height();
}
