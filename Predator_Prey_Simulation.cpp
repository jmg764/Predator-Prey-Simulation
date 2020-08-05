//
//  main.cpp
//  jmg764_hw9
//
//  Created by Jonathan Glaser on 6/15/18.
//  Copyright © 2018 Jonathan Glaser. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void initialGrid(char arr[20][20]);
void print(char arr[20][20]);

class Organism{
public:
    virtual void move(){};
};

class Ants : public Organism{
public:
    void move(char arr[20][20], int antMovements[20][20], int &antCount);
    void breed(int antMovements[20][20], char arr[20][20], int &antCount);
};

class Doodlebugs : public Organism{
public:
    void move(char arr[20][20], int doodlebugMovements[20][20], int antsEaten[20][20], int &doodlebugCount);
    void breed(int doodlebugMovements[20][20], char arr[20][20], int &doodlebugCount, int antsEaten[20][20]);
    void starve(int antsEaten[20][20], char arr[20][20], int doodlebugCount, int doodlebugMovements[20][20]);
};


int main() {
    char arr[20][20];
    int antMovements[20][20];
    int doodlebugMovements[20][20];
    int antsEaten[20][20];
    int antCount = 1;
    int doodlebugCount = 1;
    
    Doodlebugs doodlebugs;
    Ants ants;
    
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            doodlebugMovements[i][j] = 0;
        }
    }
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            antMovements[i][j] = 0;
        }
    }
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            antsEaten[i][j] = 0;
        }
    }
    
    initialGrid(arr);
    
    if (doodlebugCount % 9 == 0) {
        doodlebugCount = 1;
    }
    
    if (antCount % 4 == 0) {
        antCount = 1;
    }
    
    while (true) {
        doodlebugs.move(arr, doodlebugMovements, antsEaten, doodlebugCount);
        ants.move(arr, antMovements, antCount);
        doodlebugs.breed(doodlebugMovements, arr, doodlebugCount, antsEaten);
        doodlebugs.starve(antsEaten, arr, doodlebugCount, doodlebugMovements);
        ants.breed(antMovements, arr, antCount);
        print(arr);
        doodlebugCount++;
        antCount++;
    }
    
    return 0;
}

void initialGrid(char arr[][20]){
    srand(time(0));
    int x, y;
    bool empty;
    
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            arr[i][j] = '-';
        }
    }
    
    for (int i = 0; i < 5; i++) {
        x = rand()%20;
        y = rand()%20;
        arr[x][y] = 'X';
    }
    
    for (int i = 0; i < 100; i++) {
        x = rand()%20;
        y = rand()%20;
        empty = false;
        while (empty == false) {
            if (arr[x][y] == 'X') {
                if (y == 19) {
                    x++;
                } else if (x == 19){
                    y++;
                } else {
                    y++;
                }
            } else if (arr[x][y] == 'o'){
                if (y == 19) {
                    x++;
                } else if (x == 19){
                    y++;
                } else {
                    y++;
                }
            } else {
                arr[x][y] = 'o';
                empty = true;
            }
        }
    }
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            cout<<arr[i][j];
        }
        cout<<endl;
    }
}

