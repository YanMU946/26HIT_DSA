#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

template <class T>
struct TreeNode
{
    typedef TreeNode<T> node;
    T val;
    node* left;
    node* right;

    TreeNode(const T& _val, node* _left = nullptr, node* _right = nullptr)
        : val(_val), left(_left), right(_right)
    {
    }
};

template <class T>
class Tree
{
    using self = Tree<T>;
    using node = TreeNode<T>;

public:
    Tree(const string& _val)
    {
        int pos = 0;
        root = Prev_Est(_val, pos);
    }

    ~Tree(void) { Destroy(root); }

    node* Prev_Est(const string& _val, int& _pos)
    {
        if (_val[_pos] == '#')
        {
            _pos++;
            return nullptr;
        }
        node* cur = new node(_val[_pos++]);
        cur->left = Prev_Est(_val, _pos);
        cur->right = Prev_Est(_val, _pos);
        return cur;
    }

    void Destroy(node*& _node)
    {
        if (_node == nullptr)return;
        else
        {
            Destroy(_node->left);
            Destroy(_node->right);
            delete _node;
            _node = nullptr;
        }
    }

    node* Get_Root(void) { return root; }

    void PreOrder_Print(node* _node)
    {
        if (_node == nullptr)
        {
            // cout << "# ";
            return;
        }
        cout << _node->val << " ";
        PreOrder_Print(_node->left);
        PreOrder_Print(_node->right);
    }

    void InOrder_Print(node* _node)
    {
        if (_node == nullptr)
        {
            // cout << "# ";
            return;
        }
        InOrder_Print(_node->left);
        cout << _node->val << " ";
        InOrder_Print(_node->right);
    }

    void PostOrder_Print(node* _node)
    {
        if (_node == nullptr)
        {
            // cout << "# ";
            return;
        }
        PostOrder_Print(_node->left);
        PostOrder_Print(_node->right);
        cout << _node->val << " ";
    }

    void PreOrder_Print_N(void)
    {
        std::stack<node*> st_tree;
        st_tree.push(root);
        while (!st_tree.empty())
        {
            node* cur = st_tree.top();
            st_tree.pop();
            if (cur->right != nullptr)
                st_tree.push(cur->right);
            if (cur->left != nullptr)
                st_tree.push(cur->left);
            cout << cur->val << " ";
        }
        cout << endl;
    }

    void InOrder_Print_N(void)
    {
        std::stack<node*> st_tree;
        st_tree.push(root);
        while (!st_tree.empty())
        {
            node* cur = st_tree.top();
            st_tree.pop();
            if (cur == nullptr)
            {
                if (st_tree.empty()) break;
                cur = st_tree.top();
                st_tree.pop();
                cout << cur->val << " ";
            }
            else
            {
                st_tree.push(cur->right);
                st_tree.push(cur);
                st_tree.push(cur->left);
            }
        }
        cout << endl;
    }

    void PostOrder_Print_N(void)
    {
        std::stack<node*> st_tree;
        node* cur = root;
        node* prev = nullptr;
        while (cur != nullptr || !st_tree.empty())
        {
            while (cur != nullptr)
            {
                st_tree.push(cur);
                cur = cur->left;
            }
            node* k = st_tree.top();
            if (k->right == nullptr || k->right == prev)
            {
                cout << k->val << " ";
                st_tree.pop();
                prev = k;
            }
            else
                cur = k->right;
        }
        cout << endl;
    }

    void BFS(void)
    {
        std::queue<node*> q_tree;
        q_tree.push(root);
        while (!q_tree.empty())
        {
            node* cur = q_tree.front();
            q_tree.pop();
            if (cur->left != nullptr)
                q_tree.push(cur->left);
            if (cur->right != nullptr)
                q_tree.push(cur->right);
            cout << cur->val << " ";
        }
        cout << endl;
    }

private:
    node* root;
};

#endif /* end bt */
