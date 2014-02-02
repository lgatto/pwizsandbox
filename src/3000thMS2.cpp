

#include "pwiz/data/msdata/MSDataFile.hpp"
#include "pwiz/data/msdata/LegacyAdapter.hpp"
#include "pwiz/data/common/CVTranslator.hpp"
#include <iostream>
#include<limits>

using namespace std;
using namespace pwiz::msdata;


void printCvParams(std::vector<CVParam> cvParams)
{

    for (std::vector<CVParam>::iterator it = cvParams.begin() ; it != cvParams.end(); ++it){
        CVParam cvp = *it;
        if(!cvp.value.empty())
            cout << cvp.name() <<": " << cvp.value << endl;
    }
}
/**
* Reads info about 3000th MS2 spectrum
*/
int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        try{
            string filename = string(argv[1]);
            MSDataFile msd(filename);

            cout << "3000th MS2 spectra information:"<<endl;

            SpectrumListPtr slp = msd.run.spectrumListPtr;
            SpectrumPtr s = slp->spectrum(3000, DetailLevel_FullMetadata);
            int msLevel = s->cvParam(MS_ms_level).valueAs<int>();
            if(msLevel == 2){
                std::vector<CVParam> allcvParams= s->cvParams;
                printCvParams(allcvParams);
                std::vector<Precursor> allprecursors = s->precursors;
                for (std::vector<Precursor>::iterator it = allprecursors.begin() ; it != allprecursors.end(); ++it){
                    Precursor p = *it;
                    std::vector<SelectedIon> 	allselectedIons = p.selectedIons;
                    for (std::vector<SelectedIon>::iterator itt = allselectedIons.begin() ; itt != allselectedIons.end(); ++itt){
                        SelectedIon i = *itt;
                        printCvParams(i.cvParams);
                    }
                    cout<< endl << "Activation" <<endl;
                    printCvParams(p.activation.cvParams);
                    cout << endl << "Isolation window " << endl;
                    printCvParams(p.isolationWindow.cvParams);

                }
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

