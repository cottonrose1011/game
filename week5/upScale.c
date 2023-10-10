#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <math.h>
#include <windows.h>
#define PHI 3.141592

struct info {
	
	char name[30] ;
	char year[10];
	char month[10];
	char day[10];
	
} info;



long total_days(int year, int month, int day);
void print_biorhythm(long total, int month);
char bio_status(int val, int mod);
void setTextcolor(int color_number);
void getInfo();
void setInfo();

int main(void)
{


	int byr, bmon, bday;
	int tyr, tmon, tday;
	int choice = 0;
	const int GO_NEXT = 1;
	const int CHANGE_INFO = 2;
	long total=0;
	
	setTextcolor(6);

	
	printf("┏--------------------------------------------------------┓\n");
	printf("┃                      환영합니다                        ┃\n");
	printf("┃                                                        ┃\n");
	printf("┃              1을 누르면 바이오리듬 계산                ┃\n");
	printf("┃                 2를  누르면 정보변경                   ┃\n");
	printf("┃                                                        ┃\n");
	printf("┃       원하시는 번호를 입력 후Enter를 입력하세요        ┃\n");
	printf("┗--------------------------------------------------------┛\n");
	scanf("%d",&choice);
	
	if (choice == GO_NEXT){
		system("cls");
		getInfo(byr, bmon, bday);
		byr = atoi(info.year);
		bmon = atoi(info.month);
		bday = atoi(info.day);
		printf("┏--------------------------------------------------------┓\n");
		printf("┃               특정월의 바이오리듬 계산                 ┃\n");
		printf("                %s(%d/%d/%d/)님 안녕하세요       \n", info.name, byr, bmon, bday);
		printf("┃                                                        ┃\n");
		printf("       보시고 싶은 년도와 월을 입력하세요. (ex: 2004 11)  \n");
		printf("┃         생년월일이 입력한 날짜보다 앞서야 합니다.      ┃\n");
		printf("┗--------------------------------------------------------┛\n");
		scanf("%d%d", &tyr, &tmon);
		tday=1;
		total=total_days(tyr, tmon, tday)-total_days(byr, bmon, bday);
		
		printf("\n두 날짜 사이의 날짜수는 %ld일 입니다. \n\n", total);
		printf("바이오리듬 결과:\n");
		printf("저조기(-), 고조기(+), 위험기(D)\n");
		print_biorhythm(total, tmon);
	}
	
	if (choice == CHANGE_INFO){
		system("cls");
		setInfo();
	}
	
	
	return 0;
}


// 함수  
void print_biorhythm(long total, int month)
{
	//[함수 11.2.2]의 정의부분 참고
	int dayindex;
	int physical, emotion, intellect;
	for(dayindex=1; dayindex<=30; dayindex++)
	{
		 physical=total%23;
		 emotion=total%28;
		 intellect=total%33;
		 printf("%d월 %2d일", month, dayindex);
		 printf(" 신체:%2d %c ", physical, bio_status(physical, 23));
		 printf(" 감정:%2d %c ", emotion, bio_status(emotion, 28));
		 printf(" 지성:%2d %c\n", intellect, bio_status(intellect, 33));
		 total++;
	}
}
char bio_status(int v, int mod)
{
	//[함수 11.2.1]의 정의부분 참고
	char result;
	double r;
	r=sin(v*3.141592/(mod/2.0));
	if (r < -0.2)
	     result='-';
	else if ((-0.2<=r) && (r<=0.2))
	    result='D';
	else
	 	result='+';
	return result;
}
long total_days(int year, int month, int day)
{
	//[함수 2.3.2]의 정의부분 참고
	int months[]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int i;
	long total=0L;
	total=(year-1)*365L+(year-1)/4-(year-1)/100+(year-1)/400;
	if(!(year%4) && year%100 || !(year%400))
	    months[1]++;
	for(i=0; i<month-1; i++)
	   total += months[i];
	total+=day;
	return total;
}
void setTextcolor(int color_number)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}
void getInfo(){

	FILE *file = fopen("user.txt", "r");
	if (file == NULL) {
	    perror("파일 열기 실패");
	    return 1;
	}
	
	char line[256];
	char *token;
	
	while (fgets(line, sizeof(line), file) != NULL) {
	    char *key = strtok(line, ":");
	    char *value = strtok(NULL, ":");
	    
	    if (key != NULL && value != NULL) {
	        // 공백을 제거하여 key와 value 추출
	        char *trimmed_key = strtok(key, " \t\n");
	        char *trimmed_value = strtok(value, " \t\n");
	        
	        if (trimmed_key != NULL && trimmed_value != NULL) {
	            if (strcmp(trimmed_key, "name") == 0) {
	                strcpy(info.name, trimmed_value);
	            } else if (strcmp(trimmed_key, "birth") == 0) {
	                
					// "yyyy-mm-dd" 부분을 하이픈을 기준으로 분리
					token = strtok(trimmed_value, "-");
					if (token != NULL) {
						strcpy(info.year, token);// 연도를 year 변수에 저장
						
						token = strtok(NULL, "-");
						if (token != NULL) {
						    strcpy(info.month, token); // 월을 month 변수에 저장
						
						    token = strtok(NULL, "-");
						    if (token != NULL) {
						        strcpy(info.day, token); // 일을 day 변수에 저장
		
						    }
						}
					}
							
					
	            }
	        }
	    }
	}
	
	fclose(file);
};

void setInfo(){
	
	char newName[20];
	char newBirth[20];
	
	printf("변경할 이름을 입력하세요. 영문명만 가능합니다. \n");
	scanf("%s", &newName);
	printf("변경할 생년월일을 입력하세요. 다음의 형식으로 작성합니다. (ex: 1990-10-23) \n");
	scanf("%s", &newBirth);
	
	
	FILE *file = fopen("user.txt", "r");
	if (file == NULL) {
	    perror("파일 열기 실패");
	    return 1;
	}
	
	char line[256];
	char newContent[256];

	FILE *tempFile = fopen("temp.txt", "w");

    if (tempFile == NULL) {
        perror("임시 파일 열기 실패");
        fclose(file);
        return 1;
    }
	
	while (fgets(line, sizeof(line), file) != NULL) {
	    char *key = strtok(line, ":");
	    char *value = strtok(NULL, ":");
	    
	    if (key != NULL && value != NULL) {
	        char *trimmed_key = strtok(key, " \t\n");
	        char *trimmed_value = strtok(value, " \t\n");
	        
	        if (trimmed_key != NULL && trimmed_value != NULL) {
	            if (strcmp(trimmed_key, "name") == 0) {
	                strcpy(trimmed_value, newName);
	            } else if (strcmp(trimmed_key, "birth") == 0) {
	                strcpy(trimmed_value, newBirth);
	            }
	        }
	        sprintf(newContent, "%s:%s\n", trimmed_key, trimmed_value);
	    	fputs(newContent, tempFile);
	    }
	    
	}
	
	fclose(file);
	fclose(tempFile);
	
	remove("user.txt");
	rename("temp.txt", "user.txt");
};
