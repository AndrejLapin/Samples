#include "pch.h"
#include "BinaryTree.h"

void BinaryTree::CombineNodes(std::vector<TreeNode*>& nodes)
{
    if (nodes.size() < 1) return;
    if (root)
    {
        std::cout << "Binary tree already constructed!\n";
        return;
    }
    root = nodes[0];
    std::vector<TreeNode*> nodesA, nodesB;
    nodesA.reserve(100);
    nodesB.reserve(100);

    std::vector<TreeNode*>* currentRow = &nodesA;
    std::vector<TreeNode*>* nextRow = &nodesB;
    std::vector<TreeNode*>* tempVec = nullptr;

    currentRow->push_back(root->left);
    currentRow->push_back(root->right);

    int parentNodeIndex = 0;
    for (int nodeIndex = 1; nodeIndex < nodes.size(); nodeIndex++)
    {
        TreeNode* currentNode = nodes[nodeIndex];
        if (!currentNode) continue;
        TreeNode* currentParentNode = (*currentRow)[parentNodeIndex];
        currentParentNode = currentNode;
        nextRow->push_back(currentParentNode->left);
        nextRow->push_back(currentParentNode->right);

        parentNodeIndex++;
        if (parentNodeIndex > currentRow->size())
        {
            currentRow->clear();
            tempVec = currentRow;
            currentRow = nextRow;
            nextRow = tempVec;
        }
    }
}
