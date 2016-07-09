#!/usr/local/bin/Rscript

percent_time = function(list, bftree) {bftree/(list/100)}
lablist <- as.vector(0:9)
t <- "CPU-Zeit für k-nächste-Nachbarn-Suche"
s256 <- "k=1, Filtergröße 256"
sub256 <- list(s256, col="black", cex=0.9)
s512 <- "k=1, Filtergröße 512"
sub512 <- list(s512, col="black", cex=0.9)

cputimenn_256 <- read.csv("/Users/judith/Documents/MA/src/src/cputime_nn_256.csv", sep=",")
attach(cputimenn_256)
pdf('/Users/judith/Documents/MA/evaluation/cputime_nn_256.pdf')
plot(QFNN256, CPUTimeUList, col="darkolivegreen3", xlab="Query-Filter", ylab="CPU-Zeit in µs", xlim=c(0, 9), ylim=c(0, 1900), type="p", pch=16, xaxt="n", yaxs="i")
lines(QFNN256, CPUTimeBFTree, col="dodgerblue3", type="p", pch=16)
axis(1, at=0:9, labels=lablist)
text(8.37, 785, "Unsortierte Liste", cex=0.75)
text(8.4, 390, "BloomFilterTree", cex=0.75)
title(main=t, line=3)
title(sub256)
l256 <- c(CPUTimeUList)
b256 <- c(CPUTimeBFTree)
pdf('/Users/judith/Documents/MA/evaluation/percent_time_nn_256.pdf')
plot(percent_time(l256, b256), col="darkcyan", xlab="Query-Filter", ylab="CPU-Zeit prozentual ggü. unsortierter Liste", xlim=c(1, 10), ylim=c(0,100), type="p", pch=16, xaxt="n", yaxs="i", cex.lab=1.3, cex.axis=1.3)
axis(1, at=1:10, labels=lablist, cex.lab=1.3, cex.axis=1.3)
detach(cputimenn_256)

cputimenn_512 <- read.csv("/Users/judith/Documents/MA/src/src/cputime_nn_512.csv", sep=",")
attach(cputimenn_512)
pdf('/Users/judith/Documents/MA/evaluation/cputime_nn_512.pdf')
plot(QFNN512, CPUTimeUList, col="darkolivegreen3", xlab="Query-Filter", ylab="CPU-Zeit in µs", xlim=c(0, 9), ylim=c(0, 1500), type="p", pch=16, xaxt="n", yaxs="i")
lines(QFNN512, CPUTimeBFTree, col="dodgerblue3", type="p", pch=16)
axis(1, at=0:9, labels=lablist)
text(8.37, 1300, "Unsortierte Liste", cex=0.75)
text(8.4, 950, "BloomFilterTree", cex=0.75)
title(main=t, line=3)
title(sub512)
l512 <- c(CPUTimeUList)
b512 <- c(CPUTimeBFTree)
pdf('/Users/judith/Documents/MA/evaluation/percent_time_nn_512.pdf')
plot(percent_time(l512, b512), col="darkcyan", xlab="Query-Filter", ylab="CPU-Zeit prozentual ggü. unsortierter Liste", xlim=c(1, 10), ylim=c(0,100), type="p", pch=16, xaxt="n", yaxs="i", cex.lab=1.3, cex.axis=1.3)
axis(1, at=1:10, labels=lablist, cex.lab=1.3, cex.axis=1.3)
detach(cputimenn_512)