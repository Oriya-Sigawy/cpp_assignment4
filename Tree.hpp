// 214984932 oriyas.07@gmail.com
#pragma once
#include <queue>
#include <stack>
#include <vector>
#include <memory>
#include <algorithm>
#include <ostream>
#include <iostream>
#include <string>
#include <cstring>
#include <utility>
#include "raylib-5.0_linux_i386/include/raylib.h"
using std::stack;
using std::string;
using std::vector;

// for the gui
#define HEIGHT 600
#define WIDTH 800
#define NODE_RADIUS 50

template <class T>
struct TreeNode;
template <class T>
class Tree;

/**
 * This struct represent a node with a template data.
 * @param data - the template data of the node.
 * @param children - vector of shared pointers to the node's children.
 * This struct has:
 * constructor
 * function to add a child
 * getter for the data.
 */
template <class T>
struct TreeNode
{
    T data;
    vector<std::shared_ptr<TreeNode<T>>> children;
    TreeNode(T k) : data(k) {}
    void add_child(std::shared_ptr<TreeNode<T>> child)
    {
        if (child.use_count() == 3)
        {
            this->children.push_back(child);
        }
    }
    T get_data() const
    {
        return data;
    }
};

/**
 * This class represent a tree that has nodes with template data (nodes - instance of the struct above).
 */
template <class T>
class Tree
{
private:
    std::shared_ptr<TreeNode<T>> root;
    unsigned int k; // max degree

public:
    // constructor
    Tree(unsigned int k = 2) : root(nullptr), k(k) {} // for the style
    // copy constructor
    Tree(std::shared_ptr<TreeNode<T>> r, unsigned int k = 2) : root(r), k(k) {}

    /**
     * This function is a getter for the max degree of the tree.
     * @returns k - the max degree of the tree.
     */
    unsigned int get_k() const
    {
        return this->k;
    }

    /**
     * This function adds a root to a tree, if there is no root.
     * @param r - the new root for the tree.
     */
    void add_root(std::shared_ptr<TreeNode<T>> r)
    {
        if (!root)
        {
            root = r;
        }
        else
        {
            throw std::invalid_argument("root already exists!");
        }
    }

    /**
     * These function added a new child to existing node of the tree.
     * @param parent - the exsisting node to add child to.
     * @param child - the new child to add to the parent.
     */
    void add_sub_node(TreeNode<T> *parent, std::shared_ptr<TreeNode<T>> child)
    {
        if (parent)
        {
            if (parent->children.size() < this->k)
            {
                parent->add_child(child);
            }
            else
            {
                throw std::invalid_argument("This parent already have k children!");
            }
        }
        else
        {
            throw std::invalid_argument("Parent node does not exist!");
        }
    }

    /**
     * This is a getter for the tree root.
     * @returns the tree root.
     */
    TreeNode<T> *get_root() const
    {
        return this->root.get();
    }

    /**
     * This is a function to compare between two numbers.
     * @param x1 the first number to compare.
     * @param x2 the second number to compare.
     * @returns the max between x1, x2.
     */
    unsigned int max(unsigned int x1, unsigned int x2) const
    {
        return x1 > x2 ? x1 : x2;
    }

    /**
     * This is a recursice function to return the tree depth.
     * The idea is that a node's depth is the max between the depth of its children + 1.
     * @returns the tree's depth.
     */
    unsigned int get_depth(TreeNode<T> *node) const
    {
        if (node == nullptr)
            return 0;
        unsigned int deep = 0;

        for (unsigned int i = 0; i < node->children.size(); i++)
        {
            deep = max(deep, get_depth(node->children[i].get()));
        }
        return deep + 1;
    }

    /**
     * This class represent a preorder iterator to the tree.
     */
    class PreOrderIterator
    {
    private:
        stack<TreeNode<T> *> nodes;

    public:
        /**
         * This is a constructor for the iterator.
         * @param root - the root of the tree to iterate on.
         * This function is explicit so the constructor will not be able to implicitly convert iterators to this one.
         */
        explicit PreOrderIterator(TreeNode<T> *root)
        {
            if (root)
            {
                nodes.push(root);
            }
        }

