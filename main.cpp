#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void error(int code, int column) {

    for (int i = 0; i < column; i++) {
        cout << " ";
    }
    cout << "^" << endl;

    switch (code){
    case 1:
        cout << "Error at column " << column << ": expected 'triangle'; code = " << code <<  endl;
        break;
    case 2:
        cout << "Error at column " << column << ": expected '<double>'; code = " << code << endl;
        break;
    case 3:
        cout << "Error at column " << column << ": expected ')'; code = " << code << endl;
        break;
    case 4:
        cout << "Error at column " << column << ": unexpected token; code = " << code << endl;
        break;
    case 5:
        cout << "Error at column " << column << ": expected '('; code = " << code << endl;
        break;
    }
}

vector<string> split(string &str, string sep) {
    vector<string> res;
    string s = str;
    for (int pos = 0; pos < s.length(); pos++) {
        string elem = "";
        if (pos == s.find(sep)) {
            elem.append(s, 0, pos);
            res.push_back(elem);
            s.erase(0, pos + sep.length());
            pos = 0;
        }
    }
    res.push_back(s);


    return res;
}

string takeFigure(string &s) {
    int begin = s.find("(");

    for (int i = 0; i < size(s); i++)
    {
        s[i] = tolower(s[i]);                      //приводим к одному регистру(строчный)
    }

    string figure = "";
    figure.append(s, 0, begin);
    return figure;
}

vector<float> createTriangle(string &str) {

    string s = str;

    vector<float> data;
    vector<float> empty;

    int begin = s.find("((");
    int end = s.find("))");

    if (end == -1) {
        error(3, s.length()-1);
        return empty;
    }

   

    string dataString = "";
    dataString.append(s, begin);

    if ((dataString[0] == '(') && (dataString[1] == '(')) {
        dataString.erase(0, 2);
    }
    else {
        error(5, 8);
        return data;
    }
    int count = 0, column = 10;
    for (int i = 0; i < dataString.length(); i++) {
        
        string elem = "";
        if (count < 5) {
            if (((dataString[i] < 48) || (dataString[i] > 57)) && (dataString[i] != 32) && (dataString[i] != 44) && (dataString[i] != 46)) {
                error(2, column);
                return empty;
            }
            if (dataString[i] == ' ') {
                elem.append(dataString, 0, i);
                data.push_back(stof(elem));
                dataString.erase(0, i + 1);
                i = 0;
                count++;
                column ++;
            }
            if (dataString[i] == ',') {
                elem.append(dataString, 0, i);
                data.push_back(stof(elem));
                dataString.erase(0, i + 2);
                i = 0;
                count++;
                column += 2;
            }
        }
        else if(count == 5){
            int end = dataString.find("))");
            if (end != -1) {
                elem.append(dataString, 0, end);
                data.push_back(stof(elem));
                
                dataString.erase(0, end + 2);
                i = 0;
                count += 2;
            }
            else {
                error(3, column);
                return empty;
            }
        }
        else {
            error(4, str.find("))") + 2);
            return empty;
        }
        column++;
    }

    return data;
}

int main()
{
    setlocale(LC_CTYPE, "Russian");
    vector<pair<string, vector<float>>> figures;
    string s;
    int count = 1;

    cout << "Задайте фигуры" << endl;

    while (getline(cin, s)) {

        if (s == "") {
            break;
        }
        
        string figureName = takeFigure(s);

        vector<float> figurePoints;
        

        if (figureName == "triangle") {
            figurePoints = createTriangle(s);
        }
        else {
            error(1, 0);
        }

        pair<string, vector<float>> figure;

        if (figurePoints.size() > 0) {
            figure.first = figureName;
            figure.second = figurePoints;
            figures.push_back(figure);
            count++;
        }

        
    }

    for (int i = 0; i < figures.size(); i++) {
        cout << i + 1 << ". " << figures[i].first << ": ";
        for (int j = 0; j < figures[i].second.size(); j++) {
            cout << figures[i].second[j] << " ";
        }
        cout << endl;
    }
    return 0;
}

