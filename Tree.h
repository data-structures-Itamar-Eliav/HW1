#ifndef TREE_H
#define TREE_H


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


template <typename T>
class Tree
{
public:
    Tree() : root(nullptr) {}

    ~Tree() {
        // Implement a destructor to free memory if needed.
    }

private:
    Node<T>* root;

    // Helper functions for AVL tree balancing:

    int getHeight(Node<T>* node) {
        // if node is nullptr, height is 0.
        return node ? node->height : 0;
    }

    int getBalance(Node<T>* node) {
        // if node is nullptr, balance is 0.
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // Update the height of a node based on its children.
    void updateHeight(Node<T>* node) {
        if (node != nullptr) {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        }
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
};


// Helper funcs:

/**
 * @brief Returns the maximum of two integers.
 * IDE has warned me to use inline here, because this function is defined in a header file.
 *
 * @param a First integer.
 * @param b Second integer.
 * @return The maximum of a and b.
 */
inline int max(const int a, const int b) {
    return a > b ? a : b;
}


#endif //TREE_H
