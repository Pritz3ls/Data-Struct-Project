#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Custom made tool, to lessen line of codes and make coding easier
class ProgramTool{
    public:
        /// Display texts with parameters of newLines and a string
        void Display_Text(string text, int after_newLines = 1){
                cout << text;
                for(int i = 0; i < after_newLines; i++){cout << endl;}
            }
        /// Display a symbol and specify it's width
        void Display_Line(string symbol, int width,  int after_newLines = 1){
            for(int i = 0; i < width; i++){cout << symbol;}
            for(int i = 0; i < after_newLines; i++){cout << endl;}
        }
        /// Display a title and specify it's symbol and title
        void Display_Title(string title, string symbol, int width ,int after_newLines){
            for(int i = 0; i < width; i++){cout << symbol;}
            cout << endl << title << endl;
            for(int i = 0; i < width; i++){cout << symbol;}
            for(int i = 0; i < after_newLines; i++){cout << endl;}
        }
        /// Halt the process and ask the user to enter any key, parameter of text and new line
        string Halt(string text, int after_newLines = 0){
            string haltnull = " ";
            cout << endl << text;
            for(int i = 0; i < after_newLines; i++){cout << endl;}
            cin >> haltnull;
            return haltnull;
        }
        /// Prompt the user and return its text
        string Prompt_Text(string prompttext){
            string input;
            cout << prompttext;
            cin >> input;
            return input;
        }
        /// Prompt the user and return it's integer value
        int Prompt_Number(string prompttext){
            int input;
            cout << prompttext;
            cin >> input;
            return input;
        }
};
// Object Info
class Info{
    public:
        string name;
        string srcode;
        string address;
        string contact;
        int department = 0;
        int pin;
        
        // Having trouble assigning grades in an array
        // using a trust factor can change the outcome of the grades
        double trust_factor;

        double grades[7] = {
            92.8,
            85.7,
            90.2,
            83.5,
            92,
            91.1,
            86,
        };
        string subjects[7] = {
            "Comprog", 
            "Data Structure", 
            "Filipino", 
            "History", 
            "Mathematics",
            "Science",
            "Physical Education",
        };

        Info(string _name, string _srcode, int _pin, int _department, string _address, string _contact, double factor){
            name = _name;
            srcode = _srcode;
            department = _department;
            pin = _pin;
            address = _address;
            contact = _contact;
            trust_factor = factor;
        }
        double Evaluate_Subject(){
            double total;
            double temp[7];
            for(int i = 0; i < 7; i++){
                grades[i] += trust_factor;
                total += grades[i];
            }
            return total / 7;
        }
        void Reset(){
            name = "null";
            srcode = "null";
            pin = 0101;
            department = 0;
            address = "null";
            contact = "null";
        }
};
// Program base functions and variables
// Dyanamic Variables
class ProgramBase{
    private:
        // Admin Credentials
        Info *admin = new Info("Administrator", "22-3257", 6969, 0, "BSU - Lipa Campus", "09183026982", 5);
        // Users
    public:
        Info *info[5];
        Info *curAccount = new Info("null","00-0000",0101,1,"null","null",0);
        // Admin switch
        bool admin_enabled = false;
        // (Prototype) Initialize pre-defined student accounts
        void Start(){
            info[0] = new Info("Prince Marco Guerrero", "55-3201", 2003, 1, "Marawouy, Lipa City", "09194704561", 4.1);
            info[1] = new Info("Earl John Guno", "69-3205", 3201, 1, "Banay-Banay, Lipa City", "09177659061", 0.2);
            info[2] = new Info("Glenn Dimaano", "67-3219", 1234, 2, "California", "07819035656", 2.3);
            info[3] = new Info("Kriztel Sia", "90-3102", 5012, 3, "Del Gallego, Camarines Sur", "09691081035", 2.2);
            info[4] = new Info("Khim Frank", "12-5012", 1205, 2, "San Jose, Batangas City", "09716450871", 3.4);
        }
        // Check if it's the Admin credentials or student, or non existent account 
        bool Evaluate_Account(string _srcode, int _pin){
            for(int i = 0; i < 5; i++){
                if(info[i]->srcode == _srcode && info[i]->pin == _pin){
                    curAccount = info[i];
                    return true;
                }
            }
            if(_srcode == admin->srcode && _pin == admin->pin){
                curAccount = admin;
                admin_enabled = true;
                return true;
            }
            return false;
        }
};

