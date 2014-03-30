/*
 * mzML-read.cpp
 *
 * Created on: Mar 29, 2014
 *
 * Author: Qiang Kou
 *
 * qkou@umail.iu.edu
 */

#include "pwiz/data/msdata/MSDataFile.hpp"
#include "pwiz/data/msdata/LegacyAdapter.hpp"
#include "pwiz/data/common/CVTranslator.hpp"
#include "pwiz/utility/misc/Std.hpp"

using namespace pwiz::msdata;

int main(int argc, char* argv[]) {

  MSDataFile msd(argv[1]);

  vector<InstrumentConfigurationPtr> icp = msd.instrumentConfigurationPtrs;

  for (size_t i = 0; i < icp.size(); i++) {
    CVTranslator cvTranslator;
    LegacyAdapter_Instrument adapter(*icp[i], cvTranslator);
    cout << adapter.manufacturer() << endl;
    cout << adapter.model() << endl;
    cout << adapter.ionisation() << endl;
    cout << adapter.detector() << endl;
    cout << adapter.analyzer() << endl;
  }
  cout << endl;

  SpectrumListPtr slp = msd.run.spectrumListPtr;
  cout << "SpectrumList size: " << slp->size() << endl;

  double mzLow = slp->spectrum(0, DetailLevel_FullMetadata)->cvParam(
      MS_lowest_observed_m_z).valueAs<double>();

  double mzHigh = slp->spectrum(0, DetailLevel_FullMetadata)->cvParam(
      MS_highest_observed_m_z).valueAs<double>();

  map<int, int> msLevels;

  for (size_t i = 0; i < slp->size(); i++) {
    SpectrumPtr s = slp->spectrum(i, DetailLevel_FullMetadata);

    if (s->cvParam(MS_lowest_observed_m_z).valueAs<double>() < mzLow) {
      mzLow = s->cvParam(MS_lowest_observed_m_z).valueAs<double>();
    }
    if (s->cvParam(MS_highest_observed_m_z).valueAs<double>() > mzHigh) {
      mzHigh = s->cvParam(MS_highest_observed_m_z).valueAs<double>();
    }

    cout << "Spectrum " << i + 1 << ": MS"
         << s->cvParam(MS_ms_level).valueAs<int>() << endl;
  }
  cout << endl;
  cout << "MZ range:" << mzLow << " - " << mzHigh << endl;
}

