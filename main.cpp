//Jongmin Han didn't write this code. But he translated comments.
//This code is from http://blog.naver.com/PostView.nhn?blogId=7005ye&logNo=220691962788&categoryNo=59&parentCategoryNo=0&viewDate=&currentPage=1&postListTopCurrentPage=1&from=postView
#include <iostream>
using namespace std;

class TreeNode
{
    friend class Tree;
private:
    int mValue;
    TreeNode* mLeft;
    TreeNode* mRight;
    TreeNode(int val) : mValue(val), mLeft(nullptr), mRight(nullptr) {} //Constructor
};

class Tree
{
private:
    TreeNode* mRoot;
    void insertNodeRecursive(TreeNode*&, int);
    void removeNodeRecursive(TreeNode*&, int);
    void printPreorderRecursive(TreeNode*);
    void printPostorderRecursive(TreeNode*);
    void printInorderRecursive(TreeNode*);
public:
    Tree() : mRoot(nullptr) {}   //Constructor
    void InsertNode(int);
    void RemoveNode(int);
    void PrintPreorder();
    void PrintPostorder();
    void PrintInorder();
};

void Tree::insertNodeRecursive(TreeNode*& node, int val)
{
    if (node == nullptr)
    {
        node = new TreeNode(val); //Make new node if the current node is nullptr.(Insertion)
    }
    else if (val > node->mValue)
    {
        insertNodeRecursive(node->mRight, val); //If the value to insert is larger than current node value, then search right subtree.
    }
    else if (val < node->mValue)
    {
        insertNodeRecursive(node->mLeft, val);  //If the value to insert is less than current node value, then search left subtree.
    }
}

void Tree::removeNodeRecursive(TreeNode*& node, int val)
{
    TreeNode* removal = nullptr;

    if (node == nullptr)
    {
        return;     //End the function when the value is not found.
    }
    else if (val > node->mValue)
    {
        removeNodeRecursive(node->mRight, val); //If the value is larger than current node value, then search right subtree.
    }
    else if (val < node->mValue)
    {
        removeNodeRecursive(node->mLeft, val);  //If the value is less than current node value, then search left subtree.
    }
    else    //If the node was found, then there can be 3 cases.
    {
        if (node->mLeft == nullptr && node->mRight == nullptr)  //Case 1: Node doesn't have any child.
        {
            delete node;
            node = nullptr;
        }
        else if (node->mLeft == nullptr)  //Case 2-1: Node only has right child.
        {
            removal = node;
            node = node->mRight;
            delete removal;
        }
        else if (node->mRight == nullptr)  //Case 2-2: Node only has left child.
        {
            removal = node;
            node = node->mLeft;
            delete removal;
        }
        else    //Case 3: Node has two childs.
        {
            removal = node->mRight;
            while (removal->mLeft != nullptr)  //Find a node which has minimum value in the right subtree.
            {
                removal = removal->mLeft;
            }

            int minVal = removal->mValue;  //Save minimum value.
            removeNodeRecursive(mRoot, minVal);  //Remove mimnimum node.
            node->mValue = minVal;  //Override minimum value to node value which has an actual value removed.
        }
    }
}

void Tree::printPreorderRecursive(TreeNode* node)
{
    if (node != nullptr)
    {
        cout << node->mValue << endl;  //Visit root.
        printPreorderRecursive(node->mLeft);  //Traverse left subtree.
        printPreorderRecursive(node->mRight);  //Traverse right subtree.
    }
}

void Tree::printPostorderRecursive(TreeNode* node)
{
    if (node != nullptr)
    {
        printPostorderRecursive(node->mLeft);  //Traverse left subtree.
        printPostorderRecursive(node->mRight);  //Traverse right subtree.
        cout << node->mValue << endl;  //Visit root.
    }
}

void Tree::printInorderRecursive(TreeNode* node)
{
    if (node != nullptr)
    {
        printInorderRecursive(node->mLeft);  //Traverse left subtree.
        cout << node->mValue << endl;  //Visit root.
        printInorderRecursive(node->mRight);  //Traverse right subtree.
    }
}


////////////WRAPPING FUNCTIONS///////////////

void Tree::InsertNode(int val)
{
    insertNodeRecursive(mRoot, val);
}

void Tree::RemoveNode(int val)
{
    removeNodeRecursive(mRoot, val);
}

void Tree::PrintPreorder()
{
    cout << "PREORDER" << endl;
    printPreorderRecursive(mRoot);
}

void Tree::PrintInorder()
{
    cout << "INORDER" << endl;
    printInorderRecursive(mRoot);
}

void Tree::PrintPostorder()
{
    cout << "POSTORDER" << endl;
    printPostorderRecursive(mRoot);
}


int main()
{
    Tree* tr = new Tree();

    tr->InsertNode(50);
    tr->InsertNode(47);
    tr->InsertNode(53);
    tr->InsertNode(51);
    tr->InsertNode(55);
    tr->InsertNode(30);
    tr->InsertNode(49);
    tr->InsertNode(48);
    tr->InsertNode(35);
    tr->InsertNode(20);

//    		50
//            ↙     ↘
//    	   47		   53
//       ↙   ↘       ↙  ↘
//     30	  49	51	  55
//    ↙ ↘   ↙
//  20   35 48

    tr->PrintPostorder();
    tr->PrintPreorder();
    tr->PrintInorder();

    tr->RemoveNode(53);

    tr->PrintPostorder();
    tr->PrintPreorder();
    tr->PrintInorder();

    delete tr;
    return 0;
}
