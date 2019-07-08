//
//main.c

#include <stdio.h>
#include <stdlib.h>
#include "elevator.h"

int main()
{
	El *p;//电梯状态 
	Fl *s, *L;//电梯需到达的层数(s存储开始时需要到达的层数，L存储电梯运行过程中需要增加的层数) 
	p = (El*)malloc(sizeof(El));
	s = (Fl*)malloc(sizeof(Fl));
	L = (Fl*)malloc(sizeof(Fl));
	s->next = NULL;
	L->next = NULL;

	//电梯初始化 
	init_elevator(p);

	//电梯运行 
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
			Get_floor(s, p);//获取电梯要到达的楼层 
			if (k == 1) Sort_floorup(s);
			else Sort_floordown(s);
			printf(">> The floors to be reached are:");
			Print_floor(s);
			Every_floor(s, L, p, k);//遍历每个楼层 
		}
		else ff = 0;
		printf("\n>> Press any key to continue!");
		getch();
		system("cls");
	}
	
	//还原电梯
	init_elevator(p);

	//释放内存 
	free(p);
	free(s);
}
