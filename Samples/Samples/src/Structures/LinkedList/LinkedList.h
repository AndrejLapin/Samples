#pragma once


struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

struct LinkedList
{
    ~LinkedList();

    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    int m_Size = 0;
    int m_LoopPos = -1;

    void AddAtEnd(int x);

    void SetLoop(int pos);

    int GetNodeIndex(ListNode* node);

    void GenerateRandomListMembers(int memberCount);
    void GenerateOrderedListMembers(int memberCount);

    void SetRandomLoop();

    void PrintMembers();
};