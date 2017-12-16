library(readr)
library(ggplot2)
library(gplots)
library(pheatmap)
STK38LMicroResults <- read_csv("~/Microarray.csv")
Data <- STK38LMicroResults
LoP <- unique(Data[1],incomparables = F)

df <- data.frame(Data)
Names <- as.data.frame(Data[1])
rownames(df) <- Names[,1]
df <- split(df, df$Pathway.Name)

Total <- matrix(nrow = nrow(LoP), ncol = 3)

for (i in 1:nrow(LoP))
{
  #find number of genes in each pathway
  
  pop <- nrow(df[[i]])
  LoP[[i,1]]<- paste(LoP[[i,1]],pop, collapse = "--")
  #find average value of each variable for each pathway
  b <- mean(df[[i]]$KO.WT.Adlib)
  c <- mean(df[[i]]$KO.WT.FASTING)
  e <- mean(df[[i]]$KO.WT.REFEDING)
  #combine averages onto separate data matrix and create heatmap
  d <- c(e,b,c)
  Total[i,] <- d
  print(stderr(e))
  print(stderr(b))
  print(stderr(c))
}

d <- data.matrix(Total)
Data <- Data[,3:5]
colnames(d) <- colnames(Data)
rownames(d) <- LoP[[1]]
pheatmap(d, main = "Heatmap of Pathways in STK38L Proteomics",
          margins = c(10,10), col = greenred(256), cex = 0.9)