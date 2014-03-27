/*
 * mgf-test.cpp
 *
 *  Created on: Mar 27, 2014
 *
 *  Author: Qiang Kou
 *
 *  qkou@umail.iu.edu
 */

#include "pwiz/data/msdata/SpectrumList_MGF.hpp"
#include "pwiz/data/msdata/TextWriter.hpp"
#include "pwiz/utility/minimxml/XMLWriter.hpp"
#include "pwiz/utility/misc/unit.hpp"
#include "pwiz/utility/misc/Std.hpp"

#include <iostream>

using namespace pwiz::cv;
using namespace pwiz::msdata;
using namespace pwiz::util;
using namespace pwiz::minimxml;

int main(int argc, char* argv[]) {

  ifstream file("55merge.mgf");
  file.seekg(0, file.end);
  int length = file.tellg();
  file.seekg(0, file.beg);

  char * buffer = new char[length];

  file.read(buffer, length);

  shared_ptr<istream> is(new istringstream(buffer));

  MSData msDataTest;

  msDataTest.instrumentConfigurationPtrs.push_back(
      InstrumentConfigurationPtr(new InstrumentConfiguration("LCQDeca")));

  msDataTest.instrumentConfigurationPtrs.back()->cvParams.push_back(
      MS_LCQ_Deca);

  msDataTest.instrumentConfigurationPtrs.back()->userParams.push_back(
      UserParam("doobie", "420"));

  SpectrumListPtr sl = SpectrumList_MGF::create(is, msDataTest);
  cout << sl->size() << endl;

  IndexList list = sl->findSpotID("55.651.651.4.dta");
  cout << list.size() << endl;
  SpectrumPtr s = sl->spectrum(list[0], true);
  cout << s->cvParam(MS_ms_level).valueAs<int>() << endl;
  cout << s->defaultArrayLength << endl;
  cout << s->sourceFilePosition << endl;
  cout << s->cvParam(MS_base_peak_m_z).valueAs<double>() << endl;
  cout << s->cvParam(MS_base_peak_intensity).valueAs<double>() << endl;
  cout
      << s->precursors[0].selectedIons[0].cvParam(MS_selected_ion_m_z)
          .valueAs<double>()
      << endl;

  cout << s->precursors[0].selectedIons[0].cvParam(MS_charge_state).value
       << endl;
}

