# Робот

Вы пишете программу для управления роботом, который перемещается в двумерном дискретном пространстве.
Робот стартует в некоторой начальной точке (клетке). Задача робота - дойти до заданной целевой точки.

Некоторые точки могут быть помечены как препятствия. Робот не может переходить
в точку, являющуюся препятствием.

Робот взаимодействует только с окружающим миром (класс `World`) и может
совершать следующие действия:
- `Lookup` - получает точки, в которые в текущей топологии пространства
робот может перейти за один ход и расстояния до целевой точки от каждой из них.
- `Move` - перейти в выбранную точку. При попытке перехода в точку, в которую нельзя перейти за один шаг,
бросает исключение `IllegalMoveException`
- Получать значения стартовой, целевой и своей текущей точки

Мир зависит от топологии (класс `Topology`), определяющей структуру пространства.
Робот не знает, в какой топологии он находится.

В функции `robot::FindPath` необходимо найти кратчайший путь (вектор точек)
от стартовой до целевой клетки. Если путь не существует, вектор должен быть пустым.
Каждая точка в пути должна встречаться только один раз.
Первой точкой в пути должна быть стартовая точка, а последней - целевая.

## Топологии

Во всех топологиях расстоянием между точками `p1` и `p2` считается длина кратчайшего пути
(в шагах робота) между `p1` и `p2`. Если путь между точками не существует, метод
`Topology::MeasureDistance` возвращает `Topology::UNREACHABLE`.

Нужно реализовать следующие топологии:

### Planar

Поле описывается прямоугольником и ограничено со всех сторон. Робот может двигаться на одну клетку вверх, вниз, влево и вправо.

### Overflow

Аналогично `Planar`, но можно переходить через край поля.

### Knight

Поле ограничено со всех сторон. Робот двигается по правилам шахматного коня. Может
"перепрыгивать" через препятствия.

### Checkers

Поле ограничено со всех сторон. Робот двигается по правилам шашек: на одну клетку по диагонали.
Если по диагонали от робота находится препятствие, а следующая клетка в этом же направлении
свободна, робот может совершить переход на неё. Прыжки через препятствия можно комбинировать в рамках
одного хода.

## Реализация

Используйте наследование для выделения общего поведения и виртуальный полиморфизм для
реализации обобщенных алгоритмов.

Общую логику, связанную с созданием и хранением двумерного поля реализуйте в классе
`Field`. Конструктор `Field` должен принимать карту поля - `std::vector<std::vector<bool>>`,
где `true` означает наличие препятствия.