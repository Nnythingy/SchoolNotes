import pandas as pd
import os
import glob
from collections import Counter
from statsmodels.stats import inter_rater as irr
from pysentimiento import create_analyzer
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix
from sklearn.preprocessing import LabelEncoder

analyzer = create_analyzer(task="sentiment", lang="en")

def compare_raters(directory):
    """
    Combines and compares at least three xlsx files that have a 'sentence'
    column and a 'label' column. The values of the lable column must only be
    'neu', 'pos' or 'neg'.

    Parameters:
        directory (str): the directory where the files are located
    """
    files = sorted(glob.glob(f"{directory}/*.xlsx"))

    #check that there are at least three files
    if len(files) < 3:
        print("ERROR: There must be at least three files in the directory.")
        return None
    
    for number,fileitem in enumerate(files,1):
        print(f"Processing {fileitem}...")
        #temp_df = pd.read_excel(fileitem, index_col=0)
        temp_df = pd.read_excel(fileitem)

        #each file must have columns with "label" and "sentence"
        print(temp_df.columns.str.lower())
        if sorted(temp_df.columns.str.lower())!= ["label","sentence"]:
            print(f"ERROR in {fileitem}: The columns must be named 'label' and 'sentence', in small caps.")
            return None

        #values should only be pos, neg and neu
        if sorted(temp_df['label'].unique()) != ["neg","neu","pos"]:
            print(f"ERROR in {fileitem}: The 'label' column can only contain the values 'neg','neu'','pos' in smal caps.")
            return None

        if ("/") in fileitem:
            labeler_name = fileitem.split("/")[-1].replace(".xlsx","")
        elif ("\\") in fileitem:
            labeler_name = fileitem.split("\\")[-1].replace(".xlsx","")
        else:
            labeler_name = fileitem

        temp_df.rename(columns={'label': labeler_name}, inplace=True)
        if number == 1:
            df = temp_df
        else:
            temp_df = temp_df.drop('sentence', axis=1)
            df = pd.concat([df, temp_df], axis=1)      
    
    #for each line, find most common label
    no_agreement = 0
    for k,v in df.iterrows():
        most_common = Counter(v[1:]).most_common(1)
        if most_common[0][1] > 1:
            df.loc[k,"ground truth"] = Counter(v[1:]).most_common(1)[0][0]
        else:
            df.loc[k,"ground truth"] = "No agreement!"
            no_agreement+=1 
    
    if no_agreement > 0:
        print(f"No agreement was found for {no_agreement} observations. Please change this before calling the sentiment_analysis() fucntion.")

    #create output dir, and save the agreement file
    if not os.path.isdir(f"{directory}_output"): 
        os.mkdir(f"{directory}_output")
    df.to_excel(f"{directory}_output/agreement.xlsx")
    print(f"\nAgreement file saved at {directory}_output/agreement.xlsx")

    #to calculate Fleiss' Kappa, first we get the values from the labelers as an array
    values = df.iloc[:,1:-1].values
    
    #then we aggregate them in the format required by statsmodels and then calculate Kappa
    agg = irr.aggregate_raters(values)
    kappa = irr.fleiss_kappa(agg[0])
    print(f"Fliess Kappa is {kappa}")
    return None

class Analyzer:
    """
    A class to store the sentiment analysis outputs of 'pysentimiento', create a confusion matrix
    and explore the sentences in different quadrants of that matrix.
    ...

    Attributes
    ----------
    file_location : str
        the location of the file that contains the sentences and the 'ground truth'

    Methods
    -------
    confusion_matrix():
        displays a 3x3 confusion matrix using  seaborn

    examine_labels(actual,predicted):
        returns a dataframe with the sentences that match a specific actual/predicted pair
    """

    def __init__(self,file_location):
        #analyzer = create_analyzer(task="sentiment", lang="en")
        df = pd.read_excel(file_location,index_col=0)

        #make sure the columns are correctly named, and the ground truth has been established for each row
        if "sentence" not in df.columns:
            print("ERROR: One of the columns must be named 'sentence', in small caps.")
            return None

        if "ground truth" not in df.columns:
            print("ERROR: One of the columns must be named 'ground truth', in small caps.")
            return None

        if sorted(df['ground truth'].unique()) != ["neg","neu","pos"]:
            print("ERROR: The 'label' column can only contain the values 'neg','neu'','pos' in smal caps." +
                "\nIf 'no agreement' was found you need to resolve this through discussion or by bringing in a new labeler.")
            return None

        errors = 0
        for k,v in df.iterrows():
            label = analyzer.predict(v["sentence"]).output.lower()
            ground_truth = v["ground truth"]
            df.loc[k,"prediction"] = label
            if label != ground_truth:
                errors += 1
        
        #accuracy score
        accuracy =  100 - (errors*100/len(df))
        print(f"The accuracy score is {accuracy}")

        #sklearn treats the labels as numbers, but we still need to access the original names
        #so we create a copy here for the confusion matrix, and create a new LabelEncoder object
        df2 = df.copy()
        le = LabelEncoder()        
        df2['ground truth'] = le.fit_transform(df2['ground truth'])
        df2['prediction'] = le.transform(df2['prediction'])

        # Compute the confusion matrix and convert into a dataframe for the plot
        cm = confusion_matrix(df2['ground truth'], df2['prediction'])
        self.cm_df = pd.DataFrame(cm, index=le.classes_, columns=le.classes_)
        self.df = df

    def confusion_matrix(self):
        """plots the confusion matrix using seaborn"""
        plt.figure(figsize=(7,5))
        sns.heatmap(self.cm_df, annot=True, fmt='d',cmap='PuBuGn')
        plt.title('Confusion Matrix')
        plt.ylabel('Actual label')
        plt.xlabel('Predicted label')

    def examine_labels(self,actual="pos",predicted="pos"):
        """examines the labels give an actual/predicted pair; prints the number of matches
        and returns the matches as a df"""
        pd.set_option('display.max_colwidth', None)
        df = self.df
        results = df[(df['ground truth'] == actual) & (df['prediction'] == predicted)]
        print(len(results))
        return results

def sentiment_analysis(file_location):
    """give a file_location (an agreement.xlsx file), returns an Analyzer object"""
    return Analyzer(file_location)
