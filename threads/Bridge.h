#pragma once
#include "system.h"
#include "synch.h"
#define CROSS_BRIDGE_TIME 10
#define BASE_GREEN_LIGHT_TIME (10*CROSS_BRIDGE_TIME)		//基准绿灯时间,为服务时间的十倍

//#define FCFS            //先来先服务算法
//#define ONE_DIRECTION	//同方向优化算法
#define TRAFFIC_LIGHT	//红绿灯算法



class Bridge
{
public:
	Bridge();
	~Bridge();
	void OneVehicle(int direc)
	{
		ArriveBridge(direc);
		CrossBridge(direc);
		ExitBridge(direc);
	};
private:
	void ArriveBridge(int direc);
	void CrossBridge(int direc);
	void ExitBridge(int direc);

#ifdef FCFS            				//先来先服务算法
	int on_bridge_num;
	int current_direc;

	bool pre_is_wait;
	Lock *lock;
	Condition *con;
#endif

#ifdef ONE_DIRECTION				//同方向优化算法
	int on_bridge_num;
	int current_direc;

	Lock *lock;
	Condition *con;
#endif

#ifdef TRAFFIC_LIGHT				//红绿灯算法
	int on_bridge_num;
	int current_direc;
    int next_switch_time;
	
	bool yellow_light_on;	

	Lock *lock;
	Condition *direc_con[2];

	int direc_time[2];
	//int direc_0_time;
	//int direc_1_time;               //方向0或者方向1的剩余绿灯时间，-1代表红灯

	int direc_car_num[2];

	void switch_status();

#endif

};

