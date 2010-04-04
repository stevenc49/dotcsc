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


NRK_STK Stack1[NRK_APP_STACKSIZE];
nrk_task_type TaskOne;
void Task1(void);

NRK_STK Stack2[NRK_APP_STACKSIZE];
nrk_task_type TaskTwo;
void Task2 (void);

//****
NRK_STK Stack3[NRK_APP_STACKSIZE];
nrk_task_type TaskThree;
void Task3 (void);

//***
NRK_STK Stack4[NRK_APP_STACKSIZE];
nrk_task_type TaskFour;
void Task4 (void);

void nrk_create_taskset();

nrk_sem_t *my_semaphore;
nrk_sem_t *my_semaphore2; //**
nrk_sem_t *my_semaphore3; //***
int
main ()
{
  uint8_t t;
  nrk_setup_ports();
  nrk_setup_uart(UART_BAUDRATE_115K2);

  printf( "Starting up...\r\n" );

  nrk_init();

  nrk_led_clr(ORANGE_LED);
  nrk_led_clr(BLUE_LED);
  nrk_led_set(GREEN_LED);
  nrk_led_clr(RED_LED);
 
  nrk_time_set(0,0);
  nrk_create_taskset ();

  my_semaphore = nrk_sem_create(1,4);
  my_semaphore2 = nrk_sem_create(1,5); //***
  my_semaphore3 = nrk_sem_create(1,1); //***
  if(my_semaphore==NULL) nrk_kprintf( PSTR("Error creating sem\r\n" ));
  if(my_semaphore2==NULL) nrk_kprintf( PSTR("Error creating sem\r\n" ));
  if(my_semaphore3==NULL) nrk_kprintf( PSTR("Error creating sem\r\n" ));

  nrk_start();
  
  return 0;
}


void Task1()
{
uint16_t cnt;
int8_t v;

printf( "My node's address is %d\r\n",NODE_ADDR );

//  printf( "Task1 PID=%d\r\n",nrk_get_pid());
  cnt=0;
  while(1) {
	nrk_led_toggle(ORANGE_LED);
//	printf( "Task1 cnt=%d\r\n",cnt );
	nrk_kprintf( PSTR("Task1 accessing semaphore\r\n"));
	v = nrk_sem_pend(my_semaphore);
	if(v==NRK_ERROR) nrk_kprintf( PSTR("T1 error pend\r\n"));
	nrk_kprintf( PSTR("Task1 holding semaphore\r\n"));
	// wait some time inside semaphore to show the effect
	nrk_wait_until_next_period();
	v = nrk_sem_post(my_semaphore);
	if(v==NRK_ERROR) nrk_kprintf( PSTR("T1 error post\r\n"));
	nrk_kprintf( PSTR("Task1 released semaphore\r\n"));
	nrk_wait_until_next_period();
	cnt++;
	}
}

void Task2()
{
  uint8_t cnt;
  int8_t v;

//  printf( "Task2 PID=%d\r\n",nrk_get_pid());
  cnt=0;
  while(1) {
        nrk_led_toggle(ORANGE_LED);
//        printf( "Task1 cnt=%d\r\n",cnt );
        nrk_kprintf( PSTR("Task2 accessing semaphore\r\n"));
        v = nrk_sem_pend(my_semaphore);
	if(v==NRK_ERROR) nrk_kprintf( PSTR("T2 error pend\r\n"));
        nrk_kprintf( PSTR("Task2 holding semaphore\r\n"));

	nrk_kprintf( PSTR("Task2 accessing semaphore2\r\n"));
	v = nrk_sem_pend(my_semaphore2);
	if(v==NRK_ERROR) nrk_kprintf( PSTR("T2 error pend2\r\n"));
	nrk_kprintf( PSTR("Task2 holding semaphore2\r\n"));

	// wait some time inside semaphore to show the effect
        nrk_wait_until_next_period();
        v = nrk_sem_post(my_semaphore);
	if(v==NRK_ERROR) nrk_kprintf( PSTR("T2 error post\r\n"));
        nrk_kprintf( PSTR("Task2 released semaphore\r\n"));

	v = nrk_sem_post(my_semaphore2);
	if(v==NRK_ERROR) nrk_kprintf( PSTR("T2 error post2\r\n"));
	nrk_kprintf( PSTR("Task2 released semaphore2\r\n"));
        
	nrk_wait_until_next_period();
        cnt++;
        }



}

void Task3()
 {
   uint8_t cnt;
   int8_t v;
 
//   printf( "Task3 PID=%d\r\n",nrk_get_pid());
   cnt=0;
   while(1) {
         nrk_led_toggle(ORANGE_LED);
  //       printf( "Task1 cnt=%d\r\n",cnt );
         nrk_kprintf( PSTR("Task3 accessing semaphore2\r\n"));
         v = nrk_sem_pend(my_semaphore2);
         if(v==NRK_ERROR) nrk_kprintf( PSTR("T3 error pend\r\n"));
         nrk_kprintf( PSTR("Task3 holding semaphore2\r\n"));
         // wait some time inside semaphore to show the effect
         nrk_wait_until_next_period();
         v = nrk_sem_post(my_semaphore2);
         if(v==NRK_ERROR) nrk_kprintf( PSTR("T3 error post\r\n"));
         nrk_kprintf( PSTR("Task3 released semaphore2\r\n"));
         nrk_wait_until_next_period();
         cnt++;
         }
 }


