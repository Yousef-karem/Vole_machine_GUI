#ifndef UNTITLED_V_H
#define UNTITLED_V_H
#include<bits/stdc++.h>
using namespace std;
class Register
{
private:
    vector<string>R;
public:
    Register(int size,string InitValue);
    void setRegister(string location,string value);
    string getRegister(string location);
    void clearRegister();
    void DisplayRegisters();
};
class Memory
{
private:
    vector<string>M;
public:
    Memory(int size,string InitValue);
    void setMemory(string location,string value);
    string getMemory(string location);
    void clearMemory();
    void DisplayMemory();

};
class Machine:public Register,public Memory
{
private:
public:
    int counter;
    int counter_sz=0;
    bool Exit;
    void Instruction(int i);
    vector<vector<string>>B;
    Machine(int RegisterSize, string initValue1, int MemorySize, string initValue);
    void RunMachine(string filename);


};



#endif //UNTITLED_V_H
