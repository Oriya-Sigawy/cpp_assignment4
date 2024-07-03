# cpp_assignment4
In this assignment I made a template class of Tree that has nodes with template data.  
For that, I wrote a TreeNode struct that has:  
* template data  
* vector of shared pointers to children  
* constructor  
* method to add child  
* method to get the data   

The pointers to the children are shared_ptrs because I wanted to make sure that every child has exactly one parent, and shared_ptr allow me to count the number of the pointers to the same object.  
  
The Tree class has 2 constructors, destructor, 5 methods and 6 inner - classes of iterators, and function begin and end to each iterator.  
I will explain them one by one.  

`Constructors` : 
* `default constructor`: constructor that gets only the max degree and initialize the root to nullptr.
* `copy constructor`: constructor that gets the max degree and a shared_ptr to the root, the constructor copy them.  

`Destructor` :
* `Empty destructor`: this destructor does not do anything, because my program didn't allocate any menory.

`Methods` :
* `get_k()`: returns the max degree of the tree.
* `add_root()`: copy the root it gets if the existing root is nullptr.
* `add_sub_node()`: add a child to a node in the tree.
*  `get_root()`: returns the tree's root.
*  `get_depth()`: computes the tree's depth by recursion and returns it.

`Iterators` :  
Each iterator has a constructor and the methods current, hasNext and next.   
All the iterator's constructors have the keyword *explicit*, so no iterator will be implicitly convert to the iterators I wrote.
* `preOrder`:
  **works only on binary trees!**  
    * `constructor` - pushs the tree root it gets to the stack (and by that starting the iteration- the root will pop first and push its left child).  
    * `currnt` - returns the top of the iterator's stack.  
    * `hasNext` - checks if the iterator's stack is empty.  
    * `next` - pops the first node from the stack. Pushs the node's children from last to first to the stack and returns the data of the node.

* `postOrder`:
  **works only on binary trees!**  
    * `constructor` - pushs the tree root it gets to the nodes stack. Then pushs all its children to the visited stack from first to last, then pops the first element from the visited and pushs it to the nodes stack, and pushs its children to the visited from first to last, and so on.  
      Then moves what remains on the visited stack to the nodes stack and reverse it (push it to the reverse stack on the opposite order).  
    * `currnt` - returns the top of the reverse stack.  
    * `hasNext` - checks if the reverse stack is empty.  
    * `next` - pops the first node from the reverse stack and return its value.

* `inOrder`:
    **works only on binary trees!**  
    * `constructor` - pushs the tree root it gets to the iterator's stack, then pushs to it the root's left child, and his left child, and so on.  
    * `currnt` - returns the top of the iterator's stack.  
    * `hasNext` - checks if the iterator's stack is empty.  
    * `next` - pops the first node from the iterator's stack. Pushs to the stack its right child and the left child of the right child and its left child and so on. when it gets to nullptr, returns the node's data.

* `BFS`:
    * `constructor` - pushs the tree root it gets to the iterator's stack.
    * `currnt` - returns the top of the iterator's stack.  
    * `hasNext` - checks if the iterator's stack is empty.  
    * `next` - pops the first node from the iterator's stack. Pushs to the stack its children from first to last and returns the node's data.

* `DFS`:
    * `constructor` - pushs the tree root it gets to the iterator's stack.
    * `currnt` - returns the top of the iterator's stack.  
    * `hasNext` - checks if the iterator's stack is empty.  
    * `next` - pops the first node from the iterator's stack. Pushs to the stack its children from last to first and returns the node's data.
 
* `myHeap`:
    **works only on binary trees!**  
    * `constructor` - pushs the tree nodes to the iterstor's vector and sends the vector and the method "greater()" to std::make_heap.
    * `greater` - this is a comparator to pass to std::make_heap. Returns true if the first variable it gets is greater than the other, false otherwise.
    * `currnt` - returns the front of the iterator's vector.  
    * `hasNext` - checks if the iterator's vector is empty.  
    * `next` - remove the first node from the iterator's vector, makes heap again without it and returns its value.
 
`GUI`:  
For the gui I used the library raylib.
I wrote 2 functions to make the gui, both of them are in the end of Tree.hpp.
* `<<`: The function is an overload  for the operator <<.  
  The function opens a gui window, starts to draw ,calls to the helper recursive function and finishs to draw.  
  When the user clicks on the X, the function closes the gui window.  
  **PAY ATTENTION - THE PROGRAM WILL NOT CUNTINUE TO RUN UNTILL THE USER WILL CLOSE THE GUI WINDOW!**
* `draw_tree`: This function draws the node its gets by the parameters it gets, and draws a line from the node to each one of its children.  
  The function computes the location of the node's children by the location of the node itself and other parameters (the height of the gui window, the amount of children the node has).  
  The function calls to itself with the computed parameters.

  
Additionally, as requested, I wrote a Main that uses my Tree class.    
I used complex numbers as the template data. For that, I copied the Complex.cpp, Complex.hpp from the curse github, and added them getters to the real and the image parts of the complex number, function to_string (for the gui) and an overload to the operator > as I did in assignment 2.
