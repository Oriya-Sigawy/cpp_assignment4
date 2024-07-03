// 214984932 oriyas.07@gmail
#include <iostream>
#include "Complex.hpp"
#include "Tree.hpp"

using std::cout;
using std::endl;

int main()
{

    auto root_node = std::make_shared<TreeNode<Complex>>(Complex(1, 1));
    Tree<Complex> tree(2); // Binary tree that contains Complex.
    tree.add_root(root_node);
    auto n1 = std::make_shared<TreeNode<Complex>>(Complex(1, 2));
    auto n2 = std::make_shared<TreeNode<Complex>>(Complex(1, 3));
    auto n3 = std::make_shared<TreeNode<Complex>>(Complex(1, 4));
    auto n4 = std::make_shared<TreeNode<Complex>>(Complex(1, 5));
    auto n5 = std::make_shared<TreeNode<Complex>>(Complex(1, 6));

    tree.add_sub_node(root_node.get(), n1);
    tree.add_sub_node(root_node.get(), n2);
    tree.add_sub_node(n1.get(), n3);
    tree.add_sub_node(n1.get(), n4);
    tree.add_sub_node(n2.get(), n5);
    // cout << tree;
    // The tree should look like:
    /**
     *       root = 1,1
     *     /       \
     *    1,2      1,3
     *   /  \      /
     *  1,4  1,5  1,6
     */
    cout << "preorder:" << endl;
    for (auto iterator = tree.begin_pre_order(); iterator.hasNext(); iterator.next())
    {
        cout << iterator.current()->get_data() << endl;
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6

    cout << "postorder:" << endl;
    for (auto iterator = tree.begin_post_order(); iterator.hasNext(); iterator.next())
    {
        cout << iterator.current()->get_data() << endl;
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1

    cout << "inorder:" << endl;
    for (auto iterator = tree.begin_in_order(); iterator.hasNext(); iterator.next())
    {
        cout << iterator.current()->get_data() << endl;
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3

    cout << "BFS: " << endl;
    for (auto iterator = tree.begin_BFS_scan(); iterator.hasNext(); iterator.next())
    {
        cout << iterator.current()->get_data() << endl;
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    cout << "DFS: " << endl;
    for (auto iterator = tree.begin_DFS_scan(); iterator.hasNext(); iterator.next())
    {
        cout << iterator.current()->get_data() << endl;
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6

    cout << "minHeap: " << endl;
    for (auto iterator = tree.myHeap(); iterator.hasNext(); iterator.next())
    {
        cout << iterator.current()->get_data() << endl;
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    for (auto iterator = tree.myHeap(); iterator.hasNext(); iterator.next())
    {
        cout << iterator.current()->get_data().to_string() << endl;
    }
    cout << tree; // Should print the graph using GUI.

    return 0;
}
