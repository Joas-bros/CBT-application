#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


using namespace std;

bool verify(const string& username, const string& password){
    //edit file location as desired
    string filename = "C:\\Users\\josas\\Documents\\Login Info.txt";
    ifstream file(filename);
     if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string susername;
        string spassword;

        getline(ss,susername,',');
        getline(ss,spassword);

        if (susername == username && spassword == password){
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
void displayQuestion(const string& question, const string& op1, const string& op2, const string& op3, const string& op4, const string& cr) {
    cout << "Question: " << question << endl;
    cout << "Options:" << endl;
    cout << "a: " << op1 << endl;
    cout << "b: " << op2 << endl;
    cout << "c: " << op3 << endl;
    cout << "d: " << op4 << endl;
}


int main() {
    int n;
    int s;
    string username;
    string password;
    bool loginsucc = false;


    while (loginsucc == false){
        cout<<"CBT\n Input the following Information"<< endl;
        cout<<"Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        if (verify(username,password)){
            loginsucc = true;
            cout << "Login success"<< endl;
            //edit file location as desired
            string filename = "C:\\Users\\josas\\Documents\\questions.txt";
            ifstream file(filename);

            if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return 1;
            }

            string line;
            vector<string> questions;
            vector<string> options1;
            vector<string> options2;
            vector<string> options3;
            vector<string> options4;
            vector<string> correcto;
    

    
            while (getline(file, line)) {
            stringstream ss(line);
            string question,op1,op2,op3,op4,cr;

            getline(ss, question, ',');
            getline(ss, op1, ',');
            getline(ss, op2, ',');
            getline(ss, op3, ',');
            getline(ss, op4,',');
            getline(ss, cr);
       

            questions.push_back(question);
            options1.push_back(op1);
            options2.push_back(op2);
            options3.push_back(op3);
            options4.push_back(op4);
            correcto.push_back(cr);
        
        }

        file.close();

        int currentQuestionIndex = 0;
      ofstream myfile("userchoice.txt", ios::out);

        while (true) {
            displayQuestion(questions[currentQuestionIndex], options1[currentQuestionIndex], options2[currentQuestionIndex],
                        options3[currentQuestionIndex], options4[currentQuestionIndex], correcto[currentQuestionIndex]);

            cout << "Additional functions:" << endl;
            cout << "n - Next Question" << endl;
            cout << "p - Previous Question" << endl;
            cout << "s - Submit Test" << endl;

            char choice;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 'p':
                    currentQuestionIndex = (currentQuestionIndex - 1+ questions.size())% questions.size() ;
                    break;
                case 'n':
                    currentQuestionIndex = (currentQuestionIndex + 1 )% questions.size();
                    break;
                case 's':
                    if (currentQuestionIndex == questions.size() - 1) {
                        cout << "Test submitted." << endl;
                        s = n * 10;
                        cout << "Your score is " << s << endl;
                        myfile.close();
                        return 0;
                    } else {
                        cout << "Cannot submit on non-final question." << endl;
                    }
                    break;
                case 'a':
                case 'A':
                case 'b':
                case 'B':
                case 'c':
                case 'C':
                case 'd':
                case 'D':
                        if (toupper(choice) == correcto[currentQuestionIndex][0]) {
                            n++;
                        }
                        myfile << choice << endl;  
                        currentQuestionIndex = (currentQuestionIndex + 1) % questions.size();
                        break;
                default:
                    cout << "Invalid choice." << endl;
            }
        }   
     
     }

        
        else{
            loginsucc = false;
            cout << "Please re-login \n";

        }
    }




}
