#ifndef MOONSSFWFILELOADER_H
#define MOONSSFWFILELOADER_H

#include <iostream>
#include <vector>
#include <string>
#include "tinyxml.h"

typedef struct _PACKETDATA
{
    int type;
    int index;
    char* data;
} PACKETDATA, *PPACKETDATA;

class MoonsSfwFileLoader
{
private:
    /************* data **********/
    // BaseInfo
    int m_DriveModelNo;
    int m_DriveSubModelNo;
    std::string m_SoftwareName;
    std::string m_SoftwareVersion;
    std::string m_SoftwareGUID;
    
    // DSP
    int m_DSPPacketLength;
    std::string m_DSPRev;

    // ARM
    int m_ARMPacketLength;
    std::string m_ARMRev;

    // FPGA
    int m_FPGAPacketLength;
    std::string m_FPGARev;

    // CRC
    int m_CRC;


    //Packets
    std::vector<PACKETDATA> m_Packets;

    void ObtainChildNoodInfo(TiXmlElement *pRoot, std::vector<std::string> vecChildrenNodes);

public:
    MoonsSfwFileLoader(/* args */);
    ~MoonsSfwFileLoader();

    bool DownloadSfwFile(const char *pFilePath);

    int GetCRCValue();

    std::vector<PACKETDATA> GetPackets();
};

#endif