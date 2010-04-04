/******************************************************************************
*  Nano-RK, a real-time operating system for sensor networks.
*  Copyright (C) 2007, Real-Time and Multimedia Lab, Carnegie Mellon University
*  All rights reserved.
*
*  This is the Open Source Version of Nano-RK included as part of a Dual
*  Licensing Model. If you are unsure which license to use please refer to:
*  http://www.nanork.org/nano-RK/wiki/Licensing
*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, version 2.0 of the License.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*  Contributing Authors (specific to this file):
*  Zane Starr
*******************************************************************************/


#include <nrk.h>
#include <include.h>
#include <ulib.h>
#include <stdio.h>
#include <avr/sleep.h>
#include <hal.h>
#include <nrk_error.h>
#include <nrk_events.h>
#include <nrk_timer.h>

void my_nano_sleep(uint32_t nanos)
{
	uint32_t micros;
	uint16_t full_waits;
	uint16_t remaining_waits;
	uint16_t i;
	
	micros = nanos / 1000;
	full_waits = micros / 65535;
	remaining_waits = micros % 65535;
	
	printf("Sleep start (%lu nanos)\r\n", nanos);
	
	for(i = 0; i < full_waits; ++i)
	{
		nrk_spin_wait_us(65535);
	}
	if(remaining_waits)
	{
		nrk_spin_wait_us(remaining_waits);
	}
	
	printf("Sleep end\r\n");
}


NRK_STK Stack1[NRK_APP_STACKSIZE];
nrk_task_type TaskOne;
void Task1(void);


NRK_STK Stack2[NRK_APP_STACKSIZE];
nrk_task_type TaskTwo;
void Task2 (void);
/*
NRK_STK Stack3[NRK_APP_STACKSIZE];
nrk_task_type TaskThree;
void Task3 (void);

NRK_STK Stack4[NRK_APP_STACKSIZE];
nrk_task_type TaskFour;
void Task4 (void);

NRK_STK Stack5[NRK_APP_STACKSIZE];
nrk_task_type TaskFive;
void Task5 (void);

NRK_STK Stack6[NRK_APP_STACKSIZE];
nrk_task_type TaskSix;
void Task6 (void);

NRK_STK Stack7[NRK_APP_STACKSIZE];
nrk_task_type TaskSeven;
void Task7 (void);

NRK_STK Stack8[NRK_APP_STACKSIZE];
nrk_task_type TaskEight;
void Task8 (void);

NRK_STK Stack9[NRK_APP_STACKSIZE];
nrk_task_type TaskNine;
void Task9 (void);

NRK_STK Stack10[NRK_APP_STACKSIZE];
nrk_task_type TaskTen;
void Task10 (void);

NRK_STK Stack11[NRK_APP_STACKSIZE];
nrk_task_type TaskEleven;
void Task11 (void);

NRK_STK Stack12[NRK_APP_STACKSIZE];
nrk_task_type TaskTwelve;
void Task12 (void);

NRK_STK Stack13[NRK_APP_STACKSIZE];
nrk_task_type TaskThirteen;
void Task13 (void);

NRK_STK Stack14[NRK_APP_STACKSIZE];
nrk_task_type TaskFourteen;
void Task14 (void);

NRK_STK Stack15[NRK_APP_STACKSIZE];
nrk_task_type TaskFifteen;
void Task15 (void);

NRK_STK Stack16[NRK_APP_STACKSIZE];
nrk_task_type TaskSixteen;
void Task16 (void);
 */

void nrk_create_taskset();

int
main ()
{
  nrk_setup_ports();
  nrk_setup_uart(UART_BAUDRATE_115K2);

  printf( "Starting up...\r\n" );
  nrk_init();
  nrk_time_set(0,0);
  nrk_create_taskset ();
  nrk_start();
  
  return 0;
}


void Task1()
{
uint16_t cnt;
//printf( "My node's address is %d\r\n",NODE_ADDR );
  printf( "Task1 PID=%d\r\n",nrk_get_pid());
  cnt=0;
  while(1) {
	printf( "Task1 cnt=%d\r\n",cnt );
	
	my_nano_sleep(150*NANOS_PER_MS);
	
	  nrk_wait_until_next_period(); //TODO:might need to change this to another wait_until... function to accomodate CBS
	cnt++;
	}
}

