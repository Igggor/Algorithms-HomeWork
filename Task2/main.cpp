#include <iostream>
#include <type_traits>
#include "typelist.h"
#include "typelist_detail.h"

struct A{};
struct B{};
struct C{};
struct D{};
struct E{};

int main(){
    using namespace typelist;

    using Standard = TypeList<A, B, C>;
    using Clone = TypeList<A, B, C>;
    using Variant = TypeList<A, B, D>;
    using Empty = TypeList<>;

    static_assert(Standard{} == Clone{}, "Lists with identical types must compare equal");
    static_assert(!(Standard{} == Variant{}), "Different lists must not be equal");
    static_assert(Standard{} != Variant{}, "Operator!= should distinguish non-equal lists");

    static_assert(size_v<Standard> == 3);
    static_assert(size(Standard{}) == size(Clone{}));
    static_assert(size(Empty{}) == 0);

    using First = decltype(type_at<0>(Standard{}));
    using Second = decltype(type_at<1>(Standard{}));
    using Third = decltype(type_at<2>(Standard{}));

    static_assert(std::is_same_v<First, A>);
    static_assert(std::is_same_v<Second, B>);
    static_assert(std::is_same_v<Third, C>);
    static_assert(std::is_same_v<type_at_t<0, Standard>, A>);
    static_assert(std::is_same_v<type_at_t<1, Standard>, B>);
    static_assert(std::is_same_v<type_at_t<2, Standard>, C>);

    constexpr bool foundA = contains<A>(Standard{});
    constexpr bool foundD = contains<D>(Standard{});
    static_assert(foundA);
    static_assert(!foundD);
    static_assert(contains_v<C, Standard>);
    static_assert(!contains_v<E, Standard>);

    constexpr int whereA = index_of<A>(Standard{});
    constexpr int whereB = index_of<B>(Standard{});
    constexpr int whereC = index_of<C>(Standard{});
    static_assert(whereA == 0);
    static_assert(whereB == 1);
    static_assert(whereC == 2);
    static_assert(index_of_v<B, Standard> == 1);

    using InsertedFront = push_front_t<TypeList<B, C>, A>;
    using InsertedBack = push_back_t<TypeList<A, B, C>, D>;
    static_assert(std::is_same_v<InsertedFront, TypeList<A, B, C>>);
    static_assert(std::is_same_v<InsertedBack, TypeList<A, B, C, D>>);
    static_assert(push_front<A>(TypeList<B, C>{}) == Standard{});
    static_assert(push_back<D>(Standard{}) == TypeList<A, B, C, D>{});

    using AfterPop = pop_front_t<Standard>;
    static_assert(std::is_same_v<AfterPop, TypeList<B, C>>);
    static_assert(pop_front(Standard{}) == TypeList<B, C>{});

    static_assert(pop_front(push_front<D>(Standard{})) == Standard{});
    static_assert(push_front<D>(pop_front(Standard{})) == TypeList<D, B, C>{});

    static_assert(push_front<A>(Empty{}) == TypeList<A>{});
    static_assert(push_back<A>(Empty{}) == TypeList<A>{});
    static_assert(pop_front(TypeList<A>{}) == TypeList<>{});

    using Huge = TypeList<int, double, char, float, long, short, A, B, C, D, E>;
    static_assert(size(Huge{}) == 11);

    std::cout << "TypeList compile-time verification completed." << std::endl;
    return 0;
}
