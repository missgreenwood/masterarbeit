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
par(mar=c(5.1,5.1,4.1,2.1))
plot(QFNN256, CPUTimeUList, col="darkolivegreen3", xlab="Query-Filter", ylab="CPU-Zeit in µs", xlim=c(0, 9), ylim=c(0, 2000), type="p", pch=16, xaxt="n", yaxs="i", cex.lab=1.5, cex.axis=1.5, cex=1.5)
lines(QFNN256, CPUTimeBFTree, col="dodgerblue3", type="p", pch=16, cex=1.5)
axis(1, at=0:9, labels=lablist, cex.lab=1.5, cex.axis=1.5)
legend(4,1890, c("k=1, Filtergröße 256", "Unsortierte Liste", "BloomFilterTree"), cex=1.5, pch=16, col=c("white","darkolivegreen3","dodgerblue3")) 
l256 <- c(CPUTimeUList)
b256 <- c(CPUTimeBFTree)
pdf('/Users/judith/Documents/MA/evaluation/percent_time_nn_256.pdf')
par(mar=c(5.1,5.1,4.1,2.1))
plot(percent_time(l256, b256), col="darkcyan", xlab="Query-Filter", ylab="CPU-Zeit prozentual ggü. unsortierter Liste", xlim=c(1, 10), ylim=c(0,100), type="p", pch=16, xaxt="n", yaxs="i", cex.lab=1.5, cex.axis=1.5, cex=1.5)
axis(1, at=1:10, labels=lablist, cex.lab=1.5, cex.axis=1.5)
legend(6,85, c("k=1","Filtergröße 256"), cex=1.5) 
detach(cputimenn_256)

cputimenn_512 <- read.csv("/Users/judith/Documents/MA/src/src/cputime_nn_512.csv", sep=",")
attach(cputimenn_512)
pdf('/Users/judith/Documents/MA/evaluation/cputime_nn_512.pdf')
par(mar=c(5.1,5.1,4.1,2.1))
plot(QFNN512, CPUTimeUList, col="darkolivegreen3", xlab="Query-Filter", ylab="CPU-Zeit in µs", xlim=c(0, 9), ylim=c(0, 2000), type="p", pch=16, xaxt="n", yaxs="i", cex.lab=1.5, cex.axis=1.5, cex=1.5)
lines(QFNN512, CPUTimeBFTree, col="dodgerblue3", type="p", pch=16, cex=1.5)
axis(1, at=0:9, labels=lablist, cex.lab=1.5, cex.axis=1.5)
legend(4,1890, c("k=1, Filtergröße 512", "Unsortierte Liste", "BloomFilterTree"), cex=1.5, pch=16, col=c("white","darkolivegreen3","dodgerblue3"))
l512 <- c(CPUTimeUList)
b512 <- c(CPUTimeBFTree)
pdf('/Users/judith/Documents/MA/evaluation/percent_time_nn_512.pdf')
par(mar=c(5.1,5.1,4.1,2.1))
plot(percent_time(l512, b512), col="darkcyan", xlab="Query-Filter", ylab="CPU-Zeit prozentual ggü. unsortierter Liste", xlim=c(1, 10), ylim=c(0,100), type="p", pch=16, xaxt="n", yaxs="i", cex.lab=1.5, cex.axis=1.5, cex=1.5)
axis(1, at=1:10, labels=lablist, cex.lab=1.3, cex.axis=1.5)
legend(6,85, c("k=1","Filtergröße 512"), cex=1.5)
detach(cputimenn_512)