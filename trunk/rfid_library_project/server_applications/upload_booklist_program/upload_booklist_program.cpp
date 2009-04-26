/*
  transfer list to handheld program
*/

#include <windows.h>
#include <iostream>
#include <string>
#include <time.h>
#include "mysql.h"

using namespace std;

BOOL SetCommDefaults(HANDLE hSerial);

int main()
{
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
    
    /////////////query part
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query[260];

    mysql_init(&mysql);

    mysql_real_connect(&mysql,"localhost","root","","librarydb",0,NULL,0);
    
    sprintf(query,"SELECT DISTINCT books.bookTagNum , shelf.shelfTagNum, books.shelfNum, books.abbreviatedTitle  "
                          "FROM books, shelf, list "
                          "WHERE books.shelfNum = shelf.shelfNum "
                          "AND books.bookId = list.bookId "
                          "ORDER BY shelf.shelfTagNum ASC");

    mysql_real_query(&mysql,query,(unsigned int)strlen(query));
    res = mysql_use_result(&mysql);
    
    int numFields = mysql_num_fields(res); //get number of columns
    int counter = 0;


    while(row = mysql_fetch_row(res))
    {           
        for(int i=0; i<numFields; i++)
        {         
            WriteFile(hSerial,row[i],strlen(row[i]),
            &dwBytesWritten,&ovWrite);
            
            cout<<row[i]<<endl;
            
            //if title is less than 16 characters, fill in with space
            //microcontroller is expecting 16 bits for title
            if(i==3)
            {
                int length = strlen(row[i]);
                int fill=0;

                fill = 16-length;
                
                for(int j=0;j<fill;j++)
                {
                    WriteFile(hSerial," ",strlen(" "),
                    &dwBytesWritten,&ovWrite);
                }
            }
        }
    }
    mysql_free_result(res);

    
    //need this here to know when to exit
    while(szRxChar != 'q')
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
