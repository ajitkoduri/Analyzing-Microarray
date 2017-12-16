library(readr)
library(ggplot2)
library(gplots)
library(pheatmap)
Data <- read_csv("~/STK38LProtRes.csv")
df <- data.frame(Data)
Names <- as.data.frame(Data[1])
rownames(df) <- Names[,1]
df <- df[,2:5]

df <- df[order(df[[4]]),]
df <-df[,1:3]
d <- head(df,25)
e <- tail(df,25)

d <- data.matrix(d)
e <- data.matrix(e)
tot <- rbind(e,d)
b <- c(0,0.1,0.2,0.5,1,1.5,2,10,85)
pheatmap(tot,main = "Heatmap of Gene Expression Ratios in STK38L Proteomics", 
         col = greenred(8), breaks = b, cex = 0.9)