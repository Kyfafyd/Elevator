//
//elevator.c 

#include <stdio.h>
#include <stdlib.h>
#include "elevator.h" 

#define MAX_FLOOR 10
#define MAX_NUM 10

//��ʾ��
//�¼��б� 
void meau_event()
{
	printf(">> Event list:\n");
	printf(">> 1:EVENT_UP\n");
	printf(">> 2:EVENT_DOWN\n");
}
//״̬�б� 
void meau_state()
{
	printf("\n>> The floor range is: 1--%d, and the floor input ends after -1!\n",MAX_NUM);
	printf(">> The elevator status represented by each number is:\n");
	printf(">> 0:STATE_STOP\n");
	printf(">> 1:STATE_OPEN\n");
	printf(">> 2:STATE_UP\n");
	printf(">> 3:STATE_DOWN\n");
	printf(">> 4:STATE_WARN\n");
}
//¥���ȡ��ʾ
void meau_floor(Ele p)
{
	if (p->level == 1 && p->state != STATE_OPEN)
		printf(">> The elevator is on the ground floor now,please enter the floor you want to reach:", MAX_FLOOR);
	if (p->level == MAX_FLOOR && p->state != STATE_OPEN)
		printf(">> The elevator is on the top floor now,please enter the floor you want to reach:", MAX_FLOOR);
	if (p->level != 1 && p->level != MAX_FLOOR && p->state == STATE_UP)
		printf(">> The elevator is going up now,please enter the floor you want to reach:", MAX_FLOOR, p->level);
	if (p->level != 1 && p->level != MAX_FLOOR && p->state == STATE_DOWN)
		printf(">> The elevator is going down now,please enter the floor you want to reach:", MAX_FLOOR, p->level);
}

//����״̬��ʼ��(���ݴ���һ¥�ҵ����Źرգ� 
void init_elevator(Ele p)
{
	p->num = 0;//����������Ϊ0 
	p->level = 1;//���ݴ���һ¥ 
	p->state = (T_StateType)0;//�����Ŵ��ڹر�״̬ 
	if (p->state == STATE_STOP && p->level == 1)
		printf(">> Initializing the elevator successfully!\n");
}

//¥���ȡ 
void Get_floor(Flo L, Ele p)
{
	Fl *s, *r;
	int flag = 1;
	int x;
	r = L;
	meau_floor(p);
	while (flag) {
		if (p->level == 1) {//���ݴ��ڵ�¥ʱ 
			if (p->state == STATE_OPEN) break;
			scanf("%d", &x);
			if (x > 1 && x <= MAX_FLOOR) {
				s = (Flo)malloc(sizeof(Fl));
				s->floor = x;
				r->next = s;
				r = s;
			}
			else {
				flag = 0;
				r->next = NULL;
			}
		}
		if (p->level == MAX_FLOOR) {//���ݴ��ڶ�¥ʱ
			if (p->state == STATE_OPEN) break;
			scanf("%d", &x);
			if (x >= 1 && x < MAX_FLOOR) {
				s = (Flo)malloc(sizeof(Fl));
				s->floor = x;
				r->next = s;
				r = s;
			}
			else {
				flag = 0;
				r->next = NULL;
			}
		}
		if (p->level != 1 && p->level != MAX_FLOOR && p->state == STATE_UP) {//������һ������������ʱ 
			scanf("%d", &x);
			if (x > p->level && x <= MAX_FLOOR) {
				s = (Flo)malloc(sizeof(Fl));
				s->floor = x;
				r->next = s;
				r = s;
			}
			else {
				flag = 0;
				r->next = NULL;
			}
		}
		if (p->level != 1 && p->level != MAX_FLOOR && p->state == STATE_DOWN) {//������һ���������½�ʱ 
			scanf("%d", &x);
			if (x < p->level && x >= 1) {
				s = (Flo)malloc(sizeof(Fl));
				s->floor = x;
				r->next = s;
				r = s;
			}
			else {
				flag = 0;
				r->next = NULL;
			}
		}
		if (p->level != 1 && p->level != MAX_FLOOR && p->state == STATE_OPEN) break;
	}
}

//����״̬ת�� 
void trans_elevator(Ele p, int k)//kΪ��������Ҫ�����¥�� 
{
	switch (p->state) {
	case STATE_STOP:
		switch (p->event) {
		case EVENT_OPEN:
			p->state = (T_StateType)1;
			p->level = k;
			break;
		case EVENT_UP:
			p->state = (T_StateType)2;
			p->level = k;
			break;
		case EVENT_DOWN:
			p->state = (T_StateType)3;
			p->level = k;
			break;
		}
		break;
	case STATE_OPEN:
		switch (p->event) {
		case EVENT_CLOSE:
			p->state = (T_StateType)0;
			p->level = k;
			break;
		case EVENT_WARN:
			p->state = (T_StateType)4;
			p->level = k;
			break;
		}
		break;
	case STATE_UP:
		if (p->event == EVENT_STOP)
			p->state = (T_StateType)0;
		p->level = k;
		break;
	case STATE_DOWN:
		if (p->event == EVENT_STOP)
			p->state = (T_StateType)0;
		p->level = k;
		break;
	case STATE_WARN:
		if (p->event == EVENT_DELWARN)
			p->state = (T_StateType)1;
		p->level = k;
		break;
	}
}

