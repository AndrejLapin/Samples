#include "pch.h"
#include "LinkedList.h"

LinkedList::~LinkedList()
{
    while (head != tail)
    {
        ListNode* deleteNode = head;
        head = head->next;
        delete deleteNode;
    }
    delete tail;
}

void LinkedList::AddAtEnd(int x)
{
    if (!head)
    {
        ListNode* listNode = new ListNode(x);
        head = listNode;
        tail = listNode;
    }
    else
    {
        tail->next = new ListNode(x);
        tail = tail->next;
    }
    m_Size++;
}

void LinkedList::SetLoop(int pos)
{
    if (pos < 0) return;

    if (pos >= m_Size)
    {
        std::cout << "Position exceedes size! Pos = " << pos << "; size = " << m_Size << "; \n";
        return;
    }

    if (m_LoopPos != -1)
    {
        std::cout << "Loop has already been set up for this list!\n";
        return;
    }

    m_LoopPos = pos;
    int currentIndex = 0;
    for (ListNode* currentNode = head; currentNode; currentNode = currentNode->next)
    {
        if (currentIndex == pos)
        {
            tail->next = currentNode;
            return;
        }
        currentIndex++;
    }
}

int LinkedList::GetNodeIndex(ListNode* node)
{
    if (node == nullptr) return -1;
    int currentIndex = 0;
    for (ListNode* currentNode = head; currentNode; currentNode = currentNode->next)
    {
        if (currentNode == node)
            return currentIndex;
        currentIndex++;
    }
}

void LinkedList::GenerateRandomListMembers(int memberCount)
{
    for (int i = 0; i < memberCount; i++)
    {
        AddAtEnd(std::rand());
    }
}

void LinkedList::GenerateOrderedListMembers(int memberCount)
{
    for (int i = 0; i < memberCount; i++)
    {
        AddAtEnd(i);
    }
}

void LinkedList::SetRandomLoop()
{
    int randomLoopIndex = std::rand() % (m_Size - 1);
    std::cout << "Generated index for loop = " << randomLoopIndex << "\n";
    SetLoop(randomLoopIndex);
}

void LinkedList::PrintMembers()
{
    ListNode* current = head;
    bool first = true;
    for (int i = 0; i < m_Size; i++)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            std::cout << "->";
        }

        if (i == m_LoopPos)
        {
            std::cout << "(:loops:" << current->val << ")";
        }
        else
        {
            std::cout << "(" << current->val << ")";
        }
        current = current->next;
    }
    std::cout << "\n";
}
