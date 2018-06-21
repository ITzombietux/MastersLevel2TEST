#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void InitGame() // 숫자야구 소개.
{
	srand(time(NULL)); // 시간을 참조한 난수 생성
	printf("숫자야구 게임 by ITzombietux\r\n");
}

int IsFind(int com[3], int index) //컴퓨터의 숫자 중복 체크
{
	int re;
	int i;

	re = 0; // re 0으로 초기화
	for (i = 0; i<index; i++) 
	{
		if (com[i] == com[index]) 
		{
			return 1;
		}
	}

	return re; //1 리턴해줌
}

void MakeComData(int com[3]) // 중복이 없도록 0~9까지 3개의 숫자를 임의로 받아온다
{
	int i;

	for (i = 0; i<3; i++)
	{
		com[i] = rand() % 10;
		if (1 == IsFind(com, i)) //IsFind 함수 호출 하여 중복 체크
			//리턴 받은 값이 1이면
		{
			i--; // 반복문 다시 수행
		}
	}
}

void InputPlayer(int p[3]) // 0~9 까지 중복 없이 숫자 3개 입력 받음 총 10번
{
	int i;

	printf("0~9 까지 중복 없이 숫자 3개를 넣으시오 :");
	for (i = 0; i<3; i++)
	{
		scanf("%d", &p[i]);
	}
}

void CheckScore(int com[3], int p[3], int* s, int* b)
// 숫자야구 알고리즘(스트라이크(s)와 볼(b)의 개수를 계산하고 3s면 10회 반복문 빠져 나감.
{
	int i;
	int j;
	int ts; //스트라이크 수
	int tb; //볼 수

	ts = 0; // 초기화(ts 주소에 0대입)
	tb = 0; // 초기화(tb 주소에 0대입)

	for (i = 0; i<3; i++) // 반복문 총9회, 3x3
	{
		for (j = 0; j<3; j++)
		{
			if (p[i] == com[j]) //p의 숫자와 com의 숫자를 비교하며 스트라이크, 볼 판단
			{
				if (i == j) //숫자와 자리까지 같으면
				{
					ts++;  //스트라이크 올라감
				}
				else // 숫자만 같으면
				{
					tb++; //볼 올라감
				}
				break;
			}
		}
	}

	*s = ts; // 9회 반복 후 올라간 ts의 값을 s의 값에 대입
	*b = tb; // 9회 반복 후 올라간 tb의 값을 b의 값에 대입
}

int CheckNextGame() //게임을 종료할 것인지, 계속할 것인지 물어봄
{
	int go;
	int re;

	re = 0; // re 0으로 초기화
	printf("-1 : end else continue game?");
	scanf("%d", &go); // go를 -1로 넣으면
	if (-1 == go) 
	{
		re = -1; // re가 -1로 바뀌고
	}

	return re; //-1을 리턴해줌.
}

int main()
{
	int com[3];
	int p[3];
	int s;
	int b;
	int i;

	InitGame(); // 1. InitGame 함수 호출

	while (1) // 무한 루프
	{
		MakeComData(com); // 2. MakeComData 함수 호출

		for (i = 0; i<10; i++)  // 10번의 반복문 입력 받음.
		{
			b = 0;
			s = 0;

			InputPlayer(p); // 3. InputPlayer 함수 호출
			CheckScore(com,p, &s, &b); // 4. CheckScore 함수  호출

			if (3 == s) // 3s 이면 반복문 빠져나옴
			{
				break;
			}
			else // 그게 아니라면 S / b 개수 알려 줌
			{
				printf(" s:%d  b:%d \r\n", s, b);
			}
		}

		if (3 == s) // s의 값이 3이면 당신이 이겼다 라고 알려 줌.
		{
			printf(" 3 STRIKE !! YOU WIN !! \r\n");
		}
		else // 10회 동안 맞추지 못하면 당신이 졌다. 상대방의 숫자 알려 줌.
		{
			printf(" YOU LOSE...\r\n");
			printf(" com => %d %d %d \r\n", com[0], com[1], com[2]);
		}

		if (-1 == CheckNextGame()) // 5. CheckNextGame 함수 호출
			//리턴 받은 값이 -1과 같으면
		{
			printf(" Thank You ! \r\n"); // Thank You 로 마무리.

			break;
		}
	}

	return 0;
}
