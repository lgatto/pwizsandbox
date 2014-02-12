library("mzR")

fml <- "../data//TMT_Erwinia_1uLSike_Top10HCD_isol2_45stepped_60min_01.mzML" 
fmlz <- "../data//TMT_Erwinia_1uLSike_Top10HCD_isol2_45stepped_60min_01_zlib.mzXML"
fxml <- "../data//TMT_Erwinia_1uLSike_Top10HCD_isol2_45stepped_60min_01.mzXML"

xx <- openMSfile(fxml)
hdx <- header(xx)
k <- which(hdx$msLevel == 2)[3000]


x <- openMSfile(fml)
hd <- header(x)
i <- which(hd$msLevel == 2)[3000]

xz <- openMSfile(fmlz)
hdz <- header(xz)
j <- which(hdz$msLevel == 2)[3000]

all.equal(hd[i, ], hdz[j, ])
all.equal(peaks(x, i), peaks(xz, j))

hdz[which(hdz$peaksCount == 2118), ]
