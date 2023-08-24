<div align="center">
Министерство науки и высшего образования Российской Федерации <br />
Федеральное государственное бюджетное образовательное учреждение <br />
высшего образования <br />
«Московский государственный технический университет <br />
имени Н.Э. Баумана <br />
(национальный исследовательский университет)» <br />
(МГТУ им. Н.Э. Баумана)
</div>
<hr />
<div align="center">
ФАКУЛЬТЕТ ИНФОРМАТИКА И СИСТЕМЫ УПРАВЛЕНИЯ <br />
КАФЕДРА КОМПЬЮТЕРНЫЕ СИСТЕМЫ И СЕТИ (ИУ6)
</div>
<br />
<div align="center">
ОТЧЕТ <br />
к лабораторной работе №2 <br />
по дисциплине "Современные средства разработки <br />
программного обеспечения" <br />
Реализация типовых решений с применением шаблонов проектирования.
</div>
<br />

Преподаватель: Фетисов М.В.

Студент группы ИУ6-55Б Рожков А.В.
## Описание задания

Задание №2: Шаблон проектирования Builder (строитель).

С использованием шаблона проектирования Builder (строитель) реализуйте заполнение коллекции карточек вашего домашнего задания и вывода содержимого в стандартный поток.
## Адрес проекта

Проект хранится в репозитории по адресу: [https://bmstu.codes/lsx/mstd/iu6-5-2020/iu6-55b-avrozhkov/l2](https://bmstu.codes/lsx/mstd/iu6-5-2020/iu6-55b-avrozhkov/l2).

## Диаграммы классов

Диаграммы класса AutoPartsStore и других зависимых классов находятся в папке: https://bmstu.codes/lsx/mstd/iu6-5-2020/iu6-55b-avrozhkov/l2/-/tree/master/images
## Функция main

```cpp
    int main() {
        ChainAutoPartsStore stores;
    
        TransmissionBuilder tb;
        stores.set_auto_parts_builder(&tb);
        stores.create_new_auto_parts_store();
        auto part = stores.get_auto_parts_store();
        part->show_auto_arts_store();
    
        BodyKitBuilder kit_builder;
        stores.set_auto_parts_builder(&kit_builder);
        stores.create_new_auto_parts_store();
        auto kit_builder_part = stores.get_auto_parts_store();
        kit_builder_part->show_auto_arts_store();
    
        WheelsBuilder wheels_builder;
        stores.set_auto_parts_builder(&wheels_builder);
        stores.create_new_auto_parts_store();
        auto wheels_builder_builder_part = stores.get_auto_parts_store();
        wheels_builder_builder_part->show_auto_arts_store();
        return 0;
    }
```

Описание классов хранится в репозитории по адресу: https://bmstu.codes/lsx/mstd/iu6-5-2020/iu6-55b-avrozhkov/l2

## Выводы

В ходе выполнения данной лабораторной работы была получена рабочая программа, соответствующая требованиям из задания, изучен и применен на практике шаблон проектирования Builder (строитель). Также были улучшены навыки работы с внешним репозиторием кода и сценарием непрерывной интеграции. Получены навыки работы с Doxyfile.cfg
