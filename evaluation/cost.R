#!/usr/local/bin/Rscript

t <- "Aufbaukosten für Datenstrukturen"
s <- "n=100"
sub <- list(s, col="black", cex=0.9)
cost <- read.csv("/Users/judith/Documents/MA/src/src/cost.csv", sep=",")
attach(cost)
cost2 <- as.numeric(cost[1,])
pdf('/Users/judith/Documents/MA/evaluation/cost.pdf')
barplot(cost2, ylab="Zeitkomplexität im schlechtesten Fall (O-Notation)", col=c("darkolivegreen3", "dodgerblue3"), beside=TRUE, ylim=c(0,500), names.arg=c("Unsortierte Liste", "BloomFilterTree"))
title(main=t, line=3)
title(sub)
detach(cost)
