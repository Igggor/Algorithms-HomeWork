#include "typemap.h"
#include <iostream>
#include <string>
#include <cassert>

struct Configuration {
    std::string name;
    bool operator==(const Configuration &other) const { return name == other.name; }
};

struct Metadata {
    long identifier;
    bool operator==(const Metadata &other) const { return identifier == other.identifier; }
};

int main(){
    typemap::TypeMap<long, float, Configuration, Metadata> registry;

    assert(registry.Size() == 0);
    assert(registry.Capacity() == 4);

    // Добавление значений разных типов
    registry.AddValue<long>(999999L);
    registry.AddValue<float>(2.71828f);
    registry.AddValue<Configuration>({"AppSettings"});
    registry.AddValue<Metadata>({12345});

    // Проверка размера после добавления
    assert(registry.Size() == 4);
    assert(registry.Capacity() == 4);

    // Проверка наличия элементов
    assert(registry.Contains<long>());
    assert(registry.Contains<float>());
    assert(registry.Contains<Configuration>());
    assert(registry.Contains<Metadata>());

    // Извлечение и валидация значений
    assert(registry.GetValue<long>() == 999999L);
    assert(registry.GetValue<float>() == 2.71828f);
    assert(registry.GetValue<Configuration>().name == "AppSettings");
    assert(registry.GetValue<Metadata>().identifier == 12345);

    // Удаление элемента
    registry.RemoveValue<float>();
    assert(!registry.Contains<float>());
    assert(registry.Size() == 3);

    // Проверка оставшихся элементов
    assert(registry.Contains<long>());
    assert(registry.Contains<Configuration>());
    assert(registry.Contains<Metadata>());

    // Изменение значения
    registry.AddValue<Configuration>({"UpdatedSettings"});
    assert(registry.GetValue<Configuration>().name == "UpdatedSettings");

    // Полная очистка
    registry.Clear();
    assert(registry.Size() == 0);
    assert(!registry.Contains<long>());
    assert(!registry.Contains<Configuration>());
    assert(!registry.Contains<Metadata>());

    std::cout << "Все тесты TypeMap выполнены без ошибок" << std::endl;
    return 0;
}