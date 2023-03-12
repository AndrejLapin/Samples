#include "pch.h"
#include "ReorderList.h"

#include "Structures/LinkedList/LinkedList.h"

struct DoubleLinkedNode {
    ListNode* m_node; // currentNode
    DoubleLinkedNode* m_previous; // previous node
    DoubleLinkedNode(ListNode* myNode) : m_node(myNode), m_previous(nullptr) {}
    DoubleLinkedNode(ListNode* myNode, DoubleLinkedNode* previous) : m_node(myNode), m_previous(previous) {}
};

struct DoubleLinkedList {
    DoubleLinkedNode* head = nullptr;
    DoubleLinkedNode* tail = nullptr;

    void AddAtEnd(ListNode* node)
    {
        if (!head)
        {
            DoubleLinkedNode* headNode = new DoubleLinkedNode(node);
            head = headNode;
            tail = headNode;
        }
        else
        {
            DoubleLinkedNode* tailNode = new DoubleLinkedNode(node, tail);
            tail = tailNode;
        }
    }

    ~DoubleLinkedList()
    {
        while (tail)
        {
            DoubleLinkedNode* nodeToDelete = tail;
            tail = tail->m_previous;
            delete nodeToDelete;
        }
    }
};

void reorderListAlloc(ListNode* head) 
{
    DoubleLinkedList linkedList;
    ListNode* front = head;
    while (front)
    {
        linkedList.AddAtEnd(front);
        front = front->next;
    }

    front = head;
    DoubleLinkedNode* back = linkedList.tail;
    while (front != back->m_node)
    {
        ListNode* backNode = back->m_node;
        ListNode* nextNode = front->next;
        if (backNode == nextNode) { return; }
        front->next = backNode;
        backNode->next = nextNode;
        front = nextNode;
        back = back->m_previous;
    }
}

void reverseList(ListNode* head)
{
    ListNode* slow = head;
    ListNode* middle = head;
    ListNode* rightNext = slow->next;
    slow->next = nullptr;

    while (rightNext)
    {
        middle->next = rightNext;
        rightNext = rightNext->next;
        middle->next->next = slow;
        slow = middle->next;
    }
}

void reverseFromMiddle(ListNode* head)
{
    ListNode* fast = head;
    ListNode* slow = head;
    ListNode* middle;
    ListNode* rightNext;

    // finding middle
    while (fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    middle = slow;
    slow = slow->next;
    rightNext = slow->next;
    slow->next = nullptr;

    // reversing right list
    while (rightNext)
    {
        middle->next = rightNext;
        rightNext = rightNext->next;
        middle->next->next = slow;
        slow = middle->next;
    }
}

void reorderList(ListNode* head)
{
    if (!head || !head->next || !head->next->next) return;

    ListNode* fast = head;
    ListNode* slow = head;
    ListNode* middle;
    ListNode* rightNext;
    ListNode* start = head;

    // finding middle
    while (fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    middle = slow;
    slow = slow->next;
    rightNext = slow->next;
    slow->next = nullptr;

    // reversing right list
    while (rightNext)
    {
        middle->next = rightNext;
        rightNext = rightNext->next;
        middle->next->next = slow;
        slow = middle->next;
    }

    while (middle->next)
    {
        rightNext = start->next;
        start->next = middle->next;
        start = start->next;
        middle->next = start->next;
        start->next = rightNext;
        start = rightNext;
    }
}

void ReorderList::program()
{
    LinkedList list;
    list.GenerateOrderedListMembers(0);
    list.PrintMembers();

    //reorderListAlloc(list.head);
    reorderList(list.head);
    list.PrintMembers();
}
