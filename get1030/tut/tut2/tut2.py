import pandas as pd
import seaborn as sns
import matplotlib

df = pd.read_excel("avengers.xlsx")
print(df.head(5))
print(df.describe())

boxplot = sns.boxplot(data=df, y="Years since joining", x="Death1")
histogram = sns.displot(data=df, x="Years since joining", binwidth=20)
barplot = sns.barplot(data=df, y="Appearances", x="Death1")
scatterplot = sns.scatterplot(data=df, x="Years since joining", y="Appearances")
lineplot = sns.lineplot(data=df, x="Year", y="Appearances")
violinplot = sns.violinplot(data=df, y="Appearances", x="Current?", cut=0)
