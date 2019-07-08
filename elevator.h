//
//elevator.h

/*****************************************************************************
/*C���Լ��׵���ʵ��(ģ��״̬��)
/*
/*ͨ����������ö�����ͺ������ṹ�������ݵ�ǰ״̬
/*
/*�������¹��ܣ�
/*����״̬��ʼ��(������һ¥�ҵ����Źر�)
/*ѡ������Ƿ��������
/*���Ƶ���ÿ������ʱ�ķ���
/*�ڵ������й�������Ӳ���
/*������ݲ����ǿ���������
/*�жϵ����Ƿ���
/*���ӻ���ٵ���������
/*�궨���������ؿ�����¥�㷶Χ,�ɸ�����Ҫ�޸�elevator.c�е�MAX_FLOOR,MAX_NUM
/*�����ݻ�ԭΪ��ʼ��ʱ��״̬ 
******************************************************************************/

#ifndef elevator_h
#define elevator_h

//��ǰ�¼����� 
typedef enum tagT_EventType {
	EVENT_OPEN = 0,
	EVENT_UP,
	EVENT_DOWN,
	EVENT_CLOSE,
	EVENT_WARN,
	EVENT_STOP,
	EVENT_DELWARN
}T_EventType;

//��ǰ״̬����
typedef enum tagT_StateType {
	STATE_STOP = 0,
	STATE_OPEN,
	STATE_UP,
	STATE_DOWN,
	STATE_WARN
}T_StateType;

//����״̬�ṹ���� 
typedef struct Elevator {
	int num;
	int level;
	T_EventType event;
	T_StateType state;
}El, *Ele;

//�����赽���¥���¼�Ľṹ
typedef struct Ele_floor {
	int floor;
	struct Ele_floor *next;
}Fl, *Flo;

//��ʾ��
//�¼��б� 
void meau_event();
//״̬�б� 
void meau_state();
//¥���ȡ��ʾ
void meau_floor(Ele p);

//����״̬��ʼ��(���ݴ���һ¥�ҵ����Źرգ� 
void init_elevator(Ele p);

//¥���ȡ 
void Get_floor(Flo L, Ele p);

//ɾ���Ѿ������¥��
void Delete_floor(Flo L);

//����״̬ת�� 
void trans_elevator(Ele p, int k);//kΪ��������Ҫ�����¥�� 

//����Ҫ�����ÿ��¥�� 
void Every_floor(Flo s, Flo L, Ele p, int k);

//���Ҫ�����¥��
void Print_floor(Flo L);

//��ȡ��Ҫ�����¥����Ŀ 
int Amount_floor(Flo L);

//����ǰ�����¥����һ�����¥��ϲ�
Flo Merge_floor(Flo L1, Flo L2);

//ɾ���ظ�¥�� 
void Delete_samefloor(Flo L);

//¥����������
void Sort_floorup(Flo L);

//¥�㽵������
void Sort_floordown(Flo L);

//����¥�� 
void Reverse_floor(Flo L);

#endif/*elevator.h*/
