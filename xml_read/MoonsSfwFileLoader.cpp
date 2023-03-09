#include "MoonsSfwFileLoader.h"

MoonsSfwFileLoader::MoonsSfwFileLoader(/* args */)
{
}

MoonsSfwFileLoader::~MoonsSfwFileLoader()
{
}

bool MoonsSfwFileLoader::DownloadSfwFile(const char *pFilePath)
{
    if (!pFilePath)
    {
        // ERR("null pointer for file path");
        return false;
    }

    TiXmlDocument doc(pFilePath);
    bool bLoaded = doc.LoadFile();
    if (!bLoaded)
    {
        // ERR("failed to load XML file, //ERRor:%s ", doc.//ERRorDesc());
        return false;
    }
    // get root node
    TiXmlElement *pRoot = doc.RootElement();
    if (pRoot == nullptr)
        // ERR("null pointer for file path");
        printf("%s\n", pRoot->Value());

    // get child node
    std::vector<std::string> vecChildrenNodes{"BaseInfo", "DSP", "ARM", "FPGA", "CRC"};
    ObtainChildNoodInfo(pRoot, vecChildrenNodes);

    // get Packet
    int nType, nIndex;

    m_Packets.clear();

    TiXmlElement *pChild = pRoot->FirstChildElement("Packet")->FirstChildElement("Data");
    for (; pChild != NULL; pChild = pChild->NextSiblingElement())
    {
        pChild->QueryIntAttribute("type", &nType);
        pChild->QueryIntAttribute("index", &nIndex);
        
        PACKETDATA packet;
        packet.index = nIndex;
        packet.type = nType;
        const char* cpData = pChild->GetText();
        int nLen = strlen(cpData);
        char* pData = new char[nLen + 1];
        strcpy(pData, cpData);
        packet.data = pData;
        m_Packets.push_back(packet);
    }

    return false;
}

void MoonsSfwFileLoader::ObtainChildNoodInfo(TiXmlElement *pRoot, std::vector<std::string> vecChildrenNodes)
{
    // get child node
    for (int i = 0; i < vecChildrenNodes.size(); ++i)
    {
        std::string sNodeName = vecChildrenNodes[i];
        TiXmlElement *pChild = pRoot->FirstChildElement(sNodeName.c_str());
        if (pChild == nullptr)
            // ERR("get %s node failed");
            printf("%s\n", pChild->FirstChild()->ToText()->Value());
        if (sNodeName == "BaseInfo")
        {
            TiXmlElement *pElement1 = pChild->FirstChildElement("DriveModelNo");
            m_DriveModelNo =atoi(pElement1->GetText());
            TiXmlElement *pElement2 = pChild->FirstChildElement("DriveSubModelNo");
            m_DriveSubModelNo = atoi(pElement2->GetText());
            TiXmlElement *pElement3 = pChild->FirstChildElement("SoftwareName");
            m_SoftwareName = pElement3->GetText();
            TiXmlElement *pElement4 = pChild->FirstChildElement("SoftwareVersion");
            m_SoftwareVersion = pElement4->GetText();
            TiXmlElement *pElement5 = pChild->FirstChildElement("SoftwareGUID");
            m_SoftwareGUID = pElement5->GetText();
        }
        else if (sNodeName == "DSP")
        {
            TiXmlElement *pElement1 = pChild->FirstChildElement("Revision");
            m_DSPRev = pElement1->GetText();
            TiXmlElement *pElement2 = pChild->FirstChildElement("PacketLength");
            m_DSPPacketLength = atoi(pElement2->GetText());
        }
        else if (sNodeName == "ARM")
        {
            TiXmlElement *pElement1 = pChild->FirstChildElement("Revision");
            m_ARMRev = pElement1->GetText();
            TiXmlElement *pElement2 = pChild->FirstChildElement("PacketLength");
            m_ARMPacketLength = atoi(pElement2->GetText());
        }
        else if (sNodeName == "FPGA")
        {
            TiXmlElement *pElement1 = pChild->FirstChildElement("Revision");
            m_FPGARev = pElement1->GetText();
            TiXmlElement *pElement2 = pChild->FirstChildElement("PacketLength");
            m_FPGAPacketLength = atoi(pElement2->GetText());
        }
        else if (sNodeName == "CRC")
        {
            m_CRC = strtoul(pChild->GetText(), NULL, 16);
        }
    }
}


int MoonsSfwFileLoader::GetCRCValue()
{
    return m_CRC;
}

std::vector<PACKETDATA> MoonsSfwFileLoader::GetPackets()
{
    return m_Packets;
}
