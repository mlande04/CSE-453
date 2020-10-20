//
//  main.cpp
//  Week5Lab
//
//  Created by Jacob Johnson on 10/17/20.
//  Copyright © 2020 Jacob Johnson. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// This function creates a list of strings e.g. {"C:", "Users", ...} from the input string breakign them apart by the specificed delimiter
void tokenize(string const &str, const char delim,
            vector<string> &out)
{
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

//main function canocalizes. two file paths on Windows 10 to see if they are homographs.
int main(int argc, const char * argv[]) {
    string forbidden = "C:\\Users\\Reynold\\downloads\\secrets\\secret.txt";
    string currDir = "C:\\Users\\Reynold\\downloads\\secrets\\";
    string newPath;

    
    vector<string> forbiddenList;
    vector<string> newPathList;
    vector<string> finalDirList;
    
    tokenize(currDir, '\\', forbiddenList);
    
    cout << "Please input the file path \n";
    getline(cin,newPath);
    
    if (newPath == "secret.txt"){
        cout << "YES, Homograph" << endl;
        return 0;
    }
    
    tokenize(newPath, '\\', newPathList);
    
    vector<string> addDir;
    string finalDir= "";
    
    
    
    if (newPath[0] == '.'){
        for (int i = 0; i< newPathList.size(); i++){
            if (newPathList[i] == ".") {
                continue;
            }
            if (newPathList[i] == "..") {
                forbiddenList.pop_back();
            }
            else {
                forbiddenList.push_back(newPathList[i]);
            }
        }
        for (int i = 0; i < forbiddenList.size(); i++){
            //cout <<"looping final list:" << forbiddenList[i]<<endl;
            if (i != forbiddenList.size()-1){
                finalDir = finalDir + forbiddenList[i] + "\\";
            } else {
                finalDir = finalDir + forbiddenList[i];
            }
        }
        cout << "forbidden file path = " << forbidden << endl;
        cout << "input file path = " << finalDir << endl;
        transform(forbidden.begin(), forbidden.end(), forbidden.begin(), ::tolower);
        transform(finalDir.begin(), finalDir.end(), finalDir.begin(), ::tolower);
        if (forbidden==finalDir){
            cout << "YES, Homographs" << endl;
        } else {
            cout << "NO, Non-Homographs" << endl;
        }
    } else {
        if (newPath[0] == '\\'){
            finalDirList.push_back("C:");
        }
//        } else {
//            finalDirList.clear();
//        }
        for (int i = 0; i< newPathList.size(); i++){
            if (newPathList[i] == ".") {
                continue;
            }
            if (newPathList[i] == "..") {
                finalDirList.pop_back();
            }
            else {
                finalDirList.push_back(newPathList[i]);
            }
        }
        for (int i = 0; i < finalDirList.size(); i++){
            //cout <<"looping final list:" << finalDirList[i]<<endl;
            if (i != finalDirList.size()-1){
                finalDir = finalDir + finalDirList[i] + "\\";
            } else {
                finalDir = finalDir + finalDirList[i];
            }
        }
        cout << "forbidden file path = " << forbidden << endl;
        cout << "input file path = " << finalDir << endl;
        transform(forbidden.begin(), forbidden.end(), forbidden.begin(), ::tolower);
        transform(finalDir.begin(), finalDir.end(), finalDir.begin(), ::tolower);
        if (forbidden == finalDir){
            cout << "YES, Homographs" << endl;
        } else {
            cout << "NO, Non-Homographs" << endl;
        }
    }
    return 0;
}

//input = C:\Users\Reynolds
//currentDir = "C:\\Users\\Reynold\\downloads\\secrets\\";
//if input = . then don't change currentDir
//if input = \ then change currentDir to root (C:)
//if input = D: or \\networkloc\\ then change currentDir {}, so that D: or networkloc fill spot 1.
