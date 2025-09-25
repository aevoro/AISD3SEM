using namespace std;

#include <iostream>

void Solve(int N, int i, int K, int mid)
{
    if (N == 0) return;
    Solve(N - 1, i, mid, K);
    cout << "ѕереместить диск " << N << " с " << i << " стержн€ на " << K << " стержень" << endl;
    Solve(N - 1, mid, K, i);
}

    int main()
    {
        setlocale(LC_ALL, "RU");
        int N; int K;
        cout << "¬ведите количество дисков: ";
        cin >> N;
        cout << "¬ведите количество стержней: ";
        cin >> K;
        int i = 1;
        int mid = 6 - K - i;
        Solve(N, i, K, mid);
    }
   