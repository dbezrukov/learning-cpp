#include <iostream>
#include <map>

#include "hashmap.h"

int main()
{
    /** Хэш отображение работает быстрее обычного отображения
        Ниже приведен пример таблицы студентов, где ключу id соответствует имя студента
        Запрещено дублирование id
        Теоретически, если хеш функция не стойка к коллизиям, хеш-коды для двух разных ключей могут совпасть,
        поэтому в сегментах сделаны списки. H(key1)=H(key2) -возникает коллизия
    */

    hashmap<int, string> myHash;
    myHash.insert( make_pair(2046, "Ivan Petrov") );
    myHash.insert( make_pair(4027, "Olga Sidorova") );

    /// Печать hashmap с использованием итератора
    for (hashmap<int, string>::iterator it = myHash.begin(); it != myHash.end(); ++it)
    {
        /// Тестируем операторы * и ->
        cout << it->first << " maps to " << (*it).second << endl;
    }

    /// Создем отображение
    map<int, string> myMap(myHash.begin(), myHash.end());
    for (map<int, string>::iterator it = myMap.begin(); it != myMap.end(); ++it)
    {
        cout << it->first << " maps to " << (*it).second << endl;
    }

    return 0;
}
