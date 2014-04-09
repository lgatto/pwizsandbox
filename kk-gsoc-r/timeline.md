##TIMELINE

There are two main objectives for this project: one is support for raw data, mz(X)ML format through "msdata" type; the other is support for mzIdentML format through "identdata" type.

And the existing support for raw data has been implemented using Ramp code and can be used as a working example for study. So I will work on this part before the mid-evaluation and study the available code as template.

Then I will implement the reading and writing support for mzIdentML format after the mid-evaluation.

I have travel plan to China, so I will adjust the plan a little.

**21 April - 30 April**: document reading, getting familiar with Reference class and Rcpp module in package development. The existing backend mzRramp in mzR will be used as the main study material.

1 May - 7 May: I have finals during the time, so I have to focus on the exams.

9 May - 20 May: Implementing the reading support for mzML file.

21 May - 31 May: Travel to China. I will still be working, however, not full time.

1 June - 16 June: Implementing the reading support for mzML file and testing on real files.

17 June - 23 June: Make sure the part I have implemented can pass the R CMD check, so it can be added into mzR. Also writing documents for this part of work.

24 June - 10 July: Reading support for mzIdentML format.

11 July - 15 July: Testing and documents for the reading part.

16 July - 2 August: Writing support for mzIdentML format.

3 August - 11 August: Testing and documents. Make sure the mzR can pass the R CMD check. If we have time, we will also update the related pacakges, such as MSnbase.
