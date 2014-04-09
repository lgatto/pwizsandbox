#Project title: Extending mzR

Extending capabilities of mzR by adding support for the proteowizard project

URL of project idea page: http://rwiki.sciviews.org/doku.php?id=developers:projects:gsoc2014:bio-mzr

#Background:

## mzData/mzXML/mzML and mzIdentML format

mzData/mzXML/mzML formats are all used to store the information on spectra and metadata. mzData was the first attempt by the Proteomics Standards Initiative from the Human Proteome Organization to create a standardized format for Mass Spectrometry data. This format is now deprecated, and replaced by mzML.

mzXML is a XML-based common file format for proteomics mass spectrometric data. This format was developed at the Seattle Proteome Center/Institute for Systems Biology while the HUPO-PSI was trying to specify the standardized mzData format, and is still in use in the proteomics community.

mzML is a joint effort set by HUPO-PSI, the SPC/ISB and instrument vendors to create a unified standard borrowing the best aspects of both mzData and mzXML, and intended to replace them. 

All the mass spectrometry file formats are organized similarly, where a set of metadata nodes about the run is followed by a list of spectra with the actual masses and intensities. In addition, each of these spectra has its own set of metadata, such as the retention time and acquisition parameters.

The mzIdentML format stores peptide and protein identifications based on mass spectrometry and captures metadata about methods, parameters, and quality metrics. Data are represented through a collection of protein sequences, peptide sequences (with modifications), and structures for capturing the scores associated with ranked peptide matches for each spectrum searched.

## Ramp and pwiz::msdata

The existing backend RAMP to read mzData and mzXML via the ISB RAMP parser (http://tools.proteomecenter.org/).

This backend can also read mzML through the proteowizard RAMPadapter around the proteowizard infrastructure, but this interface is limited to the lowest common denominator between the mzXML/mzData/mzML formats.

In the pwiz::msdata, the complete support for mzXML and mzML format is provided through two classes, pwiz::msdata::Reader_mzXML and pwiz::msdata::Reader_mzML respectively. The replacement of the backend will provide users more complete access to information stored in the file.

## pwiz::identdata

pwiz::identdata class pwiz library provides the support for accessing the peptide-spectrum-match information stored in mzIdentML format, which is not available in mzR.

#Bio of Student

I got my undergraduate degree in biotechnology and statistics in China. And now I am a PhD student in Informatics, and my research field is the data analysis and software development for top-down mass spectrometry.

The extending of mzR package requires two parts of background, R/Rcpp and understanding of mass spectra data.

For the R/Rcpp part, I have used R for three years and I will be using R during my PhD study. I am the Chinese translator of Dirk's Rcpp book and other documents on Rcpp. Also I have translated some documents on parallel computing in R language. So I think I have a good understanding of using Rcpp for development.

For mass spectra, it is my research topic for my PhD life. The file formats mzR dealing with are the formats I analyse everyday. So I think I am really familiar with these kinds of things.

#CONTACT INFORMATION

Student name: Qiang Kou

Email(s): qkou1989@gmail.com OR qkou@umail.iu.edu

#MENTORS

Mentor names: Laurent Gatto, Steffen Neuman, Dirk Eddelbuettel. 

Mentor emails: lg390@cam.ac.uk, sneumann@ipb.halle.de 

Mentor link_ids: lgatto, sneumann

# CODING PLAN & METHODS

## Perceived obstacles

The main obstacle in this project is to use an R reference class as an interface to the C++ implementation using Rcpp modules. There is already such an interface using Rcpp modules to the Ramp infrastructure. While simpler than proteowizard, it should prove a helpful template to get started.

## Critical objectives.

First, extending mzR on raw data and meta-data accession using the proteowizard "msdata" object type. To be more specific, the reading part in mzR has been implemented using the older Ramp code. So one of our objectives is to provide support XML-based formats function using the proteowizard code base.

Second, implementing support mzIdentML format by using the "identdata" from proteowizard.

## Methods of evaluating success or problems as coding progresses.

Since I am working in a mass spectra lab, I have enough data for my testing. Also, we have Java library and C++ library with similar functions, so the results of mzR can be tested. 

Also test files for development will be provided by mentors to facilitate the development of unit tests.

## TIMELINE

There are two main objectives for this project: one is support for raw data, mz(X)ML format through "msdata" type; the other is support for mzIdentML format through "identdata" type.

And the existing support for raw data has been implemented using Ramp code and can be used as a working example for study. So I will work on this part before the mid-evaluation and study the available code as template.

Then I will implement the reading and writing support for mzIdentML format after the mid-evaluation.

I have travel plan to China, so I will adjust the plan a little.

**21 April-30 April**: document reading, getting familiar with Reference class and Rcpp module in package development. The existing backend mzRramp in mzR will be used as the main study material.

**1 May-7 May**: I have finals during the time, so I have to focus on the exams.

**9 May-20 May**: Implementing the writing support for mzML file.

**21 May-31 May**: Travel to China. I will still be working, however, not full time.

**1 June-16 June**: Implementing the writing support for mzML file and testing on real files.

**17 June-23 June**: Make sure the part I have implemented can pass the R CMD check, so it can be added into mzR. Also writing documents for this part of work.

**24 June-10 July**: Reading support for mzIdentML format.

**11 July-15 July**: Testing and documents for the reading part.

**16 July-2 August**: Writing support for mzIdentML format.

**3 August-11 August**: Testing and documents. Make sure the mzR can pass the R CMD check. If we have time, we will also update the related pacakges, such as MSnbase.

##MANAGEMENT OF CODING PROJECT

We will use the github for management.

First, I will fork the project, add new functions and classes;

Second, when I finish one class and pass the unit testing, the code will be merged back to the project.

In my own repo, I will commit code everyday. It will be merged into the mainstream when passing unit testing.