void Task4()
  {
    uint8_t cnt;
    int8_t v;

  //  printf( "Task4 PID=%d\r\n",nrk_get_pid());
    cnt=0;
    while(1) {
          nrk_led_toggle(ORANGE_LED);
//          printf( "Task1 cnt=%d\r\n",cnt );
          nrk_kprintf( PSTR("Task4 accessing semaphore3\r\n"));
          v = nrk_sem_pend(my_semaphore3);
          if(v==NRK_ERROR) nrk_kprintf( PSTR("T4 error pend\r\n"));
          nrk_kprintf( PSTR("Task4 holding semaphore3\r\n"));
          // wait some time inside semaphore to show the effect
          nrk_wait_until_next_period();
          v = nrk_sem_post(my_semaphore3);
          if(v==NRK_ERROR) nrk_kprintf( PSTR("T4 error post\r\n"));
          nrk_kprintf( PSTR("Task4 released semaphore3\r\n"));
          nrk_wait_until_next_period();
          cnt++;
          } 
 }

void
nrk_create_taskset()
{
  TaskOne.task = Task1;
  TaskOne.Ptos = (void *) &Stack1[NRK_APP_STACKSIZE];
  TaskOne.Pbos = (void *) &Stack1[0];
  TaskOne.prio = 3; //1
  TaskOne.FirstActivation = TRUE;
  TaskOne.Type = BASIC_TASK;
  TaskOne.SchType = PREEMPTIVE;
  TaskOne.period.secs = 0;
  TaskOne.period.nano_secs = 300*NANOS_PER_MS; //250
  TaskOne.cpu_reserve.secs = 0;
  TaskOne.cpu_reserve.nano_secs = 0*NANOS_PER_MS; //50
  TaskOne.offset.secs = 0;
  TaskOne.offset.nano_secs= 0;
  TaskOne.plvl = 3; //4
  nrk_activate_task (&TaskOne);

  TaskTwo.task = Task2;
  TaskTwo.Ptos = (void *) &Stack2[NRK_APP_STACKSIZE];
  TaskTwo.Pbos = (void *) &Stack2[0];
  TaskTwo.prio = 4;  //2 //3
  TaskTwo.FirstActivation = TRUE;
  TaskTwo.Type = BASIC_TASK;
  TaskTwo.SchType = PREEMPTIVE;
  TaskTwo.period.secs = 0; //3
  TaskTwo.period.nano_secs = 200*NANOS_PER_MS; //0
  TaskTwo.cpu_reserve.secs = 0;
  TaskTwo.cpu_reserve.nano_secs = 0*NANOS_PER_MS; //100 //nsaoijdas
  TaskTwo.offset.secs = 0;
  TaskTwo.offset.nano_secs= 0;
  TaskTwo.plvl = 4; //3
  nrk_activate_task (&TaskTwo);

  TaskThree.task = Task3;
  TaskThree.Ptos = (void *) &Stack3[NRK_APP_STACKSIZE];
  TaskThree.Pbos = (void *) &Stack3[0];
  TaskThree.prio = 5;  //2 //3
  TaskThree.FirstActivation = TRUE;
  TaskThree.Type = BASIC_TASK;
  TaskThree.SchType = PREEMPTIVE;
  TaskThree.period.secs = 0; //3
  TaskThree.period.nano_secs = 100*NANOS_PER_MS; //0 
  TaskThree.cpu_reserve.secs = 0;
  TaskThree.cpu_reserve.nano_secs = 0*NANOS_PER_MS; //100 //nsaoijdas
  TaskThree.offset.secs = 0;
  TaskThree.offset.nano_secs= 0;
  TaskThree.plvl = 5; //3
  nrk_activate_task (&TaskThree);

  TaskFour.task = Task4;
  TaskFour.Ptos = (void *) &Stack4[NRK_APP_STACKSIZE];
  TaskFour.Pbos = (void *) &Stack4[0];
  TaskFour.prio = 1;  //2 //3
  TaskFour.FirstActivation = TRUE;
  TaskFour.Type = BASIC_TASK;
  TaskFour.SchType = PREEMPTIVE;
  TaskFour.period.secs = 3; //3
  TaskFour.period.nano_secs = 50*NANOS_PER_MS; //0
  TaskFour.cpu_reserve.secs = 0;
  TaskFour.cpu_reserve.nano_secs = 0*NANOS_PER_MS; //100 //nsaoijdas
  TaskFour.offset.secs = 0;
  TaskFour.offset.nano_secs= 0;
  TaskFour.plvl = 1; //3
  nrk_activate_task (&TaskFour);

}



