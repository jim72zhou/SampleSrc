#ifndef GEEKS_AVL_H
#define GEEKS_AVL_H

#include <queue>
#include <cassert>

using namespace std;

// https://en.wikipedia.org/wiki/AVL_tree
// http://www.geeksforgeeks.org/avl-tree-set-1-insertion/
// http://www.geeksforgeeks.org/avl-tree-set-2-deletion/
// https://www.cs.purdue.edu/homes/ayg/CS251/slides/chap7b.pdf

/* 2 preconditions:
1. AVL tree is a self-balancing Binary Search Tree (BST)
2. The difference between heights of left and right subtrees cannot be more than one for all nodes.

For lookup-intensive applications, AVL trees are faster than red–black trees because they are
more strictly balanced. Similar to red–black trees, AVL trees are height-balanced.
AVL trees are more rigidly balanced than red–black trees, leading to faster retrieval but slower insertion and deletion.
*/

template <typename Key, typename Value>
class AVL
{
private:
	struct TreeNode
	{
		Key key;
		Value value;
		int height;
		TreeNode *left;
		TreeNode *right;
		
		TreeNode(Key key, Value value)
		{
			this->key = key;
			this->value = value;
			this->height = 1;
			this->left = this->right = nullptr;
		}
	};

public:
	AVL()
	{
		m_count = 0;
		m_root = nullptr;
	}

	~AVL()
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
	
	int height()
	{
		return height(m_root);
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
        TreeNode* node = search(m_root, key);
		if(node)
			return &(node->value);
		else
			return nullptr;
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

			if(node->left != nullptr)
				q.emplace(node->left);
			if(node->right != nullptr)
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

    void remove(Key key)
	{
		m_root = remove(m_root, key);
    }

	void removeMin()
	{
		remove(minimum());
    }

    void removeMax()
	{
        remove(maximum());
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
	// Recursive function to insert key in subtree root
	// and returns new root of the subtree.
	TreeNode* insert(TreeNode* root, Key key, Value value)
	{
		/* 1.  Perform the normal BST insertion */
		if (root == nullptr)
		{
			++m_count;
			return(new TreeNode(key, value));
		}
 
		if (key < root->key)
			root->left  = insert(root->left, key, value);
		else if (key > root->key)
			root->right = insert(root->right, key, value);
		else // Equal key's value is updated by new value
		{
			root->value = value;
			return root;
		}
 
		/* 2. Update height of this ancestor root */
		root->height = 1 + max(height(root->left), height(root->right));
 
		/* 3. Get the balance factor of this ancestor root
			  to check whether this root became unbalanced */
		int bf = getBF(root);
 
		// If this root becomes unbalanced, then
		// there are 4 cases
 
		// Left Left Case
		if (bf > 1 && key < root->left->key)
			return rotateRight(root);
 
		// Right Right Case
		if (bf < -1 && key > root->right->key)
			return rotateLeft(root);
 
		// Left Right Case
		if (bf > 1 && key > root->left->key)
		{
			root->left =  rotateLeft(root->left);
			return rotateRight(root);
		}
 
		// Right Left Case
		if (bf < -1 && key < root->right->key)
		{
			root->right = rotateRight(root->right);
			return rotateLeft(root);
		}
 
		/* return the (unchanged) root pointer */
		return root;
	}

	// Recursive function to remove a node with given key
	// from subtree with given root. It returns root of
	// the modified subtree.
	TreeNode* remove(TreeNode* root, int key)
	{
		// STEP 1: PERFORM STANDARD BST DELETE
		if (root == nullptr)
			return root;
 
		// If the key to be deleted is smaller than the
		// root's key, then it lies in left subtree
		if (key < root->key)
			root->left = remove(root->left, key);
 
		// If the key to be deleted is greater than the
		// root's key, then it lies in right subtree
		else if(key > root->key)
			root->right = remove(root->right, key);
 
		// if key is same as root's key, then This is
		// the node to be deleted
		else
		{
			// node with only one child or no child
			if((root->left == nullptr) || (root->right == nullptr))
			{
				TreeNode* successor = root->left ? root->left : root->right;
 
				// No child case
				if (successor == nullptr)
				{
					successor = root;
					root = nullptr;
				}
				else // One child case
				{
					*root = *successor; // Copy the contents of the non-empty child
				}

				--m_count;
				delete successor;
			}
			else
			{
				// node with two children: Get the inorder
				// successor (smallest in the right subtree)
				TreeNode* successor = minimum(root->right);
 
				// Copy the inorder successor's data to this node
				root->key = successor->key;
				root->value = successor->value;
 
				// Delete the inorder successor
				root->right = remove(root->right, successor->key);
			}
		}
 
		// If the tree had only one node then return
		if (root == nullptr)
			return root;
 
		// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
		root->height = 1 + max(height(root->left), height(root->right));
 
		// STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
		// check whether this node became unbalanced)
		int bf = getBF(root);
 
		// If this node becomes unbalanced, then there are 4 cases
 
		// Left Left Case
		if (bf > 1 && getBF(root->left) >= 0)
			return rotateRight(root);
 
		// Left Right Case
		if (bf > 1 && getBF(root->left) < 0)
		{
			root->left =  rotateLeft(root->left);
			return rotateRight(root);
		}
 
		// Right Right Case
		if (bf < -1 && getBF(root->right) <= 0)
			return rotateLeft(root);
 
		// Right Left Case
		if (bf < -1 && getBF(root->right) > 0)
		{
			root->right = rotateRight(root->right);
			return rotateLeft(root);
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

    TreeNode* search(TreeNode* root, Key key)
	{
        if(root == nullptr)
		{
			return nullptr;
		}

		if(root->key == key)
		{
			return root;
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
		cout<< "(" << node->key << "," << node->value << "<" << node->height << ">) ";
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
		while(node->left != nullptr)
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

	// http://www.geeksforgeeks.org/avl-tree-set-1-insertion/
	// A utility function to right rotate subtree rooted with y
	// See the diagram given above.
	TreeNode* rotateRight(TreeNode* y)
	{
		TreeNode* x = y->left;
		TreeNode* T2 = x->right;
 
		// Perform rotation
		x->right = y;
		y->left = T2;
 
		// Update heights
		y->height = max(height(y->left), height(y->right)) + 1;
		x->height = max(height(x->left), height(x->right)) + 1;
 
		// Return new root
		return x;
	}
 
	// A utility function to left rotate subtree rooted with x
	// See the diagram given above.
	TreeNode* rotateLeft(TreeNode* x)
	{
		TreeNode* y = x->right;
		TreeNode* T2 = y->left;
 
		// Perform rotation
		y->left = x;
		x->right = T2;
 
		//  Update heights
		x->height = max(height(x->left), height(x->right)) + 1;
		y->height = max(height(y->left), height(y->right)) + 1;
 
		// Return new root
		return y;
	}
 
	// Get Balance factor of node
	int getBF(TreeNode* node)
	{
		if (node == nullptr)
			return 0;
		return height(node->left) - height(node->right);
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

	int height(TreeNode * node)
	{
		if(node)
			return node->height;
		else
			return 0;
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

#endif //GEEKS_AVL_H