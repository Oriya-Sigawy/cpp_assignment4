// 214984932 oriyas.07@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Tree.hpp"
#include <string>
using std::string;

TEST_CASE("check number of children")
{
    Tree<string> tree{};
    CHECK(tree.get_k() == 2); // default

    auto root_node = std::make_shared<TreeNode<string>>("air");
    Tree<string> tree2(2);
    tree2.add_root(root_node);
    auto n1 = std::make_shared<TreeNode<string>>("book");
    CHECK_THROWS(tree2.add_root(n1));
    auto n2 = std::make_shared<TreeNode<string>>("chrome");
    auto n3 = std::make_shared<TreeNode<string>>("delete");
    tree2.add_sub_node(root_node.get(), n2);
    tree2.add_sub_node(root_node.get(), n1);
    CHECK_THROWS(tree2.add_sub_node(root_node.get(), n3)); // can not add more than k children to a node
    CHECK_THROWS(tree2.add_sub_node(nullptr, n3));
}

TEST_CASE("check preorder throws")
{
    Tree<int> tree(3);
    CHECK_THROWS(tree.begin_pre_order()); // this tree is null
    auto root_node = std::make_shared<TreeNode<int>>(1);
    tree.add_root(root_node);
    CHECK_THROWS(tree.begin_pre_order()); // preorder can only work on binary tree
}

TEST_CASE("check preorder")
{
    auto root_node = std::make_shared<TreeNode<string>>("air");
    Tree<string> tree(2);
    tree.add_root(root_node);
    auto n1 = std::make_shared<TreeNode<string>>("book");
    auto n2 = std::make_shared<TreeNode<string>>("chrome");
    auto n3 = std::make_shared<TreeNode<string>>("delete");
    auto n4 = std::make_shared<TreeNode<string>>("example");
    auto n5 = std::make_shared<TreeNode<string>>("for");

    tree.add_sub_node(root_node.get(), n2);
    tree.add_sub_node(n2.get(), n1);
    tree.add_sub_node(n2.get(), n3);
    tree.add_sub_node(n1.get(), n4);
    tree.add_sub_node(n1.get(), n5);

    std::array<string, 6> check = {"air", "chrome", "book", "example", "for", "delete"}; // the true order preorder suppose to give
    unsigned int i = 0;
    for (auto iterator = tree.begin_pre_order(); iterator.hasNext(); iterator.next())
    {
        CHECK(iterator.current()->get_data() == check[i]);
        i++;
    }
}

TEST_CASE("check postorder throws")
{
    Tree<int> tree(3);
    CHECK_THROWS(tree.begin_post_order()); // this tree is null
    auto root_node = std::make_shared<TreeNode<int>>(1);
    tree.add_root(root_node);
    CHECK_THROWS(tree.begin_post_order()); // postorder can only work on binary tree
}

TEST_CASE("check postorder")
{
    auto root_node = std::make_shared<TreeNode<double>>(1.2);
    Tree<double> tree(2);
    tree.add_root(root_node);
    auto n1 = std::make_shared<TreeNode<double>>(5.6);
    auto n2 = std::make_shared<TreeNode<double>>(4.8);
    auto n3 = std::make_shared<TreeNode<double>>(0.9);
    auto n4 = std::make_shared<TreeNode<double>>(3.2);
    auto n5 = std::make_shared<TreeNode<double>>(6.3);

    tree.add_sub_node(root_node.get(), n1);
    tree.add_sub_node(n1.get(), n2);
    tree.add_sub_node(n1.get(), n3);
    tree.add_sub_node(n2.get(), n5);
    tree.add_sub_node(n3.get(), n4);

    std::array<double, 6> check = {6.3, 4.8, 3.2, 0.9, 5.6, 1.2}; // the true order postorder suppose to give
    unsigned int i = 0;
    for (auto iterator = tree.begin_post_order(); iterator.hasNext(); iterator.next())
    {
        CHECK(iterator.current()->get_data() == check[i]);
        i++;
    }
}

TEST_CASE("check inorder throws")
{
    Tree<int> tree(3);
    CHECK_THROWS(tree.begin_in_order()); // this tree is null
    auto root_node = std::make_shared<TreeNode<int>>(1);
    tree.add_root(root_node);
    CHECK_THROWS(tree.begin_in_order()); // inorder can only work on binary tree
}

