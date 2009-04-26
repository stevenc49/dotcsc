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
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

#include "mysql.h"
#include "errmsg.h"
#include "mysqld_error.h"

#define PACKET_LENGTH   4
#define RESET_TIME      1000
#define OK              "O"
#define THELF           "T"
#define NOK             "N"
#define MAX_QUERY_LENGTH 102

using namespace std;

BOOL SetCommDefaults(HANDLE hSerial);

int main()
{
    //mysql initialization
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;

    MYSQL select_mysql;
    MYSQL_RES *select_res;
    MYSQL_ROW select_row;
    
    char query[200];
    mysql_init(&mysql);
    mysql_real_connect(&mysql,"localhost","root","","librarydb",0,NULL,CLIENT_MULTI_STATEMENTS);
    
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
    
    char tagBuffer[4]; //holds the tag id
    int i=0; //index for tagBuffer
    char buf[50];
    int errno;
    bool firstPass = true;
    bool rdy2getShelf = true;
    char shelf[4];
    set<string> actual;
    set<string> expected;
    set<string> misplaced;
    bool runQueryStage = false;
    set<string>::iterator it;
    set<string>::iterator it2;
    set<string>::iterator it3;
    pair<set<string>::iterator,bool> ret;
    char iter2str[4];

    
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
           firstPass=true;
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

            //if this is the first tag
            if (firstPass)
            {
               //get shelf number and store in variable "shelf"
               strcpy(shelf, tagBuffer);
               
               if( strlen(tagBuffer)==PACKET_LENGTH )
               {
                   firstPass=false;
               }
            }
            
            //put the rest of tagBuffer into vector "actual"
            if( strlen(tagBuffer)==PACKET_LENGTH)
            {
                if( strcmp(tagBuffer,shelf) != 0 )
                {
                    actual.insert( tagBuffer );
                }
            }

            //get list of books that's expected to be on the shelf and store results in "expected" vectorc
            //TODO: need to exclude "cheched out" books
            sprintf(query,"select booktagnum "
                                  "from books, shelf "
                                  "where shelf.shelfTagNum='");
            strcat(query, shelf);
            strcat(query,"' and books.shelfNum = shelf.shelfNum");
                
            int select_errno = mysql_real_query(&mysql,query,(unsigned int)strlen(query));
            //cout<<"select..."<<select_errno<<endl;
            res = mysql_use_result(&mysql);
            int numFields = mysql_num_fields(res);
            //cout<<"numFields: "<<numFields<<endl;
    
            while(row = mysql_fetch_row(res))
            {   
                expected.insert(row[0]);
            }
            mysql_free_result(res);

            //find misplaced books and place in misplaced set
            for (it=actual.begin(); it!=actual.end(); it++)
            {
                it2=expected.find(*it); //find current book in expected set
                
                if( it2==expected.end() ) //if not found in expected set
                {
                    misplaced.insert(*it);
                }
            }

            if( misplaced.size() != 0 )
            {
                
                for (it=misplaced.begin(); it!=misplaced.end(); it++)
                {
                    cout << " " << *it;
                    strcpy(iter2str, (*it).c_str());
                }
                  cout << endl;
                
                //cout<<"iter2str: "<<iter2str<<endl;
                
                sprintf(query,"insert into misplaced (bookTagNum,foundAtShelf,lastScanned) values ('%s', '%s', NOW())", iter2str, shelf);
                    
                int insert_errno = mysql_real_query(&mysql,query,(unsigned int)strlen(query));
                //cout<<"insert..."<<insert_errno<<endl;

            }
            
            //reset tagBuffer index to receive next tag number
            if( strlen(tagBuffer) >= PACKET_LENGTH )
            {
                i = 0;
            }
            
            expected.clear();
            actual.clear();
            misplaced.clear();
        }
    }

    cout<<endl<<"shelf:"<<endl;
    cout<<shelf<<endl<<endl;

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
