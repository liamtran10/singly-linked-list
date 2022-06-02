#ifndef MY_FORWARD_LIST_HPP
#define MY_FORWARD_LIST_HPP

#include <algorithm>

template <typename T>
class Forward_list
{
public:
    class Node
    {
    public:
        T data{};
        Node* next = nullptr;

        Node(){}

        Node(T input_data, Node* next_node= nullptr)
        {
            data = input_data;
            next = next_node;
        }

        // Destructor
        ~Node(){}
    };

private:
    unsigned size_ = 0;
    Node* head_ = nullptr;

public:
    Forward_list();
    ~Forward_list();

    // Copy constructor
    Forward_list(const Forward_list<T>& other);

    // Constructor from initializer list
    Forward_list(std::initializer_list<T> input);

    // Add an element to the front of the list
    void push_front(const T& data);

    // Add an element to the back of the list
    // Added method as per assignment specification.
    void push_back(const T& data);

    // Remove the first element of the list
    void pop_front();

    // Remove the last element of the list
    // Added method as per assignment specification.
    void pop_back();

    // Return the data held in the first item of the list
    T front() const;

    // Print out all the data in the list in sequence
    void display() const;

    // Outputs if the list is empty or not
    bool empty() const;

    // outputs the size of the list
    unsigned size() const;

    // merge two sorted lists, *this and other
    void merge(Forward_list& other);

    // split *this into its first half and return second half "other"
    Forward_list split();

    // The sort function uses the helper functions merge and split that you write
    void sort();

private:
    void merge_sort(Forward_list&);

};

// Default Constructor
template <typename T>
Forward_list<T>::Forward_list()
{
}

// Destructor
template <typename T>
Forward_list<T>::~Forward_list()
{
    while(head_ != nullptr)
    {
        Node* tmp = head_;
        head_ = head_->next;
        delete tmp;
        --size_;
    }
}

// Copy Constructor
template <typename T>
Forward_list<T>::Forward_list(const Forward_list& other)
{
    if (other.size() == 0) { return; } // Check if list is empty or "null"
    else {
        size_ = other.size(); // Initialise "other" list size to be the same size as the one being copied.

        // Initialise pointers p (to populate list) and q (to traverse the list)
        // Create header node for copied list using head_->data from "other" list.
        Node* p = other.head_->next;
        head_ = new Node(other.head_->data, nullptr);
        Node* q = head_;

        // Traverse the "other" list using pointer q and populate the copied list using pointer p.
        while (p != nullptr) {
            q->next = new Node(p->data, nullptr);
            p = p->next;
            q = q->next;
        }
    }
}

// Constructor from initializer list
template <typename T>
Forward_list<T>::Forward_list(std::initializer_list<T> input)
{
    size_ = input.size(); // Initialise linked list size to equal to input list size.
    head_ = nullptr; // Assign head node to null.
    Node* ptr = head_; // Initalise point ptr to head node to traverse list.

    // For each element in the input list...
    for (auto it = input.begin(); it != input.end(); it++) {
        // First, create the head_ node.
        if (head_ == nullptr) {
            head_ = new Node(*it);
            ptr = head_;

        // Then, traverse through list using ptr and create new nodes in linked list
        } else {
            if (ptr != nullptr) {
                ptr->next = new Node(*it);
                ptr = ptr->next;
            }
        }
    }
}

// Add element to front of list
template <typename T>
void Forward_list<T>::push_front(const T& data)
{
    Node* new_node = new Node(); // Allocate a new node.
    new_node->data = data; // Assign data element to the node. 
    new_node->next = head_; // Make new node point to previous first node.
    head_= new_node; // Assign new node to be the head of the list.
    ++size_; // Increase list size by one.
}

// Add element to back of list
// Added method as per assignment specification.
template <typename T>
void Forward_list<T>::push_back(const T& data) 
{
    Node* new_node = new Node(); // Allocate a new node
    new_node->data = data; // Assign data element to the node.
    new_node->data = nullptr; // Assign null to the next node to signify end of list. 

    // Check if the list is empty. If empty, make the new node as head.
    if (this->head == nullptr) {
        this->head = new_node;
    } else {

        // Else traverse to the last node 
        Node* ptr = this->head;
        while(ptr->next) {
            ptr = ptr->next;
        }
        // Change the next of the last node to the new node. 
        ptr->next = new_node;
    }
}

// Remove the front element of the list.
template <typename T>
void Forward_list<T>::pop_front()
{
    Node* temp = head_; // Store current head node into temp.
    if (temp == nullptr) {return;} // If list is empty, do nothing.
    else {
        // Make next node the new head and delete temp.
        // Reduce list size by one.
        head_ = head_->next;
        delete temp;
        --size_;
    }
}

