

#include "pwiz/data/msdata/MSDataFile.hpp"
#include "pwiz/data/msdata/LegacyAdapter.hpp"
#include "pwiz/data/common/CVTranslator.hpp"
#include <iostream>


using namespace std;
using namespace pwiz::msdata;
using namespace pwiz::cv;


/**
* Prints all chromatograms: time intensity pairs
*/
int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        try{
          
            string filename = string(argv[1]);
            MSDataFile msd(filename);

            cout << "\"\", \"time\",\"intensity\""<<endl;
           
            ChromatogramListPtr clp = msd.run.chromatogramListPtr;
            
            for(int ci = 0; ci < clp->size(); ci++){
                ChromatogramPtr c = clp->chromatogram(ci, true);  
               
                vector<TimeIntensityPair> pairs;
                c->getTimeIntensityPairs (pairs);
                
                for(int i =1; i <= pairs.size(); i++)
                 {
                    TimeIntensityPair p = pairs.at(i-1);
                    cout << "\""<<i<<"\", \""<< p.time <<"\",\""<< p.intensity << "\""<<endl;                   
                }
                cout << endl;
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

