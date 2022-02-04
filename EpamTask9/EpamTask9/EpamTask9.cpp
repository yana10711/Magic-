
#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include<algorithm>
#include <Windows.h>
using namespace std;

struct Human
{
    string Fullname;
    int numberbirth;
    int monthbirth;
    int yearbirth;
    string gender;
};
vector <Human> UploadData() {  
    vector <Human> v(11); 
    ifstream fin; int i = 0; 
    fin.exceptions(ifstream::badbit | ifstream::failbit);
    //the function of reading all lines from a file into a vector of stucts
    try
    {
        
        fin.open("Inlet.in");
        while (!fin.eof() && i<v.size()) {
            
         
            if (i > 0) {
                getline(fin, v[i].Fullname);getline(fin, v[i].Fullname);
                fin >> v[i].numberbirth>> v[i].monthbirth>> v[i].yearbirth>> v[i].gender;
           }
            else {
                getline(fin, v[i].Fullname); fin >> v[i].numberbirth >> v[i].monthbirth >> v[i].yearbirth >> v[i].gender;
            }
           
          ++i;            
        }
        fin.close();
        return v;

    }
    catch (const ifstream::failure& ex)
    {
        cout << endl << "Вызвано исключение:" << endl;    // catches exceptions
        cout << "Код ошибки:" << ex.code() << endl;
        exit(0);
    }
}
void print(vector <Human>& v, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << "Fullname:" << v.at(i).Fullname << endl;         //output of a vector of structures to the console
        cout << "Number" << v.at(i).numberbirth << endl;
        (v.at(i).monthbirth / 10 > 0) ? cout << "Месяц:" << v.at(i).monthbirth << endl : cout << "Месяц:0" << v.at(i).monthbirth << endl;
        cout << "Yearofborn:" << v.at(i).yearbirth << endl;
        cout << "Gender:" << v.at(i).gender << endl;
        cout << endl;
    }
    cout << endl;
}
int getValue()
{
    while (true)
    {
        cout << "Enter the date in numeric format:" << endl;
        unsigned int a;
        cin >> a;                                                           // checks the correct month entry
        if (cin.fail() || a > 12) {
            cin.clear();
            cin.ignore(32767, '\n'); cout << "Incorrect input:" << endl;
        }
        else if (a <= 12 && a > 0) {
            return a;
        }
    }
}
char getSymbol()
{
    while (true)
    {
        cout << "Enter the letter:" << endl;
        string s;  char c;
        cin >> s;
        if (s.length() == 1)
        {
            c = s[0];
            if (isalpha((unsigned char)c))     //checks the correct character input 
            {
                c = toupper(c); return c;
            }
            else { cout << "Incorrect input!" << endl; }
        }

        else {
            cin.clear();
            cin.ignore(32767, '\n'); cout << "Incorrect input!" << endl;
        }

    }
}
bool lastName(struct Human a, struct Human b)
{
    return b.Fullname > a.Fullname;                  // sorting the vector of structures alphabetically (by last name)
}
bool TheOldestMan(struct Human a, struct Human b)
{
    return a.gender > b.gender;                         //moving all men to the beginning of the array

}
bool Bm(struct Human a, struct Human b)             //sorting by descending age of men
{
    return (a.gender == "мужской" && b.gender == "мужской" && a.yearbirth < b.yearbirth) ||

        (a.gender == "мужской" && b.gender == "мужской" && a.yearbirth == b.yearbirth && a.monthbirth < b.monthbirth) ||
        (a.gender == "мужской" && b.gender == "мужской" && a.yearbirth == b.yearbirth && a.monthbirth == b.monthbirth && a.numberbirth < b.numberbirth)
        ;
}
int main()
{
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    vector <Human> v1 = UploadData();   // a vector of structures consisting of data that is read from a file
    int count = 0;
    int condition = -1;
    int month;


    while (condition != 0)     // checking user input
    {

        cout << "1 Data output to the console" << endl;
        cout << "2 Sorting the database alphabetically (by last name)" << endl;
        cout << "3 Output: a list of people born in a given month" << endl;
        cout << "4 Output the oldest man" << endl;
        cout << "5 Output: all surnames starting with a given letter" << endl;
        cout << "0 Exit" << endl;

        while (true)
        {
            cin >> condition;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(32767, '\n'); cout << "Incorrect input:" << endl;
            }
            else break;
        }
        switch (condition)
        {
        case 1:
            print(v1, v1.size());     // output of data read from the file to the console
            break;
        case 2:
            sort(v1.begin(), v1.end(), lastName);     // sorting the array in ascending order (by last name)
            print(v1, v1.size());
            break;
        case 3:

            month = getValue();




            for (int i = 0; i < v1.size(); i++)       //checking and output for the presence of people born in a given month
            {
                if (month == v1.at(i).monthbirth)
                {
                    cout << v1.at(i).Fullname << endl; count++;
                }
            }
            if (count == 0) cout << "There are no people born in a given month!" << endl;
            count = 0;
            break;


        case 4:
            sort(v1.begin(), v1.end(), TheOldestMan);    // moving all males to the beginning of the array
            sort(v1.begin(), v1.end(), Bm);          //sorting the array in descending order of dates
            for (int i = 1; i < v1.size(); i++) {
                if (v1.at(i).gender == v1.at(0).gender && v1.at(i).yearbirth == v1.at(0).yearbirth && v1.at(i).monthbirth == v1.at(0).monthbirth
                    && v1.at(i).numberbirth == v1.at(0).numberbirth)  //checking whether there are men in the array who were born on the same day and how many of them
                    count++;
            }


            if (count != 0)
            {
                cout << "The oldest men:" << endl;
                for (int i = 0; i <= count; i++) {
                    cout << v1.at(i).Fullname << endl;
                }
            }
            else cout << "The oldest man:" << v1.at(0).Fullname << endl;
            count = 0;
            break;

        case 5:
        {
            char c = getSymbol();
            for (int i = 0; i < v1.size(); i++)
            {

                if (v1.at(i).Fullname[0] == c)
                {
                    cout << v1.at(i).Fullname << endl; count++;
                }
            }
            if (count == 0) { cout << "There are no surnames that begin with a given letter!" << endl; }
            count = 0;
            break;
        }
        case 0:
            return 0;
            break;
        default:
            cout << "Error: Invalid data" << endl;
            break;
        }
        cout << endl;

    }


}