        /**
         * This function return the element that the iterator is "on" now.
         * @returns the top of the nodes stack.
         */
        TreeNode<T> *current()
        {
            return this->nodes.top();
        }

        /**
         * This function moves the iterator to the next element.
         * This iterator works in preorder, so after every node, comes the first of its children.
         * Therefore, the iterator pops the current node and pushs to the stack its second and then its first child.
         * @returns the data of the next node.
         */
        T next()
        {
            if (hasNext())
            {
                TreeNode<T> *node = nodes.top();
                nodes.pop();
                // push the children from the last to the first.
                for (int i = node->children.size() - 1; i >= 0; i--)
                {
                    nodes.push(node->children[i].get());
                }
                return node->get_data();
            }
            else
            {
                throw std::invalid_argument("no more elements!");
            }
        }

        /**
         * This function checks if the current element that the iterator is "on" has a next element.
         * @returns true if the current elemnet has next, false otherwise.
         */
        bool hasNext()
        {
            return !nodes.empty();
        }
    };

    /**
     * This function returns preorder iterator to the tree, if the tree is binary and not empty.
     * @returns preorder iterator for the tree.
     */
    PreOrderIterator begin_pre_order()
    {
        if (!root)
        {
            throw std::invalid_argument("This tree is null!");
        }
        if (this->k != 2)
        {
            throw std::invalid_argument("There is no preOrder iterator on a non-binary tree! call DFS instead!");
        }
        return PreOrderIterator(root.get());
    }

    /**
     * This function returns the element after the end of the tree (empty tree)
     * @returns end to compare with
     */
    PreOrderIterator end_pre_order()
    {
        if (!root)
        {
            throw std::invalid_argument("This tree is null!");
        }
        if (this->k != 2)
        {
            throw std::invalid_argument("There is no preOrder iterator on a non-binary tree! call DFS instead!");
        }
        return PreOrderIterator(nullptr);
    }

    /**
     * This class represent a postorder iterator to the tree.
     */
    class PostOrderIterator
    {
    private:
        std::stack<TreeNode<T> *> visited;
        std::stack<TreeNode<T> *> nodes;
        std::stack<TreeNode<T> *> reverse;

    public:
        /**
         * This is a constructor for the iterator.
         * @param root - the root of the tree to iterate on.
         * This function is explicit so the constructor will not be able to implicitly convert iterators to this one.
         * This function pushs after each node it pops all its children from the first to the last.
         * Then the function pushs all the remain nodes to the "visited" stack.
         * After that, the function reverse the stack to create the postOrder.
         */
        PostOrderIterator(TreeNode<T> *root)
        {
            if (!root)
            {
                throw std::invalid_argument("This tree is null!");
            }
            visited.push(root);
            while (!visited.empty())
            {
                TreeNode<T> *temp = visited.top();
                visited.pop();
                nodes.push(temp);
                for (unsigned int i = 0; i < temp->children.size(); i++)
                {
                    visited.push(temp->children[i].get());
                }
            }
            while (!nodes.empty())
            {
                visited.push(nodes.top());
                nodes.pop();
            }
            while (!visited.empty())
            {
                reverse.push(visited.top());
                visited.pop();
            }
        }

        /**
         * This function return the element that the iterator is "on" now.
         * @returns the top of the nodes stack.
         */
        TreeNode<T> *current()
        {
            return reverse.top();
        }

        /**
         * This function checks if the current element that the iterator is "on" has a next element.
         * @returns true if the current elemnet has next, false otherwise.
         */
        bool hasNext()
        {
            return !reverse.empty();
        }

        /**
         * This function returns the data of the next element.
         * @returns the data of the next element.
         */
        T next()
        {
            TreeNode<T> *temp = reverse.top();
            reverse.pop();
            return temp->get_data();
        }
    };

    /**
     * This function returns postorder iterator to the tree, if the tree is binary and not empty.
     * @returns postorder iterator for the tree.
     */
    PostOrderIterator begin_post_order()
    {
        if (!root)
        {
            throw std::invalid_argument("This tree is null!");
        }
        if (this->k != 2)
        {
            throw std::invalid_argument("There is no postOrder iterator on a non-binary tree! call DFS instead!");
        }
        return PostOrderIterator(root.get());
    }

