import textprocessing as tp
tp.compare_raters("coffee")
sa = tp.sentiment_analysis("coffee_output/agreement.xlsx")
sa.df.head()
sa.confusion_matrix()
sa.examine_labels(actual="neu", predicted="neg")
