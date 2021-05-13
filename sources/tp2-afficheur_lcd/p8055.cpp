#include "p8055.h"

P8055::P8055(int addcarte)
{
   // QLibrary lib( QDir(QCoreApplication::applicationDirPath()).filePath("K8055D.dll"));
    QLibrary lib( QDir(QApplication::applicationDirPath()).filePath("K8055D.dll"));
    ncarte = -1;
    if (lib.load())
    {
        opendevice = (OpenDevice)lib.resolve("OpenDevice");
        closedevice = (CloseDevice)lib.resolve("CloseDevice");
        setdigitalchannel = (SetDigitalChannel)lib.resolve("SetDigitalChannel");
        cleardigitalchannel = (ClearDigitalChannel)lib.resolve("ClearDigitalChannel");
        writealldigital = (WriteAllDigital)lib.resolve("WriteAllDigital");
        readalldigital = (ReadAllDigital)lib.resolve("ReadAllDigital");
        readdigitalchannel = (ReadDigitalChannel)lib.resolve("ReadDigitalChannel");
        setanalogchannel = (SetAnalogChannel)lib.resolve("SetAnalogChannel");
        clearanalogchannel = (ClearAnalogChannel)lib.resolve("ClearAnalogChannel");
        outputanalogchannel = (OutputAnalogChannel)lib.resolve("OutputAnalogChannel");

        QMessageBox::information(NULL, "Chargement", "Chargement dll réussi");

        ncarte = opendevice(addcarte);
        vals = 0;
        vale = 0;
    }
    else
    {
        QMessageBox::information(NULL, "Chargement", "Chargement dll impossible");

    }

}
//----------------------------------------------------------------------------
P8055::~P8055()
{
    if (ncarte!=-1)
    {
        closedevice();
    }
}
//----------------------------------------------------------------------------
char P8055::P8055_present()
{
        return ncarte;
}
//----------------------------------------------------------------------------
void P8055::clearbit(char val)
{
    if (ncarte!=-1)
    {
        setdigitalchannel(val);
        val = (1<<(val-1));
        vals = vals | val;
    }
}
//----------------------------------------------------------------------------
void P8055::setbit(char val)
{
    if (ncarte!=-1)
    {
        cleardigitalchannel(val);
        val = ~(1<<(val-1)) ;
        vals = vals &  val ;

    }
}
//----------------------------------------------------------------------------
void P8055::val_output(char unsigned val)
{
    vals = ~val;
    if (ncarte!=-1)
    {
        writealldigital(vals);
    }
}
//----------------------------------------------------------------------------
char P8055::get_output( )
{
        return ~vals;
}
//----------------------------------------------------------------------------
char P8055::get_input()
{
    unsigned char x = -1;
    if (ncarte!=-1)
    {
        x = ~ (readalldigital());
    }

    return x;
}
//----------------------------------------------------------------------------
bool P8055::get_bitinput(char val)
{
    //vale = readalldigital();
   // bool nb = (vale >> (val-1))& 0x01;
    bool nb = 1;
    if (ncarte!=-1)
    {
         nb = readdigitalchannel(val);
    }
    return !nb ;

}
//----------------------------------------------------------------------------
void P8055::set_DAC1_5V()
{
    if (ncarte!=-1)
    {
        setanalogchannel(1);
    }
}
//----------------------------------------------------------------------------
void P8055::Clear_DAC1_0V()
{
    if (ncarte!=-1)
    {
        clearanalogchannel(1);
    }
}
//----------------------------------------------------------------------------
void P8055::Cna(char voie, unsigned char data)
{
    if (ncarte!=-1)
    {
        outputanalogchannel(voie,data);
    }
}
//-----------------------------------------------------------------------------
