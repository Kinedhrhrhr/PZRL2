#include "FL.h"
#include <iostream>

int main()
{
    using namespace names;
    ForwardList list;
    std::cout << "1. Проверка empty() в начале: " << (list.empty() ? "список пуст" : "список не пуст") << std::endl;

    std::cout << "2. Добавление элементов через push_front():" << std::endl;
    list.push_front(5.5);
    list.push_front(3.2);
    list.push_front(7.8);
    list.push_front(3.2);
    list.display();

    std::cout << "3. Первый элемент (front()): " << list.front() << std::endl;

    std::cout << "4. Размер списка (size()): " << list.size() << std::endl;

    std::cout << "5. Удаление первого элемента (pop_front()):" << std::endl;
    list.pop_front();
    list.display();

    std::cout << "6. Удаление всех элементов со значением 3.2 (erase(3.2)):" << std::endl;
    list.erase(3.2);
    list.display();

    std::cout << "7. Добавим 2.2, 2.2 в начало:" << std::endl;
    list.push_front(2.2);
    list.push_front(2.2);
    list.display();

    std::cout << "8. Удаление всех элементов со значением 2.2 (erase(2.2)):" << std::endl;
    list.erase(2.2);
    list.display();

    std::cout << "9. Очистка списка (clear()):" << std::endl;
    list.clear();
    list.display();

    std::cout << "10. pop_front() на пустом списке:" << std::endl;
    list.pop_front();

    std::cout << "11. Поиск цикла: " << std::endl;

    ForwardList listcycle;
    for (int i = 1; i <= 5; ++i)
        listcycle.push_front(i);

    listcycle.display();

    Node* last_node = listcycle.get_node(4);
    Node* third_node = listcycle.get_node(2);
    last_node->next = third_node;

    std::cout << "Новый список с циклом: " << std::endl;
    listcycle.display();

    auto [cycle_start, cycle_length] = listcycle.find_cycle();

    if (cycle_start != nullptr)
    {
        std::cout << "Цикл найден" << std::endl;
        std::cout << "Значение в начале цикла: " << cycle_start->data << std::endl;
        std::cout << "Длина цикла: " << cycle_length << std::endl;
    }
    else
    {
        std::cout << "Цикл не найден" << std::endl;
    }
    return 0;
}
