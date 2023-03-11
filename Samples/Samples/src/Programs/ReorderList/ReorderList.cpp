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

void reorderList(ListNode* head)
{

}

void ReorderList::program()
{
    LinkedList list;
    list.GenerateOrderedListMembers(4);
    list.PrintMembers();

    reorderListAlloc(list.head);
    list.PrintMembers();
}
