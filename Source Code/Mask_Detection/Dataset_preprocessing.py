"""
--------------------------------------------------------------------------------------------------------------------------------------------
@Author : Ibrahim Saber Mohamed 
@Date   : April 2022
@description : This is a python file holds the helper functions to work with the CNN-Face-Mask Detection Deep learning model
    this file contains several Function that helps to plot the model performane over number of epochs
    and plotting the model confusion matrix and the Model ROC curve and other functions are used to load the data and preprocess it to be 
    ready to be used in our model
---------------------------------------------------------------------------------------------------------------------------------------------
"""


import tensorflow as tf
import keras
from keras.preprocessing.image import load_img , img_to_array 
from keras.utils.np_utils import to_categorical
from sklearn.preprocessing import LabelBinarizer
from sklearn.metrics import auc , roc_curve
from sklearn.metrics import confusion_matrix , ConfusionMatrixDisplay
import os
import numpy as np
import cv2
import matplotlib.pyplot as plt


def Load_images(FilePath , Categories, Target_Size):
    '''
    @description : This Function load the data set and save it in two lists 
                  one for the images and one for the labels.
    @parameters 
        Filepath : the path of the Data set
        Categories : the list of classes name of the data (i.e folder name)
        Target_Size : a tuble of the target size (Height , Width)
    @return
        A List of Images and labels 
    '''
    Images = [] # List to save the images data
    Labels = [] # List to save the label of each image

    for category in Categories:
        '''
        for each folder in the dataset file path load the data (images)
        then turn the image into array and the save the image into the list 
        and save the label (the label is the folder name) 
        '''
        Path = os.path.join(FilePath , category ) # get the path of the folder inside the dataset
        for image in os.listdir(Path): # getting all images of that folder
            image_path = os.path.join(Path , image) # reading the path of the image
            image = load_img(path = image_path , 
                            color_mode='rgb' , 
                            target_size=Target_Size 
                            ) #loading the images and scale it into the target size
            image = img_to_array(image) # converting the images into array of numbers
            Images.append(image) # adding the image into the Images list
            Labels.append(category) #adding the coressponding image label to the labels list
    
    return Images , Labels


def Preprocess_Data(Images , Labels , Categories):
    '''
    @description : this Function is used to preprocessing the Images and labels
         1. Converting the categorical labels int one-hot-encodeing (binary data)
         2. Normalizing the images to be between 0 and one using Min-Max scaling
         3. converting the labels and images into batches 

    @parameters 
        Images : array of images 
        Categories : the list of classes name of the data.
        Labels : array of the labels.
    @return
        A Tensor of all of  the Images and labels 
    '''
    LB = LabelBinarizer()
    Labels = LB.fit_transform(Labels) # creating an object
    Labels = to_categorical(Labels , num_classes=len(Categories)) #performing one hot encoding 
    Labels = np.array(Labels) # converting the labels into a batch 
    Images = np.array(Images , dtype = 'float32') #converting images into a batch 
    Images = cv2.normalize(Images ,None, alpha=0, beta=1, norm_type=cv2.NORM_MINMAX, dtype=cv2.CV_32F) #Normalizing the image data
    return Images , Labels




def Plot_ROC(True_Labels , Predictions):
    '''
    @description:
    This Function is used to plot the ROC Curve.
    The Function Calculate the area under the Curve then plot.
    ------------
    @parameters:
        True_Labels : the true labels of (y_true)
        Predictions : The results of the model i.e y_preds (Predictions of the model)
         
    '''

    predict_labels = np.argmax(Predictions, axis=-1) # calculate the index of maximum probable class
    true_labels = np.argmax(True_Labels, axis=-1) # get the true class of the data  

    fpr, tpr, thresholds = roc_curve(true_labels, predict_labels, pos_label=1) 
    roc_auc = auc(fpr, tpr) # Calculate the area under the curve

    plt.style.use("ggplot") 
    plt.figure() #create a figure
    lw = 2 # Line width
    plt.plot(fpr, tpr, color='darkorange',
    lw=lw, label='ROC curve (area = %0.2f)' % roc_auc) #plotting the curve of the model

    plt.plot([0, 1], [0, 1], color='navy', lw=lw, linestyle='--') #Plotting a line of 50% Predictions
    plt.xlim([0.0, 1.0])
    plt.ylim([0.0, 1.05])
    plt.xlabel('False Positive Rate')
    plt.ylabel('True Positive Rate')
    plt.title('Receiver operating characteristic (ROC)')
    plt.legend(loc="lower right")
    plt.show()



def Plot_Confusion_Matrix(True_Labels , Predictions , Categories):
    '''
    @description:
        *This Function is ussed to Plot the Confusion matrix of the Model
        *Confusion-Matrix is a matrix that shows the true-Positive & true-negative , false-positive and false-negative of the model
        *describes the number of samples that are true calssified and false classified of each class
    ----------------------
    @parameters:
        True_Labels : The true labels of the sample input (y_true)
        Predictions : The predctions of the model (y_preds)
        Categories  : a list of the classes to distinguish between them
    ''' 
    true_labels = np.argmax(True_Labels , axis = -1)
    Predict_labels = np.argmax(Predictions , axis = -1)
    cnfm = confusion_matrix(true_labels, 
                            Predict_labels
                            )

    plt.style.use("classic")
    disp = ConfusionMatrixDisplay(confusion_matrix=cnfm, display_labels=Categories)
    disp.plot(cmap=plt.cm.Blues)
    plt.show()


def Plot_Model_History(Model_History , epochs):
    
    accuracy = Model_History.history['accuracy']
    Losses = Model_History.history['loss']

    validation_accuracy = Model_History.history['val_accuracy']
    validation_loss = Model_History.history['val_loss']

    plt.figure(figsize=(10 , 20))
    
    plt.subplot(1, 2 , 1)
    plt.plot(range(epochs) , Losses , label = 'training_losses')
    plt.plot(range(epochs) , validation_loss , label = 'validation_losess')
    plt.title("Loss Curve")
    plt.legend(loc = 'upper right')

    plt.subplot(1, 2 , 2)
    plt.plot(range(epochs) , accuracy , label = 'training_accuracy')
    plt.plot(range(epochs) , validation_accuracy , label = 'validation_accuracy')
    plt.title("acuuracy Curve")
    plt.legend(loc = 'lower right')

    plt.show()


def Plot_Image(index , Images , True_labels):
  img , True_Label = Images[index], True_labels[index]
  plt.grid(False)
  plt.xticks([])
  plt.yticks([])
    
  plt.imshow(img[... ,0])
  plt.xlabel("{}".format(True_Label),
             color='blue')