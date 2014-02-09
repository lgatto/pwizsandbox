#include "pwiz/data/msdata/MSDataFile.hpp"
#include "pwiz/data/msdata/LegacyAdapter.hpp"
#include "pwiz/data/common/CVTranslator.hpp"
#include <iostream>


using namespace std;
using namespace pwiz::msdata;
using namespace pwiz::cv;


/**
* Prints 3000th spectrum binary data: mz intensity pairs
*/
int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        try{
            string filename = string(argv[1]);
            MSDataFile msd(filename);

            cout << "\"\",\"mz\",\"intensity\""<<endl;
            
            SpectrumListPtr slp = msd.run.spectrumListPtr;           
            SpectrumPtr s= slp->spectrum(3000, true);
            vector<MZIntensityPair> pairs;
            s->getMZIntensityPairs (pairs);
            for(int i = 1; i <= pairs.size(); i++)
            {
                MZIntensityPair p = pairs.at(i - 1);
                cout << "\""<<i<<"\",\""<< p.mz <<"\",\""<< p.intensity << "\""<<endl;                   
            }
             
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

