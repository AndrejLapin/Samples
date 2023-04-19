#include "pch.h"
#include "BTPreorderTrav.h"

#include "Structures/Binarytree/BinaryTree.h"

std::vector<int> orderTraversal(TreeNode* root) {
    if (!root) return std::vector<int>();

    std::vector<TreeNode*> queueA;
    std::vector<TreeNode*> queueB;
    queueA.reserve(100);
    queueB.reserve(100);
    std::vector<int> outputVector;
    outputVector.reserve(100);

    std::vector<TreeNode*>* currentQueue = &queueA;
    std::vector<TreeNode*>* nextQueue = &queueB;
    std::vector<TreeNode*>* tempVec = nullptr;

    outputVector.push_back(root->val);
    if (root->left)
    {
        currentQueue->push_back(root->left);
    }

    if (root->right)
    {
        currentQueue->push_back(root->right);
    }

    bool loop = true;

    while (loop)
    {
        for (auto& node : *currentQueue)
        {
            outputVector.push_back(node->val);
            if (node->left)
            {
                nextQueue->push_back(node->left);
            }

            if (node->right)
            {
                nextQueue->push_back(node->right);
            }
        }
        currentQueue->clear();
        tempVec = currentQueue;
        currentQueue = nextQueue;
        nextQueue = tempVec;
        if (currentQueue->size() < 1)
        {
            loop = false;
        }
    }

    return outputVector;
}

std::vector<int> preorderTraversal(TreeNode* root) {
    if (!root) return std::vector<int>();

    std::vector<TreeNode*> rightNodeQueue;
    rightNodeQueue.reserve(10);
    std::vector<int> outputVector;
    outputVector.reserve(100);

    TreeNode* currentNode = root;

    while (currentNode)
    {
        outputVector.push_back(currentNode->val);
        if (currentNode->left)
        {
            if (currentNode->right)
            {
                rightNodeQueue.push_back(currentNode->right);
            }
            currentNode = currentNode->left;
            continue;
        }
        else if (currentNode->right)
        {
            currentNode = currentNode->right;
            continue;
        }
        else if (rightNodeQueue.size() > 0)
        {
            auto it = --rightNodeQueue.end();
            currentNode = *it;
            rightNodeQueue.erase(it);
        }
        else
        {
            currentNode = nullptr;
        }
    }

    return outputVector;
}

void BTPreorderTrav::program()
{

}
