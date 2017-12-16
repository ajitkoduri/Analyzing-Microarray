library(readr)
STK38LMicroResults <- read_csv("~/JMBSTKPhosphoProtRes.csv")
Data <- STK38LMicroResults
Data <- Data[order(Data$`Pathway Name`),]
LoP <- unique(Data[1],incomparables = F)

df <- data.frame(Data)
df <- split(df, df$Pathway.Name)


for (i in 1:nrow(LoP))
{
    rownames(df[[i]]) <- df[[i]]$Description
    df[[i]] <- df[[i]][,3:4]
    group = factor(rep(colnames(df[[i]]), each = nrow(df[[i]] )))
    a = df[[i]]$KO.WT.Fast
    b = df[[i]]$KO.WT.Refeed
    
    y = c(a,b)
    fit = lm(formula = y ~ group)
    A <- anova(fit)
    B <- fligner.test(df[[i]])
    if (A$'Pr(>F)'[1] <= 1 & B$p.value >= 0.05)
    {
      print(LoP[i,1])
      print(A$'Pr(>F)'[1])
      print(pairwise.t.test(y,group,p.adjust = "bonferroni"))
    }
}

