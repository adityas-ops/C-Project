#include <bits/stdc++.h>
using namespace std;

class Student {
  int rollno;
  string name;
  int eng_marks, math_marks, sci_marks, cs_marks, social_marks;
  double average;
  char grade;

public:
  void getdata();
  void showData() const;
  void calculate();
  int retrollno() const;
};
void Student::calculate() {
  average =
      (eng_marks + math_marks + sci_marks + cs_marks + social_marks) / 5.0;
  if (average >= 90) {
    grade = 'A';
  } else if (average >= 75) {
    grade = 'B';
  } else if (average >= 50) {
    grade = 'C';
  } else {
    grade = 'F';
  }
}
void Student::getdata() {
  std::cout << "\nEnter the student's Roll number: " << std::endl;
  cin >> rollno;
  std::cout << "enter the student's name" << std::endl;
  getline(cin, name);
  std::cout << "All marks should to be out of 100" << std::endl;
  std::cout << "\nEnter marks in English" << std::endl;
  cin >> eng_marks;
  std::cout << "Enter marks in Math" << std::endl;
  cin >> math_marks;
  std::cout << "Enter marks in Science" << std::endl;
  cin >> sci_marks;
  std::cout << "Enter marks in social Science" << std::endl;
  cin >> social_marks;
  std::cout << "Enter the marks in Computer science" << std::endl;
  cin >> cs_marks;
  calculate();
}
void Student::showData() const {
  std::cout << "\nRoll number of the student: " << rollno << std::endl;
  std::cout << "\nName of the student : " << name << std::endl;
  std::cout << "\nEnglish: " << eng_marks << std::endl;
  std::cout << "\nMaths: " << math_marks << std::endl;
  std::cout << "\nScience  " << sci_marks << std::endl;
  std::cout << "\nSocial Science  " << social_marks << std::endl;
  std::cout << "\nComputer : " << cs_marks << std::endl;
  std::cout << "\nAverage Marks: " << average << std::endl;
  std::cout << "\nGrade of the Student is :" << grade << std::endl;
}

int Student::retrollno() const { return rollno; }
// function declaration
void create_student();
void display_sp(int); // display particular record
void display_all();
void delete_student(int);
void change_student(int); // edit particular record

int main() {
  char ch;
  std::cout << setprecision(2) << std::endl;
  do {
    char ch;
    int num;
    system("cls");
    cout << "\n\n\n\tMENU";
    cout << "\n\n\t1.Create student record";
    cout << "\n\n\t2. Search student record";
    cout << "\n\n\t3. Display all students records ";
    cout << "\n\n\t4.Delete student record";
    cout << "\n\n\t5.Modify student record";
    cout << "\n\n\t6.Exit";
    cout << "\n\n\nWhat is your Choice (1/2/3/4/5/6) ";
    cin >> ch;
    system("cls");
    switch (ch) {
    case '1':
      create_student();
      break;
    case '2':
      std::cout << "\n\n\tEnter the roll number: " << std::endl;
      cin >> num;
      display_sp(num);
      break;
    case '3':
      display_all();
      break;
    case '4':
      std::cout << "\n\n\tEnter the roll number " << std::endl;
      cin >> num;
      delete_student(num);
      break;
    case '5':
      std::cout << "\n\n\tEnter the roll number" << std::endl;
      cin >> num;
      change_student(num);
      break;
    case '6':
      std::cout << "Exiting, Thank You !!" << std::endl;
      exit(0);
    }
  } while (ch != '6');
  return 0;
}

void create_student() {
  Student stud;
  ofstream oFile;
  oFile.open("stdent.dat", ios::binary | ios::app);
  stud.getdata();
  oFile.write(reinterpret_cast<char *>(&stud), sizeof(Student));
  oFile.close();
  std::cout << "\n\nStudent record Has Been Created" << std::endl;
  cin.ignore();
  cin.get();
}
// read file record
void display_all() {
  Student stud;
  ifstream inFile;
  inFile.open("student.dat", ios::binary);
  if (!inFile) {
    std::cout << "File could not opened!! Press any key to exit" << std::endl;
    cin.ignore();
    cin.get();
    return;
  }
  std::cout << "\n\n\n\tDisplaying All Records\n\n" << std::endl;
  while (inFile.read(reinterpret_cast<char *>(&stud), sizeof(Student))) {
    stud.showData();
    std::cout << "\n\n==================================================\n\n"
              << std::endl;
  }
  inFile.close();
  cin.ignore();
  cin.get();
}

// read specific record based on roll number
void display_sp(int n) {
  Student stud;
  ifstream iFile;
  iFile.open("student.dat", ios::binary);
  if (!iFile) {
    std::cout << "File could not be opened ... press any key to exit"
              << std::endl;
    cin.ignore();
    cin.get();
    return;
  }
  bool flag = false;
  while (iFile.read(reinterpret_cast<char *>(&stud), sizeof(Student))) {
    if (stud.retrollno() == n) {
      stud.showData();
      flag = true;
    }
  }
  iFile.close();
  if (flag == false) {
    std::cout << "\n\nRecord does not exist" << std::endl;
    cin.ignore();
    cin.get();
  }
}

void change_student(int n)
{
    bool found= false;
    Student stud;
    fstream f1;
    f1.open("student.dat",ios::binary|ios::in|ios::out);
    if(!f1)
    {
        std::cout << "File could not be opened. Press any key to exit..." << std::endl;
        cin.ignore();
        cin.get();
        return;
    }
    while(!f1.eof() && found==false)
    {
        f1.read(reinterpret_cast<char *> (&stud), sizeof(Student));
        if(stud.retrollno() ==n)
    {
        stud.showData();
        std::cout << "\n\nEnter new student datails: " << std::endl;
        stud.getdata();
        int pos=(-1)*static_cast<int>(sizeof(stud));
        f1.seekp(pos,ios::cur);
        f1.write(reinterpret_cast<char *>(&stud), sizeof(Student));
        std::cout << "\n\n\t Record updated" << std::endl;
        found= true;
    }
    }
    f1.close();
    if(found == false)
    {
        std::cout << "\n\n Record not found" << std::endl;
        cin.ignore();
        cin.get();

    }
}

// delete record with particular roll number
void delete_student(int n)
{
    Student stud;
    ifstream iFlie;
    iFlie.open("student.dat",ios::binary);
    if(!iFlie)
    {
        std::cout << "File could not be opened... Press any key to exit ... " << std::endl;
        cin.ignore();
        cin.get();
        return;
    }
    ofstream oFile;
    oFile.open("Temp.dat",ios::out);
    iFlie.seekg(0,ios::beg);
    while(iFlie.read(reinterpret_cast<char *>(&stud), sizeof(Student)))
    {
        if(stud.retrollno() != n)
        {
            oFile.write(reinterpret_cast<char *>(&stud), sizeof(Student));
        }
    }
    oFile.close();
    iFlie.close();
    remove("student.dat");
    rename("Temp.dat","student.dat");
    std::cout << "\n\n\n\tRecord Deleted.." << std::endl;
    cin.ignore();
    cin.get();
}
