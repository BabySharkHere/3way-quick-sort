//Если нужно проверить, правильно ли отсортировался массив, и время выполнения программы, то нужно расскомментировать все закомментированные строки
//Набор чисел берётся из файла input.txt, выводится в output.txt


#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <math.h>
#include <random>
#define inputSTR "input.txt"
#define outputSTR "output.txt"

void printVector(std::vector<int> &numbers){
    for(auto e:numbers){
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

void partition(std::vector<int> &numbers, int &left, int &right, int &i, int &j){
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(left, right-1);
    int eq = left, greater = left, now = left;
    int mass[3];
  RANDOMVALUE:  for(int i = 0 ; i < 3; i++){
        mass[i]=dist(rng);
    }
    if(mass[1] < mass[0]){
        std::swap(mass[1], mass[0]);
        if(mass[1] > mass[2]){
            std::swap(mass[1], mass[2]);
        }
        if(mass[0] > mass[1]){
            std::swap(mass[0], mass[1]);
        }
    }
    else{
        if(mass[1] > mass[2]){
            std::swap(mass[1],mass[2]);
        }
        if(mass[0] > mass[1]){
            std::swap(mass[0], mass[1]);
        }
    }
    if(mass[1] < left || mass[1] > right){
        std::cout << "ERROR! NOT RIGHT RANDOM VALUE" << std::endl;
        std::cout << "Left : " << left << " Right : " << right << " random value : " << mass[1] << std::endl;
        goto RANDOMVALUE;
    }
    int randomIndex = mass[1];
    int pivot = numbers[randomIndex];
    while(now  <= right){
        if(numbers[now] < pivot){
            std::swap(numbers[now], numbers[greater]);
            std::swap(numbers[greater], numbers[eq]);
            now++;
            eq++;
            greater++;
        }
        
        if(numbers[now] == pivot){
            std::swap(numbers[now], numbers[greater]);
            now++;
            greater++;
        }
        while(numbers[now] > pivot){
            if(now <= right){
                now++;
            }
            else{
                i = eq;
                j = greater;
                return;
            }
        }
    }
    i = eq;
    j = greater;
}

void quickSort(int left, int right, std::vector<int> &numbers){
    int i = 0, j = 0;
    if(left >= right || right-left <= 1){
        if(numbers[left] <= numbers [left+1]){
            return;
        }
        else{
            std::swap(numbers[left],numbers[right]);
            return;
        }
    }
    partition(numbers, left, right, i, j);
    quickSort(left , i, numbers);
    quickSort(j, right, numbers);
}

int main() {
    srand((unsigned int)time(0));
//    clock_t startTime = clock();
    int N = 0, input = 0;
    std::vector<int> numbers;
//    std::vector<int> checkNumbers;
    std::ifstream in(inputSTR);
    if(in.is_open()){
        in >> N;
        if(N == 0) return 0;
        while(in >> input){
            numbers.push_back(input);
//            checkNumbers.push_back(input);
        }
    }
    in.close();
    
    int left = 0;
    int right = numbers.size()-1;
    quickSort(left, right, numbers);
    
    std::ofstream out;
    out.open(outputSTR);
    
    if(out.is_open()){
        for (const auto& e : numbers)
            out << e << " ";
    }
    out.close();
    std::cout << std::endl;
//    clock_t endTime = clock();
//    double result = (double)(endTime - startTime)/CLOCKS_PER_SEC;
//    std::cout << "Time continue : " << result << std::endl;
//    startTime = clock();
//    std::sort(checkNumbers.begin(), checkNumbers.end());
//    if(checkNumbers == numbers) std::cout << "sorted" << std::endl;
//    else{
//        std::cout << "not sorted" << std::endl;
//    }
    return 0;
}
