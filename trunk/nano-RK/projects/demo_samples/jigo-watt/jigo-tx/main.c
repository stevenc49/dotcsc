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
*******************************************************************************/

#include <nrk.h>
#include <include.h>
#include <ulib.h>
#include <stdio.h>
#include <avr/sleep.h>
#include <hal.h>
#include <bmac.h>
#include <nrk_error.h>
#include <nrk_timer.h>
#include <power_driver.h>

// Only require MAC address for address decode 
#define MAC_ADDR	0x0001


nrk_task_type RX_TASK;
NRK_STK rx_task_stack[NRK_APP_STACKSIZE];
void rx_task (void);


nrk_task_type TX_TASK;
NRK_STK tx_task_stack[NRK_APP_STACKSIZE];
void tx_task (void);

void nrk_create_taskset ();

uint8_t tx_buf[RF_MAX_PAYLOAD_SIZE];
uint8_t rx_buf[RF_MAX_PAYLOAD_SIZE];
uint8_t aes_key[16] =
  { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b,
0x0c, 0x0d, 0x0e, 0x0f };

int main ()
{
  uint16_t div;
  nrk_setup_ports ();
  nrk_setup_uart (UART_BAUDRATE_115K2);

  nrk_init ();

  nrk_led_clr (0);
  nrk_led_clr (1);
  nrk_led_clr (2);
  nrk_led_clr (3);

  nrk_time_set (0, 0);

  bmac_task_config ();

  nrk_create_taskset ();
  nrk_start ();

  return 0;
}

void rx_task ()
{
  uint8_t i, len;
  int8_t rssi, val;
  uint8_t *local_rx_buf;
  nrk_time_t check_period;
  printf ("rx_task PID=%d\r\n", nrk_get_pid ());

  // init bmac on channel 25 
  bmac_init (15);

  // Enable AES 128 bit encryption
  // When encryption is active, messages from plaintext
  // source will still be received. 
  bmac_encryption_set_key (aes_key, 16);
  bmac_encryption_enable ();
  // bmac_encryption_disable();

  // By default the RX check rate is 100ms
  // below shows how to change that
  //check_period.secs=0;
  //check_period.nano_secs=200*NANOS_PER_MS;
  //val=bmac_set_rx_check_rate(check_period);

  // The default Clear Channel Assement RSSI threshold is -45
  // Setting this value higher means that you will only trigger
  // receive with a very strong signal.  Setting this lower means
  // bmac will try to receive fainter packets.  If the value is set
  // too high or too low performance will suffer greatly.
   bmac_set_cca_thresh(-35); 


  //if(val==NRK_ERROR) nrk_kprintf( PSTR("ERROR setting bmac rate\r\n" ));
  // This sets the next RX buffer.
  // This can be called at anytime before releaseing the packet
  // if you wish to do a zero-copy buffer switch
  bmac_rx_pkt_set_buffer (rx_buf, RF_MAX_PAYLOAD_SIZE);

  while (1) {
    // Wait until an RX packet is received
    val = bmac_wait_until_rx_pkt ();
    // Get the RX packet 
    nrk_led_set (ORANGE_LED);
/*    local_rx_buf = bmac_rx_pkt_get (&len, &rssi);
    if( bmac_rx_pkt_is_encrypted()==1 ) nrk_kprintf( PSTR( "Packet Encrypted\r\n" ));
    printf ("Got RX packet len=%d RSSI=%d [", len, rssi);
    for (i = 0; i < len; i++)
      printf ("%c", rx_buf[i]);
    printf ("]\r\n");*/
    // Release the RX buffer so future packets can arrive 
    bmac_rx_pkt_release ();
    nrk_led_clr (ORANGE_LED);
  }

}

uint8_t ctr_cnt[4];

