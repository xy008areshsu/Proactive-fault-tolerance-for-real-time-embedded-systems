import numpy as np
import pandas as pd
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score
import matplotlib.pyplot as plt
from class_vis import prettyPicture

training_s1 = pd.read_csv('training_s1.csv', sep = ',', header = None)
training_s2 = pd.read_csv('training_s2.csv', sep = ',', header = None)
training_s3 = pd.read_csv('training_s3.csv', sep = ',', header = None)

training_s1 = training_s1.values
training_s2 = training_s2.values
training_s3 = training_s3.values

test_s1 = pd.read_csv('test_s1.csv', sep = ',', header = None)
test_s2 = pd.read_csv('test_s2.csv', sep = ',', header = None)
test_s3 = pd.read_csv('test_s3.csv', sep = ',', header = None)

test_s1 = test_s1.values
test_s2 = test_s2.values
test_s3 = test_s3.values

training = np.vstack((training_s1, training_s2, training_s3))
labels = np.hstack(( np.ones(( 1,  len(training_s1) )), 2 * np.ones(( 1, len(training_s2) )), 3 * np.ones(( 1, len(training_s3) )) ))
labels = labels[0]

test = np.vstack((test_s1, test_s2, test_s3))
test_labels = np.hstack(( np.ones(( 1,  len(test_s1) )), 2 * np.ones(( 1, len(test_s2) )), 3 * np.ones(( 1, len(test_s3) )) ))
test_labels = test_labels[0]

clf = SVC(C = 10000, kernel = "rbf")
clf.fit(training, labels)
pred = clf.predict(training)

acc = accuracy_score(pred, labels)
print(acc)

