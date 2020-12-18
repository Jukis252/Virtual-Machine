#include <iostream>
#include <fstream>

using namespace std;

struct VMCommand
{
    char kaire;
    char desine;
};

int main()
{
    int ats;
    cout << "Pasirinkite varianta: " << endl;
    cout << "1. Pirma uzduotis" << endl;
    cout << "2. Custom!" << endl;
    cin >> ats;
    if (ats == 1)
    {
        fstream decryp;
        ifstream fd("q1_encr.txt");
        decryp.open("decryptor.bin", ios::in | ios::binary);
        char prog_memory[256];
        unsigned char reg[16];
        bool eofflag = false;
        bool zeroflag = false;

        for (int i = 0; i < 256; i++)
        {
            decryp >> noskipws >> prog_memory[i];
            if (decryp.eof())
            {
                break;
            }
        }
        decryp.close();

        VMCommand* Registrai;
        Registrai = (VMCommand*)prog_memory;
        int iReg1, iReg2;
        bool VM_work = true;
        while (VM_work)
        {

            iReg1 = Registrai->desine & 0x0F;
            iReg2 = (Registrai->desine & 0xF0) >> 4;
            switch (Registrai->kaire)
            {
            case 0x01:
                reg[iReg1]++;
                break;
            case 0x02:
                reg[iReg1]--;
                break;
            case 0x03:
                reg[iReg1] = reg[iReg2];
                break;
            case 0x04:
                reg[0] = Registrai->desine;
                break;
            case 0x05:
                reg[iReg1] = reg[iReg1] << 1;
                break;
            case 0x06:
                reg[iReg1] = reg[iReg1] >> 1;
                break;
            case 0x07:
                Registrai = (VMCommand*)((char*)Registrai + Registrai->desine);
                Registrai--;
                break;
            case 0x09:
                if (eofflag == false)
                {
                    Registrai = (VMCommand*)((char*)Registrai + Registrai->desine);
                    Registrai--;
                }
                break;
            case 0x0A:
                if (eofflag == true)
                {
                    Registrai = (VMCommand*)((char*)Registrai + Registrai->desine);
                    Registrai--;
                }
                break;
            case 0x0B:
                fd.close();
                VM_work = false;
                break;
            case 0x0C:
                reg[iReg1] = reg[iReg1] + reg[iReg2];
                break;
            case 0x0D:
                reg[iReg1] = reg[iReg1] - reg[iReg2];
                break;
            case 0x0E:
                reg[iReg1] = reg[iReg1] ^ reg[iReg2];
                break;
            case 0x0F:
                reg[iReg1] = reg[iReg1] | reg[iReg2];
                break;
            case 0x10:
                fd >> reg[iReg1];
                if (fd.eof()) 
                {
                    eofflag = true;
                }
                break;
            case 0x11:
                cout << (char)reg[iReg1];
                break;
            }
            Registrai++;
        }
    }
	else if (ats == 2)
	{
        fstream decryp;
        ifstream fd("rez.txt");
        decryp.open("decryptor1.bin", ios::in | ios::binary);
        char prog_memory[256];
        unsigned char reg[16];
        bool eofflag = false;
        bool zeroflag = false;

        for (int i = 0; i < 256; i++)
        {
            decryp >> noskipws >> prog_memory[i];
            if (decryp.eof())
            {
                break;
            }
        }
        decryp.close();
        VMCommand* Registrai;
        Registrai = (VMCommand*)prog_memory;
        int iReg1, iReg2;
        bool VM_work = true;
        ofstream fr("rez1.txt");
        while (VM_work)
        {

            iReg1 = Registrai->desine & 0x0F;
            iReg2 = (Registrai->desine & 0xF0) >> 4;
            switch (Registrai->kaire)
            {
            case 0x01:
                reg[iReg1]++;
                break;
            case 0x02:
                reg[iReg1]--;
                break;
            case 0x03:
                reg[iReg1] = reg[iReg2];
                break;
            case 0x04:
                reg[0] = Registrai->desine;
                break;
            case 0x05:
                reg[iReg1] = reg[iReg1] << 1;
                break;
            case 0x06:
                reg[iReg1] = reg[iReg1] >> 1;
                break;
            case 0x07:
                Registrai = (VMCommand*)((char*)Registrai + Registrai->desine);
                Registrai--;
                break;
            case 0x08:
                if (eofflag == true)
                {
                    Registrai = (VMCommand*)((char*)Registrai + Registrai->desine);
                    Registrai--;
                }
                break;
            case 0x09:
                if (eofflag == false)
                {
                    Registrai = (VMCommand*)((char*)Registrai + Registrai->desine);
                    Registrai--;
                }
                break;
            case 0x0A:
                if (eofflag == true)
                {
                    Registrai = (VMCommand*)((char*)Registrai + Registrai->desine);
                    Registrai--;
                }
                break;
            case 0x0B:
                fd.close();
                VM_work = false;
                break;
            case 0x0C:
                reg[iReg1] = reg[iReg1] + reg[iReg2];
                break;
            case 0x0D:
                reg[iReg1] = reg[iReg1] - reg[iReg2];
                break;
            case 0x0E:
                reg[iReg1] = reg[iReg1] ^ reg[iReg2];
                break;
            case 0x0F:
                reg[iReg1] = reg[iReg1] | reg[iReg2];
                break;
            case 0x10:
                fd >> reg[iReg1];
                if (fd.eof())
                {
                    eofflag = true;
                }
                break;
            case 0x11:
                fr << (char)reg[iReg1];
                break;
            }
            Registrai++; 
		}
        fr.close();
	}
    else
    {
        exit;
    }

    
}