TEST_CASE("check inorder")
{
    auto root_node = std::make_shared<TreeNode<bool>>(true);
    Tree<bool> tree(2);
    tree.add_root(root_node);
    auto n1 = std::make_shared<TreeNode<bool>>(false);
    auto n2 = std::make_shared<TreeNode<bool>>(true);
    auto n3 = std::make_shared<TreeNode<bool>>(false);
    auto n4 = std::make_shared<TreeNode<bool>>(false);
    auto n5 = std::make_shared<TreeNode<bool>>(true);

    tree.add_sub_node(root_node.get(), n1);
    tree.add_sub_node(root_node.get(), n2);
    tree.add_sub_node(n2.get(), n3);
    tree.add_sub_node(n2.get(), n5);
    tree.add_sub_node(n5.get(), n4);

    std::array<bool, 6> check = {false, true, false, true, false, true}; // the true order inorder suppose to give
    unsigned int i = 0;
    for (auto iterator = tree.begin_in_order(); iterator.hasNext(); iterator.next())
    {
        CHECK(iterator.current()->get_data() == check[i]);
        i++;
    }
}

TEST_CASE("check myHeap throws")
{
    Tree<int> tree(3);
    CHECK_THROWS(tree.myHeap()); // this tree is null
    auto root_node = std::make_shared<TreeNode<int>>(1);
    tree.add_root(root_node);
    CHECK_THROWS(tree.myHeap()); // heap can only work on binary tree
}

TEST_CASE("check myheap")
{
    auto root_node = std::make_shared<TreeNode<int>>(1);
    Tree<int> tree(2);
    tree.add_root(root_node);
    auto n1 = std::make_shared<TreeNode<int>>(3);
    auto n2 = std::make_shared<TreeNode<int>>(54);
    auto n3 = std::make_shared<TreeNode<int>>(2);
    auto n4 = std::make_shared<TreeNode<int>>(5);
    auto n5 = std::make_shared<TreeNode<int>>(87);

    tree.add_sub_node(root_node.get(), n1);
    tree.add_sub_node(root_node.get(), n2);
    tree.add_sub_node(n2.get(), n3);
    tree.add_sub_node(n2.get(), n5);
    tree.add_sub_node(n5.get(), n4);

    std::array<int, 6> check = {1, 2, 3, 5, 54, 87}; // the true order minHeap suppose to give
    unsigned int i = 0;
    for (auto iterator = tree.myHeap(); iterator.hasNext(); iterator.next())
    {
        CHECK(iterator.current()->get_data() == check[i]);
        i++;
    }
}

TEST_CASE("check BFS throws")
{
    Tree<int> tree(3);
    CHECK_THROWS(tree.begin_BFS_scan()); // this tree is null
}

TEST_CASE("check BFS with k=2")
{
    auto root_node = std::make_shared<TreeNode<int>>(1);
    Tree<int> tree(2);
    tree.add_root(root_node);
    auto n1 = std::make_shared<TreeNode<int>>(3);
    auto n2 = std::make_shared<TreeNode<int>>(54);
    auto n3 = std::make_shared<TreeNode<int>>(2);
    auto n4 = std::make_shared<TreeNode<int>>(5);
    auto n5 = std::make_shared<TreeNode<int>>(87);

    tree.add_sub_node(root_node.get(), n1);
    tree.add_sub_node(root_node.get(), n2);
    tree.add_sub_node(n2.get(), n3);
    tree.add_sub_node(n2.get(), n5);
    tree.add_sub_node(n1.get(), n4);

    std::array<int, 6> check = {1, 3, 54, 5, 2, 87}; // the true order BFS suppose to give
    unsigned int i = 0;
    for (auto iterator = tree.begin_BFS_scan(); iterator.hasNext(); iterator.next())
    {
        CHECK(iterator.current()->get_data() == check[i]);
        i++;
    }
}
TEST_CASE("check BFS with k = 5")
{
    auto root_node = std::make_shared<TreeNode<double>>(1.5);
    Tree<double> tree(5);
    tree.add_root(root_node);
    auto n1 = std::make_shared<TreeNode<double>>(3.7);
    auto n2 = std::make_shared<TreeNode<double>>(54.5);
    auto n3 = std::make_shared<TreeNode<double>>(2.8);
    auto n4 = std::make_shared<TreeNode<double>>(5.2);
    auto n5 = std::make_shared<TreeNode<double>>(87.1);
    auto n6 = std::make_shared<TreeNode<double>>(3.9);
    auto n7 = std::make_shared<TreeNode<double>>(54.7);
    auto n8 = std::make_shared<TreeNode<double>>(2.0);
    auto n9 = std::make_shared<TreeNode<double>>(5.3);
    auto n10 = std::make_shared<TreeNode<double>>(87.5);

    tree.add_sub_node(root_node.get(), n2);
    tree.add_sub_node(root_node.get(), n5);
    tree.add_sub_node(root_node.get(), n6);
    tree.add_sub_node(root_node.get(), n9);
    tree.add_sub_node(root_node.get(), n10);
    tree.add_sub_node(n2.get(), n3);
    tree.add_sub_node(n2.get(), n4);
    tree.add_sub_node(n6.get(), n7);
    tree.add_sub_node(n7.get(), n1);
    tree.add_sub_node(n9.get(), n8);

    std::array<double, 11> check = {1.5, 54.5, 87.1, 3.9, 5.3, 87.5, 2.8, 5.2, 54.7, 2.0, 3.7}; // the true order BFS suppose to give
    unsigned int i = 0;
    for (auto iterator = tree.begin_BFS_scan(); iterator.hasNext(); iterator.next())
    {
        CHECK(iterator.current()->get_data() == check[i]);
        i++;
    }
}