void tx_task ()
{
  uint8_t j, i, val, len, cnt;
  int8_t v;
  nrk_sig_t tx_done_signal;
  nrk_sig_mask_t ret;
  nrk_time_t r_period;

  //power_socket_disable(0);
  //power_socket_disable(1);
  printf ("tx_task PID=%d\r\n", nrk_get_pid ());

  // Wait until the tx_task starts up bmac
  // This should be called by all tasks using bmac that
  // do not call bmac_init()...
  while (!bmac_started ())
    nrk_wait_until_next_period ();

  nrk_wait_until_next_period ();
  power_init ();
/*
  for (i = 0; i < 3; i++) {
    power_socket_enable (0);
    power_socket_enable (1);
    nrk_wait_until_next_period ();
    power_socket_disable (0);
    power_socket_disable (1);
    nrk_wait_until_next_period ();
  }
*/
  power_socket_enable (0);
  power_socket_enable (1);

  //nrk_kprintf( PSTR("after outlet on\r\n"));

  // Sample of using Reservations on TX packets
  // This example allows 2 packets to be sent every 5 seconds
  // r_period.secs=5;
  // r_period.nano_secs=0;
  // v=bmac_tx_reserve_set( &r_period, 2 );
  // if(v==NRK_ERROR) nrk_kprintf( PSTR("Error setting b-mac tx reservation (is NRK_MAX_RESERVES defined?)\r\n" ));


  // Get and register the tx_done_signal if you want to
  // do non-blocking transmits
  tx_done_signal = bmac_get_tx_done_signal ();
  nrk_signal_register (tx_done_signal);

  ctr_cnt[0] = 0;
  ctr_cnt[1] = 0;
  ctr_cnt[2] = 0;
  ctr_cnt[3] = 0;
  cnt = 0;
  while (1) {
    // Build a TX packet
    //sprintf (tx_buf, "This is a test %d", cnt);
    //nrk_led_set (BLUE_LED);

    // Auto ACK is an energy efficient link layer ACK on packets
    // If Auto ACK is enabled, then bmac_tx_pkt() will return failure
    // if no ACK was received. In a broadcast domain, the ACK's will
    // typically collide.  To avoid this, one can use address decoding. 
    // The functions are as follows:
    // bmac_auto_ack_enable();
    // bmac_auto_ack_disable();

    // Address decoding is a way of preventing the radio from receiving
    // packets that are not address to a particular node.  This will 
    // supress ACK packets from nodes that should not automatically ACK.
    // The functions are as follows:
    // bmac_addr_decode_set_my_mac(uint16_t MAC_ADDR); 
    // bmac_addr_decode_dest_mac(uint16_t DST_ADDR);  // 0xFFFF is broadcast
    // bmac_addr_decode_enable();
    // bmac_addr_decode_disable();

    ctr_cnt[0] = cnt;
    if (ctr_cnt[0] == 255)
      ctr_cnt[1]++;
    if (ctr_cnt[1] == 255)
      ctr_cnt[2]++;
    if (ctr_cnt[2] == 255)
      ctr_cnt[3]++;
    // You need to increase the ctr on each packet to make the 
    // stream cipher not repeat.
    bmac_encryption_set_ctr_counter (&ctr_cnt, 4);

    // For blocking transmits, use the following function call.
    // For this there is no need to register  
    tx_buf[0] = (rms_current >> 8) & 0xff;
    tx_buf[1] = rms_current & 0xff;
    tx_buf[2] = (rms_voltage >> 8) & 0xff;
    tx_buf[3] = rms_voltage & 0xff;
    tx_buf[4] = freq & 0xff;
    tx_buf[5] = (true_power >> 16) & 0xff;
    tx_buf[6] = (true_power >> 8) & 0xff;
    tx_buf[7] = (true_power) & 0xff;
    tx_buf[8] = (tmp_energy >> 24) & 0xff;
    tx_buf[9] = (tmp_energy >> 16) & 0xff;
    tx_buf[10] = (tmp_energy >> 8) & 0xff;
    tx_buf[11] = (tmp_energy) & 0xff;
    tx_buf[12] = (l_v_p2p_high >> 8) & 0xff;
    tx_buf[13] = (l_v_p2p_high) & 0xff;
    tx_buf[14] = (l_v_p2p_low >> 8) & 0xff;
    tx_buf[15] = (l_v_p2p_low) & 0xff;
    tx_buf[16] = (l_c_p2p_high >> 8) & 0xff;
    tx_buf[17] = (l_c_p2p_high) & 0xff;
    tx_buf[18] = (l_c_p2p_low >> 8) & 0xff;
    tx_buf[19] = (l_c_p2p_low) & 0xff;
    tx_buf[20] = (total_secs >> 24) & 0xff;
    tx_buf[21] = (total_secs >> 16) & 0xff;
    tx_buf[22] = (total_secs >> 8) & 0xff;
    tx_buf[23] = (total_secs) & 0xff;

    //nrk_kprintf( PSTR("about to send\n") );
    val = bmac_tx_pkt (tx_buf, 24);
    if (val == NRK_OK)
      cnt++;
    else
      nrk_kprintf (PSTR ("NO ack or Reserve Violated!\r\n"));


    // This function shows how to transmit packets in a
    // non-blocking manner  
    // val = bmac_tx_pkt_nonblocking(tx_buf, strlen (tx_buf));
    // nrk_kprintf (PSTR ("Tx packet enqueued\r\n"));
    // This functions waits on the tx_done_signal
    // ret = nrk_event_wait (SIG(tx_done_signal));

    // Just check to be sure signal is okay
    // if(ret & SIG(tx_done_signal) == 0 ) 
    // nrk_kprintf (PSTR ("TX done signal error\r\n"));

    // If you want to see your remaining reservation
    // printf( "reserve=%d ",bmac_tx_reserve_get() );

    // Task gets control again after TX complete
    //nrk_kprintf (PSTR ("Tx task sent data!\r\n"));
    //nrk_led_clr (BLUE_LED);
    nrk_wait_until_next_period ();
  }

}

void nrk_create_taskset ()
{


  RX_TASK.task = rx_task;
  nrk_task_set_stk (&RX_TASK, rx_task_stack, NRK_APP_STACKSIZE);
  RX_TASK.prio = 2;
  RX_TASK.FirstActivation = TRUE;
  RX_TASK.Type = BASIC_TASK;
  RX_TASK.SchType = PREEMPTIVE;
  RX_TASK.period.secs = 1;
  RX_TASK.period.nano_secs = 0;
  RX_TASK.cpu_reserve.secs = 0;
  RX_TASK.cpu_reserve.nano_secs = 0;
  RX_TASK.offset.secs = 0;
  RX_TASK.offset.nano_secs = 0;
  nrk_activate_task (&RX_TASK);

  TX_TASK.task = tx_task;
  nrk_task_set_stk (&TX_TASK, tx_task_stack, NRK_APP_STACKSIZE);
  TX_TASK.prio = 2;
  TX_TASK.FirstActivation = TRUE;
  TX_TASK.Type = BASIC_TASK;
  TX_TASK.SchType = PREEMPTIVE;
  TX_TASK.period.secs = 1;
  TX_TASK.period.nano_secs = 0;
  TX_TASK.cpu_reserve.secs = 0;
  TX_TASK.cpu_reserve.nano_secs = 0;
  TX_TASK.offset.secs = 0;
  TX_TASK.offset.nano_secs = 0;
  nrk_activate_task (&TX_TASK);

}
