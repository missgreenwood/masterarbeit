#!/usr/local/bin/Rscript

t <- "Speicherverbrauch für Datenstrukturen"
compl <- read.csv("/Users/judith/Documents/MA/src/src/compl.csv", sep=",")
attach(compl)
compl2 <- as.matrix(compl)
pdf('/Users/judith/Documents/MA/evaluation/compl.pdf')
barplot(mem2, ylab="Speicherverbrauch in Bytes", main="Speicherverbrauch für Datenstrukturen", col=c("darkolivegreen3", "dodgerblue3"), beside=TRUE, ylim=c(0,300000), names.arg=c("Filtergröße 256", "Filtergröße 512", "Filtergröße 256", "Filtergröße 512"))
detach(mem)