    /**
     * This function returns the element after the end of the tree (empty tree)
     * @returns end to compare with
     */
    PostOrderIterator end_post_order()
    {
        if (!root)
        {
            throw std::invalid_argument("This tree is null!");
        }
        if (this->k != 2)
        {
            throw std::invalid_argument("There is no postOrder iterator on a non-binary tree! call DFS instead!");
        }
        return PostOrderIterator(nullptr);
    }

    /**
     * This class represent an inorder iterator to the tree.
     */
    class InOrderIterator
    {
    private:
        std::stack<TreeNode<T> *> nodes;

    public:
        /**
         * This is a constructor for the iterator.
         * @param root - the root of the tree to iterate on.
         * This function is explicit so the constructor will not be able to implicitly convert iterators to this one.
         * This is inorder iterator, ehich means that before each node will be its left child.
         * Therefore, the constructor pushs the first child of each node to the stack after it.
         */
        explicit InOrderIterator(TreeNode<T> *root)
        {
            while (root)
            {
                nodes.push(root);
                if (!root->children.empty())
                {
                    root = root->children[0].get();
                }
                else
                {
                    break;
                }
            }
        }

        /**
         * This function return the element that the iterator is "on" now.
         * @returns the top of the nodes stack.
         */
        TreeNode<T> *current()
        {
            return nodes.top();
        }

        /**
         * This function checks if the current element that the iterator is "on" has a next element.
         * @returns true if the current elemnet has next, false otherwise.
         */
        bool hasNext()
        {
            return !nodes.empty();
        }

