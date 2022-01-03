#ifndef INTERFACE_CPP_BINARYTREE_H
#define INTERFACE_CPP_BINARYTREE_H

#include <string>
#include "cstdlib"
using namespace std;

template <class T>
bool compare(T a, T b)
{
    return a < b;
}

template <class T>
class BinaryTree
{
private:
    struct node
    {
        node* parent = nullptr;
        node* left = nullptr;
        node* right = nullptr;
        T elem;
    };
    node* root = nullptr;
    int size = 0;
    bool (*cmp)(T, T) = compare;

private:
    void destructor(node* curr)
    {
        if (curr)
        {
            destructor(curr->left);
            destructor(curr->right);
            delete curr;
        }
    }

    void printAll(node* nodePtr)
    {
        if (nodePtr == nullptr) return;
        if (nodePtr->left != nullptr)
        {
            printAll(nodePtr->left);
        }
        cout << nodePtr->elem;
        cout << endl;
        if (nodePtr->right != nullptr)
        {
            printAll(nodePtr->right);
        }
    }

public:

    BinaryTree(){
        this->root = nullptr;
        this->size = 0;
        this->cmp = cmp;
    }

    BinaryTree(const T key, bool (*cmp) (T, T))
    {
        this->root = new node;
        this->root->elem = key;
        this->size = 1;
        this->cmp = cmp;
    }

    void add(const T elem)
    {
        node* nodePtr = this->root;
        this->size++;
        if (this->root == nullptr){
            this->root = new node;
            this->root->elem = elem;
            return;
        }
        while (nodePtr != nullptr)
        {
            if (this->cmp(nodePtr->elem, elem))
            {
                if (nodePtr->right != nullptr)
                {
                    nodePtr = nodePtr->right;
                }
                else
                {
                    nodePtr->right = new node;
                    nodePtr->right->elem = elem;
                    nodePtr->right->parent = nodePtr;
                    break;
                }
            }
            else
            {
                if (nodePtr->left != nullptr)
                {
                    nodePtr = nodePtr->left;
                }
                else
                {
                    nodePtr->left = new node;
                    nodePtr->left->elem = elem;
                    nodePtr->left->parent = nodePtr;
                    break;
                }
            }
        }
    }

    T minimum()
    {
        if (this->root == nullptr) return T(0);
        node* nodePtr = this->root;
        while (nodePtr->left != nullptr)
        {
            nodePtr = nodePtr->left;
        }
        return nodePtr->elem;
    }
    T maximum()
    {
        node* nodePtr = this->root;
        if (this->root == nullptr)
        {
            return T(0);
        }
        while (nodePtr->right != nullptr)
        {
            nodePtr = nodePtr->right;
        }
        return nodePtr->elem;
    }

    node* search(const T elem)
    {
        node* nodePtr = this->root;
        while (nodePtr != nullptr)
        {
            if (this->cmp(nodePtr->elem, elem))
            {
                nodePtr = nodePtr->right;
            }
            else if (this->cmp(elem, nodePtr->elem))
            {
                nodePtr = nodePtr->left;
            }
            else return nodePtr;
        }
        return nullptr;
    }

    bool find(const T key)
    {
        node * curr = root;
        while (curr && curr->elem != key)
        {
            if (curr->elem > key)
                curr = curr->left;
            else
                curr = curr->right;
        }
        return curr != nullptr;
    }

    int getSize() const
    {
        return this->size;
    }

    T getElem(node* cur)
    {
        return cur->elem;
    }

    void setElem(node* cur, T elem)
    {
        cur->elem = elem;
    }

    void erase(T key)
    {
        node * curr = root;
        node * parent = nullptr;
        while (curr && curr->elem != key)
        {
            parent = curr;
            if (curr->elem > key)
            {
                curr = curr->left;
            }
            else
            {
                curr = curr->right;
            }
        }
        if (!curr)
            return;
        if (curr->left == nullptr)
        {
            if (parent && parent->left == curr)
                parent->left = curr->right;
            if (parent && parent->right == curr)
                parent->right = curr->right;
            --size;
            delete curr;
            return;
        }
        if (curr->right == nullptr)
        {
            if (parent && parent->left == curr)
                parent->left = curr->left;
            if (parent && parent->right == curr)
                parent->right = curr->left;
            --size;
            delete curr;
            return;
        }
        node * replace = curr->right;
        while (replace->left)
            replace = replace->left;
        T replace_value = replace->elem;
        erase(replace_value);
        curr->elem = replace_value;
        this->size--;
    }

    void printAll()
    {
        if (this->root == nullptr) return;
        printAll(this->root);
        std::cout << endl;
    }

    ~BinaryTree()
    {
        destructor(this->root);
        size = 0;
    }
};
#endif //INTERFACE_CPP_BINARYTREE_H
