#include "Vole_Machine.h"
void Register::setRegister(string location, string value)
{
    int i=stoi(location,0,16);
    if(i>=R.size())
    {
        cout<<"the Register location is not found\n";
    }
    else
    {
        R[i]=value;
    }
}

void Register::clearRegister() {
    for(string &value:R)
    {
        value="00";
    }
}

void Register::DisplayRegisters() {
    cout<<"The Registers: \n";
    for (int i = 0; i < R.size(); ++i) {
        stringstream stream;
        stream << hex << i;
        cout<<stream.str()<<' '<<R[i]<<endl;
    }
}

string Register::getRegister(string location) {
    int i=stoi(location,0,16);
    if(i<R.size())
        return R[i];
    else
        cout<<"the Register is not found\n";
}

Register::Register(int size,string InitValue)
{
    for(int i=0;i<size;i++)
    {
        R.push_back(InitValue);
    }
}

void Memory::setMemory(string location, string value) {
    int i=stoi(location,0,16);
    if(i>=M.size())
    {
        cerr<<"the Memory location is not found\n";
    }
    else
    {
        M[i]=value;
    }
}

void Memory::DisplayMemory() {
    cout<<"The Memory cells: "<<endl;
    for (int i = 0; i < M.size(); ++i) {
        stringstream stream;
        stream << hex << i;
        cout<<stream.str()<<' '<<M[i]<<endl;
    }
}

Memory::Memory(int size, string InitValue) {
    for(int i=0;i<size;i++)
    {
        M.push_back(InitValue);
    }
}

void Memory::clearMemory() {
    for(string&value:M)
    {
        value="00";
    }
}

string Memory::getMemory(string location) {
    int i=stoi(location,0,16);
    if(i<M.size())
        return M[i];
}

Machine::Machine(int RegisterSize, string initValue1, int MemorySize, string initValue)
        : Register(RegisterSize, initValue1),
          Memory(MemorySize, initValue),counter(0),Exit(false) {
}
void Machine::Instruction(int i) {
    switch (i)
    {
        case 1: {
            setMemory(B[counter][2] + B[counter][3], getRegister(B[counter][1]));
        }
            break;
        case 2: {
            setRegister(B[counter][1], B[counter][2] + B[counter][3]);
        }
            break;
        case 3:
        {
            string value = getRegister(B[counter][1]);
            setMemory(B[counter][2]+B[counter][3], value);
        }
            break;
        case 4:
            setRegister(B[counter][3], getRegister(B[counter][2]));
            break;
        case 5:
        {
            const int a = stoi(getRegister(B[counter][2]), 0, 16);
            const int b = stoi(getRegister(B[counter][3]), 0, 16);
            bitset<16> bitsetA(a);
            bitset<16> bitsetB(b);
            bitset<16 + 1> resultBitset = bitsetA.to_ullong() + bitsetB.to_ullong();
            if (resultBitset[16]) {
                resultBitset &= ~(1 << 16);
            }
            int result = resultBitset.to_ulong();
            stringstream stream;
            stream << hex << result;
            string s=stream.str();
            if(s.size()==1)
                s='0'+s;
            setRegister(B[counter][1], s);
        }
            break;
        case 6:
            break;
        case 11:
        {
            if (getRegister("0") == getRegister(B[counter][1])) {
                counter = stoi(B[counter][2] + B[counter][3], 0, 16)-1;
                Instruction(stoi(B[counter][0], 0, 16));
            }
        }
            break;
        case 12:
        {
            Exit = true;
        }
            break;
        default:
            cerr<<"Error, the instruction is not valid"<<endl;

    }
}

void Machine::RunMachine(string filename)
{
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error opening the file!" << endl;
        return;
    }
    int cnt=0;

    vector<string> tmp(4);
    while (inputFile>>tmp[cnt])
    {
        tmp[cnt]=tmp[cnt].substr(2);
        if(tmp[cnt].size()==2)
        {
            tmp[cnt+1]=tmp[cnt].back();;
            tmp[cnt].pop_back();
            cnt++;
        }
        cnt++;
        if(cnt==4)
        {
            cnt=0;
            B.push_back(tmp);
            counter_sz++;
        }
    }
    for (; counter < counter_sz; ++counter) {
        int i=stoi(B[counter][0],0,16);
        Instruction(i);
        if(Exit)
            break;
    }
    inputFile.close();
    DisplayMemory();
    DisplayRegisters();
}
