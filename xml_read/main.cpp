# include <iostream>
# include <sstream>
# include "MoonsSfwFileLoader.h"


using namespace std;

int main(int argc, char* argv[]){

    const char* filePATH = "/mnt/d/SCU_Slave_Moons.sfw";
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

    return 0;
}

