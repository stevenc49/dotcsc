/*
  GATE SERVER PROGRAM
  - gets a tag number from the gate/handheld device
    and sends back a notification of whether the book has been checked out or not
*/

#include <windows.h>
#include <iostream>
#include <string>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "mysql.h"

#define PACKET_LENGTH   4
#define RESET_TIME      1000
#define OK              "O"
#define THELF           "T"

using namespace std;

BOOL SetCommDefaults(HANDLE hSerial);

int main()
{
    //mysql initialization
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    char query[80];
    mysql_init(&mysql);
    mysql_real_connect(&mysql,"localhost","root","","librarydb",0,NULL,0);
    
    //open serial
    HANDLE hSerial = CreateFile("COM4",
        GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED |
        FILE_FLAG_NO_BUFFERING,NULL);
    if (hSerial == INVALID_HANDLE_VALUE) return GetLastError();
    SetCommDefaults(hSerial);

    HANDLE hReadEvent = CreateEvent(NULL,TRUE,FALSE,"RxEvent");
    OVERLAPPED ovRead;
    OVERLAPPED ovWrite;
    memset(&ovRead,0,sizeof(ovRead));
    memset(&ovWrite,0,sizeof(ovWrite));

    ovRead.hEvent = hReadEvent;

    char szRxChar = 0;
    DWORD dwBytesRead = 0;
    DWORD dwBytesWritten = 0;
    
    char tagBuffer[8]; //holds the tag id
    int i=0; //index for tagBuffer
    char buf[50];
    
    //keep polling as long as stop character '-' is not read
    while(szRxChar != '-')
    {
        // Check if a read is outstanding
        if (HasOverlappedIoCompleted(&ovRead))
        {
            // Issue a serial port read
            if (!ReadFile(hSerial,&szRxChar,1,
                    &dwBytesRead,&ovRead))
            {
                DWORD dwErr = GetLastError();
                if (dwErr!=ERROR_IO_PENDING)
                    return dwErr;
            }
        }

        // Wait 5 seconds for serial input
        if (!(HasOverlappedIoCompleted(&ovRead)))
        {
            WaitForSingleObject(hReadEvent,RESET_TIME);
        }
        
        // if timeout, reset tagBuffer in case tagBuffer index is out of sync
        if (!HasOverlappedIoCompleted(&ovRead))
        {
           i=0;
        }

        // Check if serial input has arrived
        if (GetOverlappedResult(hSerial,&ovRead,
                &dwBytesRead,FALSE))
        {
            // Wait for the write
            GetOverlappedResult(hSerial,&ovWrite,
                &dwBytesWritten,TRUE);
                
            //load tagBuffer with byte stream
            tagBuffer[i] = szRxChar;
            i++;
            tagBuffer[i] = 0; //char arrays are \0 terminated
            
            //run query with tagBuffer  
            sprintf(query,"select status "
                                  "from books "
                                  "where booktagnum=\"");
            strcat(query, tagBuffer);
            strcat(query, "\"");
            mysql_real_query(&mysql,query,(unsigned int)strlen(query));
            
            //process result and send back to handheld
            res = mysql_use_result(&mysql);
            while(row = mysql_fetch_row(res))
            {
               printf("result of query is %s\n",row[0]);
               
               string str = "";
               str = string(row[0]);
               
               if( str == "Checked In" )
               {
                   WriteFile(hSerial,THELF,strlen(THELF),
                    &dwBytesWritten,&ovWrite);
               }
               else if ( str == "Checked Out" )
               {
                   WriteFile(hSerial,OK,strlen(OK),
                    &dwBytesWritten,&ovWrite);
               }
            }
            
            if( strlen(tagBuffer) >= PACKET_LENGTH )
            {
                i = 0;
            }
            mysql_free_result(res);
            
            // Display a response to input
            //printf("query is %s!\n", query);
            //printf("strlen(tagBuffer) is %d!\n", strlen(tagBuffer));

            
            printf("tagBuffer is %s!\n", tagBuffer);
            printf("buf is %s!\n", buf);

        }
    }

    CloseHandle(hSerial);
    CloseHandle(hReadEvent);

    system("pause");
    return 0;
} 
    

BOOL SetCommDefaults(HANDLE hSerial)
{
    DCB dcb;
    memset(&dcb,0,sizeof(dcb));
    dcb.DCBlength=sizeof(dcb);
    if (!GetCommState(hSerial,&dcb))
        return FALSE;
    dcb.BaudRate=9600;
    dcb.ByteSize=8;
    dcb.Parity=0;
    dcb.StopBits=ONESTOPBIT;
    if (!SetCommState(hSerial,&dcb))
        return FALSE;
    return TRUE;
}
