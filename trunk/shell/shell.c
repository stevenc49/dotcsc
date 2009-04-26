#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/param.h>

struct command_t
{
    char *name;
    int argc;
    char **argv;
};

char* prependPath( char* exeName )
{
      char* path = getenv("PATH");  //get path
      char* pathDeepCopy = (char *)malloc(strlen(path) + 1);    //strtok will destroy PATH so make a deep copy
      char* token[1000]; //token array
      int fileExists;    //checks if the executable's path exists
      int j, i=0;
      int length;
      char* temp;
      
      pathDeepCopy = strdup(path);    //creates the deep copy
      
      //parse and split PATH (ex: PATH=/usr/local/bin:/usr/local/sbin => token[0]="/usr/local/bin", token[2]="/usr/local/sbin")
        token[0] = strtok(pathDeepCopy, ":"); //get pointer to first token found and store in 0 and place it in array
        while(token[i]!= NULL) { //ensure a pointer was found
        i++;
        token[i] = strtok(NULL, ":"); //continue to tokenize the string
        }
        
        for(j = 0; j <= i-1; j++)
        {      
              //the next few lines fixes a problem with tokens (they end in \n\0)
              length = strlen( token[j] );
              temp = malloc( sizeof(char) * length );
              strcpy( temp, "\0");
              strncat( temp, token[j], length );
              token[j] = malloc( sizeof(char)*length + sizeof(char)*strlen(exeName) +1 );
              strcpy( token[j], temp);
              
              //concat onto the end of each path (ex: /usr/local/bin/ls )
              strcat(token[j], "/");
              strcat(token[j], exeName);
              
              //checks if path actually exists (ex: /usr/local/bin/ls exist? )
              fileExists = access(token[j], 4);
              
              //if exist, return the path
              if(fileExists==0)
              {
                 return token[j];
              }
              
              //the following line can be used to help debug
              //printf("token[%d] %s %d\n", j, token[j], fileExists ); //print out all tokens including whether the path exists
              
        }
        
         return "";
}



void runExe(int argc, char **argv, char  *name, char *envp[])    //Run execv function, forks and runs process in child
{
    pid_t pid;
    int i;
    

    pid = fork();
    
	if (pid==0)  //if child
	{

		i=execv(name, argv);     
		if (i<0)
		{
			printf("Command not found.\n");
			
		}
		
	}
	
	else if (pid <0)
	{
		printf("Error forking child");
		
	}
	else
	{
		// usleep(1000);
		wait(NULL);
	
    }
    
    
      
    
   
}


