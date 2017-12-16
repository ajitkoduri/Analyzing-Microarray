library(readr)
library(ggplot2)
library(gplots)
library(scatterplot3d)

Data <- read_csv("~/STK38LPhospho.csv")
df <- data.frame(Data)
rownames(df) <- Data[[1]]
df <- df[,2:5]
df <- df[order(df[[4]]),]
df<- df[,1:3]
df$pcolor[df$KO.WT.Chow >= 2] <- "red"
df$pcolor[df$KO.WT.Fast >= 2] <- "blue"
df$pcolor[df$KO.WT.Refed>= 2] <- "green"
df$pcolor[df$KO.WT.Chow <= 0.5] <- "gold"
df$pcolor[df$KO.WT.Fast <= 0.5] <- "magenta"
df$pcolor[df$KO.WT.Refed <= 0.5] <- "cyan"
#d <- head(df,5)
#e <- tail(df,25)
#f <- rbind(d,e)
f <- df
with(df, {a <- scatterplot3d(f,type = "h", lty.hplot = 2, scale.y = 2, box = F,
                             cex.lab = 1, angle = 45, pch = 19,
                             ylim = c(0,1), zlim = c(998.5,999.5), xlim = c(0,1),
                             sub = "(Expressed Only in KO Adlib)",
                             main = "Scatter Plot for STK38L Phosphoproteomics Gene Expression")
a.coords <- a$xyz.convert(f)
legend(x = 0, y = 0, lty = c(1,1), cex = 0.75, pch = 19, lwd= 2, yjust = 0, col = c("red","blue","green","magenta","cyan"), legend = c("KO > WT in Chow", "KO > WT in Fasting", "KO > WT in Refeeding","WT > KO in Fasting", "WT > KO in Refeeding"))
text(a.coords$x,a.coords$y, labels = row.names(f), pos = 4, cex = 0.55)
})
