#ifndef GEEKS_RBT_H
#define GEEKS_RBT_H

#include <queue>
#include <cassert>

using namespace std;

// A basic concise introduction and links of related info
// https://en.wikipedia.org/wiki/Red-black_tree
// http://www.geeksforgeeks.org/red-black-tree-set-1-introduction-2/

/* 5 basic rules:
1. Each node is either red or black.
2. The root is black.
3. There are no two adjacent red nodes (A red node cannot have a red parent or red child).
4. Every path from a given node to any of its descendant NIL nodes contains the same number of black nodes. 
5. All leaves (NIL) are black.

Comparison with AVL Tree
The AVL trees are more balanced compared to Red Black Trees, but they may cause more rotations during insertion and deletion. 
So if your application involves many frequent insertions and deletions, then Red Black trees should be preferred. 
And if the insertions and deletions are less frequent and search is more frequent operation, then AVL tree should be preferred over Red Black Tree.
*/

template <typename Key, typename Value>
class RBT
{
private:
	enum Color
	{
		RED, 
		BLACK
	};

	struct TreeNode
	{
		Key key;
		Value value;
		Color color;
		TreeNode *left;
		TreeNode *right;
		TreeNode *parent;

		TreeNode(Key key, Value value)
		{
			this->key = key;
			this->value = value;
			this->color = RED;
			this->left = this->right = this->parent = nullptr;
		}

		TreeNode(TreeNode *node)
		{
			this->key = node->key;
			this->value = node->value;
			this->color = node->color;
			this->left = node->left;
			this->right = node->right;
			this->right = node->parent;
		}
	};

public:
	RBT()
	{
		m_count = 0;
		m_root = nullptr;
	}

	~RBT()
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
		TreeNode *node = new TreeNode(key, value);
		m_root = insert(m_root, node);

		fixViolation(m_root, node);
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
	TreeNode* insert(TreeNode *root, TreeNode *node)
	{
		if(root == nullptr)
		{
			++m_count;
			return node;
		}

		// This BST is that the key in each root must be 
		// greater than all keys stored in the left sub-tree, 
		// and not greater than any key in the right sub-tree
		if(node->key == root->key)
		{
			root->value = node->value;
		}
		else if(node->key < root->key)
		{
			root->left = insert(root->left, node);
			root->left->parent = root;
		}
		else   // key > root->key
		{
			root->right = insert(root->right, node);
			root->right->parent = root;
		}

		return root;
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
		cout<< "(" << node->key << "," << node->value << "," << ((node->color == RED) ? "R" : "B") << ") ";
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

	// Find key's floor in the bst that node is the root
    TreeNode* floor(TreeNode* node, Key key)
	{
        if(node == nullptr)
            return nullptr;

		if(node->key == key)
            return node;
		else if(node->key > key)
            return floor(node->left , key);
		else // node->key < key
		{       
			// node may be key's floor
			// node->key may be greater and less than key, so need try node->right
			TreeNode* tempNode = floor(node->right , key);
			if(tempNode != nullptr)
				return tempNode;
			else
				return node;
		}
    }

    // Find key's cell in the bst that node is the root
    TreeNode* ceil(TreeNode* node, Key key)
	{
        if(node == nullptr)
            return nullptr;

        if(node->key == key)
            return node;
        else if(node->key < key)
            return ceil(node->right , key);
		else    // node->key > key
        {
			
			// node may be key's ceil node, 
			// node->key may be less and greater than key, so need try node->left
			TreeNode* tempNode = ceil(node->left , key);
			if(tempNode != nullptr)
				return tempNode;
			else
				return node;
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

	// http://www.geeksforgeeks.org/red-black-tree-set-2-insert/
    void fixViolation(TreeNode * &root, TreeNode *&node)
	{
		TreeNode *parentNode = nullptr;
		TreeNode *grandParentNode = nullptr;
 
		while ((node != root) && (node->color != BLACK) &&
			   (node->parent->color == RED))
		{
 			parentNode = node->parent;
			grandParentNode = node->parent->parent;
 
			/*  Case : A
				Parent of node is left child of Grand-parent of node */
			if (parentNode == grandParentNode->left)
			{
				TreeNode *uncleNode = grandParentNode->right;
 
				/* Case : 1
				   The uncle of node is also red
				   Only Recoloring required */
				if (uncleNode != nullptr && uncleNode->color == RED)
				{
					grandParentNode->color = RED;
					parentNode->color = BLACK;
					uncleNode->color = BLACK;
					node = grandParentNode;
				}
				else
				{
					/* Case : 2
					   node is right child of its parent
					   Left-rotation required */
					if (node == parentNode->right)
					{
						rotateLeft(root, parentNode);
						node = parentNode;
						parentNode = node->parent;
					}
 
					/* Case : 3
					   node is left child of its parent
					   Right-rotation required */
					rotateRight(root, grandParentNode);
					swap(parentNode->color, grandParentNode->color);
					node = parentNode;
				}
			}
 
			/* Case : B
			   Parent of node is right child of Grand-parent of node */
			else
			{
				TreeNode *uncleNode = grandParentNode->left;
 
				/*  Case : 1
					The uncle of node is also red
					Only Recoloring required */
				if ((uncleNode != nullptr) && (uncleNode->color == RED))
				{
					grandParentNode->color = RED;
					parentNode->color = BLACK;
					uncleNode->color = BLACK;
					node = grandParentNode;
				}
				else
				{
					/* Case : 2
					   node is left child of its parent
					   Right-rotation required */
					if (node == parentNode->left)
					{
						rotateRight(root, parentNode);
						node = parentNode;
						parentNode = node->parent;
					}
 
					/* Case : 3
					   node is right child of its parent
					   Left-rotation required */
					rotateLeft(root, grandParentNode);
					swap(parentNode->color, grandParentNode->color);
					node = parentNode;
				}
			}
		}
 
		root->color = BLACK;
	}

	void rotateLeft(TreeNode * &root, TreeNode *&node)
	{
		TreeNode *rightNode = node->right;
 
		node->right = rightNode->left;
 
		if (node->right != nullptr)
			node->right->parent = node;
 
		rightNode->parent = node->parent;
 
		if (node->parent == nullptr)
			root = rightNode;
		else if (node == node->parent->left)
			node->parent->left = rightNode;
		else
			node->parent->right = rightNode;
 
		rightNode->left = node;
		node->parent = rightNode;
	}
 
	void rotateRight(TreeNode * &root, TreeNode *&node)
	{
		TreeNode *leftNode = node->left;
 
		node->left = leftNode->right;
 
		if (node->left != nullptr)
			node->left->parent = node;
 
		leftNode->parent = node->parent;
 
		if (node->parent == nullptr)
			root = leftNode;
 
		else if (node == node->parent->left)
			node->parent->left = leftNode;
		else
			node->parent->right = leftNode;
 
		leftNode->right = node;
		node->parent = leftNode;
	}

    TreeNode *m_root;
    int m_count;
};

#endif //GEEKS_RBT_H