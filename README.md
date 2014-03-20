proteowizard sandbox
====================

Read support and data/metadata extraction is the main goal. The first
type of data that should be tackled is raw mass spectrometry data, in
particular data in the `mzML` format. After that, it would be good to
implement and interface to `mzIdentML` and `mzQuantML`, respectively
used to store identification and quantitation data (more details about
these later).

Write support to any other raw data format would also be of interest. 

See also the [mzR wiki](https://github.com/sneumann/mzR/wiki).

## data

Example data files. The most important file format is
[`mzML`](http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3013463/) and
that's the one efforts should be invested on. This format is the most
complete. The others should also be supported by `MSDataFile::Reader`,
though.

The difference between
`TMT_Erwinia_1uLSike_Top10HCD_isol2_45stepped_60min_01_zlib.mzXML` and
`TMT_Erwinia_1uLSike_Top10HCD_isol2_45stepped_60min_01.mzXML` is that
`zlib` compression has not been applied for the latter. `zlib`
compression has been used for the `mzML` example file. This is not
relevant for `mgf` (only
text). [`mz5`](http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3270111/)
uses the HDF5 format; not sure if the data inside is `zlib`
compressed.

I had issues to push the relatively big data files to github. Instead, 
I have provided links.

## Example codes

If any of the below is not clear and it seems to be essential to
understand the mass spectrometry details to make progress from a
programming point of view, please do not hesitate to ask
questions. You might also want to have a quick read
[here](http://proteome.sysbiol.cam.ac.uk/lgatto/r_projects.html). If
you would like access to any scientific references (not sure if these
would be of any help), please just ask. I will also see if I can find
some helpful introductory material for you.

- Read the `mzML` file and return metadata, including general
  instrument information (manufacturer, model, ionistation, analyser,
  detector) and general run information (number of scans: 7534, MZ
  range: 99.99945 - 2069.279, retention time range: 0.4584 - 3601.983,
  MS levels available in the file: 1 and 2, number of MS1 and MS2
  levels: 1431 MS1 and 6103 MS2). 

- Read the `mzML` data and save it to `mgf`. The opposite would not
  make much sense, as `mzML` contains much more information that the
  latter. Writing to `mz5` and `mzXML` could also be of interest. Not
  possible in current `mzR`.

- Read the `mzML` file and write a new `mzML` that contains only the
  MS1 or MS2 spectra (`ms level`). Not possible in current `mzR`.

- Extract information of the 3000th MS2 spectrum. Below is the
  information extracted with the current version of `mzR`. Also
  extract the actual spectrum data, i.e. MZ and intensities (see
  `./data/p3000.csv` ). 

```
acquisitionNum              4092.0000
msLevel                        2.0000
peaksCount                  2465.0000
totIonCurrent            5368603.0000
retentionTime               2269.6948
basePeakMZ                   129.1391
basePeakIntensity         210466.4531
collisionEnergy               45.0000
ionisationEnergy               0.0000
lowMZ                        100.0012
highMZ                      2069.2793
precursorScanNum            4083.0000
precursorMZ                 1111.0800
precursorCharge                2.0000
precursorIntensity       8771486.0000
```

- Extract a chromatogram. A chromatogram is composed of two vectors of
  the same length, encoding retention time and intensity for a given
  precursor ion defined by a MZ values. This is not directly possible
  currently and chromatograms need to be calculated (which takes some
  time in `R`). I believe it is possible to directly extract such
  chromatograms from `mzML`.

## Ontology terms

You will see many `MS:0000000` terms in the data files. These
represent ontology terms (linked curated vocabulary). At this point,
it might not be critical to take it into account, but it might be good
to keep in mind that this is how the different pieces of information
are officially defined to avoid ambiguities. `pwiz` provides its own
copy of the ontology (see `pwiz/data/common/psi-ms.obo` and similar)
and converters (probably `CVTranslator.*` in the same directory).
