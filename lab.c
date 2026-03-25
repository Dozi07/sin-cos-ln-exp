#define _USE_MATH_DEFINES
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<math.h>

void prevedenie(float *x) {

	*x = *x - floorf(*x/(2*M_PI)) * 2*M_PI;

}

// Прямая сумма 
float DirectSum(float* arr, int size) {
	float sum = 0.0f;
	for (int i = 0; i < size; i++) {
		sum += arr[i];
	}
	return sum;
}

// Обратная сума
float ReverseSum(float* arr, int size) {
	float sum = 0.0f;
	for (int i = size; i > 0; i--) {
		sum += arr[i - 1];
	}
	return sum;
}

//2Sum
float TwoSum(float* arr, int size) {
	float err = 0.0f;
	float sum = 0.0f;
	float b, tmp1 = 0.0f, tmp2 = 0.0f, c = 0.0f;
	for (int i = 0; i < size; i++) {
		b = arr[i];

		c = sum + b;
		tmp1 = c - b;
		tmp1 = sum - tmp1;
		tmp2 = c - sum;
		tmp2 = b - tmp2;
		err += tmp1 + tmp2;

		sum = c;
	}

	return err + sum;
}

//структура


struct SumFun {

	float(*direct)(float*, size_t);
	float(*reverse)(float*, size_t);
	float(*twosum)(float*, size_t);
};

// Функции для заполнения масива членами ряда тейлора и подсчета
float MySin(float x, int NumTeylor, struct SumFun sums, int SumChose) {
	prevedenie(&x);
	float* arr = (float*)malloc(NumTeylor * sizeof(float));
	float CurrentTerm = x;
	float sum = 0.0f;
	arr[0] = CurrentTerm;


	for (int i = 1; i < NumTeylor; i++) {
		
		CurrentTerm = CurrentTerm * ((-x * x) / ((2.0f * i) * (2.0f * i + 1.0f)));
		arr[i] = CurrentTerm;
	}

	if (SumChose == 1) sum = sums.direct(arr, NumTeylor);
	else if (SumChose == 2) sum = sums.reverse(arr, NumTeylor);
	else if (SumChose == 3) sum = sums.twosum(arr, NumTeylor);

	free(arr);
	
	return sum; 
		
	
}

	
float MyCos(float x, int NumTeylor, struct SumFun sums, int SumChose) {
	
	float sum = 0.0f;
	float* arr = (float*)malloc(sizeof(float) * NumTeylor);
	float CurrentTerm = 1.0f;
	prevedenie(&x);
	arr[0] = CurrentTerm;


	for (int i = 1; i < NumTeylor; i++) {

		CurrentTerm = CurrentTerm * ((-x * x) / ((2.0f * i - 1.0f) * (2.0f * i)));
		arr[i] = CurrentTerm;
	}

	

	if (SumChose == 1) sum = sums.direct(arr, NumTeylor);
	else if (SumChose == 2) sum = sums.reverse(arr, NumTeylor);
	else if (SumChose == 3) sum = sums.twosum(arr, NumTeylor);
	
	free(arr);
	
	return sum;
}

float MyExp(float x, int NumTeylor, struct SumFun sums, int SumChose) {
	
	float* arr = (float*)malloc(NumTeylor * sizeof(float));
	float CurrentTerm = 1.0f;
	float sum = 0.0f;
	arr[0] = CurrentTerm;


	for (int i = 1; i < NumTeylor; i++) {

		CurrentTerm = CurrentTerm * ((x) / (i));
		arr[i] = CurrentTerm;
	}

	if (SumChose == 1) sum = sums.direct(arr, NumTeylor);
	else if (SumChose == 2) sum = sums.reverse(arr, NumTeylor);
	else if (SumChose == 3) sum = sums.twosum(arr, NumTeylor);

	free(arr);

	return sum;

}

