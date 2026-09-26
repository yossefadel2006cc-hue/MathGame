#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enQuestionsLevel {Easy =1, Med = 2, Hard = 3, Mix =4};

enum enOperationType {Addition =1, Subtraction =2, Multiplication =3, Division =4, Mix1 =5};

struct stQuestionInfo 
{
    int Number1 = 0;
    int Number2 = 0;
    enOperationType Operation;
    int CorrectAnswer = 0;
};


struct stQuizeResults
{
    short NumberOfQuestions = 0;
    enQuestionsLevel QuestionsLevel;
    enOperationType OperationType;
    short NumberOfRightAnswers= 0;
    short NumberOfWrongAnswers= 0;
    bool pass;
};

string QuestionLevelName (enQuestionsLevel LevelChoice)
{
    string arrQuestionsLevel[4] = {"Easy", "Med", "Hard", "Mix"};
    return arrQuestionsLevel[LevelChoice-1];
}

string OperationtypeString (enOperationType OperationChoice)
{
    string arrOperationsType[5] = {"+", "-", "x", "/", "Mix"};
    return arrOperationsType[OperationChoice-1];
}

short HowManyQuestions()
{
    short Number;
    do
    {
        cout<<"How Many Questions Do You Want To Answer ? ";
        cin>>Number;
    }while(Number < 1);
    return Number;
}

int RightAnswer(int Number1, int Number2, enOperationType Operation)
{
    switch(Operation)
    {
        case enOperationType::Addition:
            return Number1 + Number2;
        case enOperationType::Subtraction:
            return Number1 - Number2;
        case enOperationType::Multiplication:
            return Number1 * Number2;
        case enOperationType::Division:
            return Number1 / Number2;
        default:
            return 0;
    }
}

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

int QuestionLevel(enQuestionsLevel QuestionLevel )
{
    switch(QuestionLevel)
    { 
        case enQuestionsLevel::Easy:
            return RandomNumber(1,10);

        case enQuestionsLevel::Med:
            return RandomNumber(10,50);

        case enQuestionsLevel::Hard:
            return RandomNumber(50,100);

        case enQuestionsLevel::Mix:
        {
            int RandomLevel = RandomNumber(1,3);

            switch(RandomLevel)
            {
                case 1:
                    return RandomNumber(1,10);
                case 2:
                    return RandomNumber(10,50);
                case 3:
                    return RandomNumber(50,100);
                 default:
                    return 0;
            }
        }

        default:
            return 0;


    }
}

enOperationType MixOperators()
{
    return enOperationType(RandomNumber(1,4));
}

enQuestionsLevel ReadQuestionLevel()
{
    int Choice;
    cout<<"Enter Question Level [1] Easy, [2]Med, [3]Hard, [4]Mix? ";
    cin>>Choice;
    return enQuestionsLevel(Choice);
}

enOperationType ReadOperatorType()
{
    int Choice;
    cout<<"Enter Operation Type [1] Add, [2] sub, [3] Mul, [4] Div, [5]Mix ? ";
    cin>>Choice;
    return enOperationType(Choice);
}

stQuestionInfo GenerateQuestion(enQuestionsLevel Level , enOperationType Operation)
{
    stQuestionInfo QuestionInfo;
    QuestionInfo.Number1 = QuestionLevel(Level);
    QuestionInfo.Number2 = QuestionLevel(Level);

    if(Operation == Mix1)
        QuestionInfo.Operation = MixOperators(); 
    else
        QuestionInfo.Operation = Operation;

    QuestionInfo.CorrectAnswer = RightAnswer(QuestionInfo.Number1, QuestionInfo.Number2,QuestionInfo.Operation);
    return QuestionInfo;
}

void PrintQuestion(stQuestionInfo QuestionInfo)
{
    cout<<"\n"<<QuestionInfo.Number1<<endl;
    cout<<QuestionInfo.Number2<<" "<<OperationtypeString(QuestionInfo.Operation)<<endl;
}


int ReadUserAnswer()
{
    int UserAnswer;
    cin>>UserAnswer;
    return UserAnswer;
}

void CheckAnswer(int UserAnswer, stQuestionInfo RightAnswer, stQuizeResults& QuizeResults)
{
    if(UserAnswer == RightAnswer.CorrectAnswer)
    {
        cout<<"\nRight Answer :)\n";
        QuizeResults.NumberOfRightAnswers++;
    }
    else
    {
        cout<<"\nWrong Answer :(\n";
        cout<<"The Correct Answer is "<<RightAnswer.CorrectAnswer;
        QuizeResults.NumberOfWrongAnswers++;
    }
    
}

stQuizeResults  StartQuize(short NumberOfQuestions, enQuestionsLevel Level, enOperationType Operation)
{   
    stQuizeResults QuizeResults;
    QuizeResults.NumberOfQuestions = NumberOfQuestions;
    QuizeResults.QuestionsLevel = Level;
    QuizeResults.OperationType = Operation;

    for(int i =1 ; i <= NumberOfQuestions ; i++)
    {
        cout<<"\nQuestion ["<<i<<"/"<<NumberOfQuestions<<"]\n";
        stQuestionInfo QuestionInfo = GenerateQuestion(Level , Operation);
        PrintQuestion(QuestionInfo);
        cout<<"_________\n";
        int UserAnswer = ReadUserAnswer();
        CheckAnswer(UserAnswer, QuestionInfo, QuizeResults);
    }
    QuizeResults.pass = (QuizeResults.NumberOfRightAnswers >= QuizeResults.NumberOfWrongAnswers);
    return QuizeResults;
}


void PrintQuizeResults(stQuizeResults QuizeResults)
{
    cout<<"\n-------------------------------------\n";
    if(QuizeResults.pass)
    {
        cout<<" Final Quize Results Is PASS :)\n";
        cout<<"\033[42m";
    }
    else
    {
        cout<<" Final Quize Results Is FAIL :(\n";
        cout << "\033[41m";
    }
    cout<<"-------------------------------------\n";
    cout<<"Number Of Questions     : "<<QuizeResults.NumberOfQuestions<<endl;
    cout<<"Questions Level         : "<<QuestionLevelName(QuizeResults.QuestionsLevel)<<endl;
    cout<<"Operation Type         : "<<OperationtypeString(QuizeResults.OperationType)<<endl;
    cout<<"Number Of Right Answers : "<<QuizeResults.NumberOfRightAnswers<<endl;
    cout<<"Number Of Wrong Answers : "<<QuizeResults.NumberOfWrongAnswers<<endl;
    cout<<"_______________________________________\n";
}

// void ResetGame()
// {
//     cout << "\033[2J\033[H";
// }

void PlayGame()
{
    char PlayAgain ='Y';
    do
    {
        int NumberOfQuestions = HowManyQuestions();
        enQuestionsLevel Level = ReadQuestionLevel();
        enOperationType OperationType =  ReadOperatorType();
        stQuizeResults QuizeResults= StartQuize(NumberOfQuestions, Level, OperationType);
        PrintQuizeResults(QuizeResults);
        cout<<endl<<"Do you want to play again? Y/N?";
        cin>>PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
    
}

int main()
{
    srand((unsigned)time(NULL));
    PlayGame();
    return 0;
}