// Declaration of class Programs~ and objects;
ProgramBase base;
ProgramTool tool;

// Functions in order, foreground
void Login_();
void Main_Student();
void Main_Admin();

// Global Collect Function
void Collect_Info();
// Student Collect Functions
void Collect_Subjects();
void Collect_Grades();
// Admin Functions
void Admin_ChangeGrades();
void Admin_ChangeInfo();
void Admin_View();
int main(){
    base.Start();
    Login_();
}

void Login_(){
    string user_srcode;
    string haltnull = " ";
    int user_pin;
    bool valid = false;

    tool.Display_Title("BATANGAS STATE UNIVERSITY\nSTUDENT PORTAL LOGIN","-",26,2);
    user_srcode = tool.Prompt_Text("Enter SR-Code: ");
    user_pin = tool.Prompt_Number("Enter Pin (4 Digit): ");
    tool.Display_Line("-",26);
    valid = base.Evaluate_Account(user_srcode, user_pin);
    while (!valid){
        tool.Display_Title("ACCOUNT NOT FOUND!", "x", 19,2);
        user_srcode = tool.Prompt_Text("Enter SR-Code: ");
        user_pin = tool.Prompt_Number("Enter Pin (4 Digit): ");
        valid = base.Evaluate_Account(user_srcode, user_pin);
    }
    tool.Display_Title("ACCOUNT FOUND!", "=", 19,2);
    haltnull = tool.Halt("Enter any key to continue...");
    if(base.admin_enabled){
        Main_Admin();
    }else{Main_Student();}
}
void Main_Admin(){
    string haltnull = " ";
    int choice;

    tool.Display_Title("BATANGAS STATE UNIVERSITY\nADMIN MAIN MENU","-",26,1);
    tool.Display_Text("Welcome, " + base.curAccount->name);
    tool.Display_Text("How may i help you today?");
    tool.Display_Line("-",26,2);
    tool.Display_Text("1 - View Admin information\n2 - Change Student Grades\n3 - Change Student Information\n4 - View Student Information\n5 - Logout",2);
    choice = tool.Prompt_Number("Enter choice: ");
    while(choice != 0){
        if(choice == 1){
            Collect_Info();
        }else if (choice == 2){
            Admin_ChangeGrades();
        }else if (choice == 3){
            Admin_ChangeInfo();
        }else if (choice == 4){
            Admin_View();
        }else if (choice == 5){
            base.admin_enabled = false;
            base.curAccount->Reset();
            Login_();   
        }else{
            tool.Display_Title("Invalid Choice", "X", 15, 2);
        }
        choice = tool.Prompt_Number("Enter choice: ");
    }
}
void Main_Student(){
    string haltnull = " ";
    int choice;

    tool.Display_Title("BATANGAS STATE UNIVERSITY\nSTUDENT MAIN MENU","-",26,1);
    tool.Display_Text("Welcome, " + base.curAccount->name);
    tool.Display_Text("How may i help you today?");
    tool.Display_Line("-",26,2);
    tool.Display_Text("1 - View Information\n2 - View Subjects\n3 - View Grades\n4 - Logout",2);
    choice = tool.Prompt_Number("Enter choice: ");
    while(choice != 0){
        if(choice == 1){
            Collect_Info();
        }else if (choice == 2){
            Collect_Subjects();
        }else if (choice == 3){
            Collect_Grades();
        }else if (choice == 4){
            base.admin_enabled = false;
            base.curAccount->Reset();
            Login_();   
        }else{
            tool.Display_Title("Invalid Choice", "X", 15, 2);
        }
        choice = tool.Prompt_Number("Enter choice: ");
    }
}

