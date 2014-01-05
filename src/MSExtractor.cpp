

#include "pwiz/data/msdata/MSDataFile.hpp"
#include "pwiz/analysis/spectrum_processing/SpectrumListFactory.hpp"
#include <boost/filesystem.hpp>
#include <iostream>

using namespace boost::filesystem;
using namespace std;
using namespace pwiz::msdata;
using namespace pwiz::analysis;


/**
* Creates 2 mzML from source  mzML one constains MS1 spectra and the other MS2
* Created files: inFileName.ms1.mzml and infileName.ms2.mzML in the working dir 
*/
int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        try
        {   
            path outDir(".");
            string inFile = string(argv[1]);
            cout << "Input file: " << inFile << endl;
            path filePath(inFile);
            string fileName = filePath.filename().string();            
            path outPath = outDir/ fileName;
            MSDataFile msdMS1(inFile);
            MSDataFile::WriteConfig writeConfig;
            // what is the appropriate write configuration? 
            /* Part of the config from msconvert tool:
            writeConfig.binaryDataEncoderConfig.precision = BinaryDataEncoder::Precision_64;
            writeConfig.binaryDataEncoderConfig.precisionOverrides[MS_m_z_array] = BinaryDataEncoder::Precision_64;
            writeConfig.binaryDataEncoderConfig.precisionOverrides[MS_intensity_array] = BinaryDataEncoder::Precision_32;*/
            SpectrumListFactory::wrap(msdMS1, "msLevel 1");
            string ms1OutFile = outPath.replace_extension(".out.ms1.mzML").string();
            cout << "mzXML with MS1 spectra: " << ms1OutFile << endl;
            MSDataFile::write(msdMS1, ms1OutFile, writeConfig);


            MSDataFile msdMS2(inFile);  
            SpectrumListFactory::wrap(msdMS2, "msLevel 2");
            outPath = outDir/ fileName; // reset the out path
            string ms2OutFile = outPath.replace_extension(".out.ms2.mzML").string();
            cout << "mzXML with MS2 spectra: " << ms2OutFile << endl;
            MSDataFile::write(msdMS2,ms2OutFile, writeConfig);
        }
        catch(exception &e)
        {
            cout << "Exception occured: "  << e.what() << endl;
        }
    }
    else
    {
        cout << "Specify input mzML file" << endl; 
    }
    return 0;
}

