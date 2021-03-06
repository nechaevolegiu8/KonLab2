#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

//Функция проверки принадлежности игры классу выпукло-вогнутых
void classTest(double a, double b) {
    cout << "Проверим выполнимость условия для принадлежности игры к классу выпукло-вогнутых: " << endl;
    cout << "Hxx = " << 2 * a;
    if ((2 * a) < 0) cout << " < 0" << endl; else cout << " > 0" << endl;
    cout << "Hyy = " << 2 * b;
    if ((2 * b) < 0) cout << " < 0" << endl; else cout << " > 0" << endl;

    if (((2 * a) < 0) && ((2 * b) > 0)) cout << "Представленная игра принадлежит классу выпукло-вогнутых" << endl;
    else cout << "Представленная игра не принадлежит классу выпукло-вогнутых" << endl;
}

//Функция рассчета y
double yCalc(double a, double b, double c, double d, double e) {
    return (double)((c * d * (-1)) + (2 * a * e)) / (-(4 * a * b) + pow(c, 2));
}

//Функция рассчета х
double xCalc(double a, double b, double c, double d, double e, double y) {
    return (double) -((c * y) + d)/(2 * a);
}

//Функция ядра
double HCalc(double x, double y, double a, double b, double c, double d, double e) {
    return (a * pow(x, 2)) + (b * pow(y, 2)) + (c * x * y) + (d * x) + (e * y);
}

//Функция проверки является ли значение седловой точкой
int isSedlo(vector<vector<double>> matr, double i, double j) {
    double max = -100000.0;
    int stlNum, strNum;

    for (int z = 0; z < matr.size(); z++) {
        if (matr[z][j] > max) {
            max = matr[z][j];
            stlNum = z;
        }
    }
    
    double min = 100000.0;

    for (int z = 0; z < matr.size(); z++) {
        if (matr[i][z] < min) {
            min = matr[i][z];
            strNum = z;
        }
    }

    if ((stlNum == i) && (strNum == j)) return 1;
    else return 0;
}

//Функция нахождения максимального выигрыша игрока А и выбора последующей из этого стратегии
int FindMax(vector<double> x, int A) {
    int c = 0; int z; z = x[0];
    for (int i = 0; i < x.size(); i++) { //Проверка - если все значения одинаковые, то остаемся на той же стратегии
        if (x[i] == z) c++;
    }
    if (c == x.size()) return A;

    c = INT_MIN; int n;
    for (int i = 0; i < x.size(); i++) {
        if (x[i] > c) {
            c = x[i]; n = i;
        }
    }

    return n;
}

//Функция нахождения минимального проигрыша игрока Б и выбора последующей из этого стратегии
int FindMin(vector<double> x, int A) {
    int c = 0; int z; z = x[0];
    for (int i = 0; i < x.size(); i++) { //Проверка - если все значения одинаковые, то остаемся на той же стратегии
        if (x[i] == z) c++;
    }
    if (c == x.size()) return A;

    c = INT_MAX; int n;
    for (int i = 0; i < x.size(); i++) {
        if (x[i] < c) {
            c = x[i]; n = i;
        }
    }

    return n;
}

//Нахождение максимума из V_
double FindMx(vector<double> x) {
    double c = -100000;
    for (int i = 0; i < x.size(); i++) {
        if (x[i] > c) {
            c = x[i];
        }
    }
    return c;
}

//Нахождение минимума из v-
double FindMn(vector<double> x) {
    double c = 100000;
    for (int i = 0; i < x.size(); i++) {
        if (x[i] < c) {
            c = x[i];
        }
    }
    return c;
}



