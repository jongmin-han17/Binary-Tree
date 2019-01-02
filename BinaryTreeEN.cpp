//Jongmin Han didn't write this code. But he translated comments.
//This code is from http://blog.naver.com/PostView.nhn?blogId=7005ye&logNo=220691962788&categoryNo=59&parentCategoryNo=0&viewDate=&currentPage=1&postListTopCurrentPage=1&from=postView
#include <iostream>
using namespace std;

class treeNode
{
    friend class tree;
private:
    int value;
    treeNode* left;
    treeNode* right;
    treeNode(int val) : value(val), left(nullptr), right(nullptr) {}   // Constructor
};

class tree
{
private:
    treeNode* root;
    void recursiveInsert(treeNode*&, int);
    void recursiveRemove(treeNode*&, int);
    void preorderRecursivePrint(treeNode*);
    void postorderRecursivePrint(treeNode*);
    void inorderRecursivePrint(treeNode*);
public:
    tree() : root(nullptr) { }   //Constructor
    void insert(int);
    void remove(int);
    void preorderPrint();
    void postorderPrint();
    void inorderPrint();
};

void tree::recursiveInsert(treeNode*& node, int val)
{
    if (node == nullptr)
        node = new treeNode(val);   //Make new node if the current node is nullptr.(Insertion)
    else if (val > node->value)
        recursiveInsert(node->right, val);   //If the value to insert is larger than current node value, then search right subtree.
    else if (val < node->value)
        recursiveInsert(node->left, val);   //If the value to insert is less than current node value, then search left subtree.
}

void tree::recursiveRemove(treeNode*& node, int val)
{
    treeNode* removal = new treeNode(0);

    if (node == nullptr)
        return;      //End the function when the value is not found.
    else if (val > node->value)
        recursiveRemove(node->right, val);   //If the value is larger than current node value, then search right subtree.
    else if (val < node->value)
        recursiveRemove(node->left, val);   //If the value is less than current node value, then search left subtree.

    else //If the node was found, then there can be 3 cases.
    {
        if (node->left == nullptr && node->right == nullptr) //Case 1: Node doesn't have any child.
        {
            delete node;
            node = nullptr;
        }

        else if (node->left == nullptr)   //Case 2-1: Node only has right child.
        {
            removal = node;
            node = node->right;
            delete removal;
        }
        else if (node->right == nullptr)   //Case 2-2: Node only has left child.
        {
            removal = node;
            node = node->left;
            delete removal;
        }
        else                     //Case 3: Node has two childs.
        {
            removal = node->right;
            while (removal->left != nullptr)   //Find a node which has minimum value in the right subtree.
                removal = removal->left;

            int minVal = removal->value;   //Save minimum value.
            recursiveRemove(root, minVal);   //Remove mimnimum node.
            node->value = minVal;         //Override minimum value to node value which has an actual value removed.
        }
    }
}

void tree::preorderRecursivePrint(treeNode* node)
{
    if (node != nullptr)
    {
        cout << node->value << endl;      //Visit root.
        preorderRecursivePrint(node->left);   //Traverse left subtree.
        preorderRecursivePrint(node->right);  //Traverse right subtree.
    }
}

void tree::inorderRecursivePrint(treeNode* node)
{
    if (node != nullptr)
    {
        inorderRecursivePrint(node->left);   //Traverse left subtree.
        cout << node->value << endl;         //Visit root.
        inorderRecursivePrint(node->right);  //Traverse right subtree.
    }
}

void tree::postorderRecursivePrint(treeNode* node)
{
    if (node != nullptr)
    {
        postorderRecursivePrint(node->left); 	//Traverse left subtree.
        postorderRecursivePrint(node->right);	//Traverse right subtree.
        cout << node->value << endl;       		//Visit root.
    }
}



//////////////////////WRAPPING FUNCTIONS//////////////////////////

void tree::insert(int val)
{
    recursiveInsert(root, val);
}

void tree::remove(int val)
{
    recursiveRemove(root, val);
}

void tree::preorderPrint()
{
    cout << "PREORDER" << endl;
    preorderRecursivePrint(root);
}

void tree::inorderPrint()
{
    cout << "INORDER" << endl;
    inorderRecursivePrint(root);
}

void tree::postorderPrint()
{
    cout << "POSTORDER" << endl;
    postorderRecursivePrint(root);
}

int main()
{
    tree* tr = new tree();

    tr->insert(50);
    tr->insert(47);
    tr->insert(53);
    tr->insert(51);
    tr->insert(55);
    tr->insert(30);
    tr->insert(49);
    tr->insert(48);
    tr->insert(35);
    tr->insert(20);

//    			50
//            ↙     ↘
//    	   47		   53
//       ↙   ↘       ↙  ↘
//     30	  49	51	  55
//    ↙ ↘   ↙
//  20   35 48

    tr->postorderPrint();
    tr->preorderPrint();
    tr->inorderPrint();

    tr->remove(53);

    tr->postorderPrint();
    tr->preorderPrint();
    tr->inorderPrint();


    delete tr;
    return 0;
}
