# Microarray-Analysis
Microarray Analysis, splitting data by pathways (as defined by KEGG), and using heatmaps of both individual genes and the group of genes in a pathway, statistical analyses such as post-hocs and 1-way ANOVAs to analyze the pathways in separate conditions to one another, and 3D plot function to visualize data.

Code is split between C++ (for the parsing and creation of pathways inside the microarrays) and R (statistical analyses, heatmaps, and 3D plots). All documents were initially downloa ed as .XML files but later converted to .txt files because parsing the data through there was significantly easier at the time.
UPDATE 5:
Have rewritten code partially for Python, have to use the following libraries:
pandas
numpy
xml.etree.cElementTree
csv
os.path
seaborn
matplotlib

The new python files are effectively Parsing_KEGG_HSA+KO.cpp, Cleaning_up_HSAEN_files.cpp, Microarray_Analysis.cpp, and HeatMapOfPathways.R inside the two files "Cleaning KEGG Data files" and "Split Microarray by Pathways, include Heatmap", which contain just the text, and "Cleaning KEGG Data files.ipynb" and "Split Microarray by Pathway [Also Include Heatmap].ipynb" as Jupyter Notebooks. The new files can read the original XML files from KEGG, so there is no need to transcribe every pathway file into a text file first.

The remaining files, Parsing Code.R, HeatMapGenExpand3DPlots.R, and 3DPlots.R have not been updated for Python.

UPDATE 4:
I was unsure if Pathways were important, however I think it is easier to just download some of the pathways I used as a test for microarrays that others use. If nothing else, it provides proof that at least 2 of the .cpp files work.

Pathways_HSA_X.txt files represent final files for all genes in Pathway according to KEGG.

UPDATE 3:

I started to use R to analyze the datasets once I finished separating them into pathways, as it would be much easier afterwards to run multiple analyses. To this end, I added a few files:

Parsing Code.R <- file that reads the initial dataset and then converts it into separate pathways. It then uses a 1-way ANOVA and posthocs to analyze each pathway alone, looking into how each separate condition affects the group dynamic. At the time, I did not figure out how to make it general, but I did not have a large volume of microarrays to analyze and it worked as fast as I needed it to. Additionally, I am unsure if ANOVA is the correct procedure: there is no real reason to believe that the genes in each group will be normally distributed.

HeatMapOfPathways.R <- file that creates heatmaps of each pathway using its average expression according to the different conditions.

HeatMapGenExpand3DPlots.R <- file that creates heatmaps of top 25 and bottom 25 most expressed genes. This can be changed to gather a longer list, however readability is sacrificed at large numbers of genes. DOES NOT MAKE 3D PLOTS.

3DPlots.R <- file that creates 3D plots of genes.

UPDATE 2:

As I worked in UTSW at the time, I realized I could parse through proteomics data while also not changing any of my code for the microarray. This came down to simply converting proteins into gene names which were already provided in the proteomics dataset luckily (though I could have used the "Gene_Bank.txt" to find matches between proteins in the KEGG bank and the proteins provided in the dataset).

ProteinCleaner.cpp is a file that returns the gene names specifically for the Proteomics Core dataset of UTSW: it can and should be modified for files that are not of the same format.

UPDATE 1:

Parsing_KEGG_HSA+KO.cpp is a file that reads all the genes from a HSA or KO file (this can be easily modified to be any species however, all it requires is to rename the corresponding files accordingly). This quickly gathers all the genes in a pathway with all the corresponding names for each gene (I chose to create an algorithm that picks all data rather than miss maybe vital ones) and puts them into Pathways_HSA_X.txt files.

Cleaning_up_HSAEN_files.cpp is a file that removes duplicates in each pathway by finding only the unique values in each pathway.

Microarray_Analysis.cpp is a file that creates a hash table for each unique gene in the microarray. It then utilizes those hash values to then create hash values for each gene in every pathway, and then compares the names of the gene in the pathway to all genes in the hash table till it finds a match (can be altered to also see duplicates in the microarray by simply searching through the linked list of the corresponding hash number for all values of the gene as opposed to the first one).

UPDATE 0:

linkedlist.h <- header file in C++ that creates the construct linkedlist. I used several versions of it in each program, but the data structure is the same, just that I changed the key variable from a string to an int or double or pair depending on the file. Probably could just be kept as string by converting all int, double, and pairs into string values.

Parsing_Enzyme_KEGG.cpp is a file that reads through the Enzyme Bank of KEGG and exports a file called "Gene Bank.txt" wherein each enzyme's name is attached in a linked list. As randomly separating each enzyme is equivalent of a linear search, the enzymes for each hash number are then uploaded in the corresponding line of the text file. So the enzyme with hash number = 1 will belong to line 1, hash number = 3 belongs to line 3, and so on.

Parsing_KEGG_Data.cpp is a file that reads through "Gene Bank.txt" and through a corresponding KEGG file that is uploaded as an enzyme file, parsing through it to find the name of the pathway in KEGG as well as all the enzyme numbers to then create an enzyme list that contains all the enzymes per pathway and places them into Pathways_X.txt files. HOWEVER, the KEGG Enzyme Bank list is extremely messy with many labels given to an enzyme that is not displayed; as such, I only initially used these two files and updated it afterwards.
