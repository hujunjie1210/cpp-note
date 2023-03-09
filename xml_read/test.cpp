# include <iostream>
# include <sstream>
# include "MoonsSfwFileLoader.h"


using namespace std;
class A
{
public:
    A() {};
    virtual ~A() {};
    virtual void out1() = 0;
    virtual void out2() { cout << "a out2 comes" << endl; };
};

class B : public A
{
public:
    B() { this->out3(); };
    virtual ~B() {};
    void out1() override { cout << "b out1 comes" << endl; };
    virtual void out2() override { cout << "b out2 comes" << endl; };
    void out3()  { cout << "out3 comes" << endl; };
    void out4()  { cout << "out4 comes" << endl; };

};

char* jjj() {
    char armVersion[2];
    armVersion[0] = 0x41;
    armVersion[1] = 0x42;
    return armVersion;
}

int main(int argc, char* argv[]){

    const char* filePATH = "D:/SCU_Slave_Moons.sfw";
    MoonsSfwFileLoader loader;
    loader.DownloadSfwFile(filePATH);
    int i = (0x03 << 8) + 0x27;
    int jjj =loader.GetCRCValue();
    auto crc = loader.GetPackets();
    for (int i = 0; i < crc.size(); i++)
    {
        int iLen = strlen(crc[i].data) / 2;
        char* packet = new char[iLen];
        for (int j = 0; j < iLen; ++j)
        {
            char tmp[2];
            memset(tmp, 0, sizeof(tmp));
            memcpy(tmp, crc[i].data + 2 * j, 2);
            packet[j] = strtoul(tmp, NULL, 16);
        }
    }


    /*char src[2];
    src[0] = (char)0x03;
    src[1] = (char)0x27;
    int k = (char)27;
    int j = 0x0327;
    int i = src[1]+(src[0] << 8);

    const char* s = "0327";
    int si = strtoul(s, NULL, 16);
    int cp = src[1] + (src[0] << 8);*/

    //A* ab = new B;
    //ab->out1();
    //ab->out2();
    ////ab->out3();
    ////ab->out4();

    //B* bb = new B;
    //bb->out1();
    //bb->out2();
    //bb->out3();
    //bb->out4();


    /*stringstream moonsVersion;
    moonsVersion << 1 << 2;
    string str = moonsVersion.str();*/

    //char* name ;
    //name = jjj();
    //printf("%x", name[0]);
    ////printf("%s\n", *name);
    //printf("--------------------\n");
   
    return 0;
}