void Task2()
{
uint16_t cnt;
//printf( "My node's address is %d\r\n",NODE_ADDR );
  printf( "Task2 PID=%d\r\n",nrk_get_pid());
  cnt=0;
  while(1) {
	  printf( "Task2 cnt=%d\r\n",cnt );
	  my_nano_sleep(10*NANOS_PER_MS);
	nrk_wait_until_next_period(); //TODO:might need to change this to another wait_until... function to accomodate CBS
	cnt++;
	}
}

void Task3()
{
uint16_t cnt;
//printf( "My node's address is %d\r\n",NODE_ADDR );
  printf( "Task3 PID=%d\r\n",nrk_get_pid());
  cnt=0;
  while(1) {
	  printf( "Task3 cnt=%d\r\n",cnt );
	  my_nano_sleep(10*NANOS_PER_MS);
	nrk_wait_until_next_period(); //TODO:might need to change this to another wait_until... function to accomodate CBS
	cnt++;
	}
}

void Task4()
{
uint16_t cnt;
//printf( "My node's address is %d\r\n",NODE_ADDR );
  printf( "Task4 PID=%d\r\n",nrk_get_pid());
  cnt=0;
  while(1) {
	  printf( "Task4 cnt=%d\r\n",cnt );
	  my_nano_sleep(10*NANOS_PER_MS);
	nrk_wait_until_next_period(); //TODO:might need to change this to another wait_until... function to accomodate CBS
	cnt++;
	}
}

void Task5()
{
uint16_t cnt;
//printf( "My node's address is %d\r\n",NODE_ADDR );
  printf( "Task5 PID=%d\r\n",nrk_get_pid());
  cnt=0;
  while(1) {
	  printf( "Task5 cnt=%d\r\n",cnt );
	  my_nano_sleep(10*NANOS_PER_MS);
	nrk_wait_until_next_period(); //TODO:might need to change this to another wait_until... function to accomodate CBS
	cnt++;
	}
}

void Task6()
{
uint16_t cnt;
//printf( "My node's address is %d\r\n",NODE_ADDR );
  printf( "Task6 PID=%d\r\n",nrk_get_pid());
  cnt=0;
  while(1) {
	  printf( "Task6 cnt=%d\r\n",cnt );
	  my_nano_sleep(10*NANOS_PER_MS);
	nrk_wait_until_next_period(); //TODO:might need to change this to another wait_until... function to accomodate CBS
	cnt++;
	}
}

void Task7()
{
uint16_t cnt;
//printf( "My node's address is %d\r\n",NODE_ADDR );
  printf( "Task7 PID=%d\r\n",nrk_get_pid());
  cnt=0;
  while(1) {
	  printf( "Task7 cnt=%d\r\n",cnt );
	  my_nano_sleep(10*NANOS_PER_MS);
	nrk_wait_until_next_period(); //TODO:might need to change this to another wait_until... function to accomodate CBS
	cnt++;
	}
}

void Task8()
{
uint16_t cnt;
//printf( "My node's address is %d\r\n",NODE_ADDR );
  printf( "Task8 PID=%d\r\n",nrk_get_pid());
  cnt=0;
  while(1) {
	  printf( "Task8 cnt=%d\r\n",cnt );
	  my_nano_sleep(10*NANOS_PER_MS);
	nrk_wait_until_next_period(); //TODO:might need to change this to another wait_until... function to accomodate CBS
	cnt++;
	}
}

void Task9()
{
uint16_t cnt;
//printf( "My node's address is %d\r\n",NODE_ADDR );
  printf( "Task9 PID=%d\r\n",nrk_get_pid());
  cnt=0;
  while(1) {
	  printf( "Task9 cnt=%d\r\n",cnt );
	  my_nano_sleep(10*NANOS_PER_MS);
	nrk_wait_until_next_period(); //TODO:might need to change this to another wait_until... function to accomodate CBS
	cnt++;
	}
}

