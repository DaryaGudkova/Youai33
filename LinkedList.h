#ifndef LAB3SEM3_LINKEDLIST_H
#define LAB3SEM3_LINKEDLIST_H
/*
#pragma once
#include<iterator>
#include "DynamicArray.h"
#include <vector>
template<typename T> class LinkedList
{
private:
    class Node
    {
    public:
        T item;
        Node* pnext;

        Node(T item = T(), Node* pnext = nullptr) {
            this->item = item;
            this->pnext = pnext;
        };
    };
    Node* head;
    int size;

public:
    //constructors
    LinkedList();
    LinkedList(int count);
    LinkedList(T* arr, int count);
    //LinkedList(vector<T> arr, int count);
    LinkedList(const LinkedList<T>& list);

    //decompose
    int GetLength() const;
    T GetFirst() const;
    T GetLast() const;
    T Get(int index) const;
    LinkedList<T>* GetSublist(int start, int end) const;


    // Operations
    void Set(int index, T value);
    void Append(T value);
    void Prepend(T value);
    void InsertAt(T value, int index);
    LinkedList<T>* Concat(LinkedList<T>* list);

    //Destructor
    ~LinkedList() = default;
};

//CONSTRUCTORS

template<typename T> LinkedList<T>::LinkedList() :size(0) {
    this->size = 0;
    this->head = nullptr;
}

template<typename T> LinkedList<T>::LinkedList(int size) :size(size) {
    this->size = size;
    this->head = nullptr;
}

template<typename T>LinkedList<T>::LinkedList(const LinkedList<T>& list) : LinkedList() {
    for (int i=0; i<list.GetLength(); i++) {
        this->Append(list.Get(i));
    }
}

template<typename T> LinkedList<T>::LinkedList(T* arr, int count) : LinkedList() {
    if (count<0) {
        throw length_error("Negative size!");
    }
    for (int i =0; i<count; i++) {
        this->Append(arr[i]);
    }
}
/*
template<typename T> LinkedList<T>::LinkedList(vector<T> arr, int count) : LinkedList() {
    if (count<0) {
        throw length_error("Negative size!");
    }
    for (int i =0; i<count; i++) {
        this->Append(arr[i]);
    }
}*

//DECOMPOSITION

template<typename T> int LinkedList<T>::GetLength() const {
    return this->size;
}

template<typename T> T LinkedList<T>::GetFirst() const {
    if (this->GetLength()==0) {
        throw out_of_range("Index out of range!");
    }
    return Get(0);
}

template<typename T> T LinkedList<T>::GetLast() const {
    if (this->GetLength()==0) {
        throw out_of_range("Index out of range!");
    }
    return Get(this->size-1);
}

template<typename T>
T LinkedList<T>::Get(int index) const {
    if (index <0 || index >= this->size) {
        throw out_of_range("Index out of range!");
    }
    int sch = 0;
    Node* temp;
    temp = this->head;
    while (temp != nullptr) {
        if (sch == index) {
            return temp->item;
        }
        temp = temp ->pnext;
        ++sch;
    }
}

template<typename T> LinkedList<T>* LinkedList<T>::GetSublist(int start, int end) const {
    if (start<0 || start>=this->size || end<0 || end >=this->size || end<start) {
        throw out_of_range("Index out of range!");
    }
    auto* nList = new LinkedList<T>();
    for (int i=start; i<=end; i++) {
        nList->Append(this->Get(i));
    }
    nList->size = end-start+1;
    return nList;
}

//OPERATIONS

template<typename T> void LinkedList<T>::Set(int index, T value) {
    if (index <0 || index > this->size-1) {
        throw out_of_range("Index out of range!");
    }
    Node* temp = this->head;
    for (int i=0; i<index; i++) {
        temp = temp->pnext;
    }
    temp->item = value;
}

template<typename T> void LinkedList<T>::Append(T value) {
    if (head == nullptr)
        head = new Node(value);
    else {
        Node* temp;
        temp = head;
        while (temp->pnext != nullptr) {
            temp = temp->pnext;
        }
        temp->pnext = new Node(value);
    }
    ++size;
}

template<typename T> void LinkedList<T>::Prepend(T value) {
    this->size++;
    this->head = new Node(value, this->head);
}

template<typename T> void LinkedList<T>::InsertAt(T value, int index) {
    if (index <0 || index >= this->size) {
        throw out_of_range("Index out of range!");
    }
    if (index == 0) {
        Prepend(value);
    }
    else  {
        Node* temp = this->head;
        for (int i=0; i<index-1; i++) {
            temp = temp->pnext;
        }
        Node* NewOne = new Node(value, temp->pnext);
        temp->pnext = NewOne;
        this->size++;
    }
}

template<typename T> LinkedList<T> *LinkedList<T>::Concat(LinkedList<T> *list) { //IMPROVED
    auto* result = new LinkedList<T>();
    result->head=this->head;
    Node* temp = this->head;
    for (int i=0; i<this->size-1; i++) {
        temp = temp->pnext;
    }
    result->size=this->size+list->size;
    temp->pnext =list->head;
    return result;
}*/
#pragma once
#include <stdexcept>

#define INDEX_OUT_OF_RANGE_MESSAGE "index out of range"
#define NEGATIVE_SIZE_MESSAGE "size is negative"
#define ZERO_SIZE_MESSAGE "size is 0"

template <class T>
class LinkedList
{
private:
    /*class Node{
    public:
        T data;
        Node* next;
        Node(T data = T(), Node next = nullptr){
            this->data = data;
            this->next = next;
        }
    };
    Node* head = nullptr;
    int size = 0;*/
    struct Node{
        T data = T();
        Node* next = nullptr;
    };

