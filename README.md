# Microarray-Analysis
Microarray Analysis, splitting data by pathways (as defined by KEGG), and using heatmaps of both individual genes and the group of genes in a pathway, statistical analyses such as post-hocs and 1-way ANOVAs to analyze the pathways in separate conditions to one another, and 3D plot function to help visualize data.

Code is split between Python (for the parsing and creation of pathways inside the microarrays and heatmap) and R (statistical analyses, heatmaps, and 3D plots). All documents from KEGG are .XML files. Documents have been parsed through with the Jupyter Notebook using Python, followed with statistical analysis in R.

UPDATE 1:

Used R for data analysis, used these files specifically.

ANOVA testing.R <- file that reads the initial dataset and then converts it into separate pathways. It then uses a 1-way ANOVA and posthocs to analyze each pathway alone, looking into how each separate condition affects the group dynamic. At the time, I did not figure out how to make it general, but I did not have a large volume of microarrays to analyze and it worked as fast as I needed it to. 

HeatMapOfPathways.R <- file that creates heatmaps of each pathway using its average expression according to the different conditions.

HeatMap_Of_Most_And_Least_Exp.R <- file that creates heatmaps of top 25 and bottom 25 most expressed genes. This can be changed to gather a longer list, however readability is sacrificed at large numbers of genes.

3DPlots.R <- file that creates 3D plots of genes.

UPDATE 0:
Have rewritten code partially for Python, have to use the following libraries:
pandas
numpy
xml.etree.cElementTree
csv
os.path
seaborn
matplotlib

The new python files are effectively Parsing_KEGG_HSA+KO.cpp, Cleaning_up_HSAEN_files.cpp, Microarray_Analysis.cpp, and HeatMapOfPathways.R inside the two files "Cleaning KEGG Data files" and "Split Microarray by Pathways, include Heatmap", which contain just the text, and "Cleaning KEGG Data files.ipynb" and "Split Microarray by Pathway [Also Include Heatmap].ipynb" as Jupyter Notebooks. The new files can read the original XML files from KEGG, so there is no need to transcribe every pathway file into a text file first.