void Task10()
{
uint16_t cnt;
//printf( "My node's address is %d\r\n",NODE_ADDR );
  printf( "Task10 PID=%d\r\n",nrk_get_pid());
  cnt=0;
  while(1) {
	  printf( "Task10 cnt=%d\r\n",cnt );
	  my_nano_sleep(10*NANOS_PER_MS);
	nrk_wait_until_next_period(); //TODO:might need to change this to another wait_until... function to accomodate CBS
	cnt++;
	}
}

void Task11()
{
uint16_t cnt;
//printf( "My node's address is %d\r\n",NODE_ADDR );
  printf( "Task11 PID=%d\r\n",nrk_get_pid());
  cnt=0;
  while(1) {
	  printf( "Task11 cnt=%d\r\n",cnt );
	  my_nano_sleep(10*NANOS_PER_MS);
	nrk_wait_until_next_period(); //TODO:might need to change this to another wait_until... function to accomodate CBS
	cnt++;
	}
}


void Task12()
{
uint16_t cnt;
//printf( "My node's address is %d\r\n",NODE_ADDR );
  printf( "Task12 PID=%d\r\n",nrk_get_pid());
  cnt=0;
  while(1) {
	printf( "Task12 cnt=%d\r\n",cnt );
	_nrk_timer_tick(); //check time of scheduler
	nrk_wait_until_next_period(); //TODO:might need to change this to another wait_until... function to accomodate CBS
	cnt++;
	}
}

void Task13()
{
uint16_t cnt;
//printf( "My node's address is %d\r\n",NODE_ADDR );
  printf( "Task13 PID=%d\r\n",nrk_get_pid());
  cnt=0;
  while(1) {
	  printf( "Task13 cnt=%d\r\n",cnt );
	  my_nano_sleep(10*NANOS_PER_MS);
	nrk_wait_until_next_period(); //TODO:might need to change this to another wait_until... function to accomodate CBS
	cnt++;
	}
}

void Task14()
{
uint16_t cnt;
//printf( "My node's address is %d\r\n",NODE_ADDR );
  printf( "Task14 PID=%d\r\n",nrk_get_pid());
  cnt=0;
  while(1) {
	  printf( "Task14 cnt=%d\r\n",cnt );
	  my_nano_sleep(10*NANOS_PER_MS);
	nrk_wait_until_next_period(); //TODO:might need to change this to another wait_until... function to accomodate CBS
	cnt++;
	}
}

void Task15()
{
uint16_t cnt;
//printf( "My node's address is %d\r\n",NODE_ADDR );
  printf( "Task15 PID=%d\r\n",nrk_get_pid());
  cnt=0;
  while(1) {
	  printf( "Task15 cnt=%d\r\n",cnt );
	  my_nano_sleep(10*NANOS_PER_MS);
	nrk_wait_until_next_period(); //TODO:might need to change this to another wait_until... function to accomodate CBS
	cnt++;
	}
}

void Task16()
{
uint16_t cnt;
//printf( "My node's address is %d\r\n",NODE_ADDR );
  printf( "Task16 PID=%d\r\n",nrk_get_pid());
  cnt=0;
  while(1) {
	  printf( "Task16 cnt=%d\r\n",cnt );
	  my_nano_sleep(10*NANOS_PER_MS);
	nrk_wait_until_next_period(); //TODO:might need to change this to another wait_until... function to accomodate CBS
	cnt++;
	}
}

