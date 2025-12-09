#ifndef TREE_H
#define TREE_H

// Exceptions:
class KeyExistsException {};

class KeyNotFoundException {};

/**
  *@brief A node in a binary tree.
  *@tparam T The type of the key stored in the node.
 */
template <typename T>
struct Node
{
    T key;
    Node* left;
    Node* right;
    int height;

    explicit Node(T k) : key(k), left(nullptr), right(nullptr), height(1) {}
};


/**
 * @brief A generic AVL Tree implementation.
 *
 * @tparam T The type of the keys stored in the tree.
 */
template <typename T>
class Tree
{
private:
    Node<T>* root;

    // Helper functions for AVL tree balancing:

    int getHeight(const Node<T>* node) const {
        // if node is nullptr, height is 0.
        return node ? node->height : 0;
    }

    int getBalance(const Node<T>* node) const {
        // if node is nullptr, balance is 0.
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // Update the height of a node based on its children.
    void updateHeight(Node<T>* node) {
        if (node != nullptr) {
            const int leftHeight = getHeight(node->left);
            const int rightHeight = getHeight(node->right);
            const int max = leftHeight > rightHeight ? leftHeight : rightHeight;
            node->height = 1 + max;
        }
    }

    // Find the node with the minimum key value in the given subtree.
    Node<T>* minValueNode(Node<T>* node) const {
        Node<T>* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    // Rotations:

    /**
     * @brief Perform a right rotation on the given subtree rooted with head.
     * This is for the LL case.
     *
     * @param head The root of the subtree to rotate.
     * @return The new root after rotation.
     */
    Node<T>* rightRotate(Node<T>* head) {
        Node<T>* newRoot = head->left;
        Node<T>* rightNode = newRoot->right;

        // Perform rotation
        newRoot->right = head;
        head->left = rightNode;

        // Update heights, head first because its lower, then newRoot.
        updateHeight(head);
        updateHeight(newRoot);

        // Return new root, for linking back to parent.
        return newRoot;
    }

    /**
     * @brief Perform a left rotation on the given subtree rooted with head.
     * This is for the RR case.
     *
     * @param head The root of the subtree to rotate.
     * @return The new root after rotation.
     */
    Node<T>* leftRotate(Node<T>* head) {
        Node<T>* newRoot = head->right;
        Node<T>* leftNode = newRoot->left;

        // Perform rotation
        newRoot->left = head;
        head->right = leftNode;

        // Update heights, head first because its lower, then newRoot.
        updateHeight(head);
        updateHeight(newRoot);

        // Return new root, for linking back to parent.
        return newRoot;
    }

    /**
     * @brief Rebalance the given node if it has become unbalanced.
     *
     * @param node The node to rebalance.
     * @return The new root of the subtree after rebalancing.
     */
    Node<T>* rebalance(Node<T>* node) {
        // Update the height of this ancestor node, while backtracking in the recursion.
        updateHeight(node);

        // Get the balance factor to check if this node became unbalanced or not.
        const int balance = getBalance(node);

        // Check for imbalance, and perform rotations accordingly:

        // Check if it's Left-Left or Left-Right:
        if (balance > 1) {
            // LL case, left child is balanced or left heavy:
            if (getBalance(node->left) >= 0) {
                return rightRotate(node);
            } else { // LR Case, left child is right heavy:
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }

        // Check if it's Right-Right or Right-Left:
        if (balance < -1) {
            // RR case, right child is balanced or right heavy:
            if (getBalance(node->right) <= 0) {
                return leftRotate(node);
            } else { // RL Case, right child is left heavy:
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }

        // Node is balanced, -1 <= balance <= 1 ,do nothing.
        return node;
    }

    // insertion, deletion:

    /**
     * @brief Insert a key into the AVL tree rooted at node recursively.
     *
     * @param node The root of the subtree where to insert the key.
     * @param key The key to insert.
     * @return The new root of the subtree after insertion and rebalancing.
     * @throws KeyExistsException if the key already exists in the tree.
     */
    Node<T>* insert(Node<T>* node, const T& key) {
        // Found null position, insert here.
        if (node == nullptr) {
            return new Node<T>(key);
        }

        // Traverse the tree to find the insertion point recursively.
        if (*key < *node->key) {
            node->left = insert(node->left, key);
        } else if (*key > *node->key) {
            node->right = insert(node->right, key);
        } else {
            // Duplicate keys are not allowed, no memory leak here as no new node was created.
            throw KeyExistsException();
        }

        // Rebalance the node if needed and return the (possibly new) root.
        return rebalance(node);
    }

    // Delete:
    Node<T>* remove(Node<T>* node, const T& key) {
        // Key is not in Tree.
        if (node == nullptr) {
            throw KeyNotFoundException();
        }

        // Traverse the tree to find the node to delete recursively.
        if (*key < *node->key) {
            node->left = remove(node->left, key);
        } else if (*key > *node->key) {
            node->right = remove(node->right, key);
        } else { // Node with the key found.
            // Two cases - Node with two children, or one/no child:

            // Node with two children, if left and right are not nullptr:
            if (node->left && node->right) {
                // Get the smallest node in the right subtree:
                Node<T>* temp = minValueNode(node->right);
                node->key = temp->key; // Copy data, no memory problems.
                node->right = remove(node->right, temp->key); // delete the min node.
            } else {
                // if we reach here, the node has at most one child.
                // Get the non-null child, if any:
                Node<T>* child = node->left ? node->left : node->right;

                // Delete the node and return the child to link to parent.
                Node<T>* temp = node;
                node = child; // could be nullptr if no children.
                delete temp; // remove the requested key.

                // No need to rebalance if node is now nullptr.
                if (node == nullptr) {
                    return nullptr;
                }
            }
        }

        // Rebalance the node if needed and return the (possibly new) root:
        return rebalance(node);
    }

    /**
     * @brief Find a node with the given key in the AVL tree rooted at node.
     *
     * @param node The root of the subtree to search.
     * @param key The key to find.
     * @return Pointer to the node with the given key.
     * @throws KeyNotFoundException if the key is not found in the tree.
     */
    Node<T>* find(Node<T>* node, const T& key) const {
        // Not in tree:
        if (node == nullptr) {
            throw KeyNotFoundException();
        }

        // Key found:
        if (*key == *node->key) {
            return node;
        }

        // Traverse left or right:
        if (*key < *node->key) {
            return find(node->left, key);
        } else {
            return find(node->right, key);
        }
    }

    // Destroy the tree recursively:
    void destroyTree(Node<T>* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    //----------------------------------------------------------------

public:
    // Constructor:
    Tree() : root(nullptr) {}

    // Destructor:
    ~Tree() {
        destroyTree(root);
    }

    /**
     * @brief Public insert method.
     *
     * @param key The key to insert.
     * @throws KeyExistsException if the key already exists in the tree.
     */
    void insert(const T& key) {
        root = insert(root, key);
    }

    /**
     * @brief Public remove method.
     *
     * @param key The key to remove.
     * @throws KeyNotFoundException if the key is not found in the tree.
     */
    void remove(const T& key) {
        root = remove(root, key);
    }

    /**
     * @brief Public find method.
     *
     * @param key The key to find.
     * @return Pointer to the node with the given key.
     * @throws KeyNotFoundException if the key is not found in the tree.
     */
    T& find(const T& key) const {
        return find(root, key)->key;
    }

    /**
     * @brief Check if the tree is empty.
     *
     * @return true if the tree is empty, false otherwise.
     */
    bool isEmpty() const {
        return root == nullptr;
    }
};


#endif //TREE_H
