# Banned-domains
  Небольшая программа для составления списка заблокированных доменных имен
***

## Развертывание
```
g++ domains.cpp -o domains -std=c++17 -O3
./domains < input.txt
```
# Формат входных данных
В первой строке написано количество запрещённых доменов.

Далее перечислены запрещённые домены, каждый на отдельной строке.

На следующей строке указано количество проверяемых доменов.

Далее перечислены проверяемые домены, каждый на отдельной строке.
# Формат выходных данных
Выводится результат для каждого проверяемого домена на отдельной строке.

Выводится Bad, если домен запрещён, и Good, если разрешён.
    
## Использование
### Ввод
```
4
gdz.ru
maps.me
m.gdz.ru
com
7
gdz.ru
gdz.com
m.maps.me
alg.m.gdz.ru
maps.com
maps.ru
gdz.ua 
```
### Вывод
```
Bad
Bad
Bad
Bad
Bad
Good
Good 
```