void
nrk_create_taskset()
{	
	nrk_task_set_entry_function( &TaskOne, Task1);
	nrk_task_set_stk( &TaskOne, Stack1, NRK_APP_STACKSIZE);
	TaskOne.prio = 1;
	TaskOne.FirstActivation = TRUE;
	TaskOne.Type = CBS_TASK;
	TaskOne.SchType = PREEMPTIVE;
	TaskOne.period.secs = 0;
	TaskOne.period.nano_secs = 1000*NANOS_PER_MS;
	TaskOne.cpu_reserve.secs = 0;
	TaskOne.cpu_reserve.nano_secs = 100*NANOS_PER_MS;
	TaskOne.offset.secs = 0;
	TaskOne.offset.nano_secs= 0;
	TaskOne.plvl = 1;
	nrk_activate_task (&TaskOne);
	
	nrk_task_set_entry_function( &TaskTwo, Task2);
	nrk_task_set_stk( &TaskTwo, Stack2, NRK_APP_STACKSIZE);
	TaskTwo.prio = 1;
	TaskTwo.FirstActivation = TRUE;
	TaskTwo.Type = CBS_TASK;
	TaskTwo.SchType = PREEMPTIVE;
	TaskTwo.period.secs = 0;
	TaskTwo.period.nano_secs = 1000*NANOS_PER_MS;
	TaskTwo.cpu_reserve.secs = 0;
	TaskTwo.cpu_reserve.nano_secs = 100*NANOS_PER_MS;
	TaskTwo.offset.secs = 0;
	TaskTwo.offset.nano_secs= 0;
	TaskTwo.plvl = 1;
	nrk_activate_task (&TaskTwo);

	/*
  TaskTwo.task = Task2;
  TaskTwo.Ptos = (void *) &Stack2[NRK_APP_STACKSIZE];
  TaskTwo.Pbos = (void *) &Stack2[0];
  TaskTwo.prio = 15;
  TaskTwo.FirstActivation = TRUE;
  TaskTwo.Type = CBS_TASK;
  TaskTwo.SchType = PREEMPTIVE;
  TaskTwo.period.secs = 20;
  TaskTwo.period.nano_secs = 0;
  TaskTwo.cpu_reserve.secs = 20;
  TaskTwo.cpu_reserve.nano_secs =  0;
  TaskTwo.offset.secs = 0;
  TaskTwo.offset.nano_secs= 0;
  nrk_activate_task (&TaskTwo);

  TaskThree.task = Task3;
  TaskThree.Ptos = (void *) &Stack3[NRK_APP_STACKSIZE];
  TaskThree.Pbos = (void *) &Stack3[0];
  TaskThree.prio = 14;
  TaskThree.FirstActivation = TRUE;
  TaskThree.Type = CBS_TASK;
  TaskThree.SchType = PREEMPTIVE;
  TaskThree.period.secs = 20;
  TaskThree.period.nano_secs = 0;
  TaskThree.cpu_reserve.secs = 20;
  TaskThree.cpu_reserve.nano_secs =  0;
  TaskThree.offset.secs = 0;
  TaskThree.offset.nano_secs= 0;
  nrk_activate_task (&TaskThree);

  TaskFour.task = Task4;
  TaskFour.Ptos = (void *) &Stack4[NRK_APP_STACKSIZE];
  TaskFour.Pbos = (void *) &Stack4[0];
  TaskFour.prio = 13;
  TaskFour.FirstActivation = TRUE;
  TaskFour.Type = CBS_TASK;
  TaskFour.SchType = PREEMPTIVE;
  TaskFour.period.secs = 20;
  TaskFour.period.nano_secs = 0;
  TaskFour.cpu_reserve.secs = 20;
  TaskFour.cpu_reserve.nano_secs =  0;
  TaskFour.offset.secs = 0;
  TaskFour.offset.nano_secs= 0;
  nrk_activate_task (&TaskFour);

  TaskFive.task = Task5;
  TaskFive.Ptos = (void *) &Stack5[NRK_APP_STACKSIZE];
  TaskFive.Pbos = (void *) &Stack5[0];
  TaskFive.prio = 12;
  TaskFive.FirstActivation = TRUE;
  TaskFive.Type = CBS_TASK;
  TaskFive.SchType = PREEMPTIVE;
  TaskFive.period.secs = 5;
  TaskFive.period.nano_secs = 0;
  TaskFive.cpu_reserve.secs = 1;
  TaskFive.cpu_reserve.nano_secs =  0;
  TaskFive.offset.secs = 0;
  TaskFive.offset.nano_secs= 0;
  nrk_activate_task (&TaskFive);

  TaskSix.task = Task6;
  TaskSix.Ptos = (void *) &Stack6[NRK_APP_STACKSIZE];
  TaskSix.Pbos = (void *) &Stack6[0];
  TaskSix.prio = 11;
  TaskSix.FirstActivation = TRUE;
  TaskSix.Type = CBS_TASK;
  TaskSix.SchType = PREEMPTIVE;
  TaskSix.period.secs = 20;
  TaskSix.period.nano_secs = 0;
  TaskSix.cpu_reserve.secs = 20;
  TaskSix.cpu_reserve.nano_secs =  0;
  TaskSix.offset.secs = 0;
  TaskSix.offset.nano_secs= 0;
  nrk_activate_task (&TaskSix);

  TaskSeven.task = Task7;
  TaskSeven.Ptos = (void *) &Stack7[NRK_APP_STACKSIZE];
  TaskSeven.Pbos = (void *) &Stack7[0];
  TaskSeven.prio = 10;
  TaskSeven.FirstActivation = TRUE;
  TaskSeven.Type = CBS_TASK;
  TaskSeven.SchType = PREEMPTIVE;
  TaskSeven.period.secs = 20;
  TaskSeven.period.nano_secs = 0;
  TaskSeven.cpu_reserve.secs = 20;
  TaskSeven.cpu_reserve.nano_secs =  0;
  TaskSeven.offset.secs = 0;
  TaskSeven.offset.nano_secs= 0;
  nrk_activate_task (&TaskSeven);

  TaskEight.task = Task8;
  TaskEight.Ptos = (void *) &Stack8[NRK_APP_STACKSIZE];
  TaskEight.Pbos = (void *) &Stack8[0];
  TaskEight.prio = 9;
  TaskEight.FirstActivation = TRUE;
  TaskEight.Type = CBS_TASK;
  TaskEight.SchType = PREEMPTIVE;
  TaskEight.period.secs = 20;
  TaskEight.period.nano_secs = 0;
  TaskEight.cpu_reserve.secs = 20;
  TaskEight.cpu_reserve.nano_secs =  0;
  TaskEight.offset.secs = 0;
  TaskEight.offset.nano_secs= 0;
  nrk_activate_task (&TaskEight);

  TaskNine.task = Task9;
  TaskNine.Ptos = (void *) &Stack9[NRK_APP_STACKSIZE];
  TaskNine.Pbos = (void *) &Stack9[0];
  TaskNine.prio = 8;
  TaskNine.FirstActivation = TRUE;
  TaskNine.Type = CBS_TASK;
  TaskNine.SchType = PREEMPTIVE;
  TaskNine.period.secs = 20;
  TaskNine.period.nano_secs = 0;
  TaskNine.cpu_reserve.secs = 20;
  TaskNine.cpu_reserve.nano_secs =  0;
  TaskNine.offset.secs = 0;
  TaskNine.offset.nano_secs= 0;
  nrk_activate_task (&TaskNine);

  TaskTen.task = Task10;
  TaskTen.Ptos = (void *) &Stack10[NRK_APP_STACKSIZE];
  TaskTen.Pbos = (void *) &Stack10[0];
  TaskTen.prio = 7;
  TaskTen.FirstActivation = TRUE;
  TaskTen.Type = CBS_TASK;
  TaskTen.SchType = PREEMPTIVE;
  TaskTen.period.secs = 20;
  TaskTen.period.nano_secs = 0;
  TaskTen.cpu_reserve.secs = 20;
  TaskTen.cpu_reserve.nano_secs =  0;
  TaskTen.offset.secs = 0;
  TaskTen.offset.nano_secs= 0;
  nrk_activate_task (&TaskTen);

  TaskEleven.task = Task11;
  TaskEleven.Ptos = (void *) &Stack11[NRK_APP_STACKSIZE];
  TaskEleven.Pbos = (void *) &Stack11[0];
  TaskEleven.prio = 6;
  TaskEleven.FirstActivation = TRUE;
  TaskEleven.Type = CBS_TASK;
  TaskEleven.SchType = PREEMPTIVE;
  TaskEleven.period.secs = 20;
  TaskEleven.period.nano_secs = 0;
  TaskEleven.cpu_reserve.secs = 20;
  TaskEleven.cpu_reserve.nano_secs =  0;
  TaskEleven.offset.secs = 0;
  TaskEleven.offset.nano_secs= 0;
  nrk_activate_task (&TaskEleven);

  TaskTwelve.task = Task12;
  TaskTwelve.Ptos = (void *) &Stack12[NRK_APP_STACKSIZE];
  TaskTwelve.Pbos = (void *) &Stack12[0];
  TaskTwelve.prio = 5;
  TaskTwelve.FirstActivation = TRUE;
  TaskTwelve.Type = CBS_TASK;
  TaskTwelve.SchType = PREEMPTIVE;
  TaskTwelve.period.secs = 20;
  TaskTwelve.period.nano_secs = 0;
  TaskTwelve.cpu_reserve.secs = 20;
  TaskTwelve.cpu_reserve.nano_secs =  0;
  TaskTwelve.offset.secs = 0;
  TaskTwelve.offset.nano_secs= 0;
  nrk_activate_task (&TaskTwelve);

  TaskThirteen.task = Task13;
  TaskThirteen.Ptos = (void *) &Stack13[NRK_APP_STACKSIZE];
  TaskThirteen.Pbos = (void *) &Stack13[0];
  TaskThirteen.prio = 4;
  TaskThirteen.FirstActivation = TRUE;
  TaskThirteen.Type = CBS_TASK;
  TaskThirteen.SchType = PREEMPTIVE;
  TaskThirteen.period.secs = 20;
  TaskThirteen.period.nano_secs = 0;
  TaskThirteen.cpu_reserve.secs = 20;
  TaskThirteen.cpu_reserve.nano_secs =  0;
  TaskThirteen.offset.secs = 0;
  TaskThirteen.offset.nano_secs= 0;
  nrk_activate_task (&TaskThirteen);

  TaskFourteen.task = Task14;
  TaskFourteen.Ptos = (void *) &Stack14[NRK_APP_STACKSIZE];
  TaskFourteen.Pbos = (void *) &Stack14[0];
  TaskFourteen.prio = 3;
  TaskFourteen.FirstActivation = TRUE;
  TaskFourteen.Type = CBS_TASK;
  TaskFourteen.SchType = PREEMPTIVE;
  TaskFourteen.period.secs = 20;
  TaskFourteen.period.nano_secs = 0;
  TaskFourteen.cpu_reserve.secs = 20;
  TaskFourteen.cpu_reserve.nano_secs =  0;
  TaskFourteen.offset.secs = 0;
  TaskFourteen.offset.nano_secs= 0;
  nrk_activate_task (&TaskFourteen);

  TaskFifteen.task = Task15;
  TaskFifteen.Ptos = (void *) &Stack15[NRK_APP_STACKSIZE];
  TaskFifteen.Pbos = (void *) &Stack15[0];
  TaskFifteen.prio = 2;
  TaskFifteen.FirstActivation = TRUE;
  TaskFifteen.Type = CBS_TASK;
  TaskFifteen.SchType = PREEMPTIVE;
  TaskFifteen.period.secs = 20;
  TaskFifteen.period.nano_secs = 0;
  TaskFifteen.cpu_reserve.secs = 20;
  TaskFifteen.cpu_reserve.nano_secs =  0;
  TaskFifteen.offset.secs = 0;
  TaskFifteen.offset.nano_secs= 0;
  nrk_activate_task (&TaskFifteen);

  TaskSixteen.task = Task16;
  TaskSixteen.Ptos = (void *) &Stack16[NRK_APP_STACKSIZE];
  TaskSixteen.Pbos = (void *) &Stack16[0];
  TaskSixteen.prio = 1;
  TaskSixteen.FirstActivation = TRUE;
  TaskSixteen.Type = CBS_TASK;
  TaskSixteen.SchType = PREEMPTIVE;
  TaskSixteen.period.secs = 20;
  TaskSixteen.period.nano_secs = 0;
  TaskSixteen.cpu_reserve.secs = 20;
  TaskSixteen.cpu_reserve.nano_secs =  0;
  TaskSixteen.offset.secs = 0;
  TaskSixteen.offset.nano_secs= 0;
  nrk_activate_task (&TaskSixteen);
	*/
}


