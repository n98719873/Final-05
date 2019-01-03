#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

enum GStatus { WON, LOSE, CONTINUE };
enum DStatus { NotUse, One, Double, Triple };

void rollDice(int *dice1, int *dice2, int *dice3); //�Y��l
void handle(int *dice1, int *dice2, int *dice3, int *dtotal, int *dstatus); //�B�z�I��
void judgeWinLose(int *Bdtotal, int *Mdtotal, int *gStatus); //�P�_�ӭt
void printDice(int dice1, int dice2, int dice3); //�C�L��l

void main(void)
{
	int *Bdice1, *Bdice2, *Bdice3, *Bdtotal, *Bdstatus; //���a����l
	int *Mdice1, *Mdice2, *Mdice3, *Mdtotal, *Mdstatus; //�ڪ���l
	int *gStatus; //�C�����A
	int totalamount = 10000; //���W�`�B
	int Gambling; //�������
	int a;
	int statistics[3] = { 0, 0, 0 };

	char keepchoice; //�O�_�n�~��

	srand(time(NULL));

	printf ("�W�h���� : \n"
			"���a���Y��l�A�U�`,�I�Ƥj�����\n\n"
			"�I�ƪ��p��覡�� : \n"
			"�T���I�ƬۦP,�I�� * 2\n"
			"�����I�ƬۦP,�I�� * 1.5\n"
			"�T�����P�I��,�I�� * 1\n\n"
			"������p��覡�� : \n"
			"��� * �ڤ��l�ۦP�Ӽ� * ���a��l�ۦP�Ӽ�\n\n"
			);
	printf("�ڲ{�b�֦�������� %d \n\n", totalamount);
	do
	{
		//�Y���a����l
		rollDice(&Bdice1, &Bdice2, &Bdice3);
		handle(&Bdice1, &Bdice2, &Bdice3, &Bdtotal, &Bdstatus);
		printf("���a�Y��l��");
		for (int i = 0; i < 4; i++)
		{
			printf(".");
			Sleep(500);
		}
		printf("\n\n");
		printDice(Bdice1, Bdice2, Bdice3);
		//printf("���a����l�O %d %d %d\n", Bdice1, Bdice2, Bdice3);
		//printf("�I�ƩM�G%d ���A�G%d\n\n", Bdtotal, Bdstatus);

		//�U�`���B
		do
		{
			printf("\n�ФU�`���B : ");
			scanf_s("%d", &Gambling);

			if (Gambling > totalamount)
			{
				printf("\n�l�B����!!!\n");
				a = -1;
			}
			else
			{
				printf("\n�U�`���\\n");
				a = 1;
			}
		} while (a == -1);

		//�Y�ڪ���l
		rollDice(&Mdice1, &Mdice2, &Mdice3);
		handle(&Mdice1, &Mdice2, &Mdice3, &Mdtotal, &Mdstatus);
		printf("\n�Y��l��");
		for (int i = 0; i < 4; i++)
		{
			printf(".");
			Sleep(500);
		}
		printf("\n\n");
		printDice(Mdice1, Mdice2, Mdice3);
		//printf("�ڪ���l�O %d %d %d\n", Mdice1, Mdice2, Mdice3);
		//printf("�I�ƩM�G%d ���A�G%d\n\n", Mdtotal, Mdstatus);

		//�ӭt�B�z
		judgeWinLose(&Bdtotal, &Mdtotal, &gStatus);
		Sleep(1500);
		if (gStatus == WON)
		{
			printf("\n***���ߧAĹ�F***\n");
			Gambling = Gambling*(int)(Mdstatus)*(int)(Bdstatus);
			totalamount += Gambling;
			printf("\n�z���l�B�� : %d\n", totalamount);
			statistics[0]++;
			
		}
		else if (gStatus == LOSE)
		{
			printf("\n***���ߧA��F***\n");
			Gambling = Gambling*(int)(Mdstatus)*(int)(Bdstatus);
			totalamount -= Gambling;
			printf("\n�z���l�B�� : %d\n", totalamount);
			statistics[1]++;
		}
		else
		{
			printf("\n***�M��***\n");
			statistics[2]++;
		}

		//�O�_�n�~��
		if (totalamount > 0)
		{
			printf("\n�O�_�n�~��C�� ? (y/n)\n\n");
			keepchoice = getch();
		}
		else
		{
			printf("\n�A�S���F�a��\n\n");
			keepchoice = 'n';
		}

	} while (keepchoice == 'y');

	//�C������
	if (totalamount > 0)
	{
		printf("�z�`�@Ĺ�F %d ��\n", statistics[0]);
		printf("�z�`�@��F %d ��\n", statistics[1]);
		printf("�� %d ���M��\n", statistics[0]);
		printf("�C������\n\n");
	}
	else
	{
		printf("�z�`�@Ĺ�F %d ��\n", statistics[0]);
		printf("�z�`�@��F %d ��\n", statistics[1]);
		printf("�� %d ���M��\n", statistics[0]);
		printf("�u!\n\n");
	}

	system("pause");
}

void rollDice(int *dice1, int *dice2, int *dice3) //�Y��l
{
	*dice1 = 1 + (rand() % 6);
	*dice2 = 1 + (rand() % 6);
	*dice3 = 1 + (rand() % 6);
}

void handle(int *dice1, int *dice2, int *dice3, int *dtotal, int *dstatus) //�B�z�I��
{
	if ((*dice1 == *dice2) && (*dice2 == *dice3)) { *dstatus = Triple; }
	else if ((*dice1 == *dice2) || (*dice2 == *dice3) || (*dice1 == *dice3)) { *dstatus = Double; }
	else { *dstatus = One; }

	//�I�ƩM
	if (*dstatus != 1)
		*dtotal = (*dice1 + *dice2 + *dice3) * (float)(*dstatus / 2 + 0.5);
	else
		*dtotal = (*dice1 + *dice2 + *dice3);
}

void judgeWinLose(int *Bdtotal, int *Mdtotal, int *gStatus) //�P�_�ӭt
{
	if (*Bdtotal < *Mdtotal) { *gStatus = WON; }
	else if (*Bdtotal > *Mdtotal) { *gStatus = LOSE; }
	else { *gStatus = CONTINUE; }
}

void printDice(int dice1, int dice2, int dice3) //�C�L��l
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