void Ants::move(char arr[20][20], int antMovements [20][20], int &antCount){
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (arr[i][j] == 'o') {
                int direction = rand()%4;
                // 0 = left, 1 = up, 2 = right, 3 = down
                if (direction == 0) {
                    if (antMovements[i][j] != antCount) {
                        if (arr[i][j-1] == '-' && j-1 >= 0) {
                            arr[i][j-1] = arr[i][j];
                            arr[i][j] = '-';
                            antMovements[i][j-1] = antMovements[i][j]+1;
                            antMovements[i][j] = 0;
                        } else {
                            antMovements[i][j] += 1;
                        }
                    }
                } else if (direction == 1) {
                    if (antMovements[i][j] != antCount) {
                        if (arr[i-1][j] == '-' && i-1 >= 0) {
                            arr[i-1][j] = arr[i][j];
                            arr[i][j] = '-';
                            antMovements[i-1][j] = antMovements[i][j]+1;
                            antMovements[i][j] = 0;
                        } else {
                            antMovements[i][j] += 1;
                        }
                    }
                } else if (direction == 2) {
                    if (antMovements[i][j] != antCount) {
                        if (arr[i][j+1] == '-' && j+1 <= 19) {
                            arr[i][j+1] = arr[i][j];
                            arr[i][j] = '-';
                            antMovements[i][j+1] = antMovements[i][j]+1;
                            antMovements[i][j] = 0;
                        } else {
                            antMovements[i][j] += 1;
                        }
                    }
                } else if (direction == 3) {
                    if (antMovements[i][j] != antCount) {
                        if (arr[i+1][j] == '-' && i+1 <= 19) {
                            arr[i+1][j] = arr[i][j];
                            arr[i][j] = '-';
                            antMovements[i+1][j] = antMovements[i][j]+1;
                            antMovements[i][j] = 0;
                        } else {
                            antMovements[i][j] += 1;
                        }
                    }
                }
            }
        }
    }
    
    cout<<endl;
}

void Doodlebugs::move(char arr[20][20], int doodlebugMovements[20][20], int antsEaten[20][20], int &doodlebugCount){
    string emptyLine2;
    bool seenEmptyLine2 = false;
    cout<<"Press enter to move doodlebugs and then ants"<<endl;
    while (seenEmptyLine2 == false) {
        getline(cin, emptyLine2);
        if (emptyLine2 == "") {
            seenEmptyLine2 = true;
        } else {
            cout<<"Error. Please press enter to move doodlebugs"<<endl;
        }
    }
    
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (arr[i][j] == 'X' && doodlebugMovements[i][j] != doodlebugCount) {
                if (arr[i][j-1] == 'o') {
                    antsEaten[i][j-1] = antsEaten[i][j]+1;
                    antsEaten[i][j] = 0;
                    arr[i][j-1] = arr[i][j];
                    arr[i][j] = '-';
                    doodlebugMovements[i][j-1] = doodlebugMovements[i][j]+1;
                    doodlebugMovements[i][j] = 0;
                } else if (arr[i-1][j] == 'o') {
                    antsEaten[i-1][j] = antsEaten[i][j]+1;
                    antsEaten[i][j] = 0;
                    arr[i-1][j] = arr[i][j];
                    arr[i][j] = '-';
                    doodlebugMovements[i-1][j] = doodlebugMovements[i][j]+1;
                    doodlebugMovements[i][j] = 0;
                } else if (arr[i][j+1] == 'o') {
                    antsEaten[i][j+1] = antsEaten[i][j]+1;
                    antsEaten[i][j] = 0;
                    arr[i][j+1] = arr[i][j];
                    arr[i][j] = '-';
                    doodlebugMovements[i][j+1] = doodlebugMovements[i][j]+1;
                    doodlebugMovements[i][j] = 0;
                } else if (arr[i+1][j] == 'o') {
                    antsEaten[i+1][j] = antsEaten[i][j]+1;
                    antsEaten[i][j] = 0;
                    arr[i+1][j] = arr[i][j];
                    arr[i][j] = '-';
                    doodlebugMovements[i+1][j] = doodlebugMovements[i][j]+1;
                    doodlebugMovements[i][j] = 0;
                } else {
                    int direction = rand()%4;
                    // 0 = left, 1 = up, 2 = right, 3 = down
                    if (direction == 0) {
                        if (arr[i][j-1] == '-' && j-1 >= 0) {
                            antsEaten[i][j-1] = antsEaten[i][j];
                            antsEaten[i][j] = 0;
                            arr[i][j-1] = arr[i][j];
                            arr[i][j] = '-';
                            doodlebugMovements[i][j-1] = doodlebugMovements[i][j]+1;
                            doodlebugMovements[i][j] = 0;
                        }
                    } else if (direction == 1) {
                        if (arr[i-1][j] == '-' && i-1 >= 0) {
                            antsEaten[i-1][j] = antsEaten[i][j];
                            antsEaten[i][j] = 0;
                            arr[i-1][j] = arr[i][j];
                            arr[i][j] = '-';
                            doodlebugMovements[i-1][j] = doodlebugMovements[i][j]+1;
                            doodlebugMovements[i][j] = 0;
                        }
                    } else if (direction == 2) {
                        if (arr[i][j+1] == '-' && j+1 <= 19) {
                            antsEaten[i][j+1] = antsEaten[i][j];
                            antsEaten[i][j] = 0;
                            arr[i][j+1] = arr[i][j];
                            arr[i][j] = '-';
                            doodlebugMovements[i][j+1] = doodlebugMovements[i][j]+1;
                            doodlebugMovements[i][j] = 0;
                        }
                    } else if (direction == 3) {
                        if (arr[i+1][j] == '-' && i+1 <= 19) {
                            antsEaten[i+1][j] = antsEaten[i][j];
                            antsEaten[i][j] = 0;
                            arr[i+1][j] = arr[i][j];
                            arr[i][j] = '-';
                            doodlebugMovements[i+1][j] = doodlebugMovements[i][j]+1;
                            doodlebugMovements[i][j] = 0;
                        }
                    }
                }
            }
        }
    }
    cout<<endl;
}

