//
//elevator.h

/*****************************************************************************
/*C语言简易电梯实现(模拟状态机)
/*
/*通过定义两个枚举类型和两个结构表征电梯当前状态
/*
/*具有如下功能：
/*电梯状态初始化(电梯在一楼且电梯门关闭)
/*选择电梯是否继续运行
/*控制电梯每次运行时的方向
/*在电梯运行过程中添加层数
/*输入电梯层数是可乱序输入
/*判断电梯是否超载
/*增加或减少电梯内人数
/*宏定义电梯最大载客数和楼层范围,可根据需要修改elevator.c中的MAX_FLOOR,MAX_NUM
/*最后电梯还原为初始化时的状态 
******************************************************************************/

#ifndef elevator_h
#define elevator_h

//当前事件类型 
typedef enum tagT_EventType {
	EVENT_OPEN = 0,
	EVENT_UP,
	EVENT_DOWN,
	EVENT_CLOSE,
	EVENT_WARN,
	EVENT_STOP,
	EVENT_DELWARN
}T_EventType;

//当前状态类型
typedef enum tagT_StateType {
	STATE_STOP = 0,
	STATE_OPEN,
	STATE_UP,
	STATE_DOWN,
	STATE_WARN
}T_StateType;

//电梯状态结构参量 
typedef struct Elevator {
	int num;
	int level;
	T_EventType event;
	T_StateType state;
}El, *Ele;

//电梯需到达的楼层记录的结构
typedef struct Ele_floor {
	int floor;
	struct Ele_floor *next;
}Fl, *Flo;

//提示语
//事件列表 
void meau_event();
//状态列表 
void meau_state();
//楼层获取提示
void meau_floor(Ele p);

//电梯状态初始化(电梯处于一楼且电梯门关闭） 
void init_elevator(Ele p);

//楼层获取 
void Get_floor(Flo L, Ele p);

//删除已经到达的楼层
void Delete_floor(Flo L);

//电梯状态转换 
void trans_elevator(Ele p, int k);//k为接下来需要到达的楼层 

//遍历要到达的每个楼层 
void Every_floor(Flo s, Flo L, Ele p, int k);

//输出要到达的楼层
void Print_floor(Flo L);

//获取还要到达的楼层数目 
int Amount_floor(Flo L);

//将当前输入的楼层与一输入的楼层合并
Flo Merge_floor(Flo L1, Flo L2);

//删除重复楼层 
void Delete_samefloor(Flo L);

//楼层升序排序
void Sort_floorup(Flo L);

//楼层降序排列
void Sort_floordown(Flo L);

//逆置楼层 
void Reverse_floor(Flo L);

#endif/*elevator.h*/
