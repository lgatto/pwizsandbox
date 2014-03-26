#Read the mzML file and return metadata, including general instrument information and general run information
library("mzR")

fml <- "TMT_Erwinia_1uLSike_Top10HCD_isol2_45stepped_60min_01.mzML"
x <- openMSfile(fml)
instrumentInfo(x)
runInfo(x)

#Read the mzML data and save it to mgf
library("MSnbase")
## clean is optional
msnexp <- readMSData(fml, clean=TRUE)
## I don't set the COM and title information, since I don't have much informatin for the experiments
writeMgfData(msnexp)

#Extract information of the 3000th MS2 spectrum
hd <- header(x)
i <- which(hd$msLevel == 2)[3000]
hd[i,]
p3000 <- peaks(x,i)
colnames(p3000) <- c("mz","intensity")
write.csv(p3000, "p3000.csv")

#chromatogram(fml)
