#include <stdio.h>
#include <stdlib.h>

typedef unsigned char ubyte;
typedef unsigned char bool;

struct taskTable
{
  ubyte TaskPriority;
  bool TaskReadyFlag;
  void (*TaskAddress)(void);
  ubyte TaskID;
};
typedef struct taskTable TaskTableType;

TaskTableType TaskTableInstance[3];
static ubyte taskcounter;
static ubyte taskprio[3];
static ubyte highestprio;
ubyte indexprio;

ubyte taskid_1=10;
ubyte taskid_2=20;
ubyte taskid_3=30;

void createTask( void (*p32i_taskaddress)(void), ubyte u8i_priority, ubyte u8i_taskID)
{
  // initialize a tasktable with arguments
  TaskTableInstance[taskcounter].TaskPriority= u8i_priority;
  TaskTableInstance[taskcounter].TaskAddress= p32i_taskaddress;
  TaskTableInstance[taskcounter].TaskID= u8i_taskID;
  TaskTableInstance[taskcounter].TaskReadyFlag = 1;
  //increment taskcounter
  taskcounter++;
  printf("taskcounter %d \n", taskcounter);
}

void scheduleTasks()
{
  highestprio = 50;
  ubyte i;
  for(i=0; i<taskcounter;i++)
  {
    if((TaskTableInstance[i].TaskPriority <= highestprio) &&
       (TaskTableInstance[i].TaskReadyFlag==1)
      )
	{
	  highestprio = TaskTableInstance[i].TaskPriority;
	  indexprio = i;
	}
  }
  TaskTableInstance[indexprio].TaskAddress();
}

int startKernel()
{
  // run the ready task with highest pirority
  scheduleTasks();
}

void waitTask()
{
  // desable ready flag
  TaskTableInstance[indexprio].TaskReadyFlag=0;
  /*ubyte i;
  for(i=0;i<taskcounter;i++)
  {
    if(TaskTableInstance[i].TaskID == taskid)
    	TaskTableInstance[indexprio].TaskReadyFlag=1;
  }*/
  // calls scheduler
  scheduleTasks();
}

void startTask(ubyte taskid)
{
  // activate task
  ubyte i;
  for(i=0;i<taskcounter;i++)
  {
    if(TaskTableInstance[i].TaskID == taskid)
    	TaskTableInstance[i].TaskReadyFlag=1;
  } 

  // call scheduler
  scheduleTasks();
}

void task1()
{
  while(1)
  {
    printf("I am task1 \n");
    // wait
    //sleep(1000);
    int i;
    for(i=0;i<19000;i++)
    {} 
    //stop the task
    waitTask();
  }
}

void task2()
{
  while(1)
  {
    printf("I am task2 \n");
    //wait
    //sleep(1000);
    int i;
    for(i=0;i<25000;i++)
    {} 
    //stop the task
    waitTask();
  }
}

void task3()
{
  while(1)
  {
    printf("I am task3 \n");
    //wait
    //sleep(1000);
    int i;
    for(i=0;i<25000;i++)
    {} 
    //stop the task
    //waitTask();
    startTask(taskid_1);
  }
}

int main(void)
{
  //printf("please enter the `service ID`: for example Read_service\n");
  //scanf("%s\n",&s_userinput);
  //printf("selected service ID is: %s \n", &s_userinput);

  // create task
  printf("create task\n");
  // create table for task1 
  createTask(task1, 1, taskid_1);
  // create table for task2
  createTask(task2, 2, taskid_1); 
  // create table for task2
  createTask(task3, 3, taskid_1);

  //start operating system
  startKernel();

  return 0;
 }

 // this ISR enables the task ready flags
 void startTaskInterrupt(ubyte task_ID)
 {
  //scanf("%d\n",&i);
  
  // enable corresponding taskreadyflag
  //if(task_ID == taskid_1) 
  // TaskTableInstance[1].TaskReadyFlag=1;
  //if(task_ID == taskid_2) 
  // TaskTableInstance[2].TaskReadyFlag=1;
  //if(task_ID == taskid_3) 
  // TaskTableInstance3].TaskReadyFlag=1;
 }


