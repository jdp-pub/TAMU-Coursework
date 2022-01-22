// These headers define some of the classes and functions we need
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

// ONLY MAKE CHANGES WHERE THERE IS A TODO

// These using declarations let us refer to things more simply
// e.g. instead of "std::cin" we can just write "cin" 
using std::cin, std::cout, std::endl;
using std::string, std::getline;

// These methods are defined below the main function

// print instructions for inputting grades
void print_instructions();

// pretty print a summary of the grades 
void print_results(double exam_average,
                   double hw_average,
                   double lw_average,
                   double engagement,
                   double weighted_total,
                   char final_letter_grade);

// YOU ARE NOT EXPECTED TO UNDERSTAND THIS ONE... YET
// extract the category and score from the line
// and store the values in the provided variables
// if line := "exam 95", then category := "exam" and score := 95
// if the line is invalid, then category := "ignore"
void get_category_and_score(const string& line,
                            string* category,
                            double* score);

int main() {
    print_instructions();

    // ONLY MAKE CHANGES WHERE THERE IS A TODO
    
    // TODO(student): declare and initialize variables that you want

    // holds raw total score per category
    double ExamScoreTotal = 0;
    double HwScoreTotal = 0;
    double LwScoreTotal = 0;
    double EngagementScoreTotal = 0;
    double FinalExamScore = 0;

    bool TakesFinal = false;

    // holds number per category, used for taking average of raw scores
    double NumExam = 0;
    double NumFinal = 0;
    double NumHw = 0;
    double NumLw = 0;
    double NumEngagement = 0;

    string line;
    // read one line from standard input (discards the ending newline character)
    getline(cin, line);
    // read lines until an empty line is read
    while (!line.empty()) {
        string category;
        double score;
        get_category_and_score(line, &category, &score);

        // process the grade entry, adds total scores and number of items in each category
        if (category == "exam") {
            // TODO(student): process exam score
            ExamScoreTotal = ExamScoreTotal + score;
            ++NumExam;
            if (score < 60)
            {
                TakesFinal = true;
            }
            
        } else if (category == "final-exam") {
            // TODO(student): process final score
            ++NumFinal;
            FinalExamScore = score;
            ExamScoreTotal = ExamScoreTotal + score;
        } else if (category == "hw") {
            // TODO(student): process hw score
            HwScoreTotal = HwScoreTotal + score;
            ++NumHw;
        } else if (category == "lw") {
            // TODO(student): process lw score
            if (score > 1)
            {
                score = 1;
            } 
            LwScoreTotal = LwScoreTotal + score * 100;
            ++NumLw;
        } else if (category == "engagement") {
            // TODO(student): process engagement score
            EngagementScoreTotal = EngagementScoreTotal + score;
            ++NumEngagement;
        } else {
            cout << "ignored invalid input" << endl;
        }

        // get the next line from standard input
        getline(cin, line);
    }

    if ((TakesFinal == true && NumFinal == 0) && (NumEngagement + NumExam + NumHw + NumLw > 30 || NumEngagement + NumExam + NumHw + NumLw < 10))
    {
        ++NumFinal;
    }

    // TODO(student): compute component averages
    double exam_average = 0; 
    double hw_average = 0; 
    double lw_average = 0; 
    double engagement = EngagementScoreTotal;

    if ((NumExam + NumFinal) != 0 )
    {
        exam_average = ExamScoreTotal / (NumExam + NumFinal);
        
        if (FinalExamScore > exam_average)
        {
            exam_average = FinalExamScore;
        }
    }
    if (NumHw != 0)
    {
        hw_average = HwScoreTotal / NumHw;
    }
    if (NumLw != 0)
    {
        lw_average = LwScoreTotal / NumLw;
    }
    if (engagement > 100)
    {
        engagement = 100;
    }

    // TODO(student): compute weighted total of components
    double weighted_total = (0.4 * exam_average) + (0.4 * hw_average) + (0.1 * lw_average) + (0.1 * engagement) ;

    // TODO(student): compute final letter grade
    char final_letter_grade = 'A';

    if (weighted_total < 90) // for every condition met, knocks grade down 1 tier
    {
        final_letter_grade = 'B';
        if(weighted_total < 80)
        {
            final_letter_grade = 'C';
            if(weighted_total < 70)
            {
                final_letter_grade = 'D';
                if (weighted_total < 60)
                {
                    final_letter_grade = 'F';
                }
            }
        }

    }

    print_results(
        exam_average, hw_average, lw_average, engagement,
        weighted_total, final_letter_grade);
}

// These methods are already implemented for you
// You should not need to modify them

void print_instructions() {
    cout << "enter grades as <category> <score>" << endl;
    cout << "  <category> := exam | final-exam | hw | lw | engagement" << endl;
    cout << "     <score> := numeric value" << endl;
    cout << "enter an empty line to end input" << endl;
}

void get_category_and_score(
    const string& line,
    string* category,
    double* score) {
    // turn the string into an input stream
    std::istringstream sin(line);

    // read the category (as string) and score (as double) from the stream
    sin >> *category;
    sin >> *score;

    if (sin.fail()) {
        // the stream is in a fail state (something went wrong)
        // clear the flags
        sin.clear();
        // clear the stream buffer (throw away whatever garbage is in there)
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // signal that the line was invalid
        *category = "ignore";
    }
}

void print_results(
    double exam_average,
    double hw_average,
    double lw_average,
    double engagement,
    double weighted_total,
    char final_letter_grade) {
    cout << "summary:" << endl;
    cout << "      exam average: " << exam_average << endl;
    cout << "        hw average: " << hw_average << endl;
    cout << "        lw average: " << lw_average << endl;
    cout << "        engagement: " << engagement << endl;
    cout << "    ---------------" << endl;

    cout << "    weighted total: " << weighted_total << endl;

    cout << "final letter grade: " << final_letter_grade << endl;
}