int main()
{
    setlocale(0, "");
    //Инициализация переменных
    double a, b, c, d, e, y, x, H, znam;
    
    //Для критерия остановки
    int m = 10; double eps = 0.001; 
    vector<double> stop;
    stop.push_back(0); stop.push_back(0);

    //Кол-во итераций (плюс один)
    int Nmax = 100;
    cout << "a: "; cin >> a; cout << "/"; cin >> znam;
    a = (double) a / znam; cout << endl;
    cout << "b: "; cin >> b; cout << "/"; cin >> znam;
    b = (double)b / znam; cout << endl;
    cout << "c: "; cin >> c; cout << "/"; cin >> znam;
    c = (double)c / znam; cout << endl;
    cout << "d: "; cin >> d; cout << "/"; cin >> znam;
    d = (double)d / znam; cout << endl;
    cout << "e: "; cin >> e; cout << "/"; cin >> znam;
    e = (double)e / znam; cout << endl;

    //Вывод условия
    cout << "Условие: " << endl << "a | " << setw(5) << a << endl << "b | " << setw(5) << b << endl << "c | " << setw(5) << c << endl << "d | " << setw(5) << d << endl << "e | " << setw(5) << e << endl;
    
    //Решение аналитическим способом ----------------------------------------
    cout << "----- Решение аналитическим способом -----" << endl;
    //Проверка принадлежности игры классу выпукло-вогнутых
    classTest(a, b);
    
    //Рассчет y и x решением системы уравнений
    cout << "Перейдем к нахождению седловой точки игры, найдя вначале значения x и y (решив систему уравнений)," << endl << "затем подставив полученные значения в функцию ядра:" << endl;
    y = yCalc(a, b, c, d, e);
    cout << "y = -(cx + d)/2b = " << y << endl;

    x = xCalc(a, b, c, d, e, y);
    cout << "x = -(cy + d)/2a = " << x << endl;

    //Подстановка найденных x и y в функцию ядра
    H = HCalc(x, y, a, b, c, d, e);
    cout << "H = ax^2 + by^2 + cxy + dx + ey = " << H << endl;

    //Решение численным способом  -------------------------------------------
    cout << "----- Решение численным способом -----" << endl;
    
    //for (int N = 2; N < Nmax; N++) {
    int st = 1; double preveps;
    int N = 2; //Счетчик итераций
    while (st) {
        cout << endl << "-------------------------------" << endl << "N = " << N << endl;
        int n = N + 1;
        vector<vector<double>> matr;

        //Создание матрицы
        for (int i = 0; i < n; i++) {
            vector<double> vect;
            for (int j = 0; j < n; j++) {
                vect.push_back(0.0);
            }
            matr.push_back(vect);
        }

        //Заполнение матрицы
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                double tempX = (double)i / N;
                double tempY = (double)j / N;
                double H = HCalc(tempX, tempY, a, b, c, d, e);
                matr[i][j] = H;
                cout << setprecision(3);
            }
            //cout << endl;
        }

        //Проверка на наличие седловой точки - плюс решение если седловая точка есть
        int sedlo = 0;
        for (double i = 0; i < n; i++) {
            for (double j = 0; j < n; j++) {
                if (isSedlo(matr, i, j)) {
                    cout << "Есть седловая точка: i = " << i << ", j = " << j << ", H = " << matr[i][j] << endl;
                    cout << "x = " << (double) (1.0 / N) * i << endl;
                    cout << "y = " << (double) (1.0 / N) * j << endl;
                    sedlo = 1;
                    
                    stop.push_back(matr[i][j]); //Для критерия остановки
                }
            }            
        }
        
        //Если нет седловой точки - решение БР методом        
        if (sedlo == 0) {
            cout << endl << "Седловой точки нет, решение методом БР: " << endl;

            int k, A, B; A = 0; B = 0;
            vector<double> x; for (int i = 0; i < n; i++) x.push_back(matr[i][A]);
            vector<double> y; for (int i = 0; i < n; i++) y.push_back(matr[B][i]);
            
            //В качестве счетчика итераций / знаменатель для столбцов пороговых значений
            k = 2;

            vector<int> cx; vector<int> cy; //Вектора-счетчики - сколько раз применили ту или иную стратегию
            for (int i = 0; i < n; i++) {
                cx.push_back(0);
                cy.push_back(0);
            }

            cx[0]++; cy[0]++;

            vector<double> delX; vector<double> delY;

            //Остальные строки
            for (int i = 0; i < k; i++) { // i - строка
                
                A = FindMax(x, A);
                B = FindMin(y, B);
                cx[A]++; cy[B]++;

                if (i != 0) {
                    
                    double X; double Y; X = (double)x[A] / (i + 1); Y = (double)y[B] / (i + 1);
                    delX.push_back(X); delY.push_back(Y);
                }
                if (i == 0) {
                    
                    double X; double Y; X = x[A] / 1.; Y = y[B] / 1.;
                    delX.push_back(X); delY.push_back(Y);
                }

                for (int j = 0; j < n; j++) x[j] = x[j] + matr[j][B];
                for (int j = 0; j < n; j++) y[j] = y[j] + matr[A][j];

                double a, b, c;
                a = FindMn(delX);
                b = FindMx(delY);
                c = a - b;

                //Результаты БР метода
                if (c <= 0.005) {
                    cout << "Погрешность = " << c << endl;
                    cout << "H = " << (a + b) / 2.0 << endl;
                    i = k; k--; cx[A]--; cy[B]--;
                    
                    stop.push_back((a + b) / 2.0); //Для критерия остановки
                    //cout << "dobavleno" << stop[N];
                }
                if (c > 0.005) k++;
            }
                     
            double cxmax, cymax;
            
            double max = -100000.0;
            for (int z = 0; z < cx.size(); z++) {
                if (cx[z] > max) {
                    max = cx[z];
                    cxmax = z;
                }
            }

            max = -100000.0;
            for (int z = 0; z < cy.size(); z++) {
                if (cy[z] > max) {
                    max = cy[z];
                    cymax = z;
                }
            }
            
            cout << "x = " << (double)(1.0 / N) * cxmax << endl;
            cout << "y = " << (double)(1.0 / N) * cymax << endl;
                                 
        }
               

        if (N > m + 2) {
            int check = 0;
            for (int i = 0; i < m; i++) {
                if ((stop[N - i] - stop[N - i - 1]) <= eps) check++;
            }
            if (check == m) {
                st = 0;
                cout << "За последние " << m << " итераций оценка игры изменилась не более чем на " << eps << ", следовательно срабатывает критерий остановки." << endl;
            }
        }
        
        N++;
    }

}


