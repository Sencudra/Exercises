#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>

using namespace std;

const int lmax = 100;

struct player {
  string name; //имя игрока
  float points[4][9]; // 4 прыжка, 7 оценок, 1 сложность , граница данных "-1"
  float fpoints; // общие очки

 void deleteData(float* num){ // удаление числа
        while(*num != -1)
        {
            *num = *(num + 1);
            num++;
        }
  }

 void findMaxMin(float* pntr){
      float* pointer = pntr; //Указатель на первый элемент строчки с результатами

      float* max;
      float* min;

      max = min = pointer;
      pointer++; // для сравнения берем след. элемент
      while (*(pointer+1) != -1)
      {

        if (*pointer > *max)
            max = pointer;
        if (*pointer < *min)
            min = pointer;
        pointer++;
      }
      // Удаление , кривое, можно сделать лучше
      if (min != max){
        while(pointer != pntr){
            if(pointer == max)
                deleteData(max);
            if(pointer == min)
                deleteData(min);
            pointer--;
        }
        if(pointer == max)
            deleteData(max);
        if(pointer == min)
            deleteData(min);
      }
      else // Если min и max не совпадают
      {
            deleteData(min);
      }
  }

 float countPoints(){

     for(int i = 0; i < 4; i++)
     {
         findMaxMin(&points[i][0]);
     }

     // Подсчет очков
     float allPoints = 0;
     for (int i = 0; i<4;i++){
        int buffer = 0;
        for(int j = 0; j < 5;j++){
            buffer+=points[i][j];
        }
        allPoints = allPoints + buffer*points[i][5];
     }
     return allPoints;
 }


};

struct tournament{
  player* base[lmax]; // массив со всеми игроками
  int playerNum;

  void count(){
      for(int i = 0; i <playerNum;i++)
         base[i]->fpoints = base[i]->countPoints();
  }

  void sortBase(){
      // обычная пузырьковая сортировка
      for (int i = 0;i < playerNum;i++)
          for (int j = playerNum - 1; j > i; j-- )
              if(base[j]->fpoints > base[j-1]->fpoints)
              {
                  swap(base[j],base[j-1]); // меняю местами
              }
      //вывод  результата
      for(int i = 0; i <playerNum;i++)
          cout << base[i]->name << " " <<  base[i]->fpoints << endl;
  }
};



int main()
{
    ifstream lolinput;
    lolinput.open("C:\\Users\\Vlad\\Desktop\\test.txt");
    
    ////////////////////////////////////////////////////////
    
    tournament currTourn;
    currTourn.playerNum=0;

    string playerName;
    
    //Чтение из файла
    while(lolinput >> playerName){
        player* nPlayer = new player();
        currTourn.base[currTourn.playerNum] = nPlayer;
        currTourn.playerNum++;
        nPlayer->name = playerName;
        
        float p;
        for(int i = 0; i < 32;i++){
            lolinput >> p;
            nPlayer->points[i/8][i%8] = p;
        }
        
        // ВНИМАНИЕ: в конец каждой строчки прыжка добавляю -1, чтобы был сигнал конца
        for(int i = 0; i<4;i++ )
           nPlayer->points[i][8] = -1;
    }
    
    // Вызвов двух методов
    currTourn.count();
    currTourn.sortBase();

    return 0;
}
