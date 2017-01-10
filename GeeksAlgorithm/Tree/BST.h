#ifndef GEEKS_BST_H
#define GEEKS_BST_H

#include <algorithm>

using namespace std;

// A basic concise introduction and links of related info
// https://en.wikipedia.org/wiki/Binary_search_tree

// Tree Terminology
// https://en.wikipedia.org/wiki/Tree_(data_structure)#Terminology

// Tree traversal: Pre-order, In-order, Post-order...
// https://en.wikipedia.org/wiki/Pre-order_traversal

template <typename Key, typename Value>
class BST
{
private:
	struct TreeNode
	{
		Key key;
		Value value;
		TreeNode *left;
		TreeNode *right;

		TreeNode(Key key, Value value)
		{
			this->key = key;
			this->value = value;
			this->left = this->right = nullptr;
		}
	};

public:
	BST()
	{
		m_count = 0;
		m_root = nullptr;
	}

	~BST()
	{
		// TODO
	}

	bool isEmpty()
	{
		return m_count == 0;	
	}

	int size()
	{
		return m_count;
	}
	
	void insert(Key key, Value value)
	{
		m_root = insert(m_root, key, value);
	}

	bool contain(Key key)
	{
        return contain(m_root, key);
    }

    Value* search(Key key)
	{
        return search(m_root, key);
    }

    void preOrder()
	{
        preOrder(m_root);
    }

    void inOrder()
	{
        inOrder(m_root);
    }

    void postOrder()
	{
        postOrder(m_root);
    }

    void printData(){        
        cout<<"The tree size is: " << size() << endl;
        cout<<"Root data in tree: ";
		cout<< "root (" << m_root->key << "," << m_root->value << ")" <<  endl;
		cout<< "left (" << m_root->left->key << "," << m_root->left->value << ")" <<  endl;
		cout<< "right (" << m_root->right->key << "," << m_root->right->value << ")" <<  endl;
		//int level = 0;
        //for(int i = 0 ; i <= size() ; ++i)
		{
   //         cout<<m_pData[i]<<" ";
			//if(pow(2, level) == i)
			//{
			//	++level;
			//	cout<<endl;
			//}
		}
        cout<<endl;
    }

private:
	TreeNode* insert(TreeNode *node, Key key, Value value)
	{
		if(node == nullptr)
		{
			++m_count;
			return new TreeNode(key, value);
		}

		// This BST is that the key in each node must be 
		// greater than all keys stored in the left sub-tree, 
		// and not greater than any key in the right sub-tree
		if(node->key == key)
		{
			node->value = value;
		}
		else if(key < node->key)
		{
			node->left = insert(node->left, key, value);
		}
		else   // key > node->key
		{
			node->right = insert(node->right, key, value);
		}

		return node;
	}

	bool contain(TreeNode* node, Key key)
	{
        if(node == nullptr)
		{
			return false;
		}

		if(node->key == key)
		{
			return true;
		}
		else if(key < node->key)
		{
			return contain(node->left, key);
		}
		else   // key > node->key
		{
			return contain(node->right, key);
		}
    }

    Value* search(TreeNode* node, Key key)
	{
        if(node == nullptr)
		{
			return nullptr;
		}

		if(node->key == key)
		{
			return &(node->value);
		}
		else if(key < node->key)
		{
			return search(node->left, key);
		}
		else   // key > node->key
		{
			return search(node->right, key);
		}
    }

	// just a placeholder for actual usage
	void nodeAction(TreeNode * node)
	{
		cout<< "(" << node->key << "," << node->value << ")" <<  endl;
	}

	// Tree traversal: Pre-order, In-order, Post-order
	// https://en.wikipedia.org/wiki/Pre-order_traversal
	void preOrder(TreeNode * node)
	{
        if(node == nullptr)
			return;
		
		nodeAction(node);
		preOrder(node->left);
		preOrder(node->right);
    }

    void inOrder(TreeNode * node)
	{
        if(node == nullptr)
			return;

		inOrder(node->left);
		nodeAction(node);
		inOrder(node->right);
    }

   void postOrder(TreeNode * node)
	{
        if(node == nullptr)
			return;

		postOrder(node->left);
		postOrder(node->right);
		nodeAction(node);
    }

    TreeNode *m_root;
    int m_count;
};

#endif //GEEKS_BST_H