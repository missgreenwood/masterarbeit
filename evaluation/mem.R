#!/usr/local/bin/Rscript

t <- "Speicherverbrauch für Datenstrukturen"
mem <- read.csv("/Users/judith/Documents/MA/src/src/mem.csv", sep=",")
attach(mem)
mem2 <- as.matrix(mem)
pdf('/Users/judith/Documents/MA/evaluation/mem.pdf')
barplot(mem2, ylab="Speicherverbrauch in Bytes", main="Speicherverbrauch für Datenstrukturen", col=c("darkolivegreen3", "dodgerblue3"), beside=TRUE, ylim=c(0,300000), names.arg=c("Filtergröße 256", "Filtergröße 512"))
detach(mem)