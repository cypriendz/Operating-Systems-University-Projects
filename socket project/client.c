#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(int argc, char **argv){
	int clientFD;
	struct sockaddr_in server;
	char sendBuf[8000];
	char recBuf[8000];

	char* email = argv[1];
	printf(" port is %s\n",argv[2]);
	server.sin_port = htons(atoi(argv[2]));

	printf(" IP is %s\n",argv[3]);
	inet_pton(AF_INET,argv[3],(void*)&(server.sin_addr));	

	server.sin_family = AF_INET;
	
	sprintf(sendBuf,"cs230 HELLO %s\n",email);

	printf("%s\n",sendBuf);
	printf("%s\n", inet_ntoa(server.sin_addr));
	printf("%d\n",ntohs(server.sin_port));
	
			
	if((clientFD = socket(AF_INET,SOCK_STREAM,0)) < 0) {return -1;}
	
	if(connect(clientFD, (struct sockaddr *)&server, sizeof(server)) < 0) {return -2;}

	size_t s = send(clientFD,sendBuf,strlen(sendBuf),0);

//	printf("%ld\n",s);
	while(1){
	size_t n = recv(clientFD,recBuf,sizeof(recBuf),0);
//	printf("%ld\n",n);

//	printf("%s\n",recBuf);
	
	 int i,j,ctr;
	char words[10][10];  
 
    j=0; ctr=0;
    for(i=0;i<=(strlen(recBuf));i++)
    {
        // if space or NULL found, assign NULL into newString[ctr]
        if(recBuf[i]==' '||recBuf[i]=='\0')
        {
            words[ctr][j]='\0';
            ctr++;  //for next word
            j=0;    //for next word, init index to 0
        }
        else
        {
            words[ctr][j]=recBuf[i];
            j++;
        }
    }	
	if(strlen(words[1]) > 10){
		printf("the flag is %s\n",words[1]);
		break;
	} 

	int num1 = atoi(words[2]);
	int num2 = atoi(words[4]);
	int answer;
	char operator[10];
	strcpy(operator,words[3]); 

	printf("num 1 = %d \n", num1);
	printf("num 2 = %d \n",num2);
	printf("operator is %s \n",operator);

	if(strcmp(words[3], "+") == 0){
		answer = num1 + num2;
	}

	if(strcmp(words[3],"-") == 0){
                answer = num1 - num2;
        }
	if(strcmp(words[3],"*") == 0){
                answer = num1 * num2;
        }
	if(strcmp(words[3],"/") == 0){
                answer = num1 / num2;
        }	
	printf(" answer is %d \n", answer);	
	
	char ansBuf[50];
	sprintf(ansBuf,"cs230 %d\n",answer);
	printf(" string form %s\n",ansBuf);
	
	send(clientFD,ansBuf,strlen(ansBuf),0);
}	

	return 0;
}	