void Ants::breed(int antMovements[20][20], char arr[20][20], int &antCount){
    if (antCount % 3 == 0) {
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                if (arr[i][j] == 'o' && antMovements[i][j] % 3 == 0) {
                    if (arr[i][j-1] == '-' && j-1 >= 0){
                        arr[i][j-1] = 'o';
                    }
                    else if (arr[i-1][j] == '-' && i-1 >= 0) {
                        arr[i-1][j] = 'o';
                    }
                    else if (arr[i][j+1] == '-' && j+1 <= 19) {
                        arr[i][j+1] = 'o';
                    }
                    else if (arr[i+1][j] == '-' && i+1 <= 19){
                        arr[i+1][j] = 'o';
                    }
                    antMovements[i][j] = 0;
                }
            }
        }
    }
}

void Doodlebugs::breed(int doodlebugMovements[20][20], char arr[20][20], int &doodlebugCount, int antsEaten[20][20]){
    if (doodlebugCount % 8 == 0) {
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                if (arr[i][j] == 'X' && doodlebugMovements[i][j] % 8 == 0){
                    if (arr[i][j-1] == '-' && j-1 >= 0){
                        arr[i][j-1] = 'X';
                        antsEaten[i][j-1] = 1;
                    }
                    else if (arr[i-1][j] == '-' && i-1 >= 0) {
                        arr[i-1][j] = 'X';
                        antsEaten[i-1][j] = 1;
                    }
                    else if (arr[i][j+1] == '-' && j+1 <= 19) {
                        arr[i][j+1] = 'X';
                        antsEaten[i][j+1] = 1;
                    }
                    else if (arr[i+1][j] == '-' && i+1 <= 19){
                        arr[i+1][j] = 'X';
                        antsEaten[i+1][j] = 1;
                    }
                }
            }
        }
    }
}


void Doodlebugs::starve(int antsEaten[20][20], char arr[20][20], int doodlebugCount, int doodlebugMovements[20][20]){
    if (doodlebugCount % 3 == 0) {
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                if (antsEaten[i][j] == 0 && arr[i][j] == 'X'){
                    arr[i][j] = '-';
                    doodlebugMovements[i][j] = 0;
                } else {
                    antsEaten[i][j] = 0;
                }
            }
        }
    }
}

void print(char arr[20][20]){
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            cout<<arr[i][j];
        }
        cout<<endl;
    }
}
