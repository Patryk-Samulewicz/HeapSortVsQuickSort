/**
 * 
 * @author Patryk Samulewicz
 * @brief 
 * @version 0.1
 * @date 2021-06-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

//---------- GENERATOR LICZB LOSOWYCH ---------------
/**
 * @brief 
 * 
 * @param tablica 
 * @param tablica1 
 * @param ile 
 * @return auto 
 */
auto generator(int *tablica, int *tablica1, int ile) //funkcja przyjmuje ilosc elementow do wylosowania oraz wskaznik do tablicy ktora wypelni
{
    srand((unsigned int)time(NULL)); ///deklaracja pseudolosowosci liczb
    for (int i = 0; i < ile; i++)    ///petla wykonujaca sie ile razy
    {
        tablica[i] = rand() % ile; ///wypelnianie tablicy losowymi elementami
        tablica1[i] = tablica[i];
    }
    return tablica; ///funkcja zwraca wypelniona tablice
}

//--------- SORTOWANIE QUICK SORT ----------------
/**
 * @brief 
 * 
 * @param tablica 
 * @param l 
 * @param r 
 */
void quick_sort(int *tablica, int l, int r) //funkcja przyjmuje wskaznik na wyslana tablice, element lewy i ostatni
{
    if (l >= r) //funkcja zabezpieczajaca gdyby element lewy byl podany jako prawy
        return;

    int left = l - 1;             //zaczynamy od -1 aby uwzglednic zerowy element tablicy
    int right = r + 1;            //od konca rowniez zaczynamy od elementu +1 aby uwzglednic elemnent ostatni
    int x = tablica[(l + r) / 2]; //deklaracja srodkowego elementu tablicy (pivota)
    while (true)                  //petla nieskonczona
    {
        while (x < tablica[++left])
            ;   //przeszukiwanie tablicy od lewej strony, musi byc preinkrementacja gdyz wczesniej jako pierwszy element
                //mielismy -1
        while (x > tablica[--right])
            ; //analogicznie to co u gory lecz na odwrot poniewaz przeszukujemy od prawej

        if (left <= right) //jezeli przeszukiwanie tablicy doszlo do pivota(elementu srodkowego tablicy)
        {
            swap(tablica[left], tablica[right]); //zamien miejscami elementy sasiadujace z pivotem
        }
        else
        {
            break; //w przeciwnym wypadku przerywamy czesc sortowania
        }
    }

    if (right > l)                     //jezeli prawy wskaznik tablicy jest wiekszy od poczatku (od zera)
        quick_sort(tablica, l, right); //wywolanie rekurencyjnie sortowania z parametrami dla tablicy gdzie :
                                       //poczatkiem jest naturalnie nadal 0 a koncem jest nasz przesuniety wskaznik dzieki czemu
                                       //nie przekazujemy calej tablicy tylko pierwsza lewa nieposortowana czesc

    if (left < r)                     //jezeli lewy wskaznik tablicy jest mniejszy od ostatniego elementu tablicy
        quick_sort(tablica, left, r); //wywolanie rekurencyjnie sortowania z parametrami dla tablicy gdzie :
                                      //poczatkiem jest nasz przesuwany wskaznik tablicy a koncem naturalnie ostatnim elelement
                                      //nie przekazujemy calej tablicy tylko ostatnia prawa nieposortowana czesc
}
//--------- SORTOWANIE PRZEZ KOPCOWANIE ----------------
/**
 * @brief 
 * 
 * @param tablica 
 * @param ile 
 * @param i 
 */
