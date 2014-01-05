

#include "pwiz/data/msdata/MSDataFile.hpp"
#include "pwiz/data/msdata/LegacyAdapter.hpp"
#include "pwiz/data/common/CVTranslator.hpp"
#include <iostream>
#include<limits>

using namespace std;
using namespace pwiz::msdata;



/**
* Reads metadata from mzML files
*/
int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        try{
            string filename = string(argv[1]);
            MSDataFile msd(filename);
            vector<InstrumentConfigurationPtr> icp = msd.instrumentConfigurationPtrs;
            for(vector<InstrumentConfigurationPtr>::iterator iter = icp.begin(); iter != icp.end(); ++iter)
            {
                cout << "Instrument Configuration: "<<endl;
                CVTranslator cvTranslator;
                LegacyAdapter_Instrument adapter(**iter, cvTranslator);
                cout << "Manufacturer:\t"<<adapter.manufacturer ()<<endl;
                cout << "Model:\t"<<adapter.model()<<endl;
                cout << "Ionisation:\t"<<adapter.ionisation ()<<endl;
                cout<< "Detector:\t"<<adapter.detector()<<endl;
                cout<< "Analyzer:\t"<<adapter.analyzer()<<endl<<endl;
            }

            cout << "General run information:"<<endl;
            int noScans = 0;
            SpectrumListPtr slp = msd.run.spectrumListPtr;
            cout <<"SpectrumList size "<<  slp->size() << endl; // does this value represent the number of scans?
            double mzLow = std::numeric_limits<double>::max();
            double mzHigh = numeric_limits<double>::min();
            map<int, int> msLevels;
            
            for(int i = 0; i < slp->size(); i++)
            {
                SpectrumPtr s= slp->spectrum(i, DetailLevel_FullMetadata);
                noScans+=s->scanList.scans.size();

                if(s->cvParam(MS_lowest_observed_m_z).valueAs<double>() < mzLow)
                {
                    mzLow=s->cvParam(MS_lowest_observed_m_z).valueAs<double>();
                }
                if(s->cvParam(MS_highest_observed_m_z).valueAs<double>() > mzHigh)
                {
                    mzHigh=s->cvParam(MS_highest_observed_m_z).valueAs<double>();
                }
                int msLevel = s->cvParam(MS_ms_level).valueAs<int>();
                map<int, int>::iterator iter = msLevels.find(msLevel);
                if (iter != msLevels.end() )
                {
                    int count=iter->second++;
                    msLevels.insert(pair<int,int>(msLevel, count));
                }
                else
                {
                    msLevels.insert(pair<int,int>(msLevel, 1));
                }
            }
            cout << "MZ range:\t" <<mzLow<<" - "<<mzHigh<<endl;
            cout << "MS levels available:\t";
            stringstream ss;
            for(map<int,int>::iterator iter = msLevels.begin(); iter != msLevels.end(); ++iter)
            {
                cout << iter->first << " ";        
                ss << iter->second << " MS" <<iter->first<<endl;      
            }
            cout <<endl << ss.str();  
            cout << "Number of scans:\t" << noScans << endl;
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

