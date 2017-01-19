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

    Key* floor(Key key)
	{
        if(m_count == 0 || key < minimum())
            return nullptr;

        TreeNode *floorNode = floor(m_root, key);
        return &(floorNode->key);
    }

    Key* ceil(Key key)
	{
        if(m_count == 0 || key > maximum())
            return nullptr;

        TreeNode *ceilNode = ceil(m_root, key);
        return &(ceilNode->key);
    }

private:
	TreeNode* insert(TreeNode *root, Key key, Value value)
	{
		if(root == nullptr)
		{
			++m_count;
			return new TreeNode(key, value);
		}

		// This BST is that the key in each node must be 
		// greater than all keys stored in the left sub-tree, 
		// and not greater than any key in the right sub-tree
		if(root->key == key)
		{
			root->value = value;
			delete root;	// new root isn't added to the tree
		}
		else if(key < root->key)
		{
			root->left = insert(root->left, key, value);
		}
		else   // key > root->key
		{
			root->right = insert(root->right, key, value);
		}

		return root;
	}

	bool contain(TreeNode* root, Key key)
	{
        if(root == nullptr)
		{
			return false;
		}

		if(root->key == key)
		{
			return true;
		}
		else if(key < root->key)
		{
			return contain(root->left, key);
		}
		else   // key > root->key
		{
			return contain(root->right, key);
		}
    }

    Value* search(TreeNode* root, Key key)
	{
        if(root == nullptr)
		{
			return nullptr;
		}

		if(root->key == key)
		{
			return &(root->value);
		}
		else if(key < root->key)
		{
			return search(root->left, key);
		}
		else   // key > root->key
		{
			return search(root->right, key);
		}
    }

	// just a placeholder for actual usage
	void nodeAction(TreeNode * node)
	{
		cout<< "(" << node->key << "," << node->value << ") ";
	}

	void preOrder(TreeNode * root)
	{
        if(root == nullptr)
			return;
		
		nodeAction(root);
		preOrder(root->left);
		preOrder(root->right);
    }

    void inOrder(TreeNode * root)
	{
        if(root == nullptr)
			return;

		inOrder(root->left);
		nodeAction(root);
		inOrder(root->right);
    }

   void postOrder(TreeNode * root)
	{
        if(root == nullptr)
			return;

		postOrder(root->left);
		postOrder(root->right);
		nodeAction(root);
    }

    // implemented as iteratively 
    TreeNode* minimum(TreeNode* root)
	{
		while(root->left)
			root = root->left;

		return root;
    }

	// implemented as recursively
    TreeNode* maximum(TreeNode* root)
	{
        if(root->right == nullptr)
			return root;

		return maximum(root->right);
    }

	// implemented as recursively
	// remove the min node from root node
    // return new root after deleted min node
    TreeNode* removeMin(TreeNode* root)
	{
		if(root->left == nullptr)
		{
			TreeNode * rightNode = root->right;
			delete root;
			--m_count;

			return rightNode;
		}

		root->left = removeMin(root->left);
		return root;
    }

	// implemented as iteratively
	// remove the max root from root root
    // return new root after deleted max root
    TreeNode* removeMax(TreeNode* root)
	{
		TreeNode* rootNode = root;
		TreeNode* parentNode = nullptr;
		while(root->right)
		{
			parentNode = root;
			root = root->right;
		}

		--m_count;
		TreeNode* leftNode = root->left;
		delete root;

		if(parentNode)
		{
			parentNode->right = leftNode;
			return rootNode;
		}
		else    // input root is root root
		{
			return leftNode;
		}
    }

	TreeNode* remove(TreeNode* root, Key key)
	{
		if(root == nullptr)
            return nullptr;

        if(key < root->key)
		{
            root->left = remove(root->left, key);
            return root;
        }
        else if(key > root->key)
		{
            root->right = remove(root->right, key);
            return root;
        }
        else   // key == root->key
		{
			TreeNode *successor = nullptr;
			if(root->left == nullptr)
			{
				successor = root->right;
			}
			else if(root->right == nullptr)
			{
				successor = root->left;
			}
			else   // root->left != nullptr && root->right != nullptr
			 
			// This page explains it very concisely and clearly
			// http://quiz.geeksforgeeks.org/binary-search-tree-set-2-delete/

			// Find inorder successor of the root, and copy contents of the 
			// inorder successor to the root and delete the inorder successor. 
			// In this particular case, inorder successor can be obtained by 
			// finding the minimum value in right child of the root.

			// Note that inorder predecessor can also be used.
			{
				successor = new TreeNode(minimum(root->right));
				++m_count;

				successor->right = removeMin(root->right);
				successor->left = root->left;
			}

			delete root;
            --m_count;

            return successor;
		}
    }

	// Find key's floor in the bst that root is the root
    TreeNode* floor(TreeNode* root, Key key)
	{
        if(root == nullptr)
            return nullptr;

		if(root->key == key)
            return root;
		else if(root->key > key)
            return floor(root->left , key);
		else // root->key < key
		{       
			// root may be key's floor
			// root->key may be greater and less than key, so need try root->right
			TreeNode* tempNode = floor(root->right , key);
			if(tempNode != nullptr)
				return tempNode;
			else
				return root;
		}
    }

    // Find key's cell in the bst that root is the root
    TreeNode* ceil(TreeNode* root, Key key)
	{
        if(root == nullptr)
            return nullptr;

        if(root->key == key)
            return root;
        else if(root->key < key)
            return ceil(root->right , key);
		else    // root->key > key
        {			
			// root may be key's ceil root, 
			// root->key may be less and greater than key, so need try root->left
			TreeNode* tempNode = ceil(root->left , key);
			if(tempNode != nullptr)
				return tempNode;
			else
				return root;
		}
        
    }

   // destroy the root as postOrder
   void destroy(TreeNode * root)
	{
        if(root == nullptr)
			return;

		destroy(root->left);
		destroy(root->right);
		delete root;
		--m_count;
    }

    TreeNode *m_root;
    int m_count;
};

#endif //GEEKS_BST_H