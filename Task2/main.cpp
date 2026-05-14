#include <iostream>
#include <type_traits>
#include "typelist.h"
#include "typelist_detail.h"

class Widget {};
class Service {};
class Model {};
class View {};
class Controller {};

int main(){
    using namespace typelist;

    using List1 = TypeList<Widget, Service, Model>;
    using List2 = TypeList<Widget, Service, Model>;
    using List3 = TypeList<Widget, Service, View>;
    using NullList = TypeList<>;

    // Проверки равенства и неравенства
    static_assert(List1{} == List2{});
    static_assert(!(List1{} == List3{}));
    static_assert(List1{} != List3{});
    
    // Проверка размера
    static_assert(size_v<List1> == 3);
    static_assert(size(List1{}) == 3);
    static_assert(size(NullList{}) == 0);
    static_assert(size(List1{}) != size(NullList{}));

    // Доступ к элементам с использованием type_at
    static_assert(std::is_same_v<type_at_t<0, List1>, Widget>);
    static_assert(std::is_same_v<type_at_t<1, List1>, Service>);
    static_assert(std::is_same_v<type_at_t<2, List1>, Model>);

    auto elem0 = type_at<0>(List1{});
    auto elem1 = type_at<1>(List1{});
    static_assert(std::is_same_v<decltype(elem0), Widget>);
    static_assert(std::is_same_v<decltype(elem1), Service>);

    // Проверка принадлежности
    static_assert(contains_v<Widget, List1>);
    static_assert(contains_v<Model, List1>);
    static_assert(!contains_v<View, List1>);
    static_assert(!contains_v<Controller, List1>);

    constexpr auto hasWidget = contains<Widget>(List1{});
    constexpr auto hasController = contains<Controller>(List1{});
    static_assert(hasWidget);
    static_assert(!hasController);

    // Поиск позиции
    static_assert(index_of_v<Widget, List1> == 0);
    static_assert(index_of_v<Service, List1> == 1);
    static_assert(index_of_v<Model, List1> == 2);

    constexpr auto pos0 = index_of<Widget>(List1{});
    constexpr auto pos2 = index_of<Model>(List1{});
    static_assert(pos0 == 0);
    static_assert(pos2 == 2);

    // Операции вставки в начало
    using PrependView = push_front_t<TypeList<Service, Model>, Widget>;
    static_assert(std::is_same_v<PrependView, List1>);
    static_assert(push_front<Widget>(TypeList<Service, Model>{}) == List1{});

    auto r1 = push_front<Controller>(TypeList<Widget, Service>{});
    static_assert(r1 == TypeList<Controller, Widget, Service>{});

    // Операции вставки в конец
    using AppendController = push_back_t<TypeList<Widget, Service>, Model>;
    static_assert(std::is_same_v<AppendController, List1>);
    static_assert(push_back<Model>(List1{}) == TypeList<Widget, Service, Model, Model>{});

    auto r2 = push_back<View>(List1{});
    static_assert(r2 == TypeList<Widget, Service, Model, View>{});

    // Удаление из начала
    using Truncated = pop_front_t<List1>;
    static_assert(std::is_same_v<Truncated, TypeList<Service, Model>>);
    static_assert(pop_front(List1{}) == TypeList<Service, Model>{});

    // Составные операции
    static_assert(
        pop_front(push_front<View>(List1{})) == List1{}
    );
    
    static_assert(
        push_front<Controller>(pop_front(List1{})) == 
        TypeList<Controller, Service, Model>{}
    );

    // Граничный случай: один элемент
    using Single = TypeList<Widget>;
    static_assert(size(Single{}) == 1);
    static_assert(pop_front(Single{}) == NullList{});
    static_assert(push_front<Service>(pop_front(Single{})) == TypeList<Service>{});

    // Граничный случай: пустой список
    static_assert(push_front<Widget>(NullList{}) == Single{});
    static_assert(push_back<Widget>(NullList{}) == Single{});

    // Большой составной список
    using MixedList = TypeList<int, double, Widget, char, Service, float, Model, long, View, short, Controller>;
    static_assert(size(MixedList{}) == 11);
    static_assert(contains_v<Service, MixedList>);
    static_assert(contains_v<double, MixedList>);
    static_assert(index_of_v<Service, MixedList> == 4);

    std::cout << "Тестирование TypeList прошло у" << std::endl;
    return 0;
}
