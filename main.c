//
//main.c

#include <stdio.h>
#include <stdlib.h>
#include "elevator.h"

int main()
{
	El *p;//����״̬ 
	Fl *s, *L;//�����赽��Ĳ���(s�洢��ʼʱ��Ҫ����Ĳ�����L�洢�������й�������Ҫ���ӵĲ���) 
	p = (El*)malloc(sizeof(El));
	s = (Fl*)malloc(sizeof(Fl));
	L = (Fl*)malloc(sizeof(Fl));
	s->next = NULL;
	L->next = NULL;

	//���ݳ�ʼ�� 
	init_elevator(p);

	//�������� 
	int ff, control;
	ff = 1;
	while (ff) {
		meau_state();
		printf("\n>> The elevator continues? If yes, please enter 1. If not, please enter 0:");
		scanf("%d", &control);
		if (control == 1) {
			int k;
			p->num = 0;
			printf(">> There are %d people in the elevator and the elevator is at %d building!\n", p->num, p->level);
			printf(">> Please enter the initial number of people on the elevator:");
			scanf("%d", &p->num);
			meau_event();
			printf(">> Please select the event:");
			scanf("%d", &k);
			if (k == 1) p->state = STATE_UP;
			else p->state = STATE_DOWN;
			Get_floor(s, p);//��ȡ����Ҫ�����¥�� 
			if (k == 1) Sort_floorup(s);
			else Sort_floordown(s);
			printf(">> The floors to be reached are:");
			Print_floor(s);
			Every_floor(s, L, p, k);//����ÿ��¥�� 
		}
		else ff = 0;
		printf("\n>> Press any key to continue!");
		getch();
		system("cls");
	}
	
	//��ԭ����
	init_elevator(p);

	//�ͷ��ڴ� 
	free(p);
	free(s);
}
