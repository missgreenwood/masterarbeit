#!/usr/local/bin/Rscript

lablist <- as.vector(0:9)
t <- "Komplexität der k-nächsten-Nachbarn-Suche"
s256 <- "k=1, Filtergröße 256"
sub256 <- list(s256, col="black", cex=0.9)
s512 <- "k=1, Filtergröße 512"
sub512 <- list(s512, col="black", cex=0.9)
compl <- read.csv("/Users/judith/Documents/MA/src/src/complexity.csv", sep=",")
attach(compl)

compl2 <- as.numeric(compl[1,])

pdf('/Users/judith/Documents/MA/evaluation/compl.pdf')

barplot(compl2, ylab="Anzahl Vergleiche", main="Komplexität der k-nächsten-Nachbarn-Suche", col=c("dodgerblue3", "darkolivegreen3"), beside=TRUE, ylim=c(0,650), names.arg=c("Filtergröße 256\nk=1", "Filtergröße 256\nk=1", "Filtergröße 256\nk=3", "Filtergröße 256\nk=3", "Filtergröße 512\nk=1", "Filtergröße 512\nk=1", "Filtergröße 512\nk=3", "Filtergröße 512\nk=3"), cex.axis=0.8, cex.names=0.8)

detach(compl)
