#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enQuestionsLevel {Easy =1, Med = 2, Hard = 3, Mix =4};

enum enOperationType {Add =1, Sub =2, Mul =3, Div =4, MixOp =5};

struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enOperationType OperationType;
    enQuestionsLevel QuestionLevel;
    int CorrectAnswer = 0;
    int UserAnswer = 0;
    bool AnswerResult = false;
};

struct stQuiz 
{
    stQuestion QuestionList[100];
    short NumberOfQuestions = 0;
    enQuestionsLevel QuestionsLevel;
    enOperationType OperationType;
    short NumberOfRightAnswers= 0;
    short NumberOfWrongAnswers= 0;
    bool Ispass = false;
};

string QuestionLevelName (enQuestionsLevel QuestionLevel)
{
    string arrQuestionsLevel[4] = {"Easy", "Med", "Hard", "Mix"};
    return arrQuestionsLevel[QuestionLevel-1];
}

string OperationtypeString (enOperationType OperationType)
{
    string arrOperationsType[5] = {"+", "-", "x", "/", "Mix"};
    return arrOperationsType[OperationType-1];
}

short RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

short ReadHowManyQuestions()
{
    short NumberOfQuestions = 0;
    do
    {
        cout<<"How Many Questions Do You Want To Answer ? ";
        cin>>NumberOfQuestions;
    }while(NumberOfQuestions < 1 || NumberOfQuestions > 20);

    return NumberOfQuestions;
}

enQuestionsLevel ReadQuestionsLevel()
{
    short QuestionsLevel;
    do
    {
        cout<<"Enter Questions Level : Easy [1], Med [2], Hard [3], Mix :[4]?\n" ;
        cin>>QuestionsLevel;
    }while(QuestionsLevel < 1 || QuestionsLevel > 4);
    return (enQuestionsLevel) QuestionsLevel;
}

enOperationType ReadOperationType()
{
    short OpType;
    do
    {
        cout<<"Enter Operation Type: Add [1], Sub :[2], Mul :[3], Div :[4], MixOpType :[5]?\n";
        cin>>OpType;
    }while(OpType < 1 || OpType > 5);
    return (enOperationType) OpType;
}

short ReadUserAnswer()
{
    short UserAnswer;
    cin>>UserAnswer;
    return UserAnswer;
}

short SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
    switch(OpType)
    {
        case enOperationType::Add:
            return Number1 + Number2;
        case enOperationType::Sub:
            return Number1 - Number2;
         case enOperationType::Mul:
            return Number1 * Number2;
        case enOperationType::Div:
            return (Number2 != 0) ? (Number1 / Number2) : 0; // Avoid division by zero.
        default:
            return 0;
    }
}

enOperationType GetRandomOpType()
{
    return (enOperationType)RandomNumber(1,4);
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
    stQuestion Question;
    
    if(QuestionLevel == enQuestionsLevel::Mix)
        Question.QuestionLevel = (enQuestionsLevel)RandomNumber(1,3); 
    else
        Question.QuestionLevel = QuestionLevel;  
    
    if(OpType == enOperationType::MixOp)
        Question.OperationType = GetRandomOpType();
    else
        Question.OperationType = OpType;
    
    switch(Question.QuestionLevel)
    {
        case enQuestionsLevel::Easy:
            Question.Number1 = RandomNumber(1,10);
            Question.Number2 = RandomNumber(1,10);
            Question.CorrectAnswer = SimpleCalculator(
                Question.Number1, Question.Number2, Question.OperationType);

            return Question;
            
        case enQuestionsLevel::Med:
            Question.Number1 = RandomNumber(10,50);
            Question.Number2 = RandomNumber(10,50);
            Question.CorrectAnswer = SimpleCalculator(
                Question.Number1, Question.Number2, Question.OperationType);

            return Question;

        case enQuestionsLevel::Hard:
            Question.Number1 = RandomNumber(50,100);
            Question.Number2 = RandomNumber(50,100);
            Question.CorrectAnswer = SimpleCalculator(
                Question.Number1, Question.Number2, Question.OperationType);

            return Question;
        default:
            return Question;
    }
}

