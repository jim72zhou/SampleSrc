#ifndef GEEKS_RBT_H
#define GEEKS_RBT_H

#include <queue>
#include <cassert>

using namespace std;

// A basic concise introduction and links of related info
// https://en.wikipedia.org/wiki/Red-black_tree
// http://www.geeksforgeeks.org/red-black-tree-set-1-introduction-2/
// https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-046j-introduction-to-algorithms-sma-5503-fall-2005/video-lectures/lecture-10-red-black-trees-rotations-insertions-deletions/lec10.pdf
// <<Introduction to Algorithms算法导论>> is the most complete and accurate description

/* 5 basic rules:
1. Each node is either red or black.
2. The root is black.
3. All leaves (NIL) are black.
4. There are no two adjacent red nodes (A red node cannot have a red parent or red child).
5. Every path from a given node to any of its descendant NIL nodes contains the same number of black nodes. 

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

		TreeNode()
		{
			this->color = BLACK;
			this->left = this->right = this->parent = nullptr;
		}
		
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
			this->parent = node->parent;
		}
	};

public:
	RBT()
	{
		m_count = 0;
		nil = new TreeNode(); // sentry for NIL
		m_root = nil;
	}

	~RBT()
	{
		destroy(m_root);
		delete nil;
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
		insert(node);

		insertFixup(node);
		++m_count;
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
		if(m_root == nil)
			return;

		queue<TreeNode*> q;		
		q.emplace(m_root);
		while(!q.empty())
		{
			TreeNode* node = q.front();
			q.pop();

			nodeAction(node);

			if(node->left != nil)
				q.emplace(node->left);
			if(node->right != nil)
				q.emplace(node->right);
		}
	}

    Key minimum()
	{
        assert(m_root != nil);
        TreeNode* minNode = minimum(m_root);
        return minNode->key;
    }

    Key maximum()
	{
        assert(m_root != nil);
        TreeNode* maxNode = maximum(m_root);
        return maxNode->key;
    }

    void remove(Key key)
	{
		TreeNode* node = search(m_root, key);
		if(node != nil)
		{
			remove(node);
			delete node;
			--m_count;
		}
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
	void insert(TreeNode *z)
	{
		TreeNode* y = nil;
		TreeNode* x = m_root;
		
		while(x != nil)
		{
			y = x;
			if(z->key < x->key)
				x = x->left;
			else
				x = x->right;
		}

		z->parent = y;
		if(y == nil)
			m_root = z;
		else if(z->key < y->key)
			y->left = z;
		else
			y->right = z;

		z->left = nil;
		z->right = nil;
	}

	bool contain(TreeNode* node, Key key)
	{
        if(node == nil)
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
        if(root == nil)
		{
			return nil;
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
		cout<< "(" << node->key << "," << node->value << "," << ((node->color == RED) ? "R" : "B") << ") ";
	}

	void preOrder(TreeNode * node)
	{
        if(node == nil)
			return;
		
		nodeAction(node);
		preOrder(node->left);
		preOrder(node->right);
    }

    void inOrder(TreeNode * node)
	{
        if(node == nil)
			return;

		inOrder(node->left);
		nodeAction(node);
		inOrder(node->right);
    }

   void postOrder(TreeNode * node)
	{
        if(node == nil)
			return;

		postOrder(node->left);
		postOrder(node->right);
		nodeAction(node);
    }

    // implemented as iteratively 
    TreeNode* minimum(TreeNode* node)
	{
		while(node->left != nil)
			node = node->left;

		return node;
    }

	// implemented as recursively
    TreeNode* maximum(TreeNode* node)
	{
        if(node->right == nil)
			return node;

		return maximum(node->right);
    }

	void transplant(TreeNode* u, TreeNode* v)
	{
		if(u->parent == nil)
			m_root = v;
		else if(u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;

		v->parent = u->parent;
	}

	void remove(TreeNode* z)
	{
		TreeNode* y = z;
		int yColor = y->color;
		TreeNode* x = nil;

		if(z->left == nil)  // has no left child
		{
			x = z->right;
			transplant(z, z->right);
		}
		else if(z->right == nil) // has  no right child
		{
			x = z->left;
			transplant(z, z->left);
		}
		else  // have both left and right children
		{
			y = minimum(z->right);
			yColor = y->color;
			x = y->right;

			if(y->parent == z)
				x->parent = y;
			else
			{
				transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}

		if(yColor == BLACK)
			removeFixup(x);
	}

	void removeFixup(TreeNode* x)
	{
		while(x != m_root && x->color == BLACK)
		{
			/*  Case : A
				Parent of x is left child of parent of x */
			if(x == x->parent->left)
			{
				TreeNode* w = x->parent->right; // sibling node

				// Case 1
				if(w->color == RED)
				{
					// parent->color should be BLACK in this case
					w->color = BLACK;
					x->parent->color = RED;
					rotateLeft(x->parent);
					w = x->parent->right;
				}

				// Case 2
				if(w->left->color == BLACK && w->right->color == BLACK)
				{
					w->color = RED;
					x = x->parent;
				}
			   else
			   {
					// Case 3
					if(w->right->color == BLACK)
					{
						w->left->color = BLACK;
						w->color = RED;
						rotateRight(w);
						w = x->parent->right;
					}

					// Case 4
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->right->color = BLACK;
					rotateLeft(x->parent);
					x = m_root;
				}
			}
			/*  Case : B
				Parent of x is right child of parent of x */
			else
			{
				TreeNode* w = x->parent->left; // sibling node

				// Case 1
				if(w->color == RED)
				{
					w->color = BLACK;
					w->parent->color = RED;
					rotateRight(x->parent);
					w = x->parent->left;
				}
				// Case 2
				else if(w->left->color == BLACK && w->right->color == BLACK)
				{
					w->color = RED;
					x = x->parent;
				}
				else
				{
					// Case 3
					if(w->left->color == BLACK)
					{
						w->right->color = BLACK;
						w->color = RED;
						rotateLeft(w);
						w = x->parent->left;
					}
					// Case 4
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					rotateRight(x->parent);
					x = m_root;
				}
			}
		}

		x->color = BLACK;
	}

	// http://www.geeksforgeeks.org/red-black-tree-set-2-insert/
    void insertFixup(TreeNode* z)
	{
		TreeNode *parentNode = nil;
		TreeNode *grandParentNode = nil;
 
		while((z != m_root) && (z->parent->color == RED))
		{
 			parentNode = z->parent;
			grandParentNode = z->parent->parent;
 
			/*  Case : A
				Parent of z is left child of Grand-parent of z */
			if (parentNode == grandParentNode->left)
			{
				TreeNode* y = grandParentNode->right;	// Uncle node
 
				/* Case : 1
				   The uncle of z is also red
				   Only Recoloring required */
				if (y != nil && y->color == RED)
				{
					parentNode->color = BLACK;
					y->color = BLACK;
					grandParentNode->color = RED;			
					z = grandParentNode;
				}
				else
				{
					/* Case : 2
					   z is right child of its parent
					   Left-rotation required */
					if (z == parentNode->right)
					{
						z = parentNode;
						rotateLeft(z);
					}
 
					/* Case : 3
					   z is left child of its parent
					   Right-rotation required */
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					rotateRight(z->parent->parent);
				}
			}
 
			/* Case : B
			   Parent of z is right child of Grand-parent of z */
			else
			{
				TreeNode *y = grandParentNode->left;
 
				/*  Case : 1
					The uncle of z is also red
					Only Recoloring required */
				if ((y != nil) && (y->color == RED))
				{
					parentNode->color = BLACK;
					y->color = BLACK;
					grandParentNode->color = RED;					
					z = grandParentNode;
				}
				else
				{
					/* Case : 2
					   z is left child of its parent
					   Right-rotation required */
					if (z == parentNode->left)
					{
						z = parentNode;
						rotateRight(z);
					}
 
					/* Case : 3
					   z is right child of its parent
					   Left-rotation required */
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					rotateLeft(z->parent->parent);
				}
			}
		}
 
		m_root->color = BLACK;
	}

	// https://en.wikipedia.org/wiki/Tree_rotation
	// Illustration here is intuitive(B=x, A=y in below source)
	void rotateLeft(TreeNode* x)
	{
		TreeNode* y = x->right;
 
		x->right = y->left;
 
		if (x->right != nil)
			x->right->parent = x;
 
		y->parent = x->parent;
 
		if (x->parent == nil)
			m_root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
 
		y->left = x;
		x->parent = y;
	}
 
	void rotateRight(TreeNode* x)
	{
		TreeNode* y = x->left;
 
		x->left = y->right;
 
		if (x->left != nil)
			x->left->parent = x;
 
		y->parent = x->parent;
 
		if (x->parent == nil)
			m_root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
 
		y->right = x;
		x->parent = y;
	}

	// Find key's floor in the bst that node is the root
    TreeNode* floor(TreeNode* node, Key key)
	{
        if(node == nil)
            return nil;

		if(node->key == key)
            return node;
		else if(node->key > key)
            return floor(node->left , key);
		else // node->key < key
		{       
			// node may be key's floor
			// node->key may be greater and less than key, so need try node->right
			TreeNode* tempNode = floor(node->right , key);
			if(tempNode != nil)
				return tempNode;
			else
				return node;
		}
    }

    // Find key's cell in the bst that node is the root
    TreeNode* ceil(TreeNode* node, Key key)
	{
        if(node == nil)
            return nil;

        if(node->key == key)
            return node;
        else if(node->key < key)
            return ceil(node->right , key);
		else    // node->key > key
        {
			
			// node may be key's ceil node, 
			// node->key may be less and greater than key, so need try node->left
			TreeNode* tempNode = ceil(node->left , key);
			if(tempNode != nil)
				return tempNode;
			else
				return node;
		}
    }

   // destroy the node as postOrder
   void destroy(TreeNode * node)
	{
        if(node == nil)
			return;

		destroy(node->left);
		destroy(node->right);
		delete node;
		--m_count;
    }

    TreeNode *m_root;
	TreeNode *nil;
    int m_count;
};

#endif //GEEKS_RBT_H