// Remove the back element of the list.
// Added method as per assignment specification.
template <typename T>
void Forward_list<T>::pop_back() 
{
    if (head_ == nullptr) { return; } // If list is empty, do nothing.
    if (head_->next == nullptr) { // If list contains only one node, delete that node.
        delete head_;
        return;
    }

    // Create pointer "second_last" to traverse the list to the second last node. 
    Node* second_last = head_;
    while (second_last->next->next != nullptr) {
        second_last = second_last->next;
    }

    delete second_last->next; // Delete the next node after second_last.
    second_last->next == nullptr; // Set value of next node after second last to null.
}

// Return the data in the front element of the list
template <typename T>
T Forward_list<T>::front() const
{
    // Create pointer front_element and have it point to the first (front) node.
    Node* front_element = head_;

    // If there is no node/the list is empty, do nothing.
    if (front_element == nullptr) { return 0; }
    else {
        // Otherwise, return the data of that first node.
        return front_element->data;
    }
}

// Print out the list
template <typename T>
void Forward_list<T>::display() const
{
    // Intialise pointer p to the head node to traverse the list.
    Node* p = head_;

    // While the end of the list has not been met, print the data of each node.
    while(p != nullptr) {
        std::cout << p->data << std::endl;
        p = p->next;
    }
}

// Outputs if the list is empty or not
template <typename T>
bool Forward_list<T>::empty() const
{
    return (head_ == nullptr);
}

// Returns the size of the list
template <typename T>
unsigned Forward_list<T>::size() const
{
    return size_;
}

// the split function 
template <typename T>
Forward_list<T> Forward_list<T>::split() // Using slow/fast pointers method. 
{
    // Initalise empty list "second_half" to store second half of list.
    Forward_list<T> second_half;

    // Create a "slow" pointer that moves one node at a time whilst
    // simultaneously, the "fast" pointer moves two nodes at a time. 
    Node* slow = head_;
    Node* fast = head_->next;

    // When "fast" pointer reaches the end of the list,
    // "slow" pointer will point to the middle element.
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Make the element AFTER the middle element, the head node of the second_half.
    // Initialise the pointer between the two halves to null to split the list.
    second_half.head_ = slow->next;
    slow->next = nullptr;

    // Size of second half should be floor(half) of *this
    // Size of *this will be the difference between original *this size and second_half size.
    second_half.size_ = this->size() / 2;
    this->size_ = this->size() - second_half.size_;

    // Return second half of split list.
    return second_half;
}

// Merging two sorted lists
template <typename T>
void Forward_list<T>::merge(Forward_list& other)
{
    // If "other" list is empty, do nothing. *this will be taken as the final merged list.
    if (other.head_ == nullptr) { return; }

    // If *this is empty, take "other" list as the new *this and make it the final merged list.
    if (this->head_ == nullptr) {
        this->head_ = other.head_;
        other.head_ = nullptr;
        return;
    }

    // Initialise pointers head1 and head2 for comparison purposes. 
    // ptr will be used to store the head node. 
    Node* head1 = this->head_;
    Node* head2 = other.head_;
    Node* ptr;

    // Compare the first nodes of both lists.
    // If the data of the first node of *this is less that that 
    // of the data of the first node of "other," make that node the head of the merged list.
    if (head1->data <= head2->data) {
        ptr = head1;
        head1 = head1->next;

    // Else vice versa..
    } else {
        ptr = head2;
        head2 = head2->next;
    }

    // ptr variable now holds the head node of the merged list.
    // Initalise temp pointer to the head node (ptr) to traverse the list.
    Node* temp = nullptr;
    temp = ptr;

    // While the end of either lists haven't been met.
    while (head1 != nullptr && head2 != nullptr) {

        // Update pointers to point towards the node which is less in value.
        if (head1->data <= head2->data) {
            temp->next = head1;
            head1 = head1->next;

        } else {
            temp->next = head2;
            head2 = head2->next;
        }

        // Continue to traverse the array.
        temp = temp->next;
    }

    // If either list is exhausted before one list is fully traversed 
    // i.e. the lists are not equal in size, populate
    // the merged list with the remaining nodes from whatever is remaining in the other list.
    if (head1 != nullptr) { temp->next = head1; }
    if (head2 != nullptr) { temp->next = head2; }

    // Make the "other" list null.
    this->head_ = ptr;
    other.head_ = nullptr;
}   

// recursive implementation of merge_sort
template <typename T>
void Forward_list<T>::merge_sort(Forward_list& my_list)
{
    if(my_list.size() == 0 || my_list.size() == 1)
    {
        return;
    }
    Forward_list<T> second = my_list.split();
    merge_sort(my_list);
    merge_sort(second);
    my_list.merge(second);
}

// sorts the list by calling merge_sort
template <typename T>
void Forward_list<T>::sort()
{
    merge_sort(*this);
}

#endif