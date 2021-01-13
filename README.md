# Симуляция жизни

## Описание проекта

![Скриншот программы](https://github.com/kot239/fat-lions/blob/master/pics/snap.png)

Результат нашего проекта – модель экосистемы. В этой экосистеме будут находится «хищники», «травоядные» и «растения». Каждый объект в экосистеме имеет свои особенности.

«Хищники» имеют определенный срок жизни. Чтобы выжить и не умереть от голода, они должны питаться травоядными.

«Травоядные» также имеют определенный срок жизни. Чтобы выжить, они должны питаться растениями. Они могут умереть из-за разных причин. Первая – естественная смерть из-за нехватки еды. Вторая – они могут быть съедены «хищниками».

«Растения» являются источником питания для травоядных.
Все объекты будут находится на карте местности, где могут быть препятствия.
У животных есть общие особенности: видят в каком-то радиусе, имеют направление движения. Если животные сыты и им не угрожает опасность, они могут размножаться, в результате появляется потомство, соединяющее в себе параметры отца и матери. Особи разделяются по полу.

Животные имеют 2 разные модели поведения: векторную и случайную.

Пользователь перед началом запуска системы может вводить начальное количество животных. В процессе же запуска экосистемы пользователь может менять логику животных, а также наблюдать на графике количество животных в определенные промежутки времени. Дополнительно пользователь может нажимать на животных и смотреть, что это за животное и какой у него пол.

Данная программа позволяет исследовать некоторые биологические законы, например, принцип экологической пирамиды.

## Разделение обязанностей

* Абрамов Никита (tg: [@n8ron][]): Создание модели системы

* Багрянова Екатерина (tg: [@bagryanova][]): Создание классов и структур

* Тарабонда Герман(tg: [@kot239][]): Создание графики модели

[@n8ron]: https://t.me/n8ron

[@bagryanova]: https://t.me/bagryanova

[@kot239]: https://t.me/kot239

## Используемые системы

QT 5.14.1 совместно с библиотекой QT5Charts

## Инструкция по установке и запуску

### Установка QT на Linux Ubuntu 16.04

```
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install qt5-default qtbase5-dev libqt5charts5 libqt5charts5-dev
```

### Установка QT на MacOS

```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
brew install qt5
```

Вместо этого можно скачать QT Creator Open Source по данной ссылке: https://www.qt.io/download

### Запуск программы

Можно запустить с помощью CMake: 
```
cmake .
make
./LifeSimulation
```

Можно запустить с помощью QT Creator:

1. Запустите CMakeLists.txt с помощью QT Creator.
2. В правом нижнем углу экрана будет кнопка "Настроить проект", нажмите на нее.
3. Нажмите на зеленый треугольник и проект запуститься.

По вопросам сборки обращаться [сюда][@kot239]

# Life Simulation

## Project Description

The result of our project is the model of ecosystem. There are different objects: ‘predators’, ‘herbivores’ and ‘plants’. Each object has own features.

‘Predators’ have a certain age of life. They should eat ‘herbivorous’ to survive.

‘Herbivores’ have a certain age of life too. They should eat ‘plants’ to survive. They could die for different reasons. First, they could die because of hunger. Second, they could be eaten by ‘predators’.

‘Herbs’ are source of power for ‘herbivores’. All objects are located on the map where obstacles could be. Animals have common features: they can see only in fixed radius, and they have direction. If animals don’t feel hungry, and they don’t feel danger then they can produce offspring that have mixed features from mother and father. Also, animals have sex.

Animals have two models of behavior: vector and random. 

User can choose initial amount of animal before model launch. While the model is launched user can change animals behavior and see the amount of animals as well. Likewise, the user can touch an animal to find some information about it.

This model allows exploring biological laws, for example, the principle of ecological pyramid.

## Segregation of duties

* Abramov Nikita (tg: [@n8ron][]): Creating a model system 

* Bagryanova Ekaterina (tg: [@bagryanova][]): Creating classes and structures

* Tarabonda German (tg: [@kot239][]): Creating a model graphic

[@n8ron]: https://t.me/n8ron

[@bagryanova]: https://t.me/bagryanova

[@kot239]: https://t.me/kot239

## System used

QT 5.14.1 together with library QT5Charts

## Installation instruction

### Installation QT on Linux Ubuntu 16.04

```
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install qt5-default qtbase5-dev libqt5charts5 libqt5charts5-dev
```

### Installation QT on MacOS

```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"
brew install qt5
```

Instead, you can download the QT Creator Open Source from this link: https://www.qt.io/download

### Run the program

You can run the program using CMake: 
```
cmake .
make
./LifeSimulation
```

You can run the program using QT Creator:

1. Run CMakeLists.txt using QT Creator.
2. Push the button ‘Configure project’ in the lower right corner of the window.
3. Push the green triangle to run the project.

If you have any questions about how to run the program: write [here][@kot239]
