// LinkedListCycleII.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_set>
#include <chrono>
#include <cstdlib>

struct ListNode 
{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct LinkedList
{
    ListNode* head = NULL;
    ListNode* tail = NULL;
    int size = 0;

    void AddAtEnd(int x) 
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
        size++;
    }

    void SetLoop(int pos)
    {
        if (pos < 0) return;

        if (pos >= size)
        {
            std::cout << "Position exceedes size! Pos = " << pos << "; size = " << size << "; \n";
            return;
        }
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

    int GetNodeIndex(ListNode* node)
    {
        if (node == NULL) return -1;
        int currentIndex = 0;
        for (ListNode* currentNode = head; currentNode; currentNode = currentNode->next)
        {
            if (currentNode == node)
                return currentIndex;
            currentIndex++;
        }
    }
};

ListNode* detectCycle(ListNode* head)
{
    std::unordered_set<ListNode*> listItems;

    for (ListNode* currentItem = head; currentItem; currentItem = currentItem->next)
    {
        auto it = listItems.find(currentItem);
        if (it != listItems.end())
        {
            return currentItem;
        }
        listItems.emplace(currentItem);
    }
    return NULL;
}

ListNode* detectCycleFast(ListNode* head)
{
    ListNode* fastPointer = head;
    ListNode* slowPointer = head;

    while (fastPointer)
    {
        fastPointer = fastPointer->next;
        if (!fastPointer) { return NULL; }
        fastPointer = fastPointer->next;
        if (!fastPointer) { return NULL; }
        slowPointer = slowPointer->next;
        if (fastPointer == slowPointer)
        {
            break;
        }
    }

    slowPointer = head;
    while (fastPointer)
    {
        if (fastPointer == slowPointer)
        {
            return fastPointer;
        }
        fastPointer = fastPointer->next;
        slowPointer = slowPointer->next;
    }

    return NULL;
}

ListNode* detectCycleFastest(ListNode* head)
{
    ListNode* slow = head;
    ListNode* fast = head;
    ListNode* enter = head;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
        {
            while (enter != slow)
            {
                enter = enter->next;
                slow = slow->next;
            }
            return slow;
        }
    }
    return NULL;
}

void GenerateRandomListMembers(LinkedList& list, int memberCount)
{
    for (int i = 0; i < memberCount; i++)
    {
        list.AddAtEnd(std::rand());
    }
}

void SetRandomLoop(LinkedList& list)
{
    int randomLoopIndex = std::rand() % (list.size - 1);
    std::cout << "Generated index for loop = " << randomLoopIndex << "\n";
    list.SetLoop(randomLoopIndex);
}

int main()
{
    LinkedList list;
    /*list.AddAtEnd(1);
    list.AddAtEnd(2);
    list.AddAtEnd(3);
    list.AddAtEnd(4);
    list.AddAtEnd(5);
    list.AddAtEnd(6);
    list.AddAtEnd(7);
    list.AddAtEnd(8);
    list.AddAtEnd(9);
    list.SetLoop(4);*/
    GenerateRandomListMembers(list, 10000);
    SetRandomLoop(list);

    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;
    int nodeIndex;
    ListNode* cycleNode;

    std::cout << " === Executing hash map solution === \n";
    start = std::chrono::high_resolution_clock::now();
    cycleNode = detectCycle(list.head);
    end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = end - start;
    nodeIndex = list.GetNodeIndex(cycleNode);
    std::cout << "Tail connects to node index " << nodeIndex << "\n";
    std::cout << "Execution time was = " << std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_seconds).count() << " nanoseconds \n";

    std::cout << " === Executing fast cycle solution === \n";
    start = std::chrono::high_resolution_clock::now();
    cycleNode = detectCycleFast(list.head);
    end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = end - start;
    nodeIndex = list.GetNodeIndex(cycleNode);
    std::cout << "Tail connects to node index " << nodeIndex << "\n";
    std::cout << "Execution time was = " << std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_seconds).count() << " nanoseconds \n";

    std::cout << " === Executing fastest cycle solution === \n";
    start = std::chrono::high_resolution_clock::now();
    cycleNode = detectCycleFastest(list.head);
    end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = end - start;
    nodeIndex = list.GetNodeIndex(cycleNode);
    std::cout << "Tail connects to node index " << nodeIndex << "\n";
    std::cout << "Execution time was = " << std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_seconds).count() << " nanoseconds \n";
}
