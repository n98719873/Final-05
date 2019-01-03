#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

enum GStatus { WON, LOSE, CONTINUE };
enum DStatus { NotUse, One, Double, Triple };

void rollDice(int *dice1, int *dice2, int *dice3); //擲骰子
void handle(int *dice1, int *dice2, int *dice3, int *dtotal, int *dstatus); //處理點數
void judgeWinLose(int *Bdtotal, int *Mdtotal, int *gStatus); //判斷勝負
void printDice(int dice1, int dice2, int dice3); //列印骰子

void main(void)
{
	int *Bdice1, *Bdice2, *Bdice3, *Bdtotal, *Bdstatus; //莊家的骰子
	int *Mdice1, *Mdice2, *Mdice3, *Mdtotal, *Mdstatus; //我的骰子
	int *gStatus; //遊戲狀態
	int totalamount = 10000; //身上總額
	int Gambling; //此局賭金
	int a;
	int statistics[3] = { 0, 0, 0 };

	char keepchoice; //是否要繼續

	srand(time(NULL));

	printf ("規則說明 : \n"
			"莊家先擲骰子再下注,點數大的獲勝\n\n"
			"點數的計算方式為 : \n"
			"三顆點數相同,點數 * 2\n"
			"兩顆點數相同,點數 * 1.5\n"
			"三顆不同點數,點數 * 1\n\n"
			"賭金的計算方式為 : \n"
			"賭金 * 我方骰子相同個數 * 莊家骰子相同個數\n\n"
			);
	printf("我現在擁有的賭金為 %d \n\n", totalamount);
	do
	{
		//擲莊家的骰子
		rollDice(&Bdice1, &Bdice2, &Bdice3);
		handle(&Bdice1, &Bdice2, &Bdice3, &Bdtotal, &Bdstatus);
		printf("莊家擲骰子中");
		for (int i = 0; i < 4; i++)
		{
			printf(".");
			Sleep(500);
		}
		printf("\n\n");
		printDice(Bdice1, Bdice2, Bdice3);
		//printf("莊家的骰子是 %d %d %d\n", Bdice1, Bdice2, Bdice3);
		//printf("點數和：%d 狀態：%d\n\n", Bdtotal, Bdstatus);

		//下注金額
		do
		{
			printf("\n請下注金額 : ");
			scanf_s("%d", &Gambling);

			if (Gambling > totalamount)
			{
				printf("\n餘額不足!!!\n");
				a = -1;
			}
			else
			{
				printf("\n下注成功\n");
				a = 1;
			}
		} while (a == -1);

		//擲我的骰子
		rollDice(&Mdice1, &Mdice2, &Mdice3);
		handle(&Mdice1, &Mdice2, &Mdice3, &Mdtotal, &Mdstatus);
		printf("\n擲骰子中");
		for (int i = 0; i < 4; i++)
		{
			printf(".");
			Sleep(500);
		}
		printf("\n\n");
		printDice(Mdice1, Mdice2, Mdice3);
		//printf("我的骰子是 %d %d %d\n", Mdice1, Mdice2, Mdice3);
		//printf("點數和：%d 狀態：%d\n\n", Mdtotal, Mdstatus);

		//勝負處理
		judgeWinLose(&Bdtotal, &Mdtotal, &gStatus);
		Sleep(1500);
		if (gStatus == WON)
		{
			printf("\n***恭喜你贏了***\n");
			Gambling = Gambling*(int)(Mdstatus)*(int)(Bdstatus);
			totalamount += Gambling;
			printf("\n您的餘額為 : %d\n", totalamount);
			statistics[0]++;
			
		}
		else if (gStatus == LOSE)
		{
			printf("\n***恭喜你輸了***\n");
			Gambling = Gambling*(int)(Mdstatus)*(int)(Bdstatus);
			totalamount -= Gambling;
			printf("\n您的餘額為 : %d\n", totalamount);
			statistics[1]++;
		}
		else
		{
			printf("\n***和局***\n");
			statistics[2]++;
		}

		//是否要繼續
		if (totalamount > 0)
		{
			printf("\n是否要繼續遊戲 ? (y/n)\n\n");
			keepchoice = getch();
		}
		else
		{
			printf("\n你沒錢了窮鬼\n\n");
			keepchoice = 'n';
		}

	} while (keepchoice == 'y');

	//遊戲結束
	if (totalamount > 0)
	{
		printf("您總共贏了 %d 局\n", statistics[0]);
		printf("您總共輸了 %d 局\n", statistics[1]);
		printf("有 %d 局和局\n", statistics[0]);
		printf("遊戲結束\n\n");
	}
	else
	{
		printf("您總共贏了 %d 局\n", statistics[0]);
		printf("您總共輸了 %d 局\n", statistics[1]);
		printf("有 %d 局和局\n", statistics[0]);
		printf("滾!\n\n");
	}

	system("pause");
}

void rollDice(int *dice1, int *dice2, int *dice3) //擲骰子
{
	*dice1 = 1 + (rand() % 6);
	*dice2 = 1 + (rand() % 6);
	*dice3 = 1 + (rand() % 6);
}

void handle(int *dice1, int *dice2, int *dice3, int *dtotal, int *dstatus) //處理點數
{
	if ((*dice1 == *dice2) && (*dice2 == *dice3)) { *dstatus = Triple; }
	else if ((*dice1 == *dice2) || (*dice2 == *dice3) || (*dice1 == *dice3)) { *dstatus = Double; }
	else { *dstatus = One; }

	//點數和
	if (*dstatus != 1)
		*dtotal = (*dice1 + *dice2 + *dice3) * (float)(*dstatus / 2 + 0.5);
	else
		*dtotal = (*dice1 + *dice2 + *dice3);
}

void judgeWinLose(int *Bdtotal, int *Mdtotal, int *gStatus) //判斷勝負
{
	if (*Bdtotal < *Mdtotal) { *gStatus = WON; }
	else if (*Bdtotal > *Mdtotal) { *gStatus = LOSE; }
	else { *gStatus = CONTINUE; }
}

void printDice(int dice1, int dice2, int dice3) //列印骰子
{
	char *diceface[7][3] = { 
		{ "|   |", "|   |", "|   |" },//0
		{ "|   |", "| * |", "|   |" },//1
		{ "|*  |", "|   |", "|  *|" },//2
		{ "|*  |", "| * |", "|  *|" },//3
		{ "|* *|", "|   |", "|* *|" },//4
		{ "|* *|", "| * |", "|* *|" },//5
		{ "|* *|", "|* *|", "|* *|" } //6
		};
	for (int i = 0; i < 3; i++)
	{
		printf("%8s%8s%8s\n", diceface[dice1][i], diceface[dice2][i], diceface[dice3][i]);
	}
}