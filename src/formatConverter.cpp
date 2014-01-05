#include "pwiz/data/msdata/Serializer_MGF.hpp"
#include "pwiz/data/msdata/Serializer_MZ5.hpp"
#include "pwiz/data/msdata/Serializer_mzXML.hpp"
#include "pwiz/data/msdata/MSDataFile.hpp"
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>

using namespace boost::filesystem;
using namespace std;
using namespace pwiz::msdata;

/**
*   converts mzML files to mgf, mz5 and mzXML
*   converted files are written to the current dir
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

            // create the MSData object in memory
            MSDataFile mzMLmsd(inFile);

            //MGF file  
            string mgfOutFile = outPath.replace_extension(".out.mgf").string();
            cout << "MGF output file: " << mgfOutFile << endl;
            std::ofstream* mgfOutFileP = new std::ofstream(mgfOutFile); 
            Serializer_MGF serializerMGF;
            serializerMGF.write(*mgfOutFileP, mzMLmsd);  
            mgfOutFileP->flush();
            mgfOutFileP->close();

            //mz5 file        
            string mz5OutFile = outPath.replace_extension(".out.mz5").string();
            cout << "mz5 output file: " << mz5OutFile << endl;
            Serializer_mz5 serializerMz5;
            serializerMz5.write(mz5OutFile, mzMLmsd);

            //mzXML file
            string mzXMLOutFile = outPath.replace_extension(".out.mzXML").string();
            cout << "mzXML output file: " << mzXMLOutFile << endl;
            std::ofstream* mzXMLOutFileP = new std::ofstream(mzXMLOutFile); 
            Serializer_mzXML::Config config;
            //what is the appropriate configuration?
            config.binaryDataEncoderConfig.compression = BinaryDataEncoder::Compression_Zlib;
            config.binaryDataEncoderConfig.precision = BinaryDataEncoder::Precision_32;

            Serializer_mzXML serializerMzXML(config);
            serializerMzXML.write(*mzXMLOutFileP, mzMLmsd);

        }
        catch(exception& e)
        {
            cout << "Exception occured: " << e.what() << endl;       
        }
    }
    else
    {
        cout << "Specify input mzML file" << endl; 
    }
    return 0;
}    