// ADMIN STUFFS
void Admin_ChangeGrades(){
    Info *temp;
    
    tool.Display_Title("(ADMIN) CHANGE STUDENT GRADE", "=", 36, 2);
    tool.Display_Text("Select a student from the list;");
    tool.Display_Line("-",20);
    for(int i = 0; i < 5; i++){
        cout << i+1 << "." << base.info[i]->name << endl;
    }
    tool.Display_Line("-",20);
    int choice = tool.Prompt_Number("Enter choice: ");
    while (choice != 0 && choice > 5){
        tool.Display_Text("Invalid choice! Try again...");
        choice = tool.Prompt_Number("Enter choice: ");
    }
    temp = base.info[choice-1];
    tool.Display_Line("-",20);
    tool.Display_Text("What grade you wish to change?");
    for(int i = 0; i < 7; i++){
        cout << i+1 << "." << temp->subjects[i];
        cout << " - " << temp->grades[i] + temp->trust_factor << endl;
    }
    int grade_choice = tool.Prompt_Number("Enter choice: ");
    while (grade_choice != 0 && grade_choice > 7){
        tool.Display_Text("Invalid choice! Try again...");
        grade_choice = tool.Prompt_Number("Enter choice: ");
    }
    tool.Display_Line("-",30);
    temp->grades[grade_choice-1] = tool.Prompt_Number("Enter new grade (Grade may vary depending on the student performance): ");
    base.info[choice-1] = temp;
    tool.Display_Text("Change Successfully!");
    string haltnull = tool.Halt("Press any key to continue...");
    tool.Display_Line("-",20,2);
    Main_Admin();
}
void Admin_ChangeInfo(){
    Info *temp;
    
    tool.Display_Title("(ADMIN) CHANGE STUDENT INFO", "=", 36, 2);
    tool.Display_Text("Select a student from the list;");
    tool.Display_Line("-",20);
    for(int i = 0; i < 5; i++){
        cout << i+1 << "." << base.info[i]->name << endl;
    }
    tool.Display_Line("-",20);
    int choice = tool.Prompt_Number("Enter choice: ");
    while (choice <= 0 && choice > 5){
        tool.Display_Text("Invalid choice! Try again...");
        choice = tool.Prompt_Number("Enter choice: ");
    }
    temp = base.info[choice-1];
    tool.Display_Line("-",20);
    tool.Display_Text("What info you wish to change?");
    tool.Display_Text("1 - Name\n2 - Address\n3 - Contact\n4 - Department",2);
    tool.Display_Text(temp->name + " selected!");
    int change_choice = tool.Prompt_Number("Enter choice: ");
    if(change_choice == 1){
        temp->name = tool.Prompt_Text("Enter new name: ");
    }else if (change_choice == 2){
        temp->address = tool.Prompt_Text("Enter new address: ");
    }else if (change_choice == 3){
        temp->contact = tool.Prompt_Text("Enter new contact: ");
    }else if (change_choice == 4){
        temp->department = tool.Prompt_Number("Enter new deparment(1 - 3): ");
    }else{
        tool.Display_Text("Invalid choice! try again...");
        change_choice = tool.Prompt_Number("Enter choice: ");
    }
    tool.Display_Line("-",30);
    base.info[choice-1] = temp;
    tool.Display_Text("Change Successfully!");
    string haltnull = tool.Halt("Press any key to continue...");
    tool.Display_Line("-",20,2);
    Main_Admin();
}
void Admin_View(){
    tool.Display_Title("(ADMIN) VIEW STUDENT INFO", "=", 36, 2);
    tool.Display_Text("Select a student from the list;");
    tool.Display_Line("-",20);
    for(int i = 0; i < 5; i++){
        cout << i+1 << "." << base.info[i]->name << endl;
    }
    tool.Display_Line("-",20);
    int choice = tool.Prompt_Number("Enter choice: ");
    while (choice <= 0 && choice > 5){
        tool.Display_Text("Invalid choice! Try again...");
        choice = tool.Prompt_Number("Enter choice: ");
    }
    tool.Display_Title("STUDENT INFORMATION", "=", 26, 1);
    tool.Display_Line("-",26);
    tool.Display_Text("Full Name: " + base.info[choice-1]->name);
    tool.Display_Text("Address: " + base.info[choice-1]->address);
    tool.Display_Text("Contact: " + base.info[choice-1]->contact);
    tool.Display_Line("-",26);
    tool.Display_Text("ACADEMIC PERFORMACE");
    cout << "Performance factor: " << base.info[choice-1]->trust_factor << endl;
    tool.Display_Line("-",26);
    for(int i = 0; i < 7; i++){
        cout << i+1 << ". " << base.info[choice-1]->subjects[i] << " - " << base.info[choice-1]->grades[i] + base.info[choice-1]->trust_factor << endl;
    }
    tool.Display_Line("-",26);
    switch (base.info[choice-1]->department){
    
    tool.Display_Text("CREDENTIALS",1);
    tool.Display_Text("SR-Code: " + base.info[choice-1]->srcode);
    tool.Display_Text("Pin Number: ",0);
    cout << base.info[choice-1]->pin << endl;
        case 1:
            tool.Display_Text("Department: CICS");
        break;
        case 2:
            tool.Display_Text("Department: CABE");
        break;
        case 3:
            tool.Display_Text("Department: CAS");
        break;
        default:
            tool.Display_Text("Department: null");
        break;
    }
    tool.Display_Line("-",26);
    string haltnull = " ";
    haltnull = tool.Halt("Enter any key to continue...");
    Main_Admin();
}