TEST_CASE("check DFS throws")
{
    Tree<int> tree(3);
    CHECK_THROWS(tree.begin_DFS_scan()); // this tree is null
}

TEST_CASE("check DFS with k = 2")
{
    auto root_node = std::make_shared<TreeNode<int>>(1);
    Tree<int> tree(2);
    tree.add_root(root_node);
    auto n1 = std::make_shared<TreeNode<int>>(3);
    auto n2 = std::make_shared<TreeNode<int>>(54);
    auto n3 = std::make_shared<TreeNode<int>>(2);
    auto n4 = std::make_shared<TreeNode<int>>(5);
    auto n5 = std::make_shared<TreeNode<int>>(87);

    tree.add_sub_node(root_node.get(), n1);
    tree.add_sub_node(root_node.get(), n2);
    tree.add_sub_node(n1.get(), n3);
    tree.add_sub_node(n2.get(), n4);
    tree.add_sub_node(n2.get(), n5);

    std::array<int, 6> check = {1, 3, 2, 54, 5, 87}; // the true order DFS suppose to give
    unsigned int i = 0;
    for (auto iterator = tree.begin_DFS_scan(); iterator.hasNext(); iterator.next())
    {
        CHECK(iterator.current()->get_data() == check[i]);
        i++;
    }
}
TEST_CASE("check DFS with k = 5")
{
    auto root_node = std::make_shared<TreeNode<double>>(1.5);
    Tree<double> tree(5);
    tree.add_root(root_node);
    auto n1 = std::make_shared<TreeNode<double>>(3.7);
    auto n2 = std::make_shared<TreeNode<double>>(54.5);
    auto n3 = std::make_shared<TreeNode<double>>(2.8);
    auto n4 = std::make_shared<TreeNode<double>>(5.2);
    auto n5 = std::make_shared<TreeNode<double>>(87.1);
    auto n6 = std::make_shared<TreeNode<double>>(3.9);
    auto n7 = std::make_shared<TreeNode<double>>(54.7);
    auto n8 = std::make_shared<TreeNode<double>>(2.0);
    auto n9 = std::make_shared<TreeNode<double>>(5.3);
    auto n10 = std::make_shared<TreeNode<double>>(87.5);

    tree.add_sub_node(root_node.get(), n2);
    tree.add_sub_node(root_node.get(), n5);
    tree.add_sub_node(root_node.get(), n6);
    tree.add_sub_node(root_node.get(), n9);
    tree.add_sub_node(root_node.get(), n10);
    tree.add_sub_node(n2.get(), n3);
    tree.add_sub_node(n2.get(), n4);
    tree.add_sub_node(n6.get(), n7);
    tree.add_sub_node(n7.get(), n1);
    tree.add_sub_node(n9.get(), n8);

    std::array<double, 11> check = {1.5, 54.5, 2.8, 5.2, 87.1, 3.9, 54.7, 3.7, 5.3, 2.0, 87.5}; // the true order DFS suppose to give
    unsigned int i = 0;
    for (auto iterator = tree.begin_DFS_scan(); iterator.hasNext(); iterator.next())
    {
        CHECK(iterator.current()->get_data() == check[i]);
        i++;
    }
}
