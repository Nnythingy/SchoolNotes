import textprocessing as tp

tp.compare_raters(".")
sa = tp.sentiment_analysis(coffee.xlsx)
sa.df.head()
sa.confusion_matrix()
sa.examine_labels(actual='neu', predicted='neg')
