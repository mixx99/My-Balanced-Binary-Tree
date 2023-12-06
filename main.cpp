
#include <iostream>
#include "MyTree.h"

int main()
{
    Tree<int> root(5);

    
    root.insert(4);
    root.erase(4);
    std::cout << root.is_find(5);

    return 0;
}
