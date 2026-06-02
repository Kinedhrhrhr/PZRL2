#include "splay_tree_api.h"
#include <iostream>
#include <string>

int main()
{
    SplayTree<int, std::string> tree;
    tree.insert(10, "слово");
    tree.insert(1, "10");
    auto* val1 = tree.search(10);
    auto* val2 = tree.search(1);
    if (val1 and val2) 
    {
        std::cout << *val1 << std::endl;
	std::cout << *val2 << std::endl;
    }
    std::cout << tree.size() << std::endl;
    return 0;
}
