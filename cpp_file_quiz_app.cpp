#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

string allCategories[10];
int marksPerCategory[10];
int k=0;
void questionAsked(string option,string option1,string option2,string option3,string option4,string correct,string category,ofstream& fp,int *score)
{
	cout << "Choose Your Option : ";
	cin >> option;
	transform(option.begin(), option.end(), option.begin(), ::toupper);         // for converting lowercase to uppercase
	option.append(")");
	
	fp<<"Question "<<category<<endl;
	
	if (option[0] == correct[0])
	{
		if (option[0] == option1[0])
        {
			fp << "Correct Answer  : " << option1 << endl;
            fp << "Your Answer     : " << option1<<endl;
        }
		if (option[0] == option2[0])
        {
			fp << "Correct Answer  : " << option2 << endl;
            fp << "Your Answer     : " << option2<<endl;
        }
		if (option[0] == option3[0])
        {
			fp << "Correct Answer  : " << option3 << endl;
            fp << "Your Answer     : " << option3<<endl;
        }
		if (option[0] == option4[0])
        {
			fp << "Correct Answer  : " << option4 << endl;
            fp << "Your Answer     : " << option4<<endl;
        }
			
        marksPerCategory[k-1] = 5;

		*score += 5;        // updating total score
		fp<<" Marks Awarded = 5 "<<endl;
	}
	else
	{
		string correctanswer;
		if (correct[0] == option1[0])
			correctanswer = option1;
		if (correct[0] == option2[0])
			correctanswer = option2;
		if (correct[0] == option3[0])
			correctanswer = option3;
		if (correct[0] == option4[0])
			correctanswer = option4;

		string wronganswer;
		
		if (option[0] == option1[0])
			wronganswer = option1;
		if (option[0] == option2[0])
			wronganswer = option2;
		if (option[0] == option3[0])
			wronganswer = option3;
		if (option[0] == option4[0])
			wronganswer = option4;

		fp << "Correct Answer  : " << correctanswer << endl;
		fp << "Your Answer     : " << wronganswer << endl;
		fp << "Marks Awarded = 0 "<<endl;

        marksPerCategory[k-1] = 0;
		
	
	}
	fp<<"\n-----------------------------------------------------------------------------\n";

}

int main()
{
    string name;
    cout<<"\n\n\n\t\t\t\tQUIZ APPLICATION in C++\t\t\t\t\n\n\n";
    cout<<"Enter your name : ";
    getline(cin,name);
    cout<<"\n\nDear "<<name<<","<<endl<<"Please go through the below mentioned points before starting the quiz :-\n\n"<<endl;

    cout<<"(1) Marks awarded for each correct answer = 5\n";
    cout<<"(2) Total number of questions = 10\n";
    cout<<"(3) Maximum score of the quiz = 50\n";
    cout<<"(4) There is no negative marking\n";
    cout<<"(5) Detailed score card will be shown after attempting all 10 questions\n";
    cout<<"\n\nBest of Luck !\n\n";
    system("pause");
    system("cls");
	ifstream read("Quiz.txt");
	ofstream writeResult("resultFile.txt");
	string text;
	string option1, option2, option3, option4,option,correct,category;
	int score = 0;
	int arr[30];        //total questions present inside the file is 30
	
	
	for (int i = 0; i < 30; i++)
	{
		arr[i] = 10 * i + 1;
	}
	
	for (int j = 0; j < 10; j++)        //total questions that can be asked in the quiz is 10
	{
		srand(time(NULL));
		int x = rand()%3;               // generating any random number from 0,1,2
		int end = (3 * j) + x;
	    
		for (int i = arr[3*j]; i < arr[end]; i++)
		{
			string empty;
			getline(read, empty);
		}

		for (int i = 1; i <= 10; i++)
		{
			getline(read, text);
			
			if(i==1)
			{
			  cout<<"\n\n\n\n\n\nQ"<<j+1<<") "<<text;
			  writeResult<<"\nQuestion Number : "<<j+1;
			}
			
				if(i==2)
				{
					writeResult<<text<<endl;	
				}
			
			if(i==3)
			option1 = text;
			
			if(i==4)
			option2 = text;
			
			if(i==5)
			option3 = text;
			
			if(i==6)
			option4 = text;
			
			if (i>1 &&  i<= 7)
				cout << text << endl;

			if (i == 8)
				correct = text.substr(0, 40);
			if (i == 9)
            {
				category = text.substr(0, 40);
                allCategories[k] = category;
                k++;

            }
		}

		questionAsked(option, option1, option2, option3, option4, correct, category,writeResult,&score);
		
        // below is the condition for non-repetition of the questions
		if (arr[end] + 10 < arr[3 * (j + 1)])
		{
			for (int i = arr[end] + 10; i < arr[3 * (j + 1)]; i++)
			{
				string empty;
				getline(read, empty);
			}
		}
		system("cls");
	}

    cout<<"Congratulations "<<name<<". You have completed the quiz.\n\n";
    cout<<"You have got "<<score/5<<" correct out of 10 questions.\n\n";
    cout<<"Here are your answers :-\n\n";
	
	read.close();
	writeResult.close();
	
	ifstream resultFileRead("resultFile.txt");
	string readResult;
	
	while(getline(resultFileRead,readResult))	
	{
		cout<<readResult<<endl;
	}
    cout<<endl<<endl;
	
	system("pause");

    cout<<"\n\nCategory wise marks is as follows :-\n\n";

    for(int i=0; i<10; i++){
        cout<<allCategories[i]<<" -> "<<marksPerCategory[i]<<" Marks"<<endl;
    }
    cout<<endl<<endl;
    system("pause");
    cout<<"\n\nYour Final Total Score : "<<score<<" out of 50.\n\n";

	return 0;
}