float MyLn(float z, int NumTeylor, struct SumFun sums, int SumChose) {
	
	float* arr = (float*)malloc(NumTeylor * sizeof(float));
	float x = (z - 1) / (z + 1);
	float CurrentTerm = x;
	float sum = 0.0f;
	arr[0] = CurrentTerm;


	for (int i = 1; i < NumTeylor; i++) {

		CurrentTerm = CurrentTerm * (x * x) * (2.0f * i - 1.0f) / (2.0f * i + 1.0f);
		arr[i] = CurrentTerm;
	}

	if (SumChose == 1) sum = sums.direct(arr, NumTeylor);
	else if (SumChose == 2) sum = sums.reverse(arr, NumTeylor);
	else if (SumChose == 3) sum = sums.twosum(arr, NumTeylor);

	free(arr);

	return 2 * sum;

}

//
int main() {

	setlocale(LC_ALL, "rus");

	//Переменные 
	int ChoseFunc, TeylorNum, SumChose;
	float x;



	
	struct SumFun sums = {
		DirectSum,
		ReverseSum,
		TwoSum
	};
	
	while (1) {
		
		//Вывод текста в консоль и задание перемееных
		printf("Выберите функцию которую хотите посчитать: \n1 - sin \n2 - cos \n3 - ln \n4 - exp\n5 - Выйти из програмы\n");
		scanf_s("%d", &ChoseFunc);
		if (ChoseFunc == 5) exit(0);
		printf("Выберите количество членов ряда тейлора которое вы хотите учитывать: ");
		scanf_s("%d", &TeylorNum);
		/*printf("Выберите метод сумирования: \n1 - Прямой \n2 - Обратный \n3 - 2Sum \n");
		scanf_s("%d", &SumChose);*/
		printf("\nВыберите значение х от которого вы хотите посчитать функцию: ");
		scanf_s("%f", &x);

		switch (ChoseFunc) {
			
			

		case 1:

			printf("%e (ошибка в вычислениях  %.10f) - прямая сумма\n", MySin(x, TeylorNum, sums, 1), sinf(x) - MySin(x, TeylorNum, sums, 1));
			printf("%e (ошибка в вычислениях  %.10f) - обратная сумма\n", MySin(x, TeylorNum, sums, 2), sinf(x) - MySin(x, TeylorNum, sums, 2));
			printf("%e (ошибка в вычислениях  %.10f) - TwoSum\n\n", MySin(x, TeylorNum, sums, 3), sinf(x) - MySin(x, TeylorNum, sums, 3));


			break;

		case 2:

			printf("%e (ошибка в вычислениях  %.10f) - прямая сумма\n", MyCos(x, TeylorNum, sums, 1), cosf(x) - MyCos(x, TeylorNum, sums, 1));
			printf("%e (ошибка в вычислениях  %.10f) - обратная сумма\n", MyCos(x, TeylorNum, sums, 2), cosf(x) - MyCos(x, TeylorNum, sums, 2));
			printf("%e (ошибка в вычислениях  %.10f) - TwoSum\n\n", MyCos(x, TeylorNum, sums, 3), cosf(x) - MyCos(x, TeylorNum, sums, 3));

			break;

		case 3:
			if (x > 0) {
				printf("%e (ошибка в вычислениях  %.10f) - прямая сумма\n", MyLn(x, TeylorNum, sums, 1), logf(x) - MyLn(x, TeylorNum, sums, 1));
				printf("%e (ошибка в вычислениях  %.10f) - обратная сумма\n", MyLn(x, TeylorNum, sums, 2), logf(x) - MyLn(x, TeylorNum, sums, 2));
				printf("%e (ошибка в вычислениях  %.10f) - TwoSum\n\n", MyLn(x, TeylorNum, sums, 3), logf(x) - MyLn(x, TeylorNum, sums, 3));
			}
			else
			{
				printf("Введите число удовлетворяющее ограничениям логарифма");
			}
			break;

		case 4:

			printf("%e (ошибка в вычислениях  %.10f) - прямая сумма\n", MyExp(x, TeylorNum, sums, 1), expf(x) - MyExp(x, TeylorNum, sums, 1));
			printf("%e (ошибка в вычислениях  %.10f) - обратная сумма\n", MyExp(x, TeylorNum, sums, 2), expf(x) - MyExp(x, TeylorNum, sums, 2));
			printf("%e (ошибка в вычислениях  %.10f) - TwoSum\n\n", MyExp(x, TeylorNum, sums, 3), expf(x) - MyExp(x, TeylorNum, sums, 3));

			

			break;

		}

	}
	
}