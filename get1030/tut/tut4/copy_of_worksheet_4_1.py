#pip install -q git+https://github.com/gei1002/networkprocessing.git

#!wget -q https://github.com/gei1002/sampledata/raw/main/harrypotter.zip
#!unzip -q harrypotter.zip

import pandas as pd
import seaborn as sns
import networkprocessing as np

np.make_network("harrypotter")
#df = pd.read_excel("harrypotter_analysis/networkInfo.xlsx",index_col=0)
#df

#df2 = pd.read_excel("harrypotter_analysis/nodeInfo.xlsx",index_col=0)
#ax = sns.barplot(data=df2, x="network",y="degree") 
#df2.sort_values(by="closeness",ascending=True).head(1)
#older = df2["network"] == "older"
#ax = sns.histplot(data=df2.loc[older],x="degree")
