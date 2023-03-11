#include "pch.h"
#include "LinkedListCycleII.h"

#include "Structures/LinkedList/LinkedList.h"

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

void LinkedListCycleII::program()
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
    list.GenerateRandomListMembers(10000);
    list.SetRandomLoop();

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