int main(int argc, char *argv[], char *envp[])
{

	int x,i,j,length;
	int commandCount;
	char *c,*token, *temp;
	struct command_t *command;
	int bytesRead,maxBytes;
	char* nothing;
	char currentDir[MAXPATHLEN];
	char* fullPath;
	commandCount=0;
	
    if(argc>1)     //this entire if statement is to allow user to enter a command at startup (ex: a.out which ls)
    {
        
            //built-in commands
			if( strcmp( argv[1],"cd")==0 )
			{
            	if( chdir(argv[1])<0 ) 
                {
            		printf("path not found\n");  
            		   
                }
                  
			}
			
		    else if( strcmp( argv[1],"set")==0 )
			{                                  
                 
                 if ( argv[2] == NULL || argv[3] == NULL )
                 {
                    printf("Usage: set <enviroment variable> <value>\n");
                 }
                 else
                 {
                    char* env = (char *)calloc(strlen(argv[1]) + strlen(argv[2]) + 1, sizeof(char));	//calculate size of env
    
                	strcat(env, argv[1]);
                	strcat(env, "=");	
                	strcat(env, argv[2]);
                	
                    if ( putenv(env)==0 )
                    {
                       printf("ENVIROMENT variable %s successfully set.\n", env);
                       
                    }
                 }
			}
            
			else if ( strcmp( argv[1],"which")==0 )
			{
                 if ( argv[1] == NULL )
                 {
                    printf("Usage: which <filename of executable>\n");
                 }
                 else
                 {
                     fullPath = prependPath( argv[1] );
                     printf("%s\n", fullPath);
                     
                 }
            }
			
			else  //else is non-built-in command
			{			
                fullPath = prependPath( argv[1] );
                
				runExe( argc, argv, fullPath, envp );
				
				    
                
			}
			 commandCount++;   
   }

	x=0;
	i=0;
	j=0;
	maxBytes=100;

    getcwd(currentDir,MAXPATHLEN);
	printf("\n[MY_SHELL ] \n%s>", currentDir);
	while(1) {    //main shell loop
	
		command = malloc(sizeof( struct command_t));
		(*command).argv = malloc(sizeof(char*) * 255);
		c=malloc(sizeof(char) * 100 );   
		
	    fgets(c, maxBytes, stdin);   //reads line and places in to 'c'
	
		if( strcmp(c,"\n") == 0 )   //if just entered
		{
            getcwd(currentDir,MAXPATHLEN);
        	printf("%s>", currentDir);
		}

		else 
			{
			
			for (i = 0 ; i < 255 ; i ++ )  
			{
			(*command).argv[i] = NULL ;
			}
			(*command).argc = 0;


			token = strtok (c," ");
			
			if (token != NULL)   //first token
			{
		
			(*command).argv[0] = malloc(sizeof(char) * strlen(token) );
			strcpy( (*command).argv[0], token) ;
			
			(*command).name = malloc(sizeof(char) * strlen(token) );
			strcpy( (*command).name, token) ; 

			(*command).argc++;

		
			i=0;
			}

			while(token != NULL)   //rest of tokens
			{
			
			token = strtok (NULL, " ");
			
			
		
			if( token != NULL)
				{
				i++;
				
				(*command).argv[i] = malloc(sizeof(char) * strlen(token) );
				strcpy( (*command).argv[i],token);
				(*command).argc++;
				}

			}

			length = strlen( (*command).argv[i] );

			temp = malloc( sizeof(char) * length );   //Have to cut off last character in last command of argv because it is \n and we cant have that 
			strcpy( temp, "\0");    // important, after you cut off \n, re-add \0 to the end

			strncat( temp, (*command).argv[i], length-1 );
			
			free( (*command).argv[i] );
				
			(*command).argv[i] = malloc(sizeof(char)*length);
			strcpy( (*command).argv[i], temp);

			if ( (*command).argc == 1)   //if only 1 command, have to cut off last character of command.name
			{
			free( (*command).name );
			(*command).name = malloc( sizeof(char) * (strlen ( (*command).argv[i] ) ) );
			strcpy( (*command).name , (*command).argv[i] ) ;		

			}

            //built-in commands
			if( strcmp( (*command).argv[0],"cd")==0 )
			{
            	if( chdir((*command).argv[1])<0 )
            	{
            		printf("path not found\n");
            		
                }
                commandCount++;   
                
			}
			
		    else if( strcmp( (*command).argv[0],"set")==0 )
			{                                  
 
                 if ( (*command).argv[1] == NULL || (*command).argv[2] == NULL )
                 {
                    printf("Usage: set <enviroment variable> <value>\n");
                    commandCount++;   
                 }
                 else
                 {
                    char* env = (char *)calloc(strlen((*command).argv[1]) + strlen((*command).argv[2]) + 1, sizeof(char));	//calculate size of env
    
                	strcat(env, (*command).argv[1]);
                	strcat(env, "=");	
                	strcat(env, (*command).argv[2]);
                	
                    if ( putenv(env)==0 )
                       {
                       printf("ENVIROMENT variable %s successfully set.\n", env);
                       commandCount++;   
                       }
                       
                 }
			}
            
			else if ( strcmp( (*command).argv[0],"which")==0 )
			{
                 if ( (*command).argv[1] == NULL )
                 {
                    printf("Usage: which <filename of executable>\n");
                    commandCount++;   
                 }
                 else
                 {
                    fullPath = prependPath( (*command).argv[1] );
                    printf("%s\n", fullPath);
                    commandCount++;   
                   
                 }
            }
            else if (strcmp( (*command).argv[0], "cmdcount") == 0 )
            {
                 printf("Current number of commands entered: %i\n", commandCount);  //prints out # succesful commands so far
            }
			
			else  //else is non-built-in command
			{			
                fullPath = prependPath( (*command).name );
                
				  runExe( (*command).argc, (*command).argv, fullPath, envp );
				 
                     
                  commandCount++;   
			}
			 
			 
            getcwd(currentDir,MAXPATHLEN);
        	printf("%s>", currentDir);


			//memory freeing area
			free( (*command).name);
			(*command).name=NULL;

			for (i = 0 ; i < 255 ; i ++ )   //resets struct command variables
			{
			free( (*command).argv[i] );
			(*command).argv[i] = NULL ;
			}
			(*command).argc = 0;

			free(token);
			token=NULL;

			free(c);
			c=NULL;

			free(temp);	
			
			temp=NULL;

			i=0;
			free(command);
			
		}
	}

	//free(command);
	printf("\n");
	return 0;
}




