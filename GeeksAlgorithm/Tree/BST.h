#ifndef GEEKS_BST_H
#define GEEKS_BST_H

#include <queue>
#include <cassert>

using namespace std;

// A basic concise introduction and links of related info
// https://en.wikipedia.org/wiki/Binary_search_tree

// Tree Terminology
// https://en.wikipedia.org/wiki/Tree_(data_structure)#Terminology

// Tree traversal: Pre-order, In-order, Post-order...
// https://en.wikipedia.org/wiki/Tree_traversal

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

		TreeNode(TreeNode *node)
		{
			this->key = node->key;
			this->value = node->value;
			this->left = node->left;
			this->right = node->right;
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
		destroy(m_root);
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

	// Depth-first search: Pre-order, In-order, Post-order
	// https://en.wikipedia.org/wiki/Tree_traversal
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

	// Breadth-first search: Level-order, In-order, Post-order
    // https://en.wikipedia.org/wiki/Tree_traversal
	void levelOrder()
	{
		if(m_root == nullptr)
			return;

		queue<TreeNode*> q;		
		q.emplace(m_root);
		while(!q.empty())
		{
			TreeNode* node = q.front();
			q.pop();

			nodeAction(node);

			if(node->left)
				q.emplace(node->left);
			if(node->right)
				q.emplace(node->right);
		}
	}

    Key minimum()
	{
        assert(m_root != nullptr);
        TreeNode* minNode = minimum(m_root);
        return minNode->key;
    }

    Key maximum()
	{
        assert(m_root != nullptr);
        TreeNode* maxNode = maximum(m_root);
        return maxNode->key;
    }

    void removeMin()
	{
        if(m_root)
            m_root = removeMin(m_root);
    }

    void removeMax()
	{
        if(m_root)
            m_root = removeMax(m_root);
    }

    void remove(Key key)
	{
        m_root = remove(m_root, key);
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
		cout<< "(" << node->key << "," << node->value << ") ";
	}

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

    // implemented as iteratively 
    TreeNode* minimum(TreeNode* node)
	{
		while(node->left)
			node = node->left;

		return node;
    }

	// implemented as recursively
    TreeNode* maximum(TreeNode* node)
	{
        if(node->right == nullptr)
			return node;

		return maximum(node->right);
    }

	// implemented as recursively
	// remove the min node from root node
    // return new root after deleted min node
    TreeNode* removeMin(TreeNode* node)
	{
		if(node->left == nullptr)
		{
			TreeNode * rightNode = node->right;
			delete node;
			--m_count;

			return rightNode;
		}

		node->left = removeMin(node->left);
		return node;
    }

	// implemented as iteratively
	// remove the max node from root node
    // return new root after deleted max node
    TreeNode* removeMax(TreeNode* node)
	{
		TreeNode* rootNode = node;
		TreeNode* parentNode = nullptr;
		while(node->right)
		{
			parentNode = node;
			node = node->right;
		}

		--m_count;
		TreeNode* leftNode = node->left;
		delete node;

		if(parentNode)
		{
			parentNode->right = leftNode;
			return rootNode;
		}
		else    // input node is root node
		{
			return leftNode;
		}
    }

	TreeNode* remove(TreeNode* node, Key key)
	{
		if(node == nullptr)
            return nullptr;

        if(key < node->key)
		{
            node->left = remove(node->left, key);
            return node;
        }
        else if(key > node->key)
		{
            node->right = remove(node->right, key);
            return node;
        }
        else   // key == node->key
		{
			TreeNode *successor = nullptr;
			if(node->left == nullptr)
			{
				successor = node->right;
			}
			else if(node->right == nullptr)
			{
				successor = node->left;
			}
			else   // node->left != nullptr && node->right != nullptr
			 
			// This page explains it very concisely and clearly
			// http://quiz.geeksforgeeks.org/binary-search-tree-set-2-delete/

			// Find inorder successor of the node, and copy contents of the 
			// inorder successor to the node and delete the inorder successor. 
			// In this particular case, inorder successor can be obtained by 
			// finding the minimum value in right child of the node.

			// Note that inorder predecessor can also be used.
			{
				successor = new TreeNode(minimum(node->right));
				++m_count;

				successor->right = removeMin(node->right);
				successor->left = node->left;
			}

			delete node;
            --m_count;

            return successor;
		}
    }

   // destroy the node as postOrder
   void destroy(TreeNode * node)
	{
        if(node == nullptr)
			return;

		destroy(node->left);
		destroy(node->right);
		delete node;
		--m_count;
    }

    TreeNode *m_root;
    int m_count;
};

#endif //GEEKS_BST_H