void Collect_Info(){
    tool.Display_Title("INFORMATION", "=", 26, 2);
    tool.Display_Text("Full Name: " + base.curAccount->name);
    tool.Display_Text("Address: " + base.curAccount->address);
    tool.Display_Text("Contact: " + base.curAccount->contact);
    switch (base.curAccount->department){
        case 1:
            tool.Display_Text("Department: CICS");
        break;
        case 2:
            tool.Display_Text("Department: CABE");
        break;
        case 3:
            tool.Display_Text("Department: CAS");
        break;
        default:
            tool.Display_Text("Department: null");
        break;
    }
    tool.Display_Line("-",26);
    tool.Display_Text("CREDENTIALS",1);
    tool.Display_Text("SR-Code: " + base.curAccount->srcode);
    tool.Display_Text("Pin Number: ",0);
    cout << base.curAccount->pin << endl;
    tool.Display_Line("-",26);
    string haltnull = " ";
    haltnull = tool.Halt("Enter any key to continue...");
    if(!base.admin_enabled){
        Main_Student();
    }else{Main_Admin();}
}
void Collect_Subjects(){
    tool.Display_Title("STUDENT SUBJECTS", "=", 26, 2);
    for(int i = 0; i < 7; i++){
        tool.Display_Text("-" + base.curAccount->subjects[i]);
    }
    string haltnull = " ";
    haltnull = tool.Halt("Enter any key to continue...");
    if(!base.admin_enabled){
        Main_Student();
    }else{Main_Admin();}
}
void Collect_Grades(){
    tool.Display_Title("STUDENT GRADES", "=", 26, 2);
    for(int i = 0; i < 7; i++){
        cout << fixed << setprecision(0) << base.curAccount->grades[i] + base.curAccount->trust_factor << " - ";
        tool.Display_Text(base.curAccount->subjects[i]);
    }
    tool.Display_Line("-",26,1);
    tool.Display_Text("Total Percentage: ", 0);
    cout << fixed << setprecision(1) << base.curAccount->Evaluate_Subject()<<endl;
    tool.Display_Line("-",26,2);
    string haltnull = " ";
    haltnull = tool.Halt("Enter any key to continue...");
    if(!base.admin_enabled){
        Main_Student();
    }else{Main_Admin();}
}