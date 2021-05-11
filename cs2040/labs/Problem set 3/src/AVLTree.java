class Node <T extends Comparable<T>> {

    T val;
    int height;
    Node<T> left;
    Node<T> right;

    Node(T t) {
        this.val = t;
        height = 1;
        left = null;
        right = null;
    }
}

class AVLTree <T extends Comparable<T>> {
    Node<T> root;

    // A utility function to get height of the tree  
    private int height(Node<T> node) {
        if (node == null) {
            return 0;
        }
        return node.height;
    }

    // to right rotate
    private Node<T> rightRotate(Node<T> y) {
        Node<T> x = y.left;
        Node<T> T2 = x.right;

        // Perform rotation  
        x.right = y;
        y.left = T2;

        // Update heights  
        y.height = Math.max(height(y.left), height(y.right)) + 1;
        x.height = Math.max(height(x.left), height(x.right)) + 1;

        // Return new root  
        return x;
    }

    // to left rotate
    private Node<T> leftRotate(Node<T> x) {
        Node<T> y = x.right;
        Node<T> T2 = y.left;

        // Perform rotation  
        y.left = x;
        x.right = T2;

        // Update heights  
        x.height = Math.max(height(x.left), height(x.right)) + 1;
        y.height = Math.max(height(y.left), height(y.right)) + 1;

        // Return new root  
        return y;
    }

    // Get Balance factor of node N  
    private int getBalance(Node<T> N) {
        if (N == null) {
            return 0;
        }
        return height(N.left) - height(N.right);
    }
    // for use in ucpc
    public void insert(T val) {
        this.root = insert(this.root, val);
    }
    // for private use to help insert method
    private Node<T> insert(Node<T> node, T val) {
        // Perform the normal BST rotation
        if (node == null) {
            return new Node<T>(val);
        }

        if (val.compareTo(node.val) < 0) {
            node.left = insert(node.left, val);
        } else if (val.compareTo(node.val) > 0) {
            node.right = insert(node.right, val);
        } else { // Equal keys not allowed
            return node;
        }

        // Update height of this parent node
        node.height = 1 + Math.max(height(node.left), height(node.right));

        // get balance factor of node
        int balance = getBalance(node);

        // If this node becomes unbalanced, then

        // Left Left Case
        if (balance > 1 && val.compareTo(node.left.val) < 0) {
            return rightRotate(node);
        }

        // Right Right Case  
        if (balance < -1 && val.compareTo(node.right.val) > 0) {
            return leftRotate(node);
        }

        // Left Right Case  
        if (balance > 1 && val.compareTo(node.left.val) > 0) {
            node.left = leftRotate(node.left);
            return rightRotate(node);
        }

        // Right Left Case  
        if (balance < -1 && val.compareTo(node.right.val) < 0) {
            node.right = rightRotate(node.right);
            return leftRotate(node);
        }
        // return original node
        return node;
    }
    // check if tree has no nodes
    public boolean isEmpty() {
        return this.root == null;
    }

    // for ucpc method
    public Node<T> minNode() {
        return minNode(this.root);
    }

    // get min node for internal
    private Node<T> minNode(Node<T> node) {
        Node<T> current = node;
        // traverse until lowest found
        while (current.left != null)
            current = current.left;

        return current;
    }

    // to use in ucpc method
    public void delete(T val) {
        this.root = deleteNode(this.root, val);
    }
    // for internal use to help delete
    private Node<T> deleteNode(Node<T> node, T val) {
        // STEP 1: PERFORM STANDARD BST DELETE
        if (node == null)
            return node;

        // If the key to be deleted is smaller than
        // the root's key, then it lies in left subtree
        if (val.compareTo(node.val) < 0) {
            node.left = deleteNode(node.left, val);

            // If the key to be deleted is greater than the
            // root's key, then it lies in right subtree
        } else if (val.compareTo(node.val) > 0) {
            node.right = deleteNode(node.right, val);

        } else { // if key is same as root's key, then this is the node to be deleted

            // node with only one child or no child
            if ((node.left == null) || (node.right == null)) {
                Node<T> temp = null;
                if (temp == node.left) {
                    temp = node.right;
                } else {
                    temp = node.left;
                }

                // No child
                if (temp == null) {
                    node = null;
                } else { // one child
                    node = temp; // Copy the contents of
                }
                // the non-empty child
            } else {

                // node with two children: Get the inorder
                // successor (smallest in the right subtree)
                Node<T> temp = minNode(node.right);

                // Copy the inorder successor's data to this node
                node.val = temp.val;

                // Delete the inorder successor
                node.right = deleteNode(node.right, temp.val);
            }
        }

        // If the tree had only one node then return
        if (node == null) {
            return node;
        }

        // update height of curr node
        node.height = Math.max(height(node.left), height(node.right)) + 1;

        // check if unbalancing happens
        int balance = getBalance(node);

        // If this node becomes unbalanced, then there are 4 cases
        // Left Left Case
        if (balance > 1 && getBalance(node.left) >= 0) {
            return rightRotate(node);
        }

        // Left Right Case
        if (balance > 1 && getBalance(node.left) < 0) {
            node.left = leftRotate(node.left);
            return rightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && getBalance(node.right) <= 0) {
            return leftRotate(node);
        }

        // Right Left Case
        if (balance < -1 && getBalance(node.right) > 0) {
            node.right = rightRotate(node.right);
            return leftRotate(node);
        }

        return node;
    }

    public void inorder() {
        inorder(root);
        System.out.println();
    }

    private void inorder(Node<T> cur) {
        if (cur == null) {
            return;
        }
        inorder(cur.left);
        System.out.print(" " + cur.val);
        inorder(cur.right);
    }
}