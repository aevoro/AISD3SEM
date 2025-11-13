#include <iostream>
#include <Windows.h>
#include <vector>

using namespace std;

vector<int> maxSequence(vector<int>& arr) {
    if (arr.empty()) {
        cout << "Ошибка";
        return {};
    }

    vector<int> longestSequence;
    vector<int> currentSequence;

    for (int i = 0; i < arr.size(); i++) {
        currentSequence = {arr[i]};

        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[j] == currentSequence.back() + 1) {
                currentSequence.push_back(arr[j]);
            }
        }

        if (currentSequence.size() > longestSequence.size()) {
            longestSequence = currentSequence;
        }
    }

    return longestSequence;
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    int N;
    cout << "Введите N: ";
    cin >> N;

    vector<int> arr(N);
    cout << "Заполните массив элементов" << endl;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    vector<int> result = maxSequence(arr);

    cout << "Максимальная длина последовательности: " << result.size() << endl;
    cout << "Последовательность: ";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}