//����Ҫ�����ÿ��¥�� 
void Every_floor(Flo s, Flo L, Ele p, int k)
{
	while (s->next != NULL) {
		int w, flag;
		flag = 1;
		p->event = EVENT_STOP;
		trans_elevator(p, s->next->floor);
		p->event = EVENT_OPEN;
		trans_elevator(p, s->next->floor);
		printf("\n>> The elevator has reached the %d floor, the elevator is in the %d state,there are %d people in the elevator!\n", p->level, p->state, p->num);
		if (Amount_floor(s) > 1) {
			printf(">> If the number of people in the elevator increases, enter a positive number, otherwise enter a negative number:");
			while (flag) {
				scanf("%d", &w);
				if ((w + p->num) > MAX_NUM) {
					p->event = EVENT_WARN;
					trans_elevator(p, s->next->floor);
					printf(">> Overweight, please re-enter:");
				}
				else {
					p->event = EVENT_CLOSE;
					trans_elevator(p, s->next->floor);
					p->num = p->num + w;
					flag = 0;
				}
			}
			if (p->state == STATE_STOP) printf(">> Elevator doors close,");
			if (k == 1) p->state = STATE_UP;
			else p->state = STATE_DOWN;
			printf("the elevator is in the state of %d, and there are %d people in the elevator\n", p->state, p->num);
		}
		Get_floor(L, p);
		Sort_floorup(L);
		Sort_floorup(s);
		Merge_floor(s, L);
		if (k == 2) Reverse_floor(s);
		Delete_samefloor(s);
		Delete_floor(s);
		if (s->next == NULL)
			printf(">> The elevator has reached all the right floors!\n");
		else {
			printf(">> The floors to be reached are:");
			Print_floor(s);
		}
	}
}

//ɾ���Ѿ������¥��
void Delete_floor(Flo L)
{
	Fl* temp;
	if (L->next != NULL) {
		temp = L->next;
		L->next = temp->next;
		free(temp);
	}
}

//���Ҫ���������¥�� 
void Print_floor(Flo L)
{
	L = L->next;
	if (L == NULL)
		printf(">> NULL!");
	while (L != NULL) {
		printf("%d ", L->floor);
		L = L->next;
	}
	printf("\n");
}

//��ȡ��Ҫ�����¥����Ŀ 
int Amount_floor(Flo L)
{
	Fl *p;
	int length = 0;
	p = L->next;
	while (p != NULL) {
		p = p->next;
		length++;
	}
	return length;
}

//����ǰ�����¥�����Ѿ������¥��ϲ� 
Flo Merge_floor(Flo L1, Flo L2)
{
	Fl *p, *q, *r, *L3;
	p = L1->next;
	q = L2->next;
	r = L3 = L1;
	while (p&&q) {
		if (p->floor <= q->floor) {
			r->next = p;
			r = r->next;
			p = p->next;
		}
		else {
			r->next = q;
			r = r->next;
			q = q->next;
		}
	}
	if (p) r->next = p;
	if (q) r->next = q;
	free(L2);
	return L3;
}

//¥����������
void Sort_floorup(Flo L)
{
	Flo p,q,r;
	r=L;
	while(r->next!=NULL){
		p=r;
		q=p->next;
		while(q->next!=NULL){
			if(p->next->floor>q->next->floor) p=q;
			q=q->next;
		}
		q=p->next;
		p->next=q->next;
		q->next=r->next;
		r->next=q;
		r=q;
	}
} 

//¥�㽵������
void Sort_floordown(Flo L)
{
	Sort_floorup(L);
	Reverse_floor(L);
}

//ɾ���ظ�¥�� 
void Delete_samefloor(Flo L)
{
	Fl *p, *q;
	p = L;
	q = L->next;
	while (q) {
		if (p->floor == q->floor) {
			q = q->next;
			p->next = q;
		}
		p = p->next;
		q = q->next;
	}
}

//����¥��˳�� 
void Reverse_floor(Flo L)
{
	Fl *p, *s;
	p = L->next;
	L->next = NULL;
	while (p) {
		s = p;
		p = p->next;
		s->next = L->next;
		L->next = s;
	}
}
