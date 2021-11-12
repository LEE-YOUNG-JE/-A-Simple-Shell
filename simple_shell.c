/**
* Simple shell interface program. *
* Operating System Concepts - Ninth Edition
* Copyright John Wiley & Sons - 2013
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE 80 /* 80 chars per line, per command */
void command(int n);
int main(void)
{
char *args[MAX_LINE/2 + 1]; /* command line (of 80) has max of 40 arguments */
int should_run = 1;
int i,j,check,number,N, upper;
check = 0; //check는 history2차원배열에서 어디에 넣을지 체크하는 변수
number = 5; //number는 history가 몇 개까지 기록하는지를 정하는 변수
i = 0; //for문에서 사용되는 변수
char history[20][20]; // history를 20개까지 저장하는 이차원 배열 선언
char *ptr; // 문자열 쪼갤 때 사용하는 포인터
char str[20]; //직접 입력받는 문자열
char temp[20]; //!!와 !N일 때 문자열 쪼개기 위해 잠시 있는 배열
 while (should_run){ 
 printf("osh>"); fflush(stdout); //출력버퍼 초기화
fflush(stdin); //입력버퍼 초기화
char str[20]; //직접 입력받는 문자열
gets(str);
if(strcmp(str,"history")==0){ //history와 같다면 continue
for(j= check –5;number>0;j++){ //개수가 5개 이하에서 history명령이 나올 수 있으므로
if(j<=-5) printf("There is not a history\n"); //history가 없는 상태일 때 문구 출력
else if(j<=0){ //그 이외에 5개 이하이면 j=0으로 초기화
j = 0;
number = check; //number도 check로 초기화
}
printf("%d %s\n",number--,history[j]); //개수만큼 history 출력
}
number = 5; //number를 다시 원래 5로 초기화
continue;
}
else if(strcmp(str,"exit")==0) return 0; //exit이 입력되면 바로 return 0
strcpy(history[check++],str);// str문자열을 history 그다음에 복사
args[0] = strtok(str," "); //str을 띄어쓰기까지 쪼개서 args[0]에 대입
ptr = args[0]; //그부분의 주소를 ptr이 가르킴
i=0;
while(ptr != NULL){ //ptr이 NULL이 아니면 계속 반복
ptr = strtok(NULL," "); //NULL그 다음을 ptr이 가르킴
args[++i] = ptr; //args그다음부터 ptr대입
}
N = str[1]-48; //!가 ASCII코드로 작용하므로 48을 뺀 값을 N에 저장
if(strcmp(history[check-1],"!!")==0){ //!!가 입력되면
int j =0;
strcpy(history[check-1],history[check-2]); //check-1에 check-2의 history를 복사
strcpy(temp, history[check-2]); //temp에도 복사
args[0] = strtok(temp," "); //args에 temp를 띄어쓰기까지 쪼개서 첫부분을 저장
//strcpy(history[check-1],args);
ptr = args[0]; //첫 번째 args[0]을 ptr이 가르킴
i = 0;
while(ptr != NULL){ 
ptr = strtok(NULL," ");
args[++i] = ptr;
}
}
else if(str[0] == '!' && N > 0 && N < 10 && strlen(str) ==2){ //첫 번째가 !이고 N이 1~10이고 길이가 2이면
strcpy(history[check-1], history[check-N-1]); //N번째에 있는 history를 이전 history에 복사
strcpy(temp, history[check-N-1]); //복사한 N번째 history를 temp에 복사하여 쪼갤 수 있도록 함
args[0] = strtok(temp," ");
ptr = args[0];
i = 0;
while(ptr != NULL){
ptr = strtok(NULL," ");
args[++i] = ptr;
}
}
int pid; //pid를 선언해서 부모, 자식 나눌 수 있도록 함
pid = fork(); //fork를 통해서 나눔
if(pid==0){ //pid가 0이면 자식 프로세스
execvp(args[0], args); //바로 입력받은 것들을 실행하도록 한다
}
else if(pid==-1){ //에러이면 에러 문구 출력
printf("error!\n");
}
else{ //그 나머지 이면 부모 프로세스
if(args[1]!=NULL && strcmp(args[1],"&")==0) continue; //그중에서 두 번째 명령어가 NULL이 아니고 &이면 
while문 continue하도록 한다. else wait(); //그 이외의 나머지는 모두 부모가 wait()을 하도록 한다. }
}//while end
 /*
 * After reading user input, the steps are: * (1) fork a child process
 * (2) the child process will invoke execvp() * (3) if command included &, parent will invoke wait() */
 
 return 0;
}
