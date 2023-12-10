import spacy
from spacy.matcher import Matcher

nlp = spacy.load("en_core_web_lg")

with open("Midterm Essay.txt", encoding="utf8") as f:
    text = f.read()

doc = nlp(text)
count_noun = 0
count_verb = 0
for token in doc:
    if token.pos_ == "NOUN":
        count_noun += 1
    if token.pos_ == "VERB":
        count_verb += 1

print("Noun per Verb:", count_noun/count_verb)
