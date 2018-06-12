// Выполнил: Зеленков Илья ИТ-41

#include <iostream>
#include <iterator>
#include <vector>
#include <limits>
#include <time.h>

using namespace std;

typedef pair<int, int> PairInt;
typedef vector<int> VectorInt;
typedef vector<VectorInt> VectorVectorInt;
typedef vector<PairInt> VectorPairInt;

#define INF 1000000000

const int inf = numeric_limits<int>::max();

// Решене задачи.
VectorPairInt HungarianAlgorithm(const VectorVectorInt &matrix) {
   
   // Размер матрицы
   int h = matrix.size(), w = matrix[0].size();
   
   // Значения, вычитаемые из строк u и столбцов v
   VectorInt u(h, 0), v(w, 0);
   
   // Индекс помеченной ячейки в каждом столбце
   VectorInt markIndices(w, -1);
   
   // Добавление строк в матрицы одну за другой
   for(int i = 0; i < h; i++) {

      VectorInt links(w, -1);
      VectorInt minimums(w, inf);
      VectorInt visitedV(w, 0);
      
      // Создание чередующейся цепи из нулевых элементов
      int markedI = i, markedJ = -1, j;
      do {
         // Обновим информацию о минимумах 
         // Плюс поместим в j индекс непосещенного столбца с самым маленьким из них
         j = -1;
         for (int j1 = 0; j1 < w; j1++)
            if (!visitedV[j1]) {
               if (matrix[markedI][j1] - u[markedI] - v[j1] < minimums[j1]) {
                  minimums[j1] = matrix[markedI][j1] - u[markedI] - v[j1];
                  links[j1] = markedJ;
               }
               if (j==-1 || minimums[j1] < minimums[j])
                  j = j1;
            }
            
         // Получим элемент с индексами (markIndices[links[j]], j)
         // Произведем манипуляции со строками и столбцами так, чтобы он обнулился
         int Delta = minimums[j];
         for (int j1 = 0; j1 < w; j1++)
            if (visitedV[j1]) {
               u[markIndices[j1]] += Delta;
               v[j1] -= Delta;
            } else {
               minimums[j1] -= Delta;
            }
         u[i] += Delta;
         
         // Если цепь не найдена - перейдем к следующей итерации
         visitedV[j] = 1;
         markedJ = j;
         markedI = markIndices[j];   

      } while (markedI != -1);

      // Пройдем по найденной чередующейся цепи ячеек и инвертируем отметки
      for (; links[j] != -1; j = links[j])
         markIndices[j] = markIndices[links[j]];
      markIndices[j] = i;
   }
   
   // Вернем результат в естественной форме
   VectorPairInt result;
   for (int j = 0; j < w; j++)
      if (markIndices[j] != -1)
         result.push_back(PairInt(markIndices[j], j));
   return result;
}

int main(){
    
    // Тестовые матрицы
    int m0[4][4] = {
    	{1, 7, 1, 3},
    	{1, 6, 4, 6},
    	{17, 1, 5, 1},
    	{1, 6, 10, 4},
    };
    
    int m1[5][5] = {
    	{32, 28, 4, 26, 4},
    	{17, 19, 4, 17, 4},
    	{4, 4, 5, 4, 4},
    	{17, 14, 4, 14, 4},
    	{21, 16, 4, 13, 4},
    };

	int m[4][4] = {
    	{6, 2, 4, 3},
    	{5, 7, 3, 3},
    	{4, 1, 4, 2},
    	{6, 7, 2, 1},
    };

	int m3[8][8] = {
    	{32, 28, 4, 26, 4, 6, 3, 4},
    	{17, 19, 4, 17, 4, 1, 5, 7},
    	{4, 4, 5, 4, 4, 21, 6, 21},
    	{17, 14, 4, 14, 4, 11, 12, 13},
		{3, 16, 4, 13, 4, 4, 15, 10},
		{21, 9, 7, 8, 4, 5, 9, 9},
		{3, 16, 4, 9, 4, 5, 6, 10},
		{9, 16, 4, 13, 4, 14, 9, 10},
    };
    
	int m4[12][12] = {
		{34523, 7858, 8743, 17325, 18510, 9231, 4920, 7056, 9701, 5034, 7825, 1233}, 
        {8128, 435, 5021, 13603, 19635, 11386, 7075, 8840, 1843, 7189, 9256, 4234}, 
        {6809, 5364, 3453, 8582, 14614, 10067, 5756, 5904, 7207, 3882, 4235, 12432}, 
        {7849, 5515, 1040, 354, 15654, 11107, 6796, 4713, 7358, 4900, 5275, 4532}, 
        {10918, 8365, 4109, 5808, 3456, 14176, 9865, 7928, 931, 7991, 8344, 23454}, 
        {336, 7285, 2830, 11412, 17444, 678, 4347, 6483, 6688, 4461, 7065, 2345}, 
        {1053, 2938, 3823, 12405, 15835, 4311, 879, 2136, 4781, 114, 2905, 1111}, 
        {8930, 802, 5823, 14405, 20437, 12188, 7877, 345, 2645, 7429, 10058, 4323}, 
        {9987, 7434, 3178, 11760, 17792, 13245, 8934, 6997, 867, 7060, 7413, 999}, 
        {10518, 2824, 3709, 12291, 15721, 13776, 9465, 2022, 4667, 3242, 7944, 888}, 
        {2574, 4459, 5344, 9561, 17356, 5832, 1521, 3657, 6302, 1635, 3265, 7890},
		{9584, 900, 4441, 1000, 17765, 546, 2221, 3357, 5302, 1631, 3235, 7690}
	};

   int n = 4;
   
   VectorVectorInt matrix;
   for (int i=0; i<n; i++) {
    	VectorInt row;
     	for (int j=0; j<n; j++) row.push_back(m[i][j]);  
     	matrix.push_back(row);
   }

   // 20000 итераций для точного измерения времени
   VectorPairInt result;
   long t1 = clock();
   for(int i=0; i < 20000; i++)
   result = HungarianAlgorithm(matrix);

   t1 = clock() - t1;

   // Получение результатов
   int cost = 0;
   for(int i = 0; i < int(result.size()); i++) {
    	pair <int,int> ans = result[i];
        cout << "x" << ans.first + 1 << "->" << "y" << ans.second + 1 << endl;
        cost += m[ans.first][ans.second];
   }

   cout << "Cost     : " << cost << endl;
   cout << "Time for 20000 iterations (ms) : " <<  t1 << endl;

   int t;
   cin >> t;

   return 0;
}
