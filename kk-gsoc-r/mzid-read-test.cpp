/*
 *  mzid-read-test.cpp
 *
 *  Created on: Mar 26, 2014
 *
 *  Author: Qiang Kou
 *
 *  qkou@umail.iu.edu
 */

#include "pwiz/data/identdata/IdentDataFile.hpp"
#include "pwiz/data/identdata/DefaultReaderList.hpp"
#include "pwiz/data/identdata/IO.hpp"
#include "pwiz/utility/misc/Std.hpp"

using namespace pwiz::identdata;

int main(int argc, char* argv[])
{

    try
    {
        if (argc == 2)
        {

            cout << "Reading the file " << argv[1] << endl;
            IdentDataFile mzid(argv[1]);
            cout << "Creation Date:\t" << mzid.creationDate << endl;
            cout << "File provider:\t" << mzid.provider.contactRolePtr.get()->name()
                 << endl << endl;
            vector<AnalysisSoftwarePtr> as = mzid.analysisSoftwareList;
            cout << "Analysis software used:" << endl;
            for (size_t i = 0; i < as.size(); i++)
            {
                cout << "\t" << as[i]->name << " v" << as[i]->version;
                cout << "\t" << as[i]->contactRolePtr->contactPtr->name << endl;
            }
            cout << endl;

            cout << "Database searched:" << endl;

            vector<SearchDatabasePtr> sdb = mzid.dataCollection.inputs.searchDatabase;

            for (size_t i = 0; i < sdb.size(); i++)
            {
                cout << "\t" << sdb[i]->name << " (" << sdb[i]->numDatabaseSequences
                     << " sequences)" << endl;
            }
            cout << endl;

            vector<SpectrumIdentificationProtocolPtr> sip = mzid
                    .analysisProtocolCollection.spectrumIdentificationProtocol;
            cout << "Modification used in the searching:";
            vector<SearchModificationPtr> sm = sip[0]->modificationParams;
            for (size_t i = 0; i < sm.size(); i++)
            {
                cout << "\tmass:" << sm[i]->massDelta;
                cout << ";residues:";
                for (size_t j = 0; j < sm[i]->residues.size(); j++)
                {
                    cout << sm[i]->residues[j];
                }
                cout << endl;
            }
            cout << endl;
            vector<EnzymePtr> enz = sip[0]->enzymes.enzymes;
            cout << "Enzymes used:" << endl;
            for (size_t i = 0; i < enz.size(); i++)
            {
                cout << "\tID: " << enz[0]->id;
                cout << " missed cleavages: " << enz[0]->missedCleavages << endl;
            }
            cout << endl;
            cout << "Spectra Data Information:" << endl;
            vector<SpectraDataPtr> sd = mzid.dataCollection.inputs.spectraData;
            for (size_t i = 0; i < sd.size(); i++)
            {

                cout << "\tFile format: " << sd[i]->fileFormat.name();
                cout << " location: " << sd[i]->location << endl;
            }
            cout << endl;

            vector<PeptidePtr> pep = mzid.sequenceCollection.peptides;
            cout << "Peptide sequence information:" << endl;
            for (size_t i = 0; i < pep.size(); i++)
            {
                cout << "\t" << pep[i]->peptideSequence << "\t";

                if (pep[i]->modification.size() != 0)
                {
                    cout << "Modification ";
                    for (size_t j = 0; j < pep[i]->modification.size(); j++)
                    {
                        cout << "mass:" << pep[i]->modification[j]->monoisotopicMassDelta
                             << ";location:" << pep[i]->modification[j]->location << ";";
                    }
                }
                cout << endl;
            }

        }

        else
        {
            cout << "Specify input mzid file" << endl;
        }

    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }
    catch (...)
    {
        cout << "Unknown exception." << endl;
    }

}