void GenerateQuiz(stQuiz& Quiz)
{
    for(int Question = 0 ; Question < Quiz.NumberOfQuestions ; Question++)
    {
        Quiz.QuestionList[Question] = 
        GenerateQuestion(Quiz.QuestionsLevel, Quiz.OperationType);
    }
}

void PrintQuestion(stQuiz Quiz, short QuestionNumber)
{
    cout<<"\n";
    cout<<"Number ["<<QuestionNumber + 1<<"/"<<Quiz.NumberOfQuestions<<"]\n";
    cout<<Quiz.QuestionList[QuestionNumber].Number1<<"\n";
    cout<<Quiz.QuestionList[QuestionNumber].Number2<<" ";
    cout<<OperationtypeString(Quiz.QuestionList[QuestionNumber].OperationType)<<"\n";
    cout<<"--------------------\n";
}

void SetScreenColorQuestion(bool Answer)
{
    if (Answer)
        cout<<"\033[42m"; //Green Screen
    else
        cout << "\033[41m"; //Red Screen
}

void CorrectAnswerQuestionList(stQuiz& Quiz, short QuestionNumber)
{
    if(Quiz.QuestionList[QuestionNumber].UserAnswer != Quiz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        cout<<"Wrong Answer :(\n";
        cout<<"The Right Answer : ";
        cout<<Quiz.QuestionList[QuestionNumber].CorrectAnswer<<"\n";

        Quiz.NumberOfWrongAnswers++;
        Quiz.QuestionList[QuestionNumber].AnswerResult = false;
    }
    else
    {
        cout<<"Right Answer :)\n";
        Quiz.NumberOfRightAnswers++;
        Quiz.QuestionList[QuestionNumber].AnswerResult = true;
    }
    SetScreenColorQuestion(Quiz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionList(stQuiz& Quiz)
{
    for(int QuestionNumber = 0 ; QuestionNumber < Quiz.NumberOfQuestions ; QuestionNumber++)
    {
        PrintQuestion(Quiz, QuestionNumber);
        Quiz.QuestionList[QuestionNumber].UserAnswer = ReadUserAnswer();
        CorrectAnswerQuestionList(Quiz, QuestionNumber);
    }
    Quiz.Ispass = (Quiz.NumberOfRightAnswers >= Quiz.NumberOfWrongAnswers);
}

string GetIsPassText(bool Pass)
{
    if(Pass)
        return "PASS";
    else
        return "FAIL";
}

void PrintQuizResults(stQuiz Quiz)
{
    cout<<"\n\n";
    cout <<"---------------------------------\n";
    cout<<"Tha Final Result Of The Quiz :" << GetIsPassText(Quiz.Ispass);
    cout <<"---------------------------------\n";
    cout<<"Number Of Questions     : "<<Quiz.NumberOfQuestions<<"\n";
    cout<<"Questions Level         : "<<QuestionLevelName(Quiz.QuestionsLevel)<<"\n";
    cout<<"Operation Type          : " <<OperationtypeString(Quiz.OperationType)<<"\n";
    cout<<"Number Of Right Answers : "<<Quiz.NumberOfRightAnswers<<"\n";
    cout<<"Number Of Wrong Answers : "<<Quiz.NumberOfWrongAnswers<<"\n";
    cout<<"_______________________________________\n";
}

void StartPlayGame()
{
    stQuiz Quiz;
    
    Quiz.NumberOfQuestions = ReadHowManyQuestions();
    Quiz.QuestionsLevel = ReadQuestionsLevel();
    Quiz.OperationType = ReadOperationType();

    GenerateQuiz(Quiz);
    AskAndCorrectQuestionList(Quiz);
    PrintQuizResults(Quiz);
}

void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        StartPlayGame();
        cout<<"Do you want to play again? Y/N?\n";
        cin>>PlayAgain;
    }while(PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() {
    srand((unsigned)time(NULL));
    StartGame();
  return 0;
}