    int size = 0;
    Node* head = nullptr;

public:
    LinkedList() : size(0), head(nullptr) {};

    LinkedList(int size) : LinkedList() {
        if (size < 0) throw std::length_error(NEGATIVE_SIZE_MESSAGE);
        Node** tmp = &(this->head);
        for (int i = 0; i < size; i++) {
            *tmp = new Node;
            (*tmp)->data = T();
            tmp = &((*tmp)->next);
        }
        this->size = size;
    }

    LinkedList(const T* data, const int size) : LinkedList(){
        if (size < 0) throw std::out_of_range(NEGATIVE_SIZE_MESSAGE);
        this->size = size;
        Node** newptr = &(this->head);
        for (int i = 0; i < size; ++i){
            (*newptr) = new Node;
            (*newptr)->data = data[i];
            newptr = &((*newptr)->next);
        }
    }

    LinkedList(const LinkedList<T>& list) {
        //if (list.head == nullptr) return;
        Node* ptr = list.head;
        Node** newptr = &(this->head);
        for (int i = 0; i < list.size; i++, ptr = ptr->next) {
            *newptr = new Node;
            (*newptr)->data = ptr->data;
            newptr = &((*newptr)->next);
        }
        this->size = list.size;
    }

    //~LinkedList() = default;
    ~LinkedList() {
        if(this) {
            Node *ptr = head;
            Node *next;
            if (this->size == 1)
                delete ptr;
            else {
                while (ptr != nullptr) {
                    next = ptr->next;
                    delete ptr;
                    ptr = next;
                }
            }
            this->size = 0;
        }
    }

    //Methods of class
    T GetFirst() const{
        if (this->size == 0) throw std::length_error(ZERO_SIZE_MESSAGE);
        return this->head->data;
    }

    T GetLast() const{
        if (this->size == 0) throw std::length_error(ZERO_SIZE_MESSAGE);
        Node* ptr = this->head;
        while (ptr->next != nullptr) ptr = ptr->next;
        return ptr->data;
    }

    T Get(const int index) const
    {
        if (index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        Node* ptr = this->head;
        for (int i = 0; i < index; i++) ptr = ptr->next;

        return ptr->data;
    }


    LinkedList<T>* GetSublist(const int start_index, const int end_index) const
    {
        if (start_index < 0 || start_index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        if (end_index < 0 || end_index > this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
        if (start_index > end_index) throw std::logic_error("end must be not less than start");

        int newsize = end_index - start_index;
        Node* ptr = this->head;
        T* newdata = new T[newsize];

        for (int i = 0; i < end_index; ++i)
        {
            if (i >= start_index) newdata[i - start_index] = ptr->data;
            ptr = ptr->next;
        }

        LinkedList<T>* newptr = new LinkedList<T>(newdata, newsize);
        delete[] newdata;

        return  newptr;

    }

    int GetSize() const
    {
        return  this->size;
    }

    void Append(const T &data)
    {
        Node** ptr = &(this->head);
        while (*ptr != nullptr) ptr = &((*ptr)->next);

        (*ptr) = new Node;
        (*ptr)->data = data;

        this->size++;

    };

    void Prepend(const T &data)
    {
        Node* ptr = new Node{data, this->head };
        this->head = ptr;

        this->size++;

    }

    void Set(const T& data, int index) {
        if (index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);


        Node* ptr;
        {
            int i = 0;
            for (i = 0, ptr = this->head; i < index; i++, ptr = ptr->next);
        }

        ptr->data = data;
    }

    void Insert(const T& data, const int index) {
        if (index < 0 || index > this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

        if (index == 0)
        {
            this->Prepend(data);
        }
        else
        {
            Node* ptr = new Node{data, this->head };
            Node* newptr = new Node{data, this->head };
            for (int i = 0; i < index ; i++)
                ptr = ptr->next;
            newptr->next = ptr->next;
            ptr->next = newptr;
            this->size++;
        }
    }

    void Remove(int index) {
        if (index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);


        Node preHead;
        preHead.next = this->head;
        Node* ptr;
        ptr = &preHead;
        for (int i = 0; i < index; i++)
            ptr = ptr->next;
        Node* tmp = ptr->next;
        ptr->next = ptr->next->next;
        delete tmp;

        this->head = preHead.next;

        this->size--;
    }

    LinkedList<T>* Concat(const LinkedList<T> &list)
    {
        Node* ptr1 = this->head;
        Node* ptr2 = list.head;

        LinkedList<T>* newList = new LinkedList<T>();
        Node** ptr = &(newList->head);
        while (ptr1 != nullptr) {
            *ptr = new Node{
                    ptr1->data,
                    ptr1->next
            };

            ptr1 = ptr1->next;
            ptr = &((*ptr)->next);
        }
        while (ptr2 != nullptr) {
            *ptr = new Node{ptr2->data, ptr2->next};
            ptr2 = ptr2->next;
            ptr = &((*ptr)->next);
        }

        newList->size = this->size + list.size;
        return newList;
    }


    T& operator [] (const int index) const
    {

        if (this->head == nullptr || index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

        Node* ptr = this->head;

        for (int i = 0; i < index; ++i) ptr = ptr->next;

        return ptr->data;

    }



    bool operator==(const LinkedList<T>& list) const {
        if (this->size != list.size) return false;

        for (int i = 0; i < this->size; i++) {
            if (this->Get(i) != list.Get(i)) return false;
        }

        return true;
    }
};

template <class T>
std::ostream& operator<< (std::ostream& out, const LinkedList<T> seq) {
    out << "<";
    for (int i = 0; i < seq.GetSize(); i++) {
        out << seq.Get(i);
    }
    out << ">";
    return out;
}
#endif //LAB3SEM3_LINKEDLIST_H
