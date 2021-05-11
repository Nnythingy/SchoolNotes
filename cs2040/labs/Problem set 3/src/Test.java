public class Test {
    public static void main(String[] args)
    {
        AVLTree<Integer> tree = new AVLTree<>();

        /* Constructing tree given in the above figure */
        tree.insert(9);
        tree.insert(5);
        tree.insert(10);
        tree.insert(0);
        tree.insert(6);
        tree.insert(11);
        tree.insert(-1);
        tree.insert(1);
        tree.insert( 2);

        /* The constructed AVL Tree would be
        9
        / \
        1 10
        / \ \
        0 5 11
        / / \
        -1 2 6
        */
        System.out.println("Preorder traversal of "+
                "constructed tree is : ");
        tree.inorder();

        tree.delete(10);

        /* The AVL Tree after deletion of 10
        1
        / \
        0 9
        /     / \
        -1 5 11
        / \
        2 6
        */
        System.out.println("");
        System.out.println("Preorder traversal after "+
                "deletion of 10 :");
        tree.inorder();
    }
}

