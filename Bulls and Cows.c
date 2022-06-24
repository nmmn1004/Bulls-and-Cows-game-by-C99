#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int equal(int a, int b[]);
int strike(int a[], int b[]);
int ball(int a[], int b[]);
int reset(int* a[]);

int main(void)
{
	srand(time(NULL));	//실행될 때 마다 무작위로 숫자를 출력해주기 위해

	int list[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };	//서로 중복되지 않도록 하기 위해 미리 번호를 만듦
	int num[4] = { -1, -1, -1, -1 };					//모두 -1로 초기화, -1은 없음으로 취급
	int new_num[4] = { -1, -1, -1, -1 };

	int random;
	int s = 0, b = 0, round = 1;
	int limit;

	for (int i = 0; i < 4; i++)		//랜덤 숫자를 뽑아 list의 숫자를 random에 저장하고 -1로 저장, -1이 걸리면 다시 재추첨
	{
		while (num[i] == -1)
		{
			random = rand() % 10;
			num[i] = list[random];
		}
		list[random] = -1;
	}
	
	printf("라운드 횟수를 입력해주세요: ");
	scanf_s("%d", &limit);

	while (s < 4)	//4스트라이크로 정답을 맞히거나 round가 limit을 넘으면 탈출
	{
		int j = 0;
		reset(new_num);
		printf("\n\t[ %d 라운드 ]\n", round);
		while (j < 4)	//숫자를 입력받아 new_num에 넣어줌
		{
			printf("%d번 숫자를 입력해주세요: ", j + 1);
			scanf_s("%d", &new_num[j]);

			if (new_num[j] < 0 || new_num[j] > 9)	//0 ~ 9 범위 밖에 있는 숫자를 입력 시 반복
			{
				printf("범위를 벗어났습니다\n");
				j = 0;
			}
			else if (equal(new_num[j], new_num))	//입력한 값과 이전에 입력한 값을 비교하여 중복이 있으면 반복
			{
				printf("중복입니다\n");
				j = 0;
			}
			else
				j++;
		}

		s = strike(num, new_num);	//자리, 숫자가 같은 개수를 s에 넣어줌
		b = ball(num, new_num);		//숫자만 같은 개수를 b에 넣어줌

		printf("\nstrike: %d\tball: %d\n\n", s, b);

		if (round >= limit)
			break;
		round++;
	}

	if (s == 4)
		printf("당신의 승리입니다!\n");
	else
		printf("당신의 패배입니다!\n");
	
	printf("정답은 ");

	for (int k = 0; k < 4; k++)
	{
		printf("%d ", num[k]);
	}

	return 0;
}

int equal(int a, int b[])	//입력된 값과 그 이전에 입력한 값의 배열을 비교하여 같은 숫자가 1개 초과할 경우 1, 1개만 있을 경우 0을 반환
{
	int s = 0;
	for (int i = 0; i < 4; i++)
	{
		if (a == b[i])
			s++;
	}
	if (s > 1)
		return 1;
	else
		return 0;
}

int strike(int a[], int b[])
{
	int s = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (a[i] == b[j] && i == j)	//숫자가 같고 인덱스도 같으면 s에 1을 더해줌
			{
				s++;
			}
		}
	}
	return s;
}
int ball(int a[], int b[])
{
	int ball = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (a[i] == b[j] && i != j)	//숫자가 같으나 인덱스가 다르면 b에 1을 더해줌
			{
				ball++;
			}
		}
	}
	return ball;
}
int reset(int* a[])	//포인터로 배열 그 자체에 접근하여 -1, 즉 없음으로 초기화
{

	for (int i = 0; i < 4; i++)
	{
		a[i] = -1;
	}
}
