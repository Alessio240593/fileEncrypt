#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <sys/stat.h>

//encrypt key, change this key to enhance the algorithm
#define KEY 100

void encrypt(const char* path) 
{
    char c;
    std::fstream fin, fout;
 
    fin.open(path, std::ios::in);
    fout.open("result.txt", std::ios::out);

 
    while (fin >> std::noskipws >> c) {
        if(c == '\n') {
            fout << '\n';
        }
        else {
            int temp = (c + KEY * KEY);
            fout << (char)temp;
        } 
    }

    fout.close();
    fin.close();

    fin.open(path, std::ios::out | std::ios::trunc);
    fout.open("result.txt", std::ios::in);

    std::cout << "Start encryption..." << std::endl;

     while(!fout.eof()){
        std::string text;       
        getline(fout, text);        
        fin << text << std::endl;
    }

    if(remove("result.txt") == 0 ) {
        std::cout << "File removed succesfully!\n";
    }
    else {
        std::cout << "File not exists!\n";
    }
    
    std::cout << "Encryption successfully!\n\n\n" << std::endl;

    fout.close();
    fin.close();
}

void decrypt(const char* path) 
{
    char c;
    std::fstream fin, fout;
 
    fin.open(path, std::ios::in);
    fout.open("result.txt", std::ios::out);

 
    while (fin >> std::noskipws >> c) {
        if(c == '\n') {
            fout << '\n';
        }
        else {
            int temp = (c - KEY * KEY);
            fout << (char)temp;
        }
        
    }

    fout.close();
    fin.close();

    fin.open(path, std::ios::out | std::ios::trunc);
    fout.open("result.txt", std::ios::in);

    std::cout << "Start decryption..." << std::endl;

     while(!fout.eof()){
        std::string text;       
        getline(fout, text);   
        text.erase(std::find(text.begin(), text.end(), '\0'), text.end());     
        fin << text << std::endl;
    }
    

    if(remove("result.txt") == 0 ) {
        std::cout << "File removed succesfully\n";
    }
    else {
        std::cout << "File not exists!\n";

    }

    std::cout << "Decryption successfully!\n\n\n" << std::endl;

    fout.close();
    fin.close();
}

int main(int argc, char** argv) {
    char choice;
    struct stat s;
    std::string path;
    std::vector<std::string> fileEncrypt;

    while (1)
    {
        do
        {
            std::cout 
            << "\nSELECT SERVICES:\n" 
            << "--------------------\n"
            << "1) FILE ENCRYPTION\n"
            << "2) FILE DECRYPTION\n"
            << "3) EXIT\n→ ";

            std::cin >> choice;

        } while (choice != '1' && choice != '2' && choice != '3');
        

        switch (choice)
        {
        case '1':
            do
            {
                std::cout << "Insert file path or press esc to return in main menu:";
                std::cin >> path;
                lstat(path.c_str(), &s);

                if(strcmp(path.c_str(), "esc") == 0) {
                    break;
                }
            } while (path.length() >= PATH_MAX || !S_ISREG(s.st_mode) || std::count(fileEncrypt.begin(), fileEncrypt.end(), path) != 0);

            if(strcmp(path.c_str(), "esc") != 0) {
                encrypt((char*)path.c_str());
                fileEncrypt.push_back(path);
            }
            break;
        case '2':
            do
            {
                std::cout << "Insert file path or press esc to return in main menu:";
                std::cin >> path;
                lstat(path.c_str(), &s);
                if(strcmp(path.c_str(), "esc") == 0) {
                    break;
                }
            } while (path.length() >= PATH_MAX || !S_ISREG(s.st_mode) || std::count(fileEncrypt.begin(), fileEncrypt.end(), path) == 0);

            if(strcmp(path.c_str(), "esc") != 0) {
                decrypt((char*)path.c_str());

                for(std::vector<std::string>::iterator it = fileEncrypt.begin(); it != fileEncrypt.end(); it++) {
                    if(strcmp((*it).c_str(), path.c_str()) == 0) {
                        fileEncrypt.erase(it);
                        break;
                    }
                }
            }
            break;
        case '3':
            std::cout << "Exit success!\n";
            exit(EXIT_SUCCESS);
        default:
            break;
        }
    }
}
