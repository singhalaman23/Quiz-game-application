#define _GNU_SOURCE
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#define size 200


char allCategories[10][1024] = {{0}};
int marksPerCategory[10];
int counter = 0;
	
void questionAsked(char option[size], char option1[size], char option2[size], char option3[size], char option4[size], char correct[size], char category[size],FILE * fp,int *score)
{
	printf("Choose Your Option : ");
	scanf("%s",&option[0]);
	option[1] = '\0';				// null character - used to terminate the string
	strupr(option);
	
		char correctanswer[size];
		char wronganswer[size];
		
		fprintf(fp,"Question %s \n",category);
		
	if (option[0] == correct[0])
	{
		if (option[0] == option1[0])
		{
			fprintf(fp,"Correct Answer : %s  \n ", option1);
			fprintf(fp,"Your Answer    : %s  \n ", option1);
		}
		if (option[0] == option2[0])
		{
			fprintf(fp,"Correct Answer : %s  \n ", option2);
			fprintf(fp,"Your Answer    : %s  \n ", option2);
		}
		if (option[0] == option3[0])
		{
			fprintf(fp,"Correct Answer : %s  \n ", option3);
			fprintf(fp,"Your Answer    : %s  \n ", option3);
		}
		if (option[0] == option4[0])
		{
			fprintf(fp,"Correct Answer : %s  \n ", option4);
			fprintf(fp,"Your Answer    : %s  \n ", option4);
		}
			
		marksPerCategory[counter-1] = 5;
		*score += 5;
			
		fprintf(fp,"\nMarks Awarded = 5\n");
	}
	else
	{
	
		if (correct[0] == option1[0])
			strncpy(correctanswer, option1,24);
		if (correct[0] == option2[0])
			strncpy(correctanswer, option2,24);
		if (correct[0] == option3[0])
			strncpy(correctanswer, option3,24);
		if (correct[0] == option4[0])
			strncpy(correctanswer, option4,24);
		
		correctanswer[24] = '\0';
	
		if (option[0] == option1[0])
			strncpy(wronganswer, option1,24);
		if (option[0] == option2[0])
			strncpy(wronganswer, option2,24);
		if (option[0] == option3[0])
			strncpy(wronganswer, option3,24);
		if (option[0] == option4[0])
			strncpy(wronganswer, option4,24);

		wronganswer[24] = '\0';
		
		fprintf(fp,"Correct Answer : %s\n", correctanswer);
		fprintf(fp,"Your Answer    : %s\n", wronganswer);
		fprintf(fp,"Marks Awarded = 0\n");

		marksPerCategory[counter-1] = 0;
	}
	
		fprintf(fp,"\n-----------------------------------------------------------------------------\n");
}


void main()
{
	char name[50];
	printf("\n\n\n\t\t\t\tQUIZ APPLICATION in C\t\t\t\t\n\n\n");
	printf("Enter your name : ");
    scanf("%[^\n]%*c",&name);
	printf("\nDear %s,\n\nPlease go through the below mentioned points before starting the quiz :-\n\n",name);
	printf("(1) Marks awarded for each correct answer = 5\n");
    printf("(2) Total number of questions = 10\n");
    printf("(3) Maximum score of the quiz = 50\n");
    printf("(4) There is no negative marking\n");
    printf("(5) Detailed score card will be shown after attempting all 10 questions\n");
    printf("\n\nBest of Luck !\n\n");
    system("pause");
    system("cls");

	char text[size],option1[size], option2[size], option3[size], option4[size], option[size], correct[size], category[size];
	char empty[256][256];
	int i,j,k;
	int arr[30],x,end;		// 30 for total questions in the file
	time_t t;
	char line[256];
	int score = 0;
	
    FILE * fp;
    FILE * output;
    fp = fopen("Quiz.txt","r");
    output = fopen("resultFile.txt","w");
 
	k = 0;
	
	for (i = 0; i < 30; i++)
	{
		arr[i] = 10 * i + 1;
	}

	for (j = 0; j < 10; j++)		// 10 for total questions which can be asked in the quiz
	{
		srand((unsigned)time(&t));
		x = rand() % 3;
		end = (3 * j) + x;

		for (i = arr[3 * j]; i < arr[end]; i++)
		{
			fgets(empty[k],sizeof(empty[k]),fp);
			k++;
		}

		for (i = 1; i <= 10; i++)
		{
			fgets(line,sizeof(line),fp);	
			if(i==1)
			{
			  printf("\n\n\n\n\n\nQ%d) %s",j+1,line);
			  fprintf(output,"Question Number : %d",j+1);
			  	
			}
			
				if(i==2)
				{
					fputs(line,output);	
				}
				
				if(i == 3)
			strncpy(option1,line,30);
			
				if(i == 4)
			strncpy(option2,line,30);
			
				if(i == 5)
			strncpy(option3,line,30);
			
				if(i == 6)
			strncpy(option4,line,30);	
	 	
			if (i >1&&i<=7)
			{
				printf("%s",line);
				
			}
			if (i == 8)
			strncpy(correct,line,30);	
				
			if (i == 9)
			{
				strncpy(category,line,30);
				strncpy(allCategories[counter], category, strlen(category)+1);
				counter++;
			}

		}

		
		questionAsked(option, option1, option2, option3, option4, correct, category,output,&score);
		
		if(j!=9)
		{
			
		if (arr[end] + 10 < arr[3 * (j + 1)])
		  {  
			for (i = arr[end] + 10; i < arr[3 * (j + 1)]; i++)
			{
			fgets(empty[k],sizeof(empty[k]),fp);
				k++;
			}
		  }
		}
		
		
		system("cls");
	}
	
	printf("Congratulations %s. You have completed the quiz.\n\n",name);
    printf("You have got %d correct out of 10 questions.\n\n",score/5);
    printf("Here are your answers :-\n\n");
	
	fclose(fp);
	fclose(output);
	
	output = fopen("resultFile.txt","r");
	
	while(fgets(line,sizeof(line),output))
	{
		printf("%s",line);
	}
	printf("\n\n");
	fclose(output);
	system("pause");

	printf("\n\nCategory wise marks is as follows :-\n\n");

    for(int i=0; i<10; i++){
        printf("%s-> %d Marks",allCategories[i],marksPerCategory[i]);
		printf("\n");
    }

    printf("\n\n");
    system("pause");
    printf("\nYour Final Total Score : %d out of 50.\n\n",score);
}
