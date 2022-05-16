# numerical-methods

lab1

Napisz program w języku „C/C++”, umożliwiający „doświadczalne” wyznaczenie liczby bitów mantysy oraz tzw. epsylona maszynowego, dla zmiennych typu float i double, tj. 
najmniejszej liczby E takiej, że fl( E + 1) > 1. Aby znaleźć odpowiedź na pytanie jak napisać taki program, zacznij od wyjaśnienia kwestii jaki jest związek E z 
precyzją arytmetyki.

lab2

Zaimplementuj w języku „C/C++” algorytm obliczający przybliżone wartości funkcji f(x) = [1 - exp(-x)]/x dla x należącego do [10^-30, 10^9], korzystając z funkcji standardowej
exp(). W oparciu o zbiór dokładnych wartości tej funkcji, udostępniony przez prowadzącego zajęcia, zbadaj jak zmieniają się błędy względne przybliżenia funkcji w tym 
algorytmie, w zależności od x. W tym celu wykonaj rysunek przedstawiający zależność logarytmu dziesiętnego z bezwzględnej wartości błędu względnego od logarytmu dziesiętnego 
z x. Z wykresu odczytaj zakres zmiennej x, w którym błąd względny pozostaje na poziomie błędu reprezentacji, oraz zakres zmiennej x, w którym błąd względny jest większy. 
Wyjaśnij przyczynę obserwowanych zmian błędów. Na tej podstawie zaproponuj alternatywny sposób obliczania wartości funkcji f(x) w sytuacjach gdy obserwowany błąd jest duży. 
Dokonaj stosownej modyfikacji programu, tak aby uzyskać błąd względny na poziomie błędu reprezentacji (czyli tzw. dokładność maszynową) dla dowolnego x należącego 
do [10^-30, 10^9]. W obliczeniach zastosuj zmienne podwójnej precyzji.

lab3

Napisz program w języku „C/C++”, realizujący metody:
(a) Picarda
(b) bisekcji
(c) Newtona
(d) siecznych
rozwiązywania pojedynczych algebraicznych równań nieliniowych. Zastosuj program do przykładów z zadania 1. Zastosuj trzy niezależne kryteria zakończenia iteracji. Zadbaj o to,
aby wyprowadzać na konsolę wyniki pośrednie obliczeń dla każdej iteracji, tak aby możliwe było obserwowanie zbieżności kolejnych przybliżeń pierwiastków i porównanie liczby 
iteracji niezbędnych do uzyskania rozwiązania o zadanej dokładności przez każdą z metod. W szczególności oblicz jak zmienia się estymator błędu rozwiązania oraz residuum 
równania w trakcie iteracji.

lab4

Napisz program w języku „C/C++”, realizujący uogólnioną metodę Newtona rozwiązywania układu trzech algebraicznych równań nieliniowych, i zastosuj ten program do przykładu z 
zadania 1. Przyjmij takie przybliżenie początkowe, aby uzyskać zbieżność metody. Zastosuj trzy niezależne kryteria zakończenia iteracji. Zadbaj o to, aby wyprowadzać na 
konsolę wyniki pośrednie obliczeń dla każdej iteracji, tak aby możliwe było obserwowanie zbieżności kolejnych przybliżeń pierwiastków. W szczególności oblicz jak zmienia się 
estymator błędu rozwiązania oraz residuum układu w trakcie iteracji.

lab5

Napisz program w języku „C/C++”, realizujący dekompozycję LU macierzy A, przy zastosowaniu eliminacji Gaussa z częściowym wyborem elementu podstawowego, a następnie 
rozwiązujący układ równań Ax = b. Program należy zrealizować w postaci dwóch odrębnych procedur: jednej, która operuje wyłącznie na macierzy A, i drugiej, która operuje
wyłącznie na wektorze b, korzystając z wyników działania procedury pierwszej.

lab6

Napisz program w języku „C/C++”, realizujący algorytm Thomasa dla macierzy trój-diagonalnej o dowolnych rozmiarach N x N, a następnie zastosuj ten program do rozwiązania 
układu równań Ax = b. Program należy zrealizować w postaci dwóch odrębnych procedur: jednej, która operuje wyłącznie na macierzy A, i drugiej, która operuje wyłącznie na 
wektorze b, korzystając z wyników działania procedury pierwszej. Uwaga: ponieważ macierz trój-diagonalna jest macierzą rzadką, więc w programie NIE NALEŻY używać tablic 
kwadratowych do reprezentacji macierzy A.

lab7

Napisz program w języku „C/C++”, rozwiązujący układ czterech równań liniowych metodami iteracyjnymi: (a) Jacobiego, (b) Gaussa-Seidela, (c) SOR z parametrem w = 1/2, 
a następnie zastosuj ten program do rozwiązania układu równań liniowych Ax = b.
Przyjmij przybliżenie początkowe x0 = [2,2,2,2]
Zastosuj trzy niezależne kryteria zakończenia iteracji. Zadbaj o to, aby wyprowadzać na konsolę wyniki pośrednie obliczeń dla każdej iteracji, tak aby możliwe było 
obserwowanie zbieżności kolejnych przybliżeń pierwiastków i porównanie liczby iteracji niezbędnych do uzyskania (za pomocą różnych metod) rozwiązania o zadanej dokładności 
bezwzględnej. W szczególności oblicz jak zmienia się estymator błędu rozwiązania oraz residuum układu w trakcie kolejnych iteracji.