void kopcowanie(int *tablica, int ile, int i)
{
    int najw, temp;
    int lewy = 2 * i, prawy = (2 * i) + 1;         //wyznaczanie indexow lewego/prawego dziecka/potomka
    if (lewy <= ile && tablica[lewy] < tablica[i]) //porownanie lewego dziecka do ilosci elementow w tablicy oraz sprawdzenie czy jest wiekszy
        najw = lewy;                               //od rodzica jezeli tak to przypisujemy go do najwiekszej liczy
    else
        najw = i;                                       //jezeli nie to nawiekszy bedzie rodzic
    if (prawy <= ile && tablica[prawy] < tablica[najw]) //porownanie prawego dziecka do ilosci elementow w tablicy oraz sprawdzenie czy jest wiekszy
        najw = prawy;                                   //od rodzica jezeli tak to przypisujemy go do najwiekszej liczy

    if (najw != i) //sprawdzenie czy najwiekszy index zostal zamieniony z rodzicem
    {
        temp = tablica[najw]; //jezeli tak to nalezy zamienic miejscami index rodzica
        tablica[najw] = tablica[i];
        tablica[i] = temp;
        kopcowanie(tablica, ile, najw); //oraz ponowne sprawdzenie kopca czy spelnia warunki z wywolaniem najw jako indexu nowego rodzica
    }
}
/**
 * @brief 
 * 
 * @param tablica 
 * @param ile 
 */
void budKopiec(int *tablica, int ile)
{
    for (int i = ile / 2; i >= 0; i--) //petla ktora definiuje rodzicow w kopcu
        kopcowanie(tablica, ile, i);   //funkcja ktora sprawdza czy struktura spelnia wlasnosci kopca
}
/**
 * @brief 
 * 
 * @param tablica 
 * @param ile 
 */
void heapsort(int *tablica, int ile) //funkcja sortujaca przyjmuje wskaznik na tablice oraz ilosc elementow do posortowania
{
    int temp;                //zmienna pomocnicza
    budKopiec(tablica, ile); //funkcja odwoluje sie do funkcji pomocniczej ktora buduje kopiec
    for (int i = ile; i >= 1; i--)
    {
        temp = tablica[i]; //zamiana rodzica/korzenia miejscami i wyslanie go na koniec tablicy
        tablica[i] = tablica[1];
        tablica[1] = temp;
        ile--;                       //zmiejszenie ilosci elementow tablicy po kazdym posortowanym elemencie
        kopcowanie(tablica, ile, 1); //ponowne sprawdzenie wlasnosci kopca rekurencyjnie
    }
}

/**
 * @brief 
 * 
 * @return int 
 */
void main()
{
    int ile; //deklaracja zmiennej przechowujacej ilosc licz do wylosowania i posortowania

    cout << "Podaj ile elementow chcesz wylosowac :" << endl;
    cin >> ile;

    int *tablica = new int[ile + 1];  //dynamiczna alokacja tablicy
    int *tablica1 = new int[ile + 1]; //dynamiczna alokacja tablicy
    cout << "Wylosowane elementy to: \n ";
    /**
     * @brief Construct a new generator object
     * 
     */
    generator(tablica, tablica1, ile); //wywolanie funkcji generujacej liczby losowe

    for (int i = 0; i < ile; i++)
    {
        cout << tablica[i] << " | "; //petla wyswietlajaca wszystkie liczby w tablicy
    }

    clock_t startq = clock();

    quick_sort(tablica, 0, ile - 1); //wywolanie funkcji sortujacej tablice

    clock_t koniecq = clock();
    cout << endl
         << "Posortowana tablica algorytmem quicksort: " << endl;
    for (int i = 0; i < ile; i++)
    {
        cout << tablica[i] << " | "; //petla wyswietlajaca posortowana juz tablice
    }
    clock_t starth = clock();
    /**
     * @brief Construct a new heapsort object
     * 
     */
    heapsort(tablica1, ile);
    clock_t koniech = clock();

    double czas_q, czas_h; //utworzenie zmiennych do oblicznia czasu odjecie taktow zegara i podzielenie ich przez stala dzieki czemu z taktow mamy sekundy
    czas_q = koniecq - startq;
    czas_h = koniech - starth;
    czas_q = czas_q / CLOCKS_PER_SEC;
    czas_h = czas_h / CLOCKS_PER_SEC;

    cout << endl
         << "Posortowana tablica algorytmem heapsort: " << endl;
    for (int i = 1; i <= ile; i++)
    {
        cout << tablica1[i] << " | "; //petla wyswietlajaca posortowana juz tablice
    }

    cout << endl
         << "Czas sortowania quicksort wynosi:  " << czas_q << endl;
    cout << endl
         << "Czas sortowania heapsort wynosi:  " << czas_h << endl;

    delete[] tablica;
}