        /**
         * This function returns the data of the next element.
         * If there is another element after the current, the function pushs the right child of the current node to the stack and after it,
         *     its left child and his left child and so on. Then the function pops the first element from the stack and return its value.
         * @returns the data of the next element.
         */
        T next()
        {
            if (hasNext())
            {
                TreeNode<T> *node = nodes.top();
                nodes.pop();
                if (node->children.size() == 2)
                {
                    TreeNode<T> *nextNode = node->children[1].get();
                    while (nextNode)
                    {
                        nodes.push(nextNode);
                        if (nextNode->children.size() != 0)
                        {
                            nextNode = nextNode->children[0].get();
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                return node->get_data();
            }
            else
            {
                throw std::invalid_argument("no more elements!");
                exit(1);
            }
        }
    };

    /**
     * This function returns inorder iterator to the tree, if the tree is binary and not empty.
     * @returns inorder iterator for the tree.
     */
    InOrderIterator begin_in_order()
    {
        if (this->k != 2)
        {
            throw std::invalid_argument("There is no inOrder iterator on a non-binary tree! call DFS instead!");
        }
        if (!root)
        {
            throw std::invalid_argument("This tree is null!");
        }
        return InOrderIterator(root.get());
    }

    /**
     * This function returns the element after the end of the tree (empty tree)
     * @returns end to compare with
     */
    InOrderIterator end_in_order()
    {
        if (this->k != 2)
        {
            throw std::invalid_argument("There is no inOrder iterator on a non-binary tree! call DFS instead!");
        }
        if (!root)
        {
            throw std::invalid_argument("This tree is null!");
        }
        return InOrderIterator(nullptr);
    }

    /**
     * This class represent a BFS iterator to the tree.
     */
    class BFSIterator
    {
    private:
        std::queue<TreeNode<T> *> nodes;

    public:
        /**
         * This is a constructor for the iterator.
         * @param root - the root of the tree to iterate on.
         * This function is explicit so the constructor will not be able to implicitly convert iterators to this one.
         */
        explicit BFSIterator(TreeNode<T> *root)
        {
            if (root)
                nodes.push(root);
        }

        /**
         * This function return the element that the iterator is "on" now.
         * @returns the top of the nodes stack.
         */
        TreeNode<T> *current()
        {
            return nodes.front();
        }

        /**
         * This function checks if the current element that the iterator is "on" has a next element.
         * @returns true if the current elemnet has next, false otherwise.
         */
        bool hasNext()
        {
            return !nodes.empty();
        }

        /**
         * This is a BFS iterator, which means that after each element come all of its direct children. Therefore, the function pops the first element,
         *      then pushs all its children and return its data.
         * @returns the data of the next element.
         */
        T next()
        {
            if (hasNext())
            {
                TreeNode<T> *node = nodes.front();
                nodes.pop();
                for (unsigned int i = 0; i < node->children.size(); i++)
                {
                    TreeNode<T> *child = (node->children[i].get());
                    if (child)
                        nodes.push(child);
                }
                return node->get_data();
            }
            else
            {
                throw std::invalid_argument("no more elements!");
                exit(1);
            }
        }
    };

    /**
     * This function returns BFS iterator to the tree, if the tree is not empty.
     * @returns BFS iterator for the tree.
     */
    BFSIterator begin_BFS_scan()
    {
        if (!root)
        {
            throw std::invalid_argument("This tree is null!");
        }
        return BFSIterator(root.get());
    }

    /**
     * This function returns the element after the end of the tree (empty tree)
     * @returns end to compare with
     */
    BFSIterator end_BFS_scan()
    {
        if (!root)
        {
            throw std::invalid_argument("This tree is null!");
        }
        return BFSIterator(nullptr);
    }

    /**
     * This class represent a DFS iterator to the tree.
     */
    class DFSIterator
    {
    private:
        std::stack<TreeNode<T> *> nodes;

    public:
        /**
         * This is a constructor for the iterator.
         * @param root - the root of the tree to iterate on.
         * This function is explicit so the constructor will not be able to implicitly convert iterators to this one.
         */
        explicit DFSIterator(TreeNode<T> *root)
        {
            if (root)
                nodes.push(root);
        }

        /**
         * This function return the element that the iterator is "on" now.
         * @returns the top of the nodes stack.
         */
        TreeNode<T> *current()
        {
            return nodes.top();
        }

        /**
         * This function checks if the current element that the iterator is "on" has a next element.
         * @returns true if the current elemnet has next, false otherwise.
         */
        bool hasNext()
        {
            return !nodes.empty();
        }

        /**
         * This is a DFS iterator, which means that after each node, comes its first child.
         * Therefore, the function pushs all of the current node's children from the last to the first.
         * Then, the function pops the first child from the stack and returns its value.
         */
        T next()
        {
            if (hasNext())
            {
                TreeNode<T> *node = nodes.top();
                nodes.pop();
                for (int i = node->children.size() - 1; i >= 0; --i)
                {
                    if (node->children[i])
                        nodes.push(node->children[i].get());
                }
                return node->get_data();
            }
            else
            {
                throw std::invalid_argument("no more elements!");
                exit(1);
            }
        }
    };

    /**
     * This function returns DFS iterator to the tree, if the tree is not empty.
     * @returns DFS iterator for the tree.
     */
    DFSIterator begin_DFS_scan()
    {
        if (!root)
        {
            throw std::invalid_argument("This tree is null!");
        }
        return DFSIterator(root.get());
    }

    /**
     * This function returns the element after the end of the tree (empty tree)
     * @returns end to compare with
     */
    DFSIterator end_DFS_scan()
    {
        if (!root)
        {
            throw std::invalid_argument("This tree is null!");
        }
        return DFSIterator(nullptr);
    }

    /**
     * This class represent a minHeap iterator to the tree.
     */
    class MinHeapIterator
    {
    private:
        vector<TreeNode<T> *> nodes;

        /**
         * This is a compare function to order the elements on the heap.
         * @param n1 - the first node to compare.
         * @param n2 - the second node to compare.
         * @returns true if n1 > n2, false otherwise.
         */
        static bool greater(const TreeNode<T> *n1, const TreeNode<T> *n2)
        {
            return (n1->get_data() > n2->get_data());
        }

    public:
        /**
         * This is a constructor for the iterator.
         * @param root - the root of the tree to make heap from.
         * This function is explicit so the constructor will not be able to implicitly convert iterators to this one.
         * The function pushs all the tree's element to a vector and uses std::make_heap.
         */
        explicit MinHeapIterator(TreeNode<T> *root)
        {
            for (auto iterator = PreOrderIterator(root); iterator.hasNext(); iterator.next())
            {
                this->nodes.push_back(iterator.current());
            }
            std::make_heap(nodes.begin(), nodes.end(), greater);
        }

        /**
         * This function return the element that the iterator is "on" now.
         * @returns the top of the nodes stack.
         */
        TreeNode<T> *current()
        {
            return this->nodes.front();
        }

        /**
         * This function checks if the current element that the iterator is "on" has a next element.
         * @returns true if the current elemnet has next, false otherwise.
         */
        bool hasNext()
        {
            return !this->nodes.empty();
        }

        /**
         * This function returns the next element.
         * The function also remove the element of the list and reorganize the heap.
         * @returns the data of the next element.
         */
        T next()
        {
            std::pop_heap(nodes.begin(), nodes.end(), greater);
            nodes.pop_back();
            TreeNode<T> *temp = nodes.front();
            return temp->get_data();
        }
    };

    /**
     * This function returns minHeap iterator to the tree, if the tree is binary and not empty.
     * @returns minHeap iterator for the tree.
     */
    MinHeapIterator myHeap()
    {
        if (!root)
        {
            throw std::invalid_argument("This tree is null!");
        }
        if (this->k != 2)
        {
            throw std::invalid_argument("Can not make hip from non-binary tree! call DFS instead!");
        }
        return MinHeapIterator(root.get());
    }

    template <class T1>
    friend std::ostream &operator<<(std::ostream &os, const Tree<T1> &t);
    /**
     * This is a destructor for the tree.
     * I used shared pointers and did not allocated any memory, and thats why the constructor is empty.
     */
    ~Tree()
    {
    }
};

/**
 * This is a recurcive help function to draw the tree.
 * The function draws a node in its position regard to its parent and siblings.
 * @param node the node to draw.
 * @param depth the tree's depth, needed to computes the yth value of the center of the node.
 * @param level the level of the node in the tree. The root is in level 1, its children is in level 2 and so on.
 * @param width the width of the space to draw the node. This space will be devide to its children.
 * @param x_start the xth value to begin the node's space from.
 */
template <class T>
void draw_tree(TreeNode<T> *node, unsigned int depth, unsigned int level, unsigned int width, unsigned int x_start)
{
    ClearBackground(WHITE);
    unsigned int x = x_start + (width / 2);
    unsigned int y = (((HEIGHT / depth) * (level - 1)) + NODE_RADIUS + 20);
    DrawCircleLines(x, y, NODE_RADIUS, DARKPURPLE);
    string node_string = node->get_data().to_string();
    DrawText(node_string.c_str(), x - 40, y - 20, 20, DARKPURPLE);
    for (unsigned int i = 0; i < node->children.size(); i++)
    {
        if (node->children[i].get())
        {
            unsigned int width_part = width / node->children.size();
            unsigned int x_next = (x_start + width_part * i) + (width_part / 2);
            unsigned int y_next = ((HEIGHT / depth) * (level) + NODE_RADIUS + 20);
            DrawLine(x, y + NODE_RADIUS, x_next, y_next - NODE_RADIUS, DARKPURPLE);
            draw_tree(node->children[i].get(), depth, level + 1, width_part, x_start + width_part * i);
        }
    }
}

/**
 * This is an overload for the operator <<.
 * The function opens a window, calls the recurcive help function
 *     and closes the window when the user click on the X buttom.
 * @param os ostream to return.
 * @param t tree to print.
 * @returns the ostream os.
 */
template <class T>
std::ostream &operator<<(std::ostream &os, const Tree<T> &t)
{
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(WIDTH, HEIGHT, "Tree visualization");
    SetTargetFPS(60); // frames per second to present, can be anything
    BeginDrawing();
    unsigned int depth = t.get_depth(t.get_root());
    draw_tree(t.get_root(), depth, 1, WIDTH, 0);
    EndDrawing();
    while (!WindowShouldClose())
    {
        BeginDrawing();
        EndDrawing();
    }
    CloseWindow();